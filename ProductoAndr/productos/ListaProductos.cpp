#include "ListaProductos.h"
#include <iostream>

ListaProductos::ListaProductos(const string& filename) : cabeza(nullptr), filename(filename) {
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

void ListaProductos::modificarProducto(const Producto& producto) {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        if (actual->producto.getId() == producto.getId()) {
            actual->producto = producto; // Actualizamos el producto en la lista
            ProductoManager pm(filename); // Creamos un ProductoManager para actualizar el archivo
            pm.modificarProducto(producto); // Llamamos al m�todo modificarProducto del ProductoManager
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
            return pm.eliminarProducto(id); // Llamamos al m�todo eliminarProducto del ProductoManager
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
    return Producto(); // Retorna un Producto vac�o
}

NodoProducto* ListaProductos::getCabeza() const {
    return cabeza;
}
