#-------------------------------------------------
#
# Project created by QtCreator 2017-12-11T15:05:22
#
#-------------------------------------------------

QT += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataStructureProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS  +=  -Wno-comment  # 防止佛祖出警告

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so,  the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        ParkingLotWidget.cpp \
        Road.cpp \
        ParkingSpaceWidget.cpp \
    monitor.cpp \
    boundary.cpp \
    car.cpp \
    path.cpp \
    parkingLotManager.cpp \
    parkinglotgraph.cpp \
    logwindow.cpp \
    carlist.cpp \
    logindialog.cpp \
    utils.cpp

HEADERS += \
        mainwindow.h \
        ParkingLotWidget.h \
        Road.h \
        ParkingSpaceWidget.h \
    monitor.h \
    boundary.h \
    car.h \
    path.h \
    parkingLotManager.h \
    parkinglotgraph.h \
    logwindow.h \
    carlist.h \
    logindialog.h \
    utils.h

FORMS += \
        mainwindow.ui \
    monitor.ui \
    logwindow.ui \
    carlist.ui \
    logindialog.ui

RESOURCES += \
    cars.qrc \
