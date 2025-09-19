#include "vehiculo.h"

Vehiculo::Vehiculo(QString placa, QString tipoVehiculo, QDateTime horaEntrada,QString nomRegIn, int recargoEntrada):
    placa(placa),tipoVehiculo(tipoVehiculo), horaEntrada(horaEntrada),nomRegIn(nomRegIn),recargoEntrada(recargoEntrada)
{
    this->valorPagado=0;
    this->nomRegOut="";
    this->tiempoParqueo="";
    this->recargoSalida=0;
    this->cantidad=1;
}

Vehiculo::~Vehiculo()
{

}

void Vehiculo::Placa(QString placa)
{
    this->placa=placa;
}

void Vehiculo::TipoVehiculo(QString tipoVehiculo)
{
    this->tipoVehiculo=tipoVehiculo;
}

void Vehiculo::NomRegIn(QString nomRegIn)
{
    this->nomRegIn=nomRegIn;
}

void Vehiculo::NomRegOut(QString nomRegOut)
{
    this->nomRegOut=nomRegOut;
}

void Vehiculo::TiempoParqueo(QString tiempoParqueo)
{
    this->tiempoParqueo=tiempoParqueo;
}

void Vehiculo::HoraEntrada(QDateTime horaEntrada)
{
    this->horaEntrada=horaEntrada;
}

void Vehiculo::HoraSalida(QDateTime horaSalida)
{
    this->horaSalida=horaSalida;
}

void Vehiculo::ValorPagado(int valorPagado)
{
    this->valorPagado=valorPagado;
}

void Vehiculo::RecargoSalida(int recargoSalida)
{
    this->recargoSalida=recargoSalida;
}

void Vehiculo::Propietario(QString propietario)
{
    this->propietario=propietario;
}

void Vehiculo::Cantidad(double cantidad)
{
    this->cantidad=cantidad;
}

QString Vehiculo::getPlaca(void)
{
    return this->placa;

}

QString Vehiculo::getTipoVehiculo(void)
{
    return this->tipoVehiculo;
}

QString Vehiculo::getNomRegIn(void)
{
    return this->nomRegIn;
}

QString Vehiculo::getNomRegOut(void)
{
    return this->nomRegOut;
}

QString Vehiculo::getTiempoParqueo(void)
{
    return this->tiempoParqueo;
}

QDateTime Vehiculo::getHoraEntrada(void)
{
    return this->horaEntrada;
}

QDateTime Vehiculo::getHoraSalida(void)
{
    return this->horaSalida;
}

QString Vehiculo::getHoraSalidaString(void)
{
    return this->horaSalida.toString("yyyy-MM-dd");
}

QString Vehiculo::getHoraEntradaString(void)
{
    return this->horaEntrada.toString("yyyy-MM-dd");
}

int Vehiculo::getValorPagado(void)
{
    return this->valorPagado;
}

int Vehiculo::getRecargoEntrada(void)
{
    return this->recargoEntrada;
}

int Vehiculo::getRecargoSalida(void)
{
    return this->recargoSalida;
}

QString Vehiculo::getPropietario(void)
{
    return this->propietario;
}

double Vehiculo::getCantidad()
{
    return this->cantidad;
}
