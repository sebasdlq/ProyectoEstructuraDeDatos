#include "ListaProductos.h"
#include <iostream>
ListaProductos::ListaProductos(const string& filename) : filename(filename) {}

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
    int n = 0;
    while (actual != nullptr) {
        n++;
        cout << n << ".- ID:" << actual->producto.getId() << ", IDEsta:"<<actual->producto.getIdEstablecimiento() << ", Nombre: " << actual->producto.getNombre() << ", Precio: " << actual->producto.getPrecio() << ", Descrip:"<<actual->producto.getDescripcion()<<"\n";
        actual = actual->siguiente;
    }
}

void ListaProductos::modificarProducto(const Producto& producto) {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        if (actual->producto.getId() == producto.getId()) {
            actual->producto = producto; // Actualizamos el producto en la lista
            ProductoManager pm(filename); // Creamos un ProductoManager para actualizar el archivo
            pm.modificarProducto(producto); // Llamamos al método modificarProducto del ProductoManager
            return;
        }
        actual = actual->siguiente;
    }
    cerr << "Producto no encontrado." << endl;
}

bool ListaProductos::eliminarProducto(int id) {
    NodoProducto* actual = cabeza;
    NodoProducto* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->producto.getId() == id) {
            if (anterior == nullptr) {
                // Si el nodo a eliminar es el primero (cabeza)
                cabeza = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual; // Liberamos la memoria del nodo eliminado

            // Actualizar el archivo usando ProductoManager
            ProductoManager pm(filename);
            return pm.eliminarProducto(id); // Llamamos al método eliminarProducto del ProductoManager
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cerr << "Producto no encontrado." << endl;
    return false;
}

Producto ListaProductos::buscarProductoPorId(int id) {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        if (actual->producto.getId() == id) {
            return actual->producto;
        }
        actual = actual->siguiente;
    }
    cerr << "Producto no encontrado." << endl;
    return Producto(); // Retorna un Producto vacío
}

NodoProducto* ListaProductos::getCabeza() const {
    return cabeza;
}
