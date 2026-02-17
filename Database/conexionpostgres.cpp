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
