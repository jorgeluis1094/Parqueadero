#include "Database/PostgresVehiculoRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool PostgresVehiculoRepository::registrarEntrada(Vehiculo* v, int valorHora) {
    // 2. Especificamos la base de datos por defecto para evitar errores de conexión
    QSqlQuery query(QSqlDatabase::database());

    // 3. Ajustamos los nombres de las columnas según el SQL que definimos (id_operario_ingreso)
    query.prepare("INSERT INTO entradavehiculos (placa, entrada, tipo, valor_hora, id_operario_ingreso) "
                  "VALUES (:placa, :entrada, :tipo, :valor, :id_ope)");

    query.bindValue(":placa", v->getPlaca());
    query.bindValue(":entrada", v->getHoraEntrada());
    query.bindValue(":tipo", v->getTipoVehiculo());
    query.bindValue(":valor", valorHora);

    // 4. Usamos el ID del SessionManager en lugar del nombre (String)
    query.bindValue(":id_ope", SessionManager::instance().idActual());

    if (!query.exec()) {
        qDebug() << "Error al registrar entrada en Postgres:" << query.lastError().text();
        return false;
    }

    return true;
}
