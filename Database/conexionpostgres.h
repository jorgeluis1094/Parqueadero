#ifndef CONEXIONPOSTGRES_H
#define CONEXIONPOSTGRES_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class ConexionPostgres {
public:
    static ConexionPostgres& instancia() {
        static ConexionPostgres instance;
        return instance;
    }

    bool conectar();
    void cerrar();
    QSqlDatabase db() const { return m_db; }

private:
    ConexionPostgres() = default;
    QSqlDatabase m_db;
};

#endif // CONEXIONPOSTGRES_H
