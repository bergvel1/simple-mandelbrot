#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T20:34:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple-mandelbrot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        mandelbrot.cpp\
        mandelbrot-main.cpp

HEADERS  += mainwindow.h\
            mandelbrot.h\

FORMS    += mainwindow.ui
