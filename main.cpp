#include "mouseEventsQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mouseEventsQt w;
    w.show();
    return a.exec();
}
