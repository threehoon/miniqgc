#pragma once

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace mini::mavlink {

/// Stream MAVLink parser (M3). Bytes in → structured messages out.
/// Does not own sockets (comms) and does not create Vehicle (M4).
/// Owned by Application (P6); QML binds properties only (P4).
class MavlinkParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int messagesParsed READ messagesParsed NOTIFY statsChanged)
    Q_PROPERTY(int heartbeatsParsed READ heartbeatsParsed NOTIFY statsChanged)
    Q_PROPERTY(int parseErrors READ parseErrors NOTIFY statsChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QStringList logLines READ logLines NOTIFY logLinesChanged)
    Q_PROPERTY(int lastSysId READ lastSysId NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(int lastCompId READ lastCompId NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(int lastType READ lastType NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(int lastAutopilot READ lastAutopilot NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(int lastBaseMode READ lastBaseMode NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(quint32 lastCustomMode READ lastCustomMode NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(int lastSystemStatus READ lastSystemStatus NOTIFY lastHeartbeatChanged)
    Q_PROPERTY(bool hasHeartbeat READ hasHeartbeat NOTIFY lastHeartbeatChanged)

public:
    explicit MavlinkParser(QObject *parent = nullptr);
    ~MavlinkParser() override;

    [[nodiscard]] int messagesParsed() const { return _messagesParsed; }
    [[nodiscard]] int heartbeatsParsed() const { return _heartbeatsParsed; }
    [[nodiscard]] int parseErrors() const { return _parseErrors; }
    [[nodiscard]] QString lastError() const { return _lastError; }
    [[nodiscard]] QStringList logLines() const { return _logLines; }

    [[nodiscard]] int lastSysId() const { return _lastSysId; }
    [[nodiscard]] int lastCompId() const { return _lastCompId; }
    [[nodiscard]] int lastType() const { return _lastType; }
    [[nodiscard]] int lastAutopilot() const { return _lastAutopilot; }
    [[nodiscard]] int lastBaseMode() const { return _lastBaseMode; }
    [[nodiscard]] quint32 lastCustomMode() const { return _lastCustomMode; }
    [[nodiscard]] int lastSystemStatus() const { return _lastSystemStatus; }
    [[nodiscard]] bool hasHeartbeat() const { return _hasHeartbeat; }

    /// Push raw link bytes (UDP datagram, serial chunk, …). Safe from any thread
    /// that already owns this QObject affinity (M3: main thread via signal).
    Q_INVOKABLE void feed(const QByteArray &bytes);

    Q_INVOKABLE void clearLog();
    Q_INVOKABLE void reset();

signals:
    void statsChanged();
    void lastErrorChanged();
    void logLinesChanged();
    void lastHeartbeatChanged();

    /// Semantic heartbeat for M4 Vehicle wiring (fields mirror mavlink_heartbeat_t + ids).
    void heartbeatReceived(int sysid, int compid, int type, int autopilot, int baseMode,
                           quint32 customMode, int systemStatus);

private:
    void _onHeartbeat(int sysid, int compid, int type, int autopilot, int baseMode, quint32 customMode,
                      int systemStatus);
    void _setLastError(const QString &message);
    void _appendLog(const QString &line);

    static constexpr int kMaxLogLines = 100;
    /// Single channel for Mini M3 (one active link). Matches mavlink COMM_0.
    static constexpr uint8_t kChannel = 0;

    // Keep parse status opaque in the header so QML consumers do not see C API.
    struct ParseState;
    ParseState *_state = nullptr;

    int _messagesParsed = 0;
    int _heartbeatsParsed = 0;
    int _parseErrors = 0;
    QString _lastError;
    QStringList _logLines;

    bool _hasHeartbeat = false;
    int _lastSysId = 0;
    int _lastCompId = 0;
    int _lastType = 0;
    int _lastAutopilot = 0;
    int _lastBaseMode = 0;
    quint32 _lastCustomMode = 0;
    int _lastSystemStatus = 0;
};

} // namespace mini::mavlink
