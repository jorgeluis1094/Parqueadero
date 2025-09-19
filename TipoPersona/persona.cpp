#include "persona.h"

Persona::Persona(QString nombre, QString direccionCasa, QString telefono):
    nombre(nombre), direccionCasa(direccionCasa), telefono(telefono)
{
}
Persona::~Persona()
{
}

void Persona::Nombre(QString nombre)
{
    this->nombre=nombre;
}

void Persona::DireccionCasa(QString direccionCasa)
{
    this->direccionCasa=direccionCasa;
}

void Persona::Telefono(QString telefono)
{
    this->telefono=telefono;
}


QString Persona::getNombre(void)
{
    return this->nombre;
}
