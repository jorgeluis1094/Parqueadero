#ifndef CIERRECAJA_H
#define CIERRECAJA_H
#include <QString>
#include <QMap>

class CierreCaja {
public:
    QString fechaHoraInicio, fechaHoraFin;
    QString usuario;

    // Totales por tipo de pago
    QMap<QString, double> totalesPago;

    // Contadores
    int totalEntradas = 0;
    int totalSalidas = 0;
    int totalMensulidadesPago = 0;

    double totalGeneral() const {
        double total = 0.0;
        for (auto it = totalesPago.begin(); it != totalesPago.end(); ++it)
            total += it.value();
        return total;
    }
};


#endif // CIERRECAJA_H
