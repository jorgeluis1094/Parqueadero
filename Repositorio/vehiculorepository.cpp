#include "vehiculorepository.h"
#include "Database/SessionManager.h"

VehiculoRepository::VehiculoRepository() {}

// vehiculorepository.cpp
bool VehiculoRepository::registrarEntrada(Vehiculo* v, int tarifa) {
    QSqlQuery query;
    query.prepare("INSERT INTO estacionamiento_activo "
                  "(placa, fecha_ingreso, categoria_vehiculo, tarifa_aplicada, id_operario_ingreso) "
                  "VALUES (:placa, :fecha, :cat, :tarifa, :id_ope)");

    query.bindValue(":placa", v->getPlaca());
    query.bindValue(":fecha", v->getHoraEntrada());
    query.bindValue(":cat", v->getTipoVehiculo());
    query.bindValue(":tarifa", tarifa);
    // Usamos el ID del operario, no el nombre (String)
    query.bindValue(":id_ope", SessionManager::instance().idActual());

    return query.exec();
}


bool VehiculoRepository::estaEnParqueadero(QString placa){
    QSqlQuery query;
    // Buscamos si la placa existe en la tabla de vehículos que están dentro actualmente
    query.prepare("SELECT COUNT(*) FROM estacionamiento_activo WHERE placa = :placa");
    query.bindValue(":placa", placa.trimmed().toUpper());

    if (query.exec() && query.next()) {
        // Si el conteo es mayor a 0, el vehículo está en el parqueadero
        return query.value(0).toInt() > 0;
    }

    return false; // Por defecto, si hay error o no está, retorna falso
};

bool VehiculoRepository::esMensualidadVigente(QString placa){
    QSqlQuery query;
    // Buscamos si la placa existe en la tabla de mensualidades
    query.prepare("SELECT COUNT(*) FROM mensualidades WHERE placa = :placa");
    query.bindValue(":placa", placa.trimmed().toUpper());

    if (query.exec() && query.next()) {
        // Si el conteo es mayor a 0, el vehículo es una mensualidad
        return query.value(0).toInt() > 0;
    }

    return false; // Por defecto, si hay error o no está, retorna falso
};


InfoCobro VehiculoRepository::calcularCobro(QString placa) {
    InfoCobro info = {0, 0, 0, 0, 0, "", QDateTime(), ""};
    QSqlQuery query;

    // 1. Obtener datos del vehículo que está en el parqueadero
    query.prepare("SELECT fecha_ingreso, categoria_vehiculo, tarifa_aplicada "
                  "FROM estacionamiento_activo WHERE placa = :placa");
    query.bindValue(":placa", placa.trimmed().toUpper());

    if (!query.exec() || !query.next()) {
        return info; // Retorna info con monto 0 si no lo encuentra
    }

    info.fechaIngreso = query.value(0).toDateTime();
    info.categoria = query.value(1).toString();
    int valorHora = query.value(2).toInt();

    // 2. Obtener Tarifas Globales (Máxima y Lavadas)
    int tarifaMaxima = 0;
    int precioLavada = 0;
    QSqlQuery qTarifas;

    // Tarifa máxima por cada 12 horas
    qTarifas.exec("SELECT valor FROM tarifas WHERE clave = 'valor_maximo_moto'");
    if(qTarifas.next()) tarifaMaxima = qTarifas.value(0).toInt();

    // Precio de lavada si aplica
    if (info.categoria.contains("Lavada")) {
        QString claveLavada = info.categoria.contains("Lavada_1") ? "lavada_1" : "lavada_2";
        qTarifas.prepare("SELECT valor FROM tarifas WHERE clave = :clave");
        qTarifas.bindValue(":clave", claveLavada);
        if(qTarifas.exec() && qTarifas.next()) precioLavada = qTarifas.value(0).toInt();
    }

    // 3. Cálculo de Tiempo
    QDateTime ahora = QDateTime::currentDateTime();
    qint64 segundosTotales = info.fechaIngreso.secsTo(ahora);
    if (segundosTotales < 0) segundosTotales = 0; // Protección contra cambios de hora del sistema

    int totalHorasReloj = segundosTotales / 3600;
    if ((segundosTotales % 3600) > 0 || segundosTotales == 0) {
        totalHorasReloj++; // Cobro por hora o fracción iniciada
    }

    info.horas = totalHorasReloj;
    info.minutos = (segundosTotales % 3600) / 60;

    // 4. Lógica de Cobro por Ciclos de 12 Horas
    int bloques12h = totalHorasReloj / 12;
    int horasSobrantes = totalHorasReloj % 12;

    int costoCiclosCompletos = bloques12h * tarifaMaxima;
    int costoResiduo = 0;

    // Punto de equilibrio dinámico: ¿Es más barato cobrar horas sueltas o la máxima?
    int costoHorasSueltas = horasSobrantes * valorHora;

    if (tarifaMaxima > 0 && costoHorasSueltas >= tarifaMaxima) {
        costoResiduo = tarifaMaxima;
    } else {
        costoResiduo = costoHorasSueltas;
    }

    info.montoTotal = costoCiclosCompletos + costoResiduo;

    // 5. Aplicar Regla de Lavada (Hora de Gracia)
    if (info.categoria.contains("Lavada")) {
        // La lavada regala la primera hora.
        // Si el montoTotal es mayor o igual a una hora, restamos ese valor.
        if (info.montoTotal >= valorHora) {
            info.montoTotal -= valorHora;
        } else {
            info.montoTotal = 0; // Caso en que la estancia fue mínima
        }

        // Sumamos el valor del servicio de lavado
        info.montoTotal += precioLavada;
    }

    return info;
}

