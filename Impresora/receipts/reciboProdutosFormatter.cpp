#include "reciboProductosFormatter.h"

ReciboProductosFormatter::ReciboProductosFormatter(const ReciboProductos& data)
    : data_(data) {}


void ReciboProductosFormatter::printBody(EscPosBuilder& b)
{
    b.center()
        .font(EscPosFont::FontB)
        .bold(true)
        .textSize(2,2)
        .text("Venta de producto")
        .bold(false)
        .line(0)
        .left()
        .text(data_.nombreProducto)
        .line(0)
        .text("Valor: $" + data_.precioProducto)
        .line(0)
        .text("Fecha: " + data_.fechaVenta)
        .line(0)
        .text("Recibio: " + data_.operarioParqueadero)
        .line(0)
        .text("Inventario: " + data_.inventarioRestante + " restantes")
        .textNormal()
        .line(3)
        .fontNormal();
}
