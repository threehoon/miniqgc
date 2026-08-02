#include "Application.h"

#include "Logging.h"
#include "UdpLink.h"

#include <QtQml/QQmlContext>

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

    // P6: create domain services here, not in QML.
    _udpLink = std::make_unique<mini::comms::UdpLink>();

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
    if (_udpLink) {
        _udpLink->stop();
    }
    if (_engine) {
        _engine.reset();
    }
    _udpLink.reset();
}

bool Application::_loadRootQml()
{
    _engine = std::make_unique<QQmlApplicationEngine>();

    // Expose link before load so Main.qml bindings resolve (P4: bind, don't own socket).
    _engine->rootContext()->setContextProperty(QStringLiteral("udpLink"), _udpLink.get());

    QObject::connect(
        _engine.get(),
        &QQmlApplicationEngine::objectCreationFailed,
        this,
        []() {
            qCCritical(MiniAppLog) << "QML object creation failed";
            QCoreApplication::exit(EXIT_FAILURE);
        },
        Qt::QueuedConnection);

    _engine->loadFromModule(u"MiniQGC", u"Main");

    if (_engine->rootObjects().isEmpty()) {
        qCCritical(MiniAppLog) << "No QML root objects after loadFromModule(MiniQGC, Main)";
        return false;
    }

    return true;
}

} // namespace mini::app
