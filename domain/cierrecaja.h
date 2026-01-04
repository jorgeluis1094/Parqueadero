#ifndef CIERRECAJA_H
#define CIERRECAJA_H

#include <QString>
#include <QVector>

struct ItemCierre {
    QString concepto;
    double valor;
};

struct CierreCaja {
    QString nombreParqueadero;
    QString fecha;
    QString operario;
    QVector<ItemCierre> items;
    double total;
};

#endif // CIERRECAJA_H
