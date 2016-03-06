#include <QApplication>

#include "windows/application_window.h"

int main( int argc, char * argv[] )
{
    QApplication a( argc, argv );
    ApplicationWindow w;
    w.show();

    return a.exec();
}
