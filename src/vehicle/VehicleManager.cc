#include "VehicleManager.h"

#include "Logging.h"
#include "Vehicle.h"

#include <QtCore/QDateTime>

namespace mini::vehicle {

VehicleManager::VehicleManager(QObject *parent)
    : QObject(parent)
{
    _timeoutTimer.setInterval(500);
    connect(&_timeoutTimer, &QTimer::timeout, this, &VehicleManager::_checkTimeout);
    _timeoutTimer.start();
}

VehicleManager::~VehicleManager()
{
    clear();
}

QString VehicleManager::statusText() const
{
    if (!_activeVehicle) {
        return QStringLiteral("No vehicle");
    }
    return QStringLiteral("Vehicle %1").arg(_activeVehicle->summaryText());
}

void VehicleManager::setHeartbeatTimeoutMs(int ms)
{
    if (ms < 1000) {
        ms = 1000;
    }
    if (_heartbeatTimeoutMs == ms) {
        return;
    }
    _heartbeatTimeoutMs = ms;
    emit heartbeatTimeoutMsChanged();
}

void VehicleManager::handleHeartbeat(int sysid, int compid, int type, int autopilot, int baseMode,
                                     quint32 customMode, int systemStatus)
{
    if (sysid <= 0 || sysid > 255) {
        qCWarning(MiniVehicleLog) << "ignore heartbeat with invalid sysid" << sysid;
        return;
    }

    // M4 first-seen policy: one vehicle; other sysids ignored until cleared.
    if (_activeVehicle && _activeVehicle->sysId() != sysid) {
        qCDebug(MiniVehicleLog) << "ignore heartbeat for other sysid" << sysid << "(tracking"
                                << _activeVehicle->sysId() << ")";
        return;
    }

    if (!_activeVehicle) {
        auto *vehicle = new Vehicle(sysid, this);
        vehicle->applyHeartbeat(compid, type, autopilot, baseMode, customMode, systemStatus);
        qCInfo(MiniVehicleLog) << "vehicle created" << vehicle->summaryText();
        _setActiveVehicle(vehicle);
        return;
    }

    _activeVehicle->applyHeartbeat(compid, type, autopilot, baseMode, customMode, systemStatus);
}

void VehicleManager::clear()
{
    if (!_activeVehicle) {
        return;
    }
    qCInfo(MiniVehicleLog) << "vehicle cleared sysid" << _activeVehicle->sysId();
    _activeVehicle->deleteLater();
    _setActiveVehicle(nullptr);
}

void VehicleManager::_checkTimeout()
{
    if (!_activeVehicle) {
        return;
    }

    const qint64 ageMs = _activeVehicle->lastHeartbeatUtc().msecsTo(QDateTime::currentDateTimeUtc());
    if (ageMs >= _heartbeatTimeoutMs) {
        qCInfo(MiniVehicleLog) << "vehicle timeout sysid" << _activeVehicle->sysId() << "ageMs" << ageMs;
        clear();
    }
}

void VehicleManager::_setActiveVehicle(Vehicle *vehicle)
{
    if (_activeVehicle == vehicle) {
        return;
    }
    _activeVehicle = vehicle;
    emit activeVehicleChanged();
}

} // namespace mini::vehicle
