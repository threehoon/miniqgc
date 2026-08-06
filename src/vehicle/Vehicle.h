#pragma once

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QString>

namespace mini::vehicle {

/// One tracked aircraft (M4). Identity = MAVLink sysid.
/// Does not own sockets or parse bytes (P5). Created by VehicleManager.
class Vehicle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int sysId READ sysId CONSTANT)
    Q_PROPERTY(int compId READ compId NOTIFY heartbeatInfoChanged)
    Q_PROPERTY(int vehicleType READ vehicleType NOTIFY heartbeatInfoChanged)
    Q_PROPERTY(int autopilotType READ autopilotType NOTIFY heartbeatInfoChanged)
    Q_PROPERTY(int baseMode READ baseMode NOTIFY heartbeatInfoChanged)
    Q_PROPERTY(quint32 customMode READ customMode NOTIFY heartbeatInfoChanged)
    Q_PROPERTY(int systemStatus READ systemStatus NOTIFY heartbeatInfoChanged)
    Q_PROPERTY(bool online READ online NOTIFY onlineChanged)
    Q_PROPERTY(QString summaryText READ summaryText NOTIFY heartbeatInfoChanged)

public:
    explicit Vehicle(int sysId, QObject *parent = nullptr);

    [[nodiscard]] int sysId() const { return _sysId; }
    [[nodiscard]] int compId() const { return _compId; }
    [[nodiscard]] int vehicleType() const { return _vehicleType; }
    [[nodiscard]] int autopilotType() const { return _autopilotType; }
    [[nodiscard]] int baseMode() const { return _baseMode; }
    [[nodiscard]] quint32 customMode() const { return _customMode; }
    [[nodiscard]] int systemStatus() const { return _systemStatus; }
    [[nodiscard]] bool online() const { return _online; }
    [[nodiscard]] QString summaryText() const;

    [[nodiscard]] QDateTime lastHeartbeatUtc() const { return _lastHeartbeatUtc; }

    void applyHeartbeat(int compId, int vehicleType, int autopilotType, int baseMode, quint32 customMode,
                        int systemStatus);
    void setOnline(bool online);

signals:
    void heartbeatInfoChanged();
    void onlineChanged();

private:
    const int _sysId;
    int _compId = 0;
    int _vehicleType = 0;
    int _autopilotType = 0;
    int _baseMode = 0;
    quint32 _customMode = 0;
    int _systemStatus = 0;
    bool _online = true;
    QDateTime _lastHeartbeatUtc;
};

} // namespace mini::vehicle
