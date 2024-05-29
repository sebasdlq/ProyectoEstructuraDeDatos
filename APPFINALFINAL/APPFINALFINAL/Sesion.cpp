#include "Sesion.h"

NodoUsuario* Sesion::buscarUsuarioPorEmail(ListaUsuarios& listaUsuarios, const string& email) {
    NodoUsuario* actual = listaUsuarios.getCabeza();
    while (actual != nullptr) {
        if (actual->usuario.getEmail() == email) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr; // Si no se encuentra el usuario, devuelve nullptr
}

NodoEstablecimiento* Sesion::buscarEstablecimientoPorEmail(ListaEstablecimientos& listaEstablecimientos, const string& email) {
    NodoEstablecimiento* actual = listaEstablecimientos.getCabeza();
    while (actual != nullptr) {
        if (actual->establecimiento.getEmail() == email) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr; // Si no se encuentra el establecimiento, devuelve nullptr
}
