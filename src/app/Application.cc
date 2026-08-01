#include "Application.h"

#include "Logging.h"

#include <QtCore/QUrl>

namespace mini::app {

Application::Application(int &argc, char **argv)
    : QGuiApplication(argc, argv)
{
    setApplicationName(QStringLiteral("MiniQGC"));
    setOrganizationName(QStringLiteral("MiniQGC"));
    setApplicationVersion(QStringLiteral("0.1.0"));
}

Application::~Application() = default;

bool Application::init()
{
    qCDebug(MiniAppLog) << "init: starting composition root";

    if (!_loadRootQml()) {
        qCCritical(MiniAppLog) << "init: failed to load root QML";
        return false;
    }

    qCDebug(MiniAppLog) << "init: root UI ready";
    return true;
}

void Application::shutdown()
{
    qCDebug(MiniAppLog) << "shutdown";
    if (_engine) {
        _engine.reset();
    }
}

bool Application::_loadRootQml()
{
    _engine = std::make_unique<QQmlApplicationEngine>();

    QObject::connect(
        _engine.get(),
        &QQmlApplicationEngine::objectCreationFailed,
        this,
        []() {
            qCCritical(MiniAppLog) << "QML object creation failed";
            QCoreApplication::exit(EXIT_FAILURE);
        },
        Qt::QueuedConnection);

    // Module registered by qt_add_qml_module(URI MiniQGC) on the executable target.
    _engine->loadFromModule(u"MiniQGC", u"Main");

    if (_engine->rootObjects().isEmpty()) {
        qCCritical(MiniAppLog) << "No QML root objects after loadFromModule(MiniQGC, Main)";
        return false;
    }

    return true;
}

} // namespace mini::app
