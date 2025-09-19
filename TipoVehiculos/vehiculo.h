#ifndef VEHICULO_H
#define VEHICULO_H
#include <QString>
#include <QDate>

class Vehiculo
{
public:
    //Vehiculo(QString placa, QString tipoVehiculo, QDateTime horaEntrada, QString nomRegIn);
    Vehiculo(QString placa, QString tipoVehiculo, QDateTime horaEntrada, QString nomRegIn, int recargoEntrada=0);
    ~Vehiculo();
    void Placa(QString placa);
    void TipoVehiculo(QString tipoVehiculo);
    void NomRegIn(QString nomRegIn);
    void NomRegOut(QString nomRegOut);
    void TiempoParqueo(QString tiempoParqueo);
    void HoraEntrada(QDateTime horaEntrada);
    void HoraSalida(QDateTime horaSalida);
    void ValorPagado(int valorPagado);
    void RecargoSalida(int recargoSalida);
    void Propietario(QString propietario);
    void Cantidad(double cantidad);


    QString getPlaca(void);
    QString getTipoVehiculo(void);
    QString getNomRegIn(void);
    QString getNomRegOut(void);
    QString getTiempoParqueo(void);
    QDateTime getHoraEntrada(void);
    QString getHoraSalidaString(void);
    QString getHoraEntradaString(void);
    QDateTime getHoraSalida(void);
    QString getPropietario(void);
    int getValorPagado(void);
    int getRecargoEntrada(void);
    int getRecargoSalida(void);
    double getCantidad(void);






private:
    QString placa;
    QString tipoVehiculo;
    QDateTime horaEntrada;
    QDateTime horaSalida;
    int valorPagado;
    QString propietario;

    QString nomRegIn;
    QString nomRegOut;
    QString tiempoParqueo;

    int recargoEntrada;
    int recargoSalida;

    double cantidad;



};

#endif // VEHICULO_H
