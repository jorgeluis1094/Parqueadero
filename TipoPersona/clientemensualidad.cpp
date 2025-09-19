#include "clientemensualidad.h"

ClienteMensualidad::ClienteMensualidad(QString nombre, QString direccionCasa, QString telefono):
    Persona(nombre,direccionCasa,telefono)
{
}
void ClienteMensualidad::PlacaVehiculo(QString placaVehiculo)
{
    this->placaVehiculo=placaVehiculo;
}

void ClienteMensualidad::ValorMensualidad(int valorMensualidad)
{
    this->valorMensualidad=valorMensualidad;
}

void ClienteMensualidad::FechaInicioM(QDate fechaInicioM)
{
    this->fechaInicioM=fechaInicioM;
}

void ClienteMensualidad::FechaFinM(QDate fechaFinM)
{
    this->fechaFinM=fechaFinM;
}

void ClienteMensualidad::TipoVehiculo(QString tipoVehiculo)
{
    this->tipoVehiculo=tipoVehiculo;
}

