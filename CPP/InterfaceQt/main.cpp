#include "applichorairewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicHoraireWindow w;
    w.show();
    return a.exec();
}
