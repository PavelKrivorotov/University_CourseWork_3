QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogs/adduserdialog.cpp \
    dialogs/changedialog.cpp \
    dialogs/deletedialog.cpp \
    dialogs/filterdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    user/deserializer.cpp \
    user/user.cpp \
    user/usermanager.cpp

HEADERS += \
    dialogs/adduserdialog.h \
    dialogs/changedialog.h \
    dialogs/deletedialog.h \
    dialogs/filterdialog.h \
    mainwindow.h \
    user/deserializer.h \
    user/user.h \
    user/usermanager.h

FORMS += \
    dialogs/adduserdialog.ui \
    dialogs/changedialog.ui \
    dialogs/deletedialog.ui \
    dialogs/filterdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
