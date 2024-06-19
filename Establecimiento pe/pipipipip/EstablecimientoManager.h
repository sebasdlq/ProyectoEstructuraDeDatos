#ifndef ESTABLECIMIENTOMANAGER_H
#define ESTABLECIMIENTOMANAGER_H

#include <fstream>
#include "Establecimiento.h"

class EstablecimientoManager {
private:
    Establecimiento* establecimientos;
    int numEstablecimientos;
    std::string filename;

    void guardarEnArchivo() const;
    void cargarDesdeArchivo();

public:
    EstablecimientoManager(const std::string& filename);
    ~EstablecimientoManager();

    bool agregarEstablecimiento(const Establecimiento& establecimiento);
    bool modificarEstablecimiento(const Establecimiento& establecimiento);
    bool eliminarEstablecimiento(int id);
    Establecimiento buscarEstablecimientoPorId(int id);
    Establecimiento buscarEstablecimientoPorEmail(const std::string& email);
    Establecimiento buscarEstablecimientoPorNombre(const std::string& nombre);
    void imprimirEstablecimientos() const;
};

#endif // ESTABLECIMIENTOMANAGER_H
