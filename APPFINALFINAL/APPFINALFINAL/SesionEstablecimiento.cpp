#include "SesionEstablecimiento.h"

SesionEstablecimiento::SesionEstablecimiento(ListaEstablecimientos* lista, EstablecimientoManager* manager)
    : listaEstablecimientos(lista), establecimientoManager(manager), establecimiento(nullptr) {}

bool SesionEstablecimiento::iniciarSesion(const string& email, const string& contrasena) {
    NodoEstablecimiento* actual = listaEstablecimientos->getCabeza();
    while (actual != nullptr) {
        if (actual->establecimiento.getEmail() == email && actual->establecimiento.getContrasena() == contrasena) {
            establecimiento = &actual->establecimiento;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

Establecimiento* SesionEstablecimiento::getEstablecimientoActual() const {
    return establecimiento;
}

void SesionEstablecimiento::cerrarSesion() {
    establecimiento = nullptr;
}

bool SesionEstablecimiento::agregarEstablecimiento(const Establecimiento& establecimiento) {
    return establecimientoManager->agregarEstablecimiento(establecimiento);
}

bool SesionEstablecimiento::modificarEstablecimiento(const Establecimiento& establecimiento) {
    return establecimientoManager->modificarEstablecimiento(establecimiento);
}

bool SesionEstablecimiento::eliminarEstablecimiento(int id) {
    return establecimientoManager->eliminarEstablecimiento(id);
}

Establecimiento SesionEstablecimiento::buscarEstablecimientoPorId(int id) {
    return establecimientoManager->buscarEstablecimientoPorId(id);
}

Establecimiento SesionEstablecimiento::buscarEstablecimientoPorEmail(const string& email) {
    return establecimientoManager->buscarEstablecimientoPorEmail(email);
}

bool SesionEstablecimiento::agregarProducto(const Producto& producto) {
    return establecimientoManager->agregarProducto(*establecimiento, producto);
}

bool SesionEstablecimiento::modificarProducto(const Producto& producto) {
    return establecimientoManager->modificarProducto(*establecimiento, producto);
}

bool SesionEstablecimiento::eliminarProducto(int id) {
    return establecimientoManager->eliminarProducto(*establecimiento, id);
}

Producto SesionEstablecimiento::buscarProductoPorId(int id) {
    return establecimientoManager->buscarProductoPorId(*establecimiento, id);
}
