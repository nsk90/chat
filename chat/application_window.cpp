#include "application_window.h"
#include "ui_application_window.h"

ApplicationWindow::ApplicationWindow(QWidget * parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

ApplicationWindow::~ApplicationWindow()
{
}
