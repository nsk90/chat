#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <QMainWindow>

#include "ui_application_window.h"
///
/// \brief Основное окно приложения
///
class ApplicationWindow :
    public QMainWindow,
    private Ui::ApplicationWindow
{
    Q_OBJECT
public:
    explicit ApplicationWindow( QWidget * parent = 0 );
    virtual ~ApplicationWindow();
};

#endif // APPLICATION_WINDOW_H
