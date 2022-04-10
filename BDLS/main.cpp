#include "BDLS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BDLS w;
    w.show();
    return a.exec();
}
