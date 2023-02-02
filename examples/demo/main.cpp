#include <QApplication>
#include <QPixmap>
#include <toolbox/ImageDisplayArea>

#include "config.h"

using ImageToolBox::ImageDisplayArea;

int main(int argc, char *argv[])
{
    qSetMessagePattern(
        "[%{time yyyyMMdd h:mm:ss.zzz}] [%{time process}] "
        "[%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-"
        "fatal}F%{endif}]: %{message}\t| (%{function}) [%{file}:%{line}]");

    QApplication::setOrganizationName("moth");  // 此属性保存编写此应用程序的组织的名称
    QApplication::setApplicationName(PROJECT_NAME);            // 程序名
    QGuiApplication::setApplicationDisplayName(PROJECT_NAME);  // 程序名
    QGuiApplication::setApplicationVersion(PROJECT_VER);       // 程序版本
#ifdef Q_OS_UNIX
    // Unix doesn't provide an application version by default
    QGuiApplication::setApplicationVersion(PROJECT_VER);  // 程序版本
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    // Log some debug info
    qInfo("=============================");
    qInfo("%s v%s",
          qUtf8Printable(QApplication::applicationDisplayName()),
          qUtf8Printable(QApplication::applicationVersion()));
    qInfo("Build Date/Time: %s %s", __DATE__, __TIME__);
    qInfo("Qt: %s", qVersion());
    qInfo("OS: %s", qUtf8Printable(QSysInfo::prettyProductName()));
    qInfo("Locale: %s", qUtf8Printable(QLocale::system().name()));
    qInfo("CPU: %s", qUtf8Printable(QSysInfo::currentCpuArchitecture()));
    qInfo("File Path: %s", qUtf8Printable(QApplication::applicationFilePath()));
    qInfo("Arguments: %s", qUtf8Printable(app.arguments().join(' ')));
    qInfo("=============================");

    app.setWindowIcon(QIcon(":/icon.ico"));  // 给app添加图标

    ImageDisplayArea view;
    view.resize(800, 600);
    view.show();

    return app.exec();
}