bool VehiculoRepository::ejecutarSalida(QString placa, int montoTotal, QString duracion, int idOperarioSalida) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.transaction()) return false;

    QSqlQuery query;

    try {
        // 1. Mover datos incluyendo la DURACIÓN formateada
        query.prepare("INSERT INTO registro_salidas "
                      "(placa, fecha_ingreso, fecha_salida, duracion_total, monto_pagado, id_ope_entrada, id_ope_salida) "
                      "SELECT placa, fecha_ingreso, CURRENT_TIMESTAMP, :duracion, :monto, id_operario_ingreso, :id_ope_sal "
                      "FROM estacionamiento_activo WHERE placa = :placa");

        query.bindValue(":duracion", duracion);
        query.bindValue(":monto", montoTotal);
        query.bindValue(":id_ope_sal", idOperarioSalida);
        query.bindValue(":placa", placa);

        if (!query.exec()) throw std::runtime_error("Error al archivar salida");

        // 2. Registrar en caja
        query.prepare("INSERT INTO transacciones_caja (id_operario, monto, tipo_movimiento, id_referencia) "
                      "VALUES (:id_ope, :monto, 'PARQUEO', :placa)");
        query.bindValue(":id_ope", idOperarioSalida);
        query.bindValue(":monto", montoTotal);
        query.bindValue(":placa", placa);

        if (!query.exec()) throw std::runtime_error("Error en caja");

        // 3. Eliminar de activos
        query.prepare("DELETE FROM estacionamiento_activo WHERE placa = :placa");
        query.bindValue(":placa", placa);

        if (!query.exec()) throw std::runtime_error("Error al eliminar activo");

        return db.commit();

    } catch (...) {
        db.rollback();
        return false;
    }
}


