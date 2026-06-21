#include "ui/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName(QStringLiteral("SmartPath"));
    QApplication::setOrganizationName(QStringLiteral("TingLaoShiDeHua"));

    MainWindow window;
    window.show();
    return app.exec();
}
