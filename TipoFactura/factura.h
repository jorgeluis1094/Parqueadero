#ifndef FACTURA_H
#define FACTURA_H
#include <QPainter>
#include <QPrinter>
#include "TipoPersona/operario.h"
#include "TipoVehiculos/vehiculo.h"



class Factura
{
public:
    Factura();
    void Imprimir(QPrinter *printer, int tipoRecibo);
    void setVehiculo(Vehiculo *vehiculo);
    void setTrabajador(Operario *trabajador);
private:
    Vehiculo *vehiculo;
    Operario* trabajador;

    //Datos del Parqueadero
    QString NombreParqueadero;
    QString direccionParqueadero;
    QString telefonoParqueadero;
    QString propietarioParqueadero;
    QString nITParquieadero;
    QString reglamentoParqueadero;
    QString imagenDerecha;
    QString imagenIzquierda;

    QString OperarioTurno;


};

#endif // FACTURA_H
