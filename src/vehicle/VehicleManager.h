#pragma once

#include "Vehicle.h"

#include <QtCore/QObject>
#include <QtCore/QTimer>

namespace mini::vehicle {

/// Tracks 0..N vehicles by sysid. M4 policy: first-seen single vehicle only.
/// activeVehicle may be null (P2). Owned by Application (P6).
class VehicleManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(mini::vehicle::Vehicle *activeVehicle READ activeVehicle NOTIFY activeVehicleChanged)
    Q_PROPERTY(bool hasVehicle READ hasVehicle NOTIFY activeVehicleChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY activeVehicleChanged)
    Q_PROPERTY(int heartbeatTimeoutMs READ heartbeatTimeoutMs WRITE setHeartbeatTimeoutMs NOTIFY
                   heartbeatTimeoutMsChanged)

public:
    /// Default: drop vehicle after 5s without HEARTBEAT.
    static constexpr int kDefaultHeartbeatTimeoutMs = 5000;

    explicit VehicleManager(QObject *parent = nullptr);
    ~VehicleManager() override;

    [[nodiscard]] Vehicle *activeVehicle() const { return _activeVehicle; }
    [[nodiscard]] bool hasVehicle() const { return _activeVehicle != nullptr; }
    [[nodiscard]] QString statusText() const;

    [[nodiscard]] int heartbeatTimeoutMs() const { return _heartbeatTimeoutMs; }
    void setHeartbeatTimeoutMs(int ms);

    /// From MavlinkParser::heartbeatReceived. First sysid wins until cleared.
    Q_INVOKABLE void handleHeartbeat(int sysid, int compid, int type, int autopilot, int baseMode,
                                     quint32 customMode, int systemStatus);

    /// Forget active vehicle (link stop / manual reset).
    Q_INVOKABLE void clear();

signals:
    void activeVehicleChanged();
    void heartbeatTimeoutMsChanged();

private:
    void _checkTimeout();
    void _setActiveVehicle(Vehicle *vehicle);

    Vehicle *_activeVehicle = nullptr;
    int _heartbeatTimeoutMs = kDefaultHeartbeatTimeoutMs;
    QTimer _timeoutTimer;
};

} // namespace mini::vehicle
