#include "ListaProductos.h"
#include <iostream>

ListaProductos::ListaProductos(const string& filename) : cabeza(nullptr) {
    ProductoManager productoManager(filename);
    vector<Producto> productos = productoManager.obtenerTodosProductos();

    for (const Producto& producto : productos) {
        agregarProducto(producto);
    }
}

ListaProductos::~ListaProductos() {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        NodoProducto* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaProductos::agregarProducto(const Producto& producto) {
    NodoProducto* nuevoNodo = new NodoProducto(producto);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

void ListaProductos::imprimirProductos() const {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->producto.getId() << ", Nombre: " << actual->producto.getNombre() << ", Precio: " << actual->producto.getPrecio() << endl;
        actual = actual->siguiente;
    }
}

NodoProducto* ListaProductos::getCabeza() const {
    return cabeza;
}
