#ifndef CLIENTEMENSUALIDAD_H
#define CLIENTEMENSUALIDAD_H
#include "persona.h"
#include <QDateTime>

class ClienteMensualidad : public Persona
{
public:
    ClienteMensualidad(QString nombre, QString direccionCasa, QString telefono);
    void PlacaVehiculo(QString placaVehiculo);
    void ValorMensualidad(int valorMensualidad);
    void FechaInicioM(QDate fechaInicioM);
    void FechaFinM(QDate fechaFinM);
    void TipoVehiculo(QString tipoVehiculo);

private:
    QString placaVehiculo;
    int valorMensualidad;
    QDate fechaInicioM;
    QDate fechaFinM;
    QString tipoVehiculo;



};

#endif // CLIENTEMENSUALIDAD_H
