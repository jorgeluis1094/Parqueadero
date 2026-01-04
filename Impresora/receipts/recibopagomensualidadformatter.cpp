#include "recibopagomensualidadformatter.h"

ReciboPagoMensualidadFormatter::ReciboPagoMensualidadFormatter(const ReciboMensualidad& data)
    : data_(data) {}


void ReciboPagoMensualidadFormatter::printBody(EscPosBuilder& b)
{
    b.center()
        .font(EscPosFont::FontB)
        .textSize(2,2)
        .bold(true)
        .text("Recibo de pago de mensualidad")
        .bold(false)
        .line(0)
        .left()
        .text("Dia Pago: " + data_.fechaPago)
        .line(0)
        .text("Placa: " + data_.placa)
        .line(0)
        .text("Pago: $" + data_.pagoRecibido)
        .line(0)
        .text("Tipo: " + data_.tipoVehiculo)
        .line(0)
        .text("Inicio mensualidad: " + data_.inicioMensualidad)
        .line(0)
        .text("Fin mensualidad:  " + data_.finMensualidad)
        .line(0)
        .text("Recibio: " + data_.operarioParqueadero)
        .line(0)
        .textNormal()
        .fontNormal()
        .text(" Conserve este recibo, es su unico comprobante.")
        .line(3);
}
