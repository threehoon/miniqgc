#include "Application.h"

#include "Logging.h"

#include <QtCore/QLoggingCategory>
#include <QtQuickControls2/QQuickStyle>

/// Process entry — keep thin; composition lives in mini::app::Application (P6).
int main(int argc, char *argv[])
{
    // Fusion allows ToolBar/Button chrome customization on macOS (native style is limited).
    QQuickStyle::setStyle(QStringLiteral("Fusion"));

    // Optional: enable mini.* categories in Debug without QT_LOGGING_RULES.
    QLoggingCategory::setFilterRules(QStringLiteral("mini.*.debug=true"));

    mini::app::Application app(argc, argv);

    if (!app.init()) {
        qCCritical(MiniAppLog) << "main: Application::init failed";
        return EXIT_FAILURE;
    }

    qCInfo(MiniAppLog) << "main: entering event loop";
    const int code = app.exec();

    app.shutdown();
    qCInfo(MiniAppLog) << "main: exit code" << code;
    return code;
}
