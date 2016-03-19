#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <QObject>

class ApplicationWindow;
///
/// \brief обработчик нажатий меню главного окна
///
class MenuHandler :
    public QObject
{
    Q_OBJECT
public:
    explicit MenuHandler( ApplicationWindow & appWindow, QObject * parent = 0 );
public slots:
    void onExitTriggered();
private:
    void connectUi();

    ApplicationWindow & m_appWindow;
};

#endif // MENUHANDLER_H
