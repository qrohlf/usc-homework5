#include <QtGui/QApplication>
#include "gamewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget window;
    window.show();

    return a.exec();
}
