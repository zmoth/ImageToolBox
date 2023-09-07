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

    QApplication::setOrganizationName("moth");                 // 此属性保存编写此应用程序的组织的名称
    QApplication::setApplicationName(PROJECT_NAME);            // 程序名
    QGuiApplication::setApplicationDisplayName(PROJECT_NAME);  // 程序名
    QGuiApplication::setApplicationVersion(PROJECT_VERSION);   // 程序版本

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/icon.ico"));  // 给app添加图标

    ImageDisplayArea view;
    view.resize(800, 600);
    view.show();

    return app.exec();
}
