#include "UdpLink.h"

#include "Logging.h"

#include <QtCore/QDateTime>
#include <QtNetwork/QNetworkDatagram>

Q_LOGGING_CATEGORY(MiniCommsLog, "mini.comms")

namespace mini::comms {

UdpLink::UdpLink(QObject *parent)
    : QObject(parent)
{
}

UdpLink::~UdpLink()
{
    stop();
}

void UdpLink::setLocalPort(int port)
{
    if (port <= 0 || port > 65535) {
        _setLastError(QStringLiteral("Invalid port: %1").arg(port));
        return;
    }
    if (_localPort == port) {
        return;
    }
    if (_running) {
        _setLastError(QStringLiteral("Stop the link before changing port"));
        return;
    }
    _localPort = port;
    emit localPortChanged();
}

QString UdpLink::statusText() const
{
    if (_running) {
        return QStringLiteral("Listening UDP :%1").arg(_localPort);
    }
    return QStringLiteral("Stopped");
}

bool UdpLink::start()
{
    if (_running) {
        return true;
    }

    _socket = std::make_unique<QUdpSocket>(this);
    if (!_socket->bind(QHostAddress::AnyIPv4, static_cast<quint16>(_localPort),
                       QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        _setLastError(QStringLiteral("Bind failed on port %1: %2")
                          .arg(_localPort)
                          .arg(_socket->errorString()));
        qCWarning(MiniCommsLog) << _lastError;
        _socket.reset();
        return false;
    }

    connect(_socket.get(), &QUdpSocket::readyRead, this, &UdpLink::_onReadyRead);

    _running = true;
    _setLastError(QString());
    _appendLog(QStringLiteral("Started listening on UDP port %1").arg(_localPort));
    qCInfo(MiniCommsLog) << "UDP listening on" << _localPort;
    emit runningChanged();
    return true;
}

void UdpLink::stop()
{
    if (!_socket && !_running) {
        return;
    }

    if (_socket) {
        _socket->disconnect(this);
        _socket->close();
        _socket.reset();
    }

    if (_running) {
        _running = false;
        _appendLog(QStringLiteral("Stopped"));
        qCInfo(MiniCommsLog) << "UDP stopped";
        emit runningChanged();
    }
}

void UdpLink::clearLog()
{
    if (_logLines.isEmpty()) {
        return;
    }
    _logLines.clear();
    emit logLinesChanged();
}

void UdpLink::_onReadyRead()
{
    if (!_socket) {
        return;
    }

    while (_socket->hasPendingDatagrams()) {
        const QNetworkDatagram datagram = _socket->receiveDatagram();
        const QByteArray data = datagram.data();
        const QString host = datagram.senderAddress().toString();
        const quint16 port = datagram.senderPort();

        ++_packetsReceived;
        _bytesReceived += static_cast<int>(data.size());

        const QString preview = QString::fromLatin1(data.left(16).toHex(' '));
        _appendLog(QStringLiteral("RX %1:%2  %3 B  %4%5")
                       .arg(host)
                       .arg(port)
                       .arg(data.size())
                       .arg(preview)
                       .arg(data.size() > 16 ? QStringLiteral(" …") : QString()));

        emit statsChanged();
        emit datagramReceived(data, host, port);
    }
}

void UdpLink::_setLastError(const QString &message)
{
    if (_lastError == message) {
        return;
    }
    _lastError = message;
    emit lastErrorChanged();
}

void UdpLink::_appendLog(const QString &line)
{
    const QString stamped =
        QStringLiteral("[%1] %2").arg(QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss")), line);
    _logLines.append(stamped);
    while (_logLines.size() > kMaxLogLines) {
        _logLines.removeFirst();
    }
    emit logLinesChanged();
}

} // namespace mini::comms
