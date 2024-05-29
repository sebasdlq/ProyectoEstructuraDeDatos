#include "ListaUsuarios.h"
#include <iostream>

ListaUsuarios::ListaUsuarios(const string& filename) : cabeza(nullptr) {
    UsuarioManager usuarioManager(filename);
    vector<Usuario> usuarios = usuarioManager.obtenerTodosUsuarios();

    for (const Usuario& usuario : usuarios) {
        agregarUsuario(usuario);
    }
}

ListaUsuarios::~ListaUsuarios() {
    NodoUsuario* actual = cabeza;
    while (actual != nullptr) {
        NodoUsuario* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaUsuarios::agregarUsuario(const Usuario& usuario) {
    NodoUsuario* nuevoNodo = new NodoUsuario(usuario);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

void ListaUsuarios::imprimirUsuarios() const {
    NodoUsuario* actual = cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->usuario.getId() << ", Nombre: " << actual->usuario.getNombre() << endl;
        actual = actual->siguiente;
    }
}

NodoUsuario* ListaUsuarios::getCabeza() const {
    return cabeza;
}
