#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T16:05:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorSphere
TEMPLATE = app

INCLUDEPATH += "C:/Assimp-3.1.1/include"
LIBS += "C:/Assimp-3.1.1/libs/libassimp.dll"


SOURCES += main.cpp\
        Dialog.cpp \
    Scene.cpp \
    LoaderOfSphere.cpp \
    Sphere.cpp

HEADERS  += Dialog.h \
    Scene.h \
    LoaderOfSphere.h \
    Sphere.h

FORMS    += Dialog.ui

RESOURCES += \
    Shaders.qrc
