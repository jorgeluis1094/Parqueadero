#ifndef VEHICULOREPOSITORY_H
#define VEHICULOREPOSITORY_H

#include <QString>
#include <QSqlQuery>
#include "TipoVehiculos/vehiculo.h"


struct InfoCobro {
    int montoTotal = 0;
    int horas = 0;
    int minutos = 0;
    int valorParqueo = 0;
    int valorLavada = 0;
    QString tipoLavada = "";
    QDateTime fechaIngreso = QDateTime();
    QString categoria = "";
};

struct DatosCierre {
    QDateTime fechaInicio = QDateTime();
    QDateTime fechaFin = QDateTime();
    int totalMotosDentro = 0;
    int totalSalidasTurno = 0;
    int dineroMotos = 0;
    int dineroLavadas1 = 0;
    int dineroLavadas2 = 0;
    int dineroMensualidades = 0;
    QString nombreOperario = "";
    QMap<QString, int> productosVendidos; // Clave: Nombre Producto, Valor: Cantidad
    int dineroProductos = 0;                  // Suma total de dinero por productos
    int totalEfectivo = 0;
};

// vehiculorepository.h
class VehiculoRepository {
public:
    VehiculoRepository();
    // Verifica si el vehículo ya está dentro
    bool estaEnParqueadero(QString placa);

    // Verifica si es un cliente de mensualidad vigente
    bool esMensualidadVigente(QString placa);

    // Registra solo la entrada
    bool registrarEntrada(Vehiculo* v, int tarifa);

    // Obtiene los datos de un vehículo que está dentro para calcular el cobro
    Vehiculo* obtenerVehiculoActivo(QString placa);

    // Realiza el calculo de un vehiculo dentro
    InfoCobro calcularCobro(QString placa);

    // Ingresa los datos de la placa en las tablas de caja e historico, tambien borra de estacionados_activos
    bool ejecutarSalida(QString placa, int montoTotal, QString duracion, int idOperarioSalida);

    // Calcula cuando debe haber en caja
    DatosCierre obtenerEstadisticasCierre(int idOperario);

    // Registra en las tablas correspondientes el cierre de caja y salida de operario
    bool registrarCierreSesion(int idOperario, int montoTotalEntregado);

    //
    void registrarVentaProducto(QString nombre, int precio);
};


#endif // VEHICULOREPOSITORY_H
