#ifndef OPERARIO_H
#define OPERARIO_H
#include "persona.h"
#include <QDate>

class Operario : public Persona
{

public:
    Operario(QString nombre="", QString direccionCasa="", QString telefono="");
    ~Operario();
    void HoraEntrada(QString horaEntrada);
    void HoraSalida(QString horaSalida);
    void TotalRealizado(int totalRealizado);
    void TotalMensualidades(int totalMensualidades);
    void TotalMotos(int totalMotos);
    void TotalCarros(int totalCarros);
    void TotalOtrosArticulos(int totalOtrosArticulos);
    void NumMensualidadesPagadas(int numMensualidadesPagadas);
    void TotalOtrosPagos(int totalOtrosPagos);

    QString getHoraEntrada(void);
    QString getHoraSalida(void);
    int getTotalRealizado(void);

    int getTotalMensualidades(void);
    int getTotalMotos(void);
    int getTotalCarros(void);
    int getTotalOtrosArticulos(void);
    int getNumMensualidadesPagadas(void);
    int getTotalOtrosPagos(void);

private:
    QString horaEntrada;
    QString horaSalida;
    int totalRealizado;
    int totalMotos;
    int totalCarros;
    int totalMensualidades;
    int numMensualidadesPagadas;
    int totalOtrosArticulos;
    int totalOtrosPagos;

};

#endif // OPERARIO_H
