#ifndef ESTABLECIMIENTOMANAGER_H
#define ESTABLECIMIENTOMANAGER_H

#include "Establecimiento.h"
#include <vector>
#include <string>

using namespace std;

class EstablecimientoManager {
private:
    string filename;

public:
    EstablecimientoManager(const string& filename);
    bool agregarEstablecimiento(const Establecimiento& establecimiento);
    bool modificarEstablecimiento(const Establecimiento& establecimiento);
    bool eliminarEstablecimiento(int id);
    Establecimiento buscarEstablecimientoPorId(int id);
    Establecimiento buscarEstablecimientoPorEmail(const string& email);
    vector<Establecimiento> obtenerTodosEstablecimientos();
};

#endif // ESTABLECIMIENTOMANAGER_H
