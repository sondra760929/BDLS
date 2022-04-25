#include "BDLS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BDLS w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.setWindowTitleHeight(40);
    w.show();
    return a.exec();
}
