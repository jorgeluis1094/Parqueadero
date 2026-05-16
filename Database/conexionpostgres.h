#ifndef CONEXIONPOSTGRES_H
#define CONEXIONPOSTGRES_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>

class ConexionPostgres {
public:
    static ConexionPostgres& instancia() {
        static ConexionPostgres instance;
        return instance;
    }

    bool conectar();
    void cerrar();
    QSqlDatabase db() const { return m_db; }
    bool actualizarEstadoLicenciaLocal(bool estado);
    bool esLicenciaValidaOffline(int horasMaximas = 24*5);


private:
    ConexionPostgres() = default;
    QSqlDatabase m_db;

};

#endif // CONEXIONPOSTGRES_H
