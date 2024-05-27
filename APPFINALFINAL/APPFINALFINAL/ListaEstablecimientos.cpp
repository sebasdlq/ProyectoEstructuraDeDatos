#include "ListaEstablecimientos.h"
#include <iostream>

ListaEstablecimientos::ListaEstablecimientos(const string& filename) : cabeza(nullptr) {
    EstablecimientoManager establecimientoManager(filename);
    vector<Establecimiento> establecimientos = establecimientoManager.obtenerTodosEstablecimientos();

    for (const Establecimiento& establecimiento : establecimientos) {
        agregarEstablecimiento(establecimiento);
    }
}

ListaEstablecimientos::~ListaEstablecimientos() {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        NodoEstablecimiento* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaEstablecimientos::agregarEstablecimiento(const Establecimiento& establecimiento) {
    NodoEstablecimiento* nuevoNodo = new NodoEstablecimiento(establecimiento);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

void ListaEstablecimientos::imprimirEstablecimientos() const {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->establecimiento.getId() << ", Nombre: " << actual->establecimiento.getNombre() << endl;
        actual = actual->siguiente;
    }
}

NodoEstablecimiento* ListaEstablecimientos::getCabeza() const {
    return cabeza;
}
