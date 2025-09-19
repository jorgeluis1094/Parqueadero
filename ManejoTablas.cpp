#include "ManejoTablas.h"


void IngresarFilaTabla(int numTabla, Vehiculo* vehiculo ,QString valorHora)
{
    QSqlQuery query;
    QString Formato="yyyy-MM-dd hh:mm:ss";
    switch (numTabla)
    {
    case 0:

     //realiza el registro
        query.exec("INSERT INTO EntradaVehiculos "
                   "VALUES ('"+vehiculo->getPlaca()+"', "
                   "'"+vehiculo->getHoraEntrada().toString(Formato)+ "' , '"+vehiculo->getNomRegIn()+"', "
                   "'"+vehiculo->getTipoVehiculo()+"', '"+valorHora+"' )");
        break;
    case 1:
         query.exec("INSERT INTO RegVehiculos "
                   "VALUES ( '"+vehiculo->getPlaca()+"' ,"  //Placa,
                   "'"+vehiculo->getHoraEntrada().toString(Formato)+"' ," //HoraEntrada,
                   "'"+vehiculo->getHoraSalida().toString(Formato)+"' ,"  //HoraSalida,
                   "'"+QString::number(vehiculo->getValorPagado())+"' ,"  //ValorPagado,
                   "'"+vehiculo->getNomRegIn()+"',"  //QuienRegistroEntrada,
                   "'"+vehiculo->getNomRegOut()+"', " //QuienRegistroSalida,
                   "'"+vehiculo->getTipoVehiculo()+"',"  //TipoVehiculo,
                   "'"+vehiculo->getTiempoParqueo()+"' )"); //TiempoParqueo

        break;
    case 2:

        query.exec("INSERT INTO TablaOtrosVeh"
                   " VALUES ('"+vehiculo->getPlaca()+"', " //nombre
                   " '"+vehiculo->getHoraEntrada().toString(Formato)+"', "//hora Entrada
                   " '"+QString::number(vehiculo->getRecargoEntrada())+"', "//Recargo Entrada
                   " '"+vehiculo->getNomRegOut()+"', "  //hora Salida
                   " '"+QString::number(vehiculo->getRecargoSalida())+"', "  //Recargo Salida
                   " '"+QString::number(vehiculo->getValorPagado())+"', "  //valor a Pagar
                   " '"+vehiculo->getNomRegIn()+"', "  //Registro entrada
                   " '"+vehiculo->getNomRegOut()+"', " //Registro salida
                   " '"+vehiculo->getTipoVehiculo()+"', "  //tipo vehiculo
                   " '"+vehiculo->getTiempoParqueo()+"', " //Tiempo Parqueo
                   " '"+QString::number(vehiculo->getCantidad())+"'  )");
        break;
    case 3:

        break;
    }

}

QSqlQuery RealizarConsulta(QString Datos, QString NombreTabla, QString Parametros)
{
    QSqlQuery query;
    query.exec("SELECT "+Datos+" FROM "+NombreTabla+" WHERE  "+Parametros+" ");
    query.next();
    return query;
}

void BorrarFilaTabla(QString nombreTabla, QString Parametros)
{
    QSqlQuery query;
    query.exec("DELETE FROM "+nombreTabla+" WHERE "+Parametros+" ");
}

