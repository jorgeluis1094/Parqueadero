#ifndef CIERRECAJAFORMATTER_H
#define CIERRECAJAFORMATTER_H

#include "ReceiptFormatter.h"
#include "domain/cierrecaja.h"

class CierreCajaFormatter : public ReceiptFormatter {
public:
    explicit CierreCajaFormatter(const CierreCaja& data);

protected:
    void printBody(EscPosBuilder& b) override;
    bool hasFooter() const override { return false; }

private:
    const CierreCaja& data_;
};


#endif // CIERRECAJAFORMATTER_H
