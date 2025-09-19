#include "FuncioneTiempo.h"

double DiferenciaHora(QDateTime HoraBase, QDateTime HoraDiferencia)
{
   return HoraBase.secsTo(HoraDiferencia.currentDateTime());
}

QString HMS2seg(int &Hora, int &Min, int &sec)
{
    QString Tiempo;

    Hora = sec / (60*60);
    sec %= 60*60;
    Min = sec / 60;
    sec %= 60;
    Tiempo=QString::number(Hora)+":"+QString::number(Min)+":"+QString::number(sec);

    return Tiempo;
}


int CobroXMotos(int Hora,int Min, int TMuero, int ValorHora)
{
    int Recargo=0;

    if(Min>TMuero)
       Recargo=1;

    if(Hora==0)
       Recargo=1;

     return (Hora+Recargo)*ValorHora;
}




