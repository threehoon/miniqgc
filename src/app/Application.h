#pragma once

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <memory>

namespace mini::app {

/// Composition root / coordinator (Architecture Pattern P6).
/// Owns application lifecycle and (later) wires domain modules.
class Application : public QGuiApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    ~Application() override;

    /// Load root QML and prepare the shell UI. @return false on fatal failure.
    [[nodiscard]] bool init();

    void shutdown();

private:
    [[nodiscard]] bool _loadRootQml();

    std::unique_ptr<QQmlApplicationEngine> _engine;
};

} // namespace mini::app
