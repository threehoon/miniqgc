#pragma once

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <memory>

namespace mini::comms {
class UdpLink;
}

namespace mini::app {

/// Composition root / coordinator (Architecture Pattern P6).
/// Owns application lifecycle and wires domain modules for QML.
class Application : public QGuiApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application() override;

    /// Create services, expose to QML, load root UI. @return false on fatal failure.
    [[nodiscard]] bool init();

    void shutdown();

    [[nodiscard]] mini::comms::UdpLink *udpLink() const { return _udpLink.get(); }

private:
    [[nodiscard]] bool _loadRootQml();

    std::unique_ptr<QQmlApplicationEngine> _engine;
    std::unique_ptr<mini::comms::UdpLink> _udpLink;
};

} // namespace mini::app
