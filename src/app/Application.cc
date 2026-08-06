#include "Application.h"

#include "Logging.h"
#include "MavlinkParser.h"
#include "UdpLink.h"
#include "VehicleManager.h"

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
    _mavlinkParser = std::make_unique<mini::mavlink::MavlinkParser>();
    _vehicleManager = std::make_unique<mini::vehicle::VehicleManager>();
    _wireModules();

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
    if (_vehicleManager) {
        _vehicleManager->clear();
    }
    if (_engine) {
        _engine.reset();
    }
    _vehicleManager.reset();
    _mavlinkParser.reset();
    _udpLink.reset();
}

void Application::_wireModules()
{
    // Link → Parser (bytes)
    QObject::connect(_udpLink.get(), &mini::comms::UdpLink::datagramReceived, _mavlinkParser.get(),
                     [this](const QByteArray &data, const QString & /*host*/, quint16 /*port*/) {
                         if (_mavlinkParser) {
                             _mavlinkParser->feed(data);
                         }
                     });

    // Parser → VehicleManager (semantic heartbeat)
    QObject::connect(_mavlinkParser.get(), &mini::mavlink::MavlinkParser::heartbeatReceived,
                     _vehicleManager.get(), &mini::vehicle::VehicleManager::handleHeartbeat);

    // Link stop → no vehicle (pipe closed; first-seen lock resets)
    QObject::connect(_udpLink.get(), &mini::comms::UdpLink::runningChanged, this, [this]() {
        if (_udpLink && !_udpLink->running() && _vehicleManager) {
            _vehicleManager->clear();
        }
    });
}

bool Application::_loadRootQml()
{
    _engine = std::make_unique<QQmlApplicationEngine>();

    // Expose before load so Main.qml bindings resolve (P4: bind, don't own services).
    _engine->rootContext()->setContextProperty(QStringLiteral("udpLink"), _udpLink.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("mavlinkParser"), _mavlinkParser.get());
    _engine->rootContext()->setContextProperty(QStringLiteral("vehicleManager"), _vehicleManager.get());

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
