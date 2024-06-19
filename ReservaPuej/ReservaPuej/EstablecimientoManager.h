#ifndef ESTABLECIMIENTOMANAGER_H
#define ESTABLECIMIENTOMANAGER_H

#include "Establecimiento.h"
#include <string>

class NodoEstablecimiento {
public:
    Establecimiento establecimiento;
    NodoEstablecimiento* siguiente;

    NodoEstablecimiento(const Establecimiento& establecimiento)
        : establecimiento(establecimiento), siguiente(nullptr) {}
};

class EstablecimientoManager {
private:
    NodoEstablecimiento* cabeza;
    std::string filename;

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
    void cargarDesdeArchivo();
    void guardarEnArchivo() const;
};

#endif // ESTABLECIMIENTOMANAGER_H
