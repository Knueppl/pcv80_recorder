#include <QApplication>

#include <cstring>

#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mw(argc == 2 ? argv[1] : "/dev/ttyS1");

    mw.show();

    return app.exec();
}
