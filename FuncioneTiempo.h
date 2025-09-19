#ifndef FUNCIONETIEMPO_H
#define FUNCIONETIEMPO_H
#include <QDate>

double DiferenciaHora(QDateTime HoraBase, QDateTime HoraDiferencia);

QString HMS2seg(int &Hora, int &Min , int &sec);

int CobroXMotos(int Hora, int Min, int TMuero, int ValorHora);


#endif // FUNCIONETIEMPO_H
