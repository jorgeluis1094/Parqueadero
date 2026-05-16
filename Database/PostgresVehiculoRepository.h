#ifndef POSTGRESVEHICULOREPOSITORY_H
#define POSTGRESVEHICULOREPOSITORY_H

#include "Database/IVehiculoRepository.h" // Incluye la interfaz
#include "Database/SessionManager.h"

class PostgresVehiculoRepository : public IVehiculoRepository {
public:
    PostgresVehiculoRepository() = default;
    ~PostgresVehiculoRepository() override = default;

    // Aquí "anulamos" (override) el método virtual de la interfaz para darle cuerpo
    bool registrarEntrada(Vehiculo* v, int valorHora) override;
};

#endif // POSTGRESVEHICULOREPOSITORY_H
