#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "relojdigital.h"
#include "FuncioneTiempo.h"
#include "TipoVehiculos/vehiculo.h"
#include "TipoPersona/clientemensualidad.h"
#include "TipoPersona/operario.h"
#include "ManejoTablas.h"

#include <QPainter>
#include <QPrinter>
#include <QtSql>
#include <QDate>
#include <QRadioButton>
#include <QVector>
#include <QPageLayout>
#include <QPageSize>
#include <QMarginsF>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void imprimir(int tipoRecibo);
    void printDocument(QPrinter *printer, int tipoRecibo);
    QString seg2time(double seg, double &ValorAPagar);
    void NuevoOperario(QString Nombre, bool Registrado);
    void RefrescarTablas();
    void CrearTablas();
    void ConectarTablas();
    void initInterfaz();

private slots:

    void on_pushButtonRegistrar_clicked();

    void on_lineEditRegInOut_returnPressed();

    void on_pushButtonLogin_clicked();

    void on_pushButtonEntrega_clicked();

    void setUsuario(QString Nombre);

    void imprimirReciboTabla1(void);

    void imprimirReciboTabla2(void);

    void imprimirReciboTablaOtros(void);

    void on_lineEditRegPago_editingFinished();

    void on_pushButtonRegPago_clicked();

    void on_comboBoxVerMensualidad_currentIndexChanged(int index);

    void on_tableInOutCar_doubleClicked(const QModelIndex &index);

    void on_cB_Productos_currentTextChanged(const QString &arg1);

    void on_pB_VentaOtroProducto_clicked();


    void on_lineEditFiltarmensualidad_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase  db;
    QSqlTableModel *modelUno, *modelDos,*modelTres, *modeloTablaProductos;
    QFile File;
    QTextStream out;
    QString TipoVehiculo;
    QString OperarioTurno;
    //QDateTime *HoraEntrada;

    int valorHoraMoto;
    int valorLavada1;
    int valorLavada2;
    //int valorNocheOtro;
    int valorMaxPagar;

    int DineroTurno;

    QLineEdit *LineLogin;
    QLineEdit *lineEditsRE;
    QDialog *WinLogin;
    QDialog *ReciboTablas;

    bool impCopia;

    //

    Vehiculo* vehiculo;
    //Datos del Parqueadero
    QString NombreParqueadero;
    QString direccionParqueadero;
    QString telefonoParqueadero;
    QString propietarioParqueadero;
    QString nITParquieadero;
    QString reglamentoParqueadero;
    QString imagenDerecha;
    QString imagenIzquierda;



    QDateTime HoraUmbralD;
    QDateTime HoraUmbralN;
    int hhUmbralD,MMUmbralD,ssUmbralD;
    int hhUmbralN,MMUmbralN,ssUmbralN;

    Operario* trabajador;

    QVector<QString> VecTipoVeh;



};

#endif // MAINWINDOW_H
