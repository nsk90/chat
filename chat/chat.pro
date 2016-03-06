#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T20:44:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat
TEMPLATE = app


SOURCES += \
    source/main.cpp\
    source/windows/application_window.cpp \
    source/connection_handler.cpp \
    source/windows/send_message_dialog.cpp \
    source/criptographer_xor.cpp

HEADERS  += \
    source/windows/application_window.h \
    source/connection_handler.h \
    source/windows/send_message_dialog.h \
    source/criptographer_xor.h

FORMS    += \
    application_window.ui \
    send_message_dialog.ui

INCLUDEPATH += /source
