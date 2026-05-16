#include <QApplication>
#include <QMessageBox>
#include <QEventLoop>
#include "mainwindow.h"
#include "Database/conexionpostgres.h"
#include "Network/licenciamanager.h"

// Función auxiliar para obtener el ID de hardware (puedes moverla a una utilidad luego)
#include <QFile>
#include <QTextStream>
QString obtenerHWID() {
    QFile file("/var/lib/dbus/machine-id");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return "UNKNOWN_VOSTRO";
    QTextStream in(&file);
    return in.readLine().trimmed();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. Intentar conectar a la Base de Datos Local (Postgres)
    if (!ConexionPostgres::instancia().conectar()) {
        QMessageBox::critical(nullptr, "Error de Base de Datos",
                              "No se pudo conectar con la base de datos local del parqueadero.");
        return -1;
    }

    // 2. Iniciar validación de licencia con la API (Python/FastAPI)
    LicenciaManager licencia;
    QEventLoop loop; // Bucle temporal para esperar la respuesta de red

    bool validacionExitosa = false;
    QString mensajeError = "Error desconocido";

    // Conectar la señal del manager al bucle para que termine de esperar
    QObject::connect(&licencia, &LicenciaManager::resultadoValidacion,
                     [&](bool exito, QString mensaje) {
                         validacionExitosa = exito;
                         mensajeError = mensaje;
                         loop.quit(); // Desbloquea el main
                     });

    // Lanzar la petición (Aquí deberías leer la KEY de un archivo de config o de la DB local)
    QString keyDePrueba = "CLAVE-PRUEBA-001";
    licencia.solicitarValidacion(keyDePrueba, obtenerHWID());

    // El programa se queda aquí hasta que la API responda o el tiempo expire
    loop.exec();

    if (!validacionExitosa) {
        // Si la API falló por "Servidor no disponible" (error de red)
        if (mensajeError == "Servidor central no disponible.") {
            if (ConexionPostgres::instancia().esLicenciaValidaOffline(24*5)) { // Damos 48h de gracia
                QMessageBox::information(nullptr, "Modo Offline",
                                         "Sin conexión al servidor central. Trabajando con caché local (Modo Contingencia).");
                validacionExitosa = true;
            } else {
                QMessageBox::critical(nullptr, "Error de Validación",
                                      "No hay conexión a internet y el periodo de gracia offline ha expirado. Por favor, conéctese a la red.");
            }
        } else {
            // Si la API respondió pero dijo "DENEGADO" (Licencia vencida o HWID incorrecto)
            QMessageBox::warning(nullptr, "Acceso Denegado", mensajeError);
            ConexionPostgres::instancia().actualizarEstadoLicenciaLocal(false);
        }
    } else {
        // Si la validación por API fue exitosa, refrescamos el caché local
        ConexionPostgres::instancia().actualizarEstadoLicenciaLocal(true);
    }

    if (validacionExitosa) {
        MainWindow w;
        w.show();
        return a.exec();
    }
}
