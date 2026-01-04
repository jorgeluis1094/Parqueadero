#ifndef RECIBOPRODUCTOSFORMATTER_H
#define RECIBOPRODUCTOSFORMATTER_H

#include "ReceiptFormatter.h"
#include "Impresora/commands/EscPosBuilder.h"
#include "domain/reciboProductos.h"


class ReciboProductosFormatter : public ReceiptFormatter
{
public:
    ReciboProductosFormatter(const ReciboProductos& data);
    bool hasFooter() const override { return false; }

protected:
    void printBody(EscPosBuilder& b) override;

private:
    ReciboProductos data_;

};

#endif // RECIBOPRODUCTOSFORMATTER_H
