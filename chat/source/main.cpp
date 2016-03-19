#include <QApplication>

#include "windows/application_window.h"
#include "app_model.h"

int main( int argc, char * argv[] )
{
    QApplication a( argc, argv );

    //создаем модель
    AppModel model;

    ApplicationWindow w;
    w.show();

    return a.exec();
}
