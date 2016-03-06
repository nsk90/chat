#ifndef SEND_MESSAGE_DIALOG_H
#define SEND_MESSAGE_DIALOG_H

#include "ui_send_message_dialog.h"

class SendMessageDialog :
    public QDialog,
    private Ui::SendMessageDialog
{
    Q_OBJECT
public:
    explicit SendMessageDialog( QWidget * parent = 0 );
};

#endif // SEND_MESSAGE_DIALOG_H
