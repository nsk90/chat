#include "menu_handler.h"

#include <QApplication>

#include "windows/application_window.h"

MenuHandler::MenuHandler( ApplicationWindow & appWindow, QObject * parent ) :
    QObject( parent ),
    m_appWindow( appWindow )
{
    connectUi();
}

void MenuHandler::onExitTriggered()
{
    qApp->exit();
}

void MenuHandler::connectUi()
{
    connect( m_appWindow.m_actionExit, &QAction::triggered,
             this, &MenuHandler::onExitTriggered );

}

