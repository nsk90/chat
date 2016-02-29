#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <QMainWindow>

namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow :
    public QMainWindow,
    private Ui::ApplicationWindow
{
    Q_OBJECT

public:
    explicit ApplicationWindow(QWidget * parent = 0);
    ~ApplicationWindow();
};

#endif // APPLICATION_WINDOW_H
