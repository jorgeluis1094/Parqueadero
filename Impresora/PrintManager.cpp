#include "PrintManager.h"


PrintManager::PrintManager()
{
}


bool PrintManager::printReciboEntrada(const ReciboEntrada& data) {
    ReciboEntradaFormatter formatter(data);
    QByteArray bytes = formatter.format();

    auto transport = std::make_unique<UsbLpTransport>("/dev/usb/lp0");
    PrintDevice printer(std::move(transport));

    if (!printer.connect())
        return false;

    bool ok = printer.send(bytes);
    printer.disconnect();

    return ok;
}

bool PrintManager::printReciboMensualidad(const ReciboMensualidad& data) {
    ReciboPagoMensualidadFormatter formatter(data);
    //ReciboEntradaFormatter formatter(data);
    QByteArray bytes = formatter.format();

    auto transport = std::make_unique<UsbLpTransport>("/dev/usb/lp0");
    PrintDevice printer(std::move(transport));

    if (!printer.connect())
        return false;

    bool ok = printer.send(bytes);
    printer.disconnect();

    return ok;
}

bool PrintManager::printReciboVentaProductos(const ReciboProductos& data) {
    ReciboProductosFormatter formatter(data);
    //ReciboEntradaFormatter formatter(data);
    QByteArray bytes = formatter.format();

    auto transport = std::make_unique<UsbLpTransport>("/dev/usb/lp0");
    PrintDevice printer(std::move(transport));

    if (!printer.connect())
        return false;

    bool ok = printer.send(bytes);
    printer.disconnect();

    return ok;
}
