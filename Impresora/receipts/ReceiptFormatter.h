#pragma once

#include <QImage>
#include <QByteArray>
#include <QPainter>
#include "../commands/EscPosBuilder.h"
#include "Impresora/config/printconfig.h"

class ReceiptFormatter {
public:
    virtual ~ReceiptFormatter() = default;

    // MÉTODO PRINCIPAL (NO SE SOBREESCRIBE)
    QByteArray format();

protected:
    // SOLO el cuerpo cambia entre recibos
    virtual void printBody(EscPosBuilder& b) = 0;

    // Comunes a todos (puedes sobreescribir si quieres)
    virtual void printHeader(EscPosBuilder& b);
    virtual void printFooter(EscPosBuilder& b);

    virtual bool hasFooter() const { return true; }

};



