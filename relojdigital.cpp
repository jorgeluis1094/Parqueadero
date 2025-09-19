#include <QtGui>
#include "relojdigital.h"

relojdigital::relojdigital(QWidget *parent)
    : QLCDNumber(parent)

{
    setSegmentStyle(Filled);

    QTimer *temporalizador = new QTimer(this);
    connect(temporalizador, SIGNAL(timeout()), this, SLOT(tiempo()));
    temporalizador->start(1000);

    tiempo();

    setWindowTitle("Reloj Digital");
    resize(150, 60);
}

void relojdigital::tiempo()
{
    QTime tiempo = QTime::currentTime();
    QString texto = tiempo.toString("hh:mm");
    if ((tiempo.second() % 2) == 0)
            texto[2] = ' ';

    display(texto);
}
