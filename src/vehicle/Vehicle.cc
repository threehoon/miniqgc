#include "Vehicle.h"

#include "Logging.h"

#include <QtCore/QDateTime>

Q_LOGGING_CATEGORY(MiniVehicleLog, "mini.vehicle")

namespace mini::vehicle {

Vehicle::Vehicle(int sysId, QObject *parent)
    : QObject(parent)
    , _sysId(sysId)
{
    _lastHeartbeatUtc = QDateTime::currentDateTimeUtc();
}

QString Vehicle::summaryText() const
{
    return QStringLiteral("sys=%1 type=%2 ap=%3 status=%4")
        .arg(_sysId)
        .arg(_vehicleType)
        .arg(_autopilotType)
        .arg(_systemStatus);
}

void Vehicle::applyHeartbeat(int compId, int vehicleType, int autopilotType, int baseMode, quint32 customMode,
                             int systemStatus)
{
    _compId = compId;
    _vehicleType = vehicleType;
    _autopilotType = autopilotType;
    _baseMode = baseMode;
    _customMode = customMode;
    _systemStatus = systemStatus;
    _lastHeartbeatUtc = QDateTime::currentDateTimeUtc();

    if (!_online) {
        _online = true;
        emit onlineChanged();
    }

    emit heartbeatInfoChanged();
}

void Vehicle::setOnline(bool online)
{
    if (_online == online) {
        return;
    }
    _online = online;
    emit onlineChanged();
}

} // namespace mini::vehicle
