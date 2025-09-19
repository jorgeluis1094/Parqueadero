#ifndef MANEJOTABLAS_H
#define MANEJOTABLAS_H
#include <QString>
#include <QSqlQuery>
#include "TipoVehiculos/vehiculo.h"



void IngresarFilaTabla(int numTabla, Vehiculo *vehiculo, QString valorHora);

QSqlQuery RealizarConsulta(QString Datos, QString NombreTabla, QString Parametros);

void BorrarFilaTabla(QString nombreTabla, QString Parametros);

#endif // MANEJOTABLAS_H
