#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <QMainWindow>
#include <QPointer>

#include "ui_application_window.h"

class MenuHandler;
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
private:
    friend class MenuHandler;

    QPointer< MenuHandler > m_menuHandler;
};

#endif // APPLICATION_WINDOW_H
