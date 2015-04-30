#include "xtools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XTools w;
    w.show();

    return a.exec();
}
