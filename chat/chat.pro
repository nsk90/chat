#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T20:44:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app


SOURCES += main.cpp\
        application_window.cpp \
    connection_handler.cpp \
    send_message_dialog.cpp

HEADERS  += application_window.h \
    connection_handler.h \
    send_message_dialog.h

FORMS    += application_window.ui \
    send_message_dialog.ui
