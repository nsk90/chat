#include "application_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationWindow w;
    w.show();

    return a.exec();
}
