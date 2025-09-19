#ifndef RELOJDIGITAL_H
#define RELOJDIGITAL_H

#include <QLCDNumber>

class relojdigital : public QLCDNumber
{
    Q_OBJECT

public:
    relojdigital(QWidget *parent = 0);

public slots:
    void tiempo();
};

#endif // RELOJDIGITAL_H
