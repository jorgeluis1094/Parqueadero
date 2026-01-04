#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

//#pragma once
#include "Impresora/output/PrintDevice.h"
#include "Impresora/transport/UsbLpTransport.h"
#include "Impresora/receipts/ReciboEntradaFormatter.h"
#include "Impresora/receipts/recibopagomensualidadformatter.h"
#include "Impresora/receipts/reciboProductosFormatter.h"


#include "domain/reciboentrada.h"
#include "domain/recibomensualidad.h"
#include "domain/reciboProductos.h"

class PrintManager {
public:
    PrintManager();
    bool printReciboEntrada(const ReciboEntrada& data);
    bool printReciboMensualidad(const ReciboMensualidad& data);
    bool printReciboVentaProductos(const ReciboProductos& data);
};



#endif // PRINTMANAGER_H
