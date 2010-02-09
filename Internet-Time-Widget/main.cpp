/******************************************************************************
*
* Copyright (C) 2010 Jeff Parent
*
******************************************************************************/

#include <QtGui>

#include "ClockWindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(systray);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::critical(
            0,
            QObject::tr("Internet Time Widget"),
            QObject::tr("Could not detect SysTray on this system."));

        return 1;
    }

    QApplication::setQuitOnLastWindowClosed(false);

    ClockWindow window;

    window.hide();

    return app.exec();
}
