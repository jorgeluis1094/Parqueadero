#ifndef IVEHICULOREPOSITORY_H
#define IVEHICULOREPOSITORY_H

#include "TipoVehiculos/vehiculo.h" // Asegúrate de que esta ruta sea correcta
#include <QString>

class IVehiculoRepository {
public:
    virtual ~IVehiculoRepository() {}
    // El "Contrato": Cualquier repositorio de vehículos debe saber registrar una entrada
    virtual bool registrarEntrada(Vehiculo* v, int valorHora) = 0;
};

#endif // IVEHICULOREPOSITORY_H
