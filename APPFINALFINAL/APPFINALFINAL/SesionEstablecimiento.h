#ifndef SESIONESTABLECIMIENTO_H
#define SESIONESTABLECIMIENTO_H

#include "EstablecimientoManager.h"
#include "ListaEstablecimientos.h"
#include "Producto.h"

using namespace std;

class SesionEstablecimiento {
private:
    Establecimiento* establecimiento;
    ListaEstablecimientos* listaEstablecimientos;
    EstablecimientoManager* establecimientoManager;

public:
    SesionEstablecimiento(ListaEstablecimientos* lista, EstablecimientoManager* manager);
    bool iniciarSesion(const string& email, const string& contrasena);
    Establecimiento* getEstablecimientoActual() const;
    void cerrarSesion();
    // Métodos para redirigir a EstablecimientoManager
    bool agregarEstablecimiento(const Establecimiento& establecimiento);
    bool modificarEstablecimiento(const Establecimiento& establecimiento);
    bool eliminarEstablecimiento(int id);
    Establecimiento buscarEstablecimientoPorId(int id);
    Establecimiento buscarEstablecimientoPorEmail(const string& email);
    // Métodos específicos para establecimientos
    bool agregarProducto(const Producto& producto);
    bool modificarProducto(const Producto& producto);
    bool eliminarProducto(int id);
    Producto buscarProductoPorId(int id);
    // ...
};

#endif // SESIONESTABLECIMIENTO_H

\
