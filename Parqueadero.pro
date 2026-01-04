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
    Impresora/PrintManager.cpp \
    Impresora/commands/EscPosBuilder.cpp \
    Impresora/config/printconfig.cpp \
    Impresora/output/PrintDevice.cpp \
    Impresora/receipts/ReceiptFormatter.cpp \
    Impresora/receipts/ReciboEntradaFormatter.cpp \
    Impresora/receipts/reciboProdutosFormatter.cpp \
    Impresora/receipts/recibopagomensualidadformatter.cpp \
    Impresora/transport/UsbLpTransport.cpp \
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
    Impresora/PrintManager.h \
    Impresora/commands/EscPosBuilder.h \
    Impresora/config/printconfig.h \
    Impresora/output/PrintDevice.h \
    Impresora/receipts/CierreCajaFormatter.h \
    Impresora/receipts/ReceiptFormatter.h \
    Impresora/receipts/ReciboEntradaFormatter.h \
    Impresora/receipts/ReciboSalidaFormatter.h \
    Impresora/receipts/reciboProductosFormatter.h \
    Impresora/receipts/recibopagomensualidadformatter.h \
    Impresora/transport/ITransport.h \
    Impresora/transport/UsbLpTransport.h \
    ManejoTablas.h \
    TipoPersona/persona.h \
    TipoPersona/operario.h \
    TipoPersona/clientemensualidad.h \
    TipoVehiculos/vehiculo.h \
    domain/cierrecaja.h \
    domain/reciboProductos.h \
    domain/reciboentrada.h \
    domain/recibomensualidad.h \
    relojdigital.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/mysql

