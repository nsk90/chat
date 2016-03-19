#include "application_window.h"

#include "menu_handler.h"

ApplicationWindow::ApplicationWindow( QWidget * parent ) :
    QMainWindow( parent )
{
    setupUi( this );
    setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowTitleHint |
                    Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint );

    m_menuHandler = new MenuHandler( *this, this );
}

ApplicationWindow::~ApplicationWindow()
{
}

