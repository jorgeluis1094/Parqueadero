#include "conexionpostgres.h"

bool ConexionPostgres::conectar() {
    m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db.setHostName("127.0.0.1");
    m_db.setDatabaseName("parqueadero_sedecero");
    m_db.setUserName("lynx_dev");
    m_db.setPassword("lynx1094"); // La que validamos en DBeaver
    m_db.setPort(5432);

    if (!m_db.open()) {
        qDebug() << "Error conectando a Postgres:" << m_db.lastError().text();
        return false;
    }
    qDebug() << "Conexión exitosa a PostgreSQL local";
    return true;
}

void ConexionPostgres::cerrar() {
    m_db.close();
}

bool ConexionPostgres::actualizarEstadoLicenciaLocal(bool estado) {
    QSqlQuery query;
    query.prepare("UPDATE control_licencia SET ultimo_check = :ahora, estado_local = :estado WHERE id_licencia = 1");
    query.bindValue(":ahora", QDateTime::currentDateTime());
    query.bindValue(":estado", estado);
    return query.exec();
}

bool ConexionPostgres::esLicenciaValidaOffline(int horasMaximas) {
    QSqlQuery query("SELECT ultimo_check, estado_local FROM control_licencia WHERE id_licencia = 1");
    if (query.next()) {
        QDateTime ultimoCheck = query.value(0).toDateTime();
        bool estadoLocal = query.value(1).toBool();

        if (!estadoLocal) return false;

        qint64 horasDesdeUltimoCheck = ultimoCheck.secsTo(QDateTime::currentDateTime()) / 3600;
        return (horasDesdeUltimoCheck <= horasMaximas);
    }
    return false;
}
