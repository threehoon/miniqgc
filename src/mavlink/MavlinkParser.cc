#include "MavlinkParser.h"

#include "Logging.h"
#include "MavlinkLib.h"

#include <QtCore/QDateTime>

#include <cstring>

Q_LOGGING_CATEGORY(MiniMavlinkLog, "mini.mavlink")

namespace mini::mavlink {

struct MavlinkParser::ParseState
{
    mavlink_status_t status {};
    mavlink_message_t message {};
};

MavlinkParser::MavlinkParser(QObject *parent)
    : QObject(parent)
    , _state(new ParseState)
{
    std::memset(&_state->status, 0, sizeof(_state->status));
    std::memset(&_state->message, 0, sizeof(_state->message));
}

MavlinkParser::~MavlinkParser()
{
    delete _state;
    _state = nullptr;
}

void MavlinkParser::feed(const QByteArray &bytes)
{
    if (!_state || bytes.isEmpty()) {
        return;
    }

    bool statsDirty = false;

    for (const char ch : bytes) {
        const auto byte = static_cast<uint8_t>(static_cast<unsigned char>(ch));
        if (mavlink_parse_char(kChannel, byte, &_state->message, &_state->status) != MAVLINK_FRAMING_OK) {
            continue;
        }

        ++_messagesParsed;
        statsDirty = true;

        const mavlink_message_t &message = _state->message;

        // M3: decode HEARTBEAT only; other message ids still count as framed messages.
        if (message.msgid != MAVLINK_MSG_ID_HEARTBEAT) {
            qCDebug(MiniMavlinkLog) << "msg id" << message.msgid << "sys" << message.sysid << "comp"
                                    << message.compid;
            continue;
        }

        mavlink_heartbeat_t heartbeat {};
        mavlink_msg_heartbeat_decode(&message, &heartbeat);
        _onHeartbeat(message.sysid, message.compid, heartbeat.type, heartbeat.autopilot, heartbeat.base_mode,
                     heartbeat.custom_mode, heartbeat.system_status);
    }

    if (statsDirty) {
        emit statsChanged();
    }
}

void MavlinkParser::_onHeartbeat(int sysid, int compid, int type, int autopilot, int baseMode,
                                 quint32 customMode, int systemStatus)
{
    _hasHeartbeat = true;
    _lastSysId = sysid;
    _lastCompId = compid;
    _lastType = type;
    _lastAutopilot = autopilot;
    _lastBaseMode = baseMode;
    _lastCustomMode = customMode;
    _lastSystemStatus = systemStatus;
    ++_heartbeatsParsed;

    const QString line = QStringLiteral(
                             "HB sys=%1 comp=%2 type=%3 autopilot=%4 base_mode=0x%5 custom_mode=%6 status=%7")
                             .arg(sysid)
                             .arg(compid)
                             .arg(type)
                             .arg(autopilot)
                             .arg(baseMode, 2, 16, QLatin1Char('0'))
                             .arg(customMode)
                             .arg(systemStatus);

    _appendLog(line);
    _setLastError(QString());

    qCInfo(MiniMavlinkLog) << line;

    emit lastHeartbeatChanged();
    emit heartbeatReceived(sysid, compid, type, autopilot, baseMode, customMode, systemStatus);
}

void MavlinkParser::clearLog()
{
    if (_logLines.isEmpty()) {
        return;
    }
    _logLines.clear();
    emit logLinesChanged();
}

void MavlinkParser::reset()
{
    if (_state) {
        std::memset(&_state->status, 0, sizeof(_state->status));
        std::memset(&_state->message, 0, sizeof(_state->message));
    }

    _messagesParsed = 0;
    _heartbeatsParsed = 0;
    _parseErrors = 0;
    _hasHeartbeat = false;
    _lastSysId = 0;
    _lastCompId = 0;
    _lastType = 0;
    _lastAutopilot = 0;
    _lastBaseMode = 0;
    _lastCustomMode = 0;
    _lastSystemStatus = 0;
    _logLines.clear();
    _setLastError(QString());

    emit statsChanged();
    emit lastHeartbeatChanged();
    emit logLinesChanged();
}

void MavlinkParser::_setLastError(const QString &message)
{
    if (_lastError == message) {
        return;
    }
    _lastError = message;
    emit lastErrorChanged();
}

void MavlinkParser::_appendLog(const QString &line)
{
    const QString stamped =
        QStringLiteral("[%1] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss")), line);
    _logLines.append(stamped);
    while (_logLines.size() > kMaxLogLines) {
        _logLines.removeFirst();
    }
    emit logLinesChanged();
}

} // namespace mini::mavlink
