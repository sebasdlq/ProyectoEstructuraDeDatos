#ifndef LISTAPRODUCTOS_H
#define LISTAPRODUCTOS_H

#include "Producto.h"
#include "ProductoManager.h"
#include <string>

using namespace std;

struct NodoProducto {
    Producto producto;
    NodoProducto* siguiente;

    NodoProducto(const Producto& producto) : producto(producto), siguiente(nullptr) {}
};

class ListaProductos {
private:
    NodoProducto* cabeza;

public:
    ListaProductos(const string& filename);
    ~ListaProductos();

    void agregarProducto(const Producto& producto);
    void imprimirProductos() const;
    NodoProducto* getCabeza() const;
};

#endif // LISTAPRODUCTOS_H
