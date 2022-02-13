#-------------------------------------------------
#
# Project created by QtCreator 2022-01-10T18:58:25
#
#-------------------------------------------------

QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChartMaker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Model/column.cpp \
    Model/model.cpp \
    Model/record.cpp \
    Model/table.cpp \
    Model/wordrecord.cpp \
    View/barchart.cpp \
    View/chart.cpp \
    View/create1.cpp \
    View/create2.cpp \
    View/createchartview.cpp \
    View/linechart.cpp \
    View/mainwindow.cpp \
    View/piechart.cpp \
    View/tableview.cpp \
    View/tabview.cpp \
    Model/intrecord.cpp \
    Model/doublerecord.cpp \
    Controller/controller.cpp

HEADERS += \
    Model/column.h \
    Model/model.h \
    Model/record.h \
    Model/table.h \
    Model/wordrecord.h \
    View/barchart.h \
    View/chart.h \
    View/create1.h \
    View/create2.h \
    View/createchartview.h \
    View/linechart.h \
    View/mainwindow.h \
    View/piechart.h \
    View/tableview.h \
    View/tabview.h \
    Model/intrecord.h \
    Model/doublerecord.h \
    Controller/controller.h

OTHER_FILES += \

RESOURCES += \
    ChartMaker.qrc
