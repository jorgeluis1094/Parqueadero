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

    // 3. Evaluar el resultado
    if (!validacionExitosa) {
        QMessageBox::warning(nullptr, "Licencia Inválida",
                             "El sistema no pudo ser validado:\n" + mensajeError);
        ConexionPostgres::instancia().cerrar();
        return 0; // Se cierra el programa antes de mostrar la MainWindow
    }

    // 4. Si todo está OK, mostrar la ventana principal
    MainWindow w;
    w.show();

    int resultado = a.exec();

    // Al cerrar el programa, cerrar la conexión a la base de datos
    ConexionPostgres::instancia().cerrar();

    return resultado;
}
