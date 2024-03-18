QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp\
    src/chat.cpp\
    src/clientCode.cpp\
    src/jsonHandler.cpp\
    src/messages.cpp\
    src/sha1.cpp\
    src/user.cpp\
    src/user_screen.cpp \
    src/widget.cpp

HEADERS += \
    headers/mainwindow.h\
    headers/IObserver.h\
    headers/ISubject.h\
    headers/chat.h\
    headers/clientCode.h\
    headers/jsonHandler.h\
    headers/messages.h\
    headers/sha1.h\
    headers/user.h \
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
