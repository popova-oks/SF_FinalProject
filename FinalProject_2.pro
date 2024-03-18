QT       += \
    core gui\
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/handler_MySQL.cpp \
    src/main.cpp \
    src/mainwindow.cpp\
    src/chat.cpp\
    src/messages.cpp\
    src/sha1.cpp\
    src/user_screen.cpp \
    src/widget.cpp

HEADERS += \
    headers/handler_MySQL.h \
    headers/mainwindow.h\
    headers/ISubject.h\
    headers/chat.h\
    headers/messages.h\
    headers/sha1.h\
    headers/user_screen.h \
    headers/widget.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    json/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