DatosCierre VehiculoRepository::obtenerEstadisticasCierre(int idOperario) {
    DatosCierre d;
    d.fechaFin = QDateTime::currentDateTime();
    QSqlQuery query;

    // 1. Obtener inicio de sesión
    query.prepare("SELECT fecha_inicio FROM sesiones_operarios WHERE id_operario = :id AND fecha_fin IS NULL ORDER BY id DESC LIMIT 1");
    query.bindValue(":id", idOperario);
    if(query.exec() && query.next()) d.fechaInicio = query.value(0).toDateTime();

    // 2. TOTAL motos dentro del parqueadero
    query.exec("SELECT COUNT(*) FROM estacionamiento_activo");
    if(query.next()) d.totalMotosDentro = query.value(0).toInt();

    // 3. PRODUCTOS DE VITRINA (Estadística detallada)
    d.dineroProductos = 0;
    query.prepare("SELECT id_referencia, COUNT(*), SUM(monto) "
                  "FROM transacciones_caja "
                  "WHERE id_operario = :id AND fecha >= :inicio AND tipo_movimiento = 'PRODUCTO' "
                  "GROUP BY id_referencia");
    query.bindValue(":id", idOperario);
    query.bindValue(":inicio", d.fechaInicio);

    if(query.exec()) {
        while(query.next()) {
            QString nombreProd = query.value(0).toString();
            int cantidad = query.value(1).toInt();
            int subtotal = query.value(2).toInt();

            d.productosVendidos.insert(nombreProd, cantidad);
            d.dineroProductos += subtotal;
        }
    }

    // Suma el total recibido por motos (fracción)
     d.dineroMotos = 0;
     query.prepare("SELECT SUM(monto) FROM transacciones_caja WHERE id_operario = :id AND tipo_movimiento = 'PARQUEO' AND fecha_transaccion >= :inicio" );
     query.bindValue(":id", idOperario);
     query.bindValue(":inicio", d.fechaInicio);
     if(query.exec() && query.next())
         d.dineroMotos = query.value(0).toInt();

     // Suma el total recibido por motos (fracción)
     d.dineroLavadas1 = 0;
     query.prepare("SELECT SUM(monto) FROM transacciones_caja WHERE id_operario = :id AND tipo_movimiento = 'LAVADA_1' AND fecha_transaccion >= :inicio" );
     query.bindValue(":id", idOperario);
     query.bindValue(":inicio", d.fechaInicio);
     if(query.exec() && query.next())
         d.dineroLavadas1 = query.value(0).toInt();

     // Suma el total recibido por motos (fracción)
     d.dineroLavadas2 = 0;
     query.prepare("SELECT SUM(monto) FROM transacciones_caja WHERE id_operario = :id AND tipo_movimiento = 'LAVADA_2' AND fecha_transaccion >= :inicio" );
     query.bindValue(":id", idOperario);
     query.bindValue(":inicio", d.fechaInicio);
     if(query.exec() && query.next())
         d.dineroLavadas2 = query.value(0).toInt();

     // cuenta la cantidad de motos que salieron en el turno
     d.totalSalidasTurno = 0;
     query.prepare("SELECT COUNT(*) FROM transacciones_caja WHERE id_operario = :id AND tipo_movimiento = 'PARQUEO' AND fecha_transaccion >= :inicio" );
     query.bindValue(":id", idOperario);
     query.bindValue(":inicio", d.fechaInicio);
     if(query.exec() && query.next())
         d.totalSalidasTurno = query.value(0).toInt();


    // 4. TOTAL EFECTIVO FINAL
    d.totalEfectivo = 0;
    query.prepare("SELECT SUM(monto) FROM transacciones_caja WHERE id_operario = :id AND fecha_transaccion >= :inicio");
    query.bindValue(":id", idOperario);
    query.bindValue(":inicio", d.fechaInicio);
    if(query.exec() && query.next())
        d.totalEfectivo = query.value(0).toInt();

    return d;
}

bool VehiculoRepository::registrarCierreSesion(int idOperario, int montoCalculado) {
    QSqlQuery query;
    // Buscamos la sesión que no tiene fecha_fin (la actual)
    query.prepare("UPDATE sesiones_operarios SET "
                  "fecha_fin = CURRENT_TIMESTAMP, "
                  "monto_calculado_sistema = :monto "
                  "WHERE id_operario = :id AND fecha_fin IS NULL");

    query.bindValue(":monto", montoCalculado);
    query.bindValue(":id", idOperario);

    return query.exec();
}

void VehiculoRepository::registrarVentaProducto(QString nombre, int precio) {
    QSqlQuery q;
    q.prepare("INSERT INTO transacciones_caja (id_operario, monto, tipo_movimiento, id_referencia) "
              "VALUES (:id_ope, :monto, 'PRODUCTO', :prod)");
    q.bindValue(":id_ope", SessionManager::instance().idActual());
    q.bindValue(":monto", precio);
    q.bindValue(":prod", nombre); // Ejemplo: "Chaleco"
    q.exec();
}
