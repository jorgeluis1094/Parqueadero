#ifndef PERSONA_H
#define PERSONA_H
#include <QString>

class Persona
{
public:
    Persona(QString nombre, QString direccionCasa, QString telefono);
    ~Persona();

    void Nombre(QString nombre);
    void DireccionCasa(QString direccionCasa);
    void Telefono(QString telefono);

    QString getNombre(void);

private:
    QString nombre;
    QString direccionCasa;
    QString telefono;
};

#endif // PERSONA_H
