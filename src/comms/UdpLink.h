#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QUdpSocket>

#include <memory>

namespace mini::comms {

/// UDP link for raw byte IO (M2). No MAVLink parse (that is M3).
/// Owned by Application (P6); exposed to QML as context property `udpLink` (P4: UI binds only).
class UdpLink : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(int localPort READ localPort WRITE setLocalPort NOTIFY localPortChanged)
    Q_PROPERTY(int packetsReceived READ packetsReceived NOTIFY statsChanged)
    Q_PROPERTY(int bytesReceived READ bytesReceived NOTIFY statsChanged)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)
    Q_PROPERTY(QStringList logLines READ logLines NOTIFY logLinesChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY runningChanged)

public:
    explicit UdpLink(QObject *parent = nullptr);
    ~UdpLink() override;

    [[nodiscard]] bool running() const { return _running; }
    [[nodiscard]] int localPort() const { return _localPort; }
    void setLocalPort(int port);

    [[nodiscard]] int packetsReceived() const { return _packetsReceived; }
    [[nodiscard]] int bytesReceived() const { return _bytesReceived; }
    [[nodiscard]] QString lastError() const { return _lastError; }
    [[nodiscard]] QStringList logLines() const { return _logLines; }
    [[nodiscard]] QString statusText() const;

    Q_INVOKABLE [[nodiscard]] bool start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void clearLog();

signals:
    void runningChanged();
    void localPortChanged();
    void statsChanged();
    void lastErrorChanged();
    void logLinesChanged();
    /// Raw datagram for future mavlink module (M3).
    void datagramReceived(const QByteArray &data, const QString &senderHost, quint16 senderPort);

private:
    void _onReadyRead();
    void _setLastError(const QString &message);
    void _appendLog(const QString &line);

    static constexpr int kMaxLogLines = 100;

    std::unique_ptr<QUdpSocket> _socket;
    bool _running = false;
    int _localPort = 14550;
    int _packetsReceived = 0;
    int _bytesReceived = 0;
    QString _lastError;
    QStringList _logLines;
};

} // namespace mini::comms
