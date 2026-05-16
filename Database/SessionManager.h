#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>

class SessionManager {
public:
    static SessionManager& instance() {
        static SessionManager _instance;
        return _instance;
    }

    void login(int id, const QString& nombre) {
        m_idActual = id;
        m_nombreActual = nombre;
        m_isLoggedIn = true;
    }

    void logout() {
        m_idActual = -1;
        m_nombreActual = "";
        m_isLoggedIn = false;
    }

    int idActual() const { return m_idActual; }
    QString usuarioActual() const { return m_nombreActual; }
    bool estaLogueado() const { return m_isLoggedIn; }

private:
    SessionManager() : m_idActual(-1), m_isLoggedIn(false) {}
    int m_idActual;
    QString m_nombreActual;
    bool m_isLoggedIn;
};

#endif // SESSIONMANAGER_H
