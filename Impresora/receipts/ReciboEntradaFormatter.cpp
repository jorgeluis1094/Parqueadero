#include "ReciboEntradaFormatter.h"

ReciboEntradaFormatter::ReciboEntradaFormatter(const ReciboEntrada& data)
    : data_(data) {}



void ReciboEntradaFormatter::printBody(EscPosBuilder& b)
{
    b.center()
        .bold(true)
        .text("Ingreso: " + data_.fechaHora)
        .text("Recibido: " + data_.operarioParqueadero)
        .text("Tipo: " + data_.tipoVehiculo)
        .bold(false)
        .line(0)
        .textSize(2,2)
        .text(data_.placa)
        .textNormal()
        .barcode(data_.placa,73,100,3,2);
        //.line(0);

}
