#include "CierreCajaFormatter.h"

CierreCajaFormatter::CierreCajaFormatter(const CierreCaja& data)
    : data_(data)
{
}

void CierreCajaFormatter::printBody(EscPosBuilder& b)
{
    b.center()
    .bold(true)
        .text("CIERRE DE CAJA")
        .bold(false)
        .line(1)
        .left();

    b.text("Fecha: " + data_.fechaHora);
    b.text("Usuario: " + data_.usuario);
    b.line(0);

    b.text("Entradas: " + QString::number(data_.totalEntradas));
    b.text("Salidas:  " + QString::number(data_.totalSalidas));
    b.text("Mensualidades pagas:  " + QString::number(data_.totalMensulidadesPago));
    b.line(0);

    b.text("TOTALES POR PAGO");
    b.line(0);

    for (auto it = data_.totalesPago.begin(); it != data_.totalesPago.end(); ++it) {
        b.text(it.key() + ": $" + QString::number(it.value(), 'f', 0));
    }

    b.line(0)
        .bold(true)
        .text("TOTAL GENERAL: $" + QString::number(data_.totalGeneral(), 'f', 0))
        .bold(false)
        .line(3);
}
