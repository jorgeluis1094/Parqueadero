#ifndef RECIBOENTRADAFORMATTER_H
#define RECIBOENTRADAFORMATTER_H

#pragma once
#include "ReceiptFormatter.h"
#include "domain/reciboentrada.h"
#include <QPainter>
#include <QDebug>
#include "Impresora/commands/EscPosBuilder.h"


class ReciboEntradaFormatter : public ReceiptFormatter {
public:
    ReciboEntradaFormatter(const ReciboEntrada& data);
    //bool hasFooter() const override { return false; }

protected:
    void printBody(EscPosBuilder& b) override;

private:
    ReciboEntrada data_;
};


#endif // RECIBOENTRADAFORMATTER_H
