#include "loginwidget.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWidget login;
    login.move((app.desktop()->width() - login.width()) / 2, (app.desktop()->height() - login.height()) / 2);
    login.show();

    return app.exec();
}
