#ifndef LISTAPRODUCTOS_H
#define LISTAPRODUCTOS_H

#include "Producto.h"
#include "ProductoManager.h"
#include <string>
#include <iostream>
using namespace std;

struct NodoProducto {
    Producto producto;
    NodoProducto* siguiente;

    NodoProducto(const Producto& producto) : producto(producto), siguiente(nullptr) {}
};

class ListaProductos {
private:
    NodoProducto* cabeza;
    string filename;

public:
    ListaProductos(const string& filename);
    ~ListaProductos();
    void agregarProducto(const Producto& producto);
    void imprimirProductos() const;
    void modificarProducto(const Producto& producto);
    bool eliminarProducto(int id);
    Producto buscarProductoPorId(int id);
    NodoProducto* getCabeza() const;
};

#endif // LISTAPRODUCTOS_H
