#-------------------------------------------------
#
# Project created by QtCreator 2013-05-29T10:22:47
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parqueadero
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    FuncionesTiempo.cpp \
    ManejoTablas.cpp \
    TipoPersona/persona.cpp \
    TipoPersona/operario.cpp \
    TipoPersona/clientemensualidad.cpp \
    TipoVehiculos/vehiculo.cpp \
    relojdigital.cpp

HEADERS  += mainwindow.h \
    FuncioneTiempo.h \
    ManejoTablas.h \
    TipoPersona/persona.h \
    TipoPersona/operario.h \
    TipoPersona/clientemensualidad.h \
    TipoVehiculos/vehiculo.h \
    relojdigital.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/mysql

