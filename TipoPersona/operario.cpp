#include "operario.h"

Operario::Operario(QString nombre,QString direccionCasa,QString telefono):
    Persona(nombre,direccionCasa,telefono)
{
}
Operario::~Operario()
{
}

void Operario::HoraEntrada(QString horaEntrada)
{
    this->horaEntrada=horaEntrada;
}

void Operario::HoraSalida(QString horaSalida)
{
    this->horaSalida=horaSalida;
}

void Operario::TotalRealizado(int totalRealizado)
{
    this->totalRealizado=totalRealizado;
}

void Operario::TotalMensualidades(int totalMensualidades)
{
    this->totalMensualidades=totalMensualidades;
}

void Operario::TotalMotos(int totalMotos)
{
    this->totalMotos=totalMotos;
}

void Operario::TotalCarros(int totalCarros)
{
    this->totalCarros=totalCarros;
}

void Operario::TotalOtrosArticulos(int totalOtrosArticulos)
{
    this->totalOtrosArticulos=totalOtrosArticulos;
}

void Operario::NumMensualidadesPagadas(int numMensualidadesPagadas)
{
    this->numMensualidadesPagadas=numMensualidadesPagadas;
}

void Operario::TotalOtrosPagos(int totalOtrosPagos)
{
    this->totalOtrosPagos=totalOtrosPagos;
}

QString Operario::getHoraEntrada(void)
{
    return this->horaEntrada;
}

QString Operario::getHoraSalida(void)
{
    return this->horaSalida;
}

int Operario::getTotalRealizado(void)
{
    return this->totalRealizado;
}

int Operario::getTotalMensualidades(void)
{
    return this->totalMensualidades;
}

int Operario::getTotalMotos(void)
{
    return this->totalMotos;
}

int Operario::getTotalCarros(void)
{
    return this->totalCarros;
}

int Operario::getTotalOtrosArticulos(void)
{
    return this->totalOtrosArticulos;
}

int Operario::getNumMensualidadesPagadas(void)
{
    return this->numMensualidadesPagadas;
}

int Operario::getTotalOtrosPagos(void)
{
    return this->totalOtrosPagos;
}
