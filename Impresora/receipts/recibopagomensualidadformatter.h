#ifndef RECIBOPAGOMENSUALIDADFORMATTER_H
#define RECIBOPAGOMENSUALIDADFORMATTER_H

#include "ReceiptFormatter.h"
#include "Impresora/commands/EscPosBuilder.h"
#include "domain/recibomensualidad.h"


class ReciboPagoMensualidadFormatter : public ReceiptFormatter
{
public:
    ReciboPagoMensualidadFormatter(const ReciboMensualidad& data);
    bool hasFooter() const override { return false; }

protected:
    void printBody(EscPosBuilder& b) override;

private:
    ReciboMensualidad data_;

};

#endif // RECIBOPAGOMENSUALIDADFORMATTER_H
