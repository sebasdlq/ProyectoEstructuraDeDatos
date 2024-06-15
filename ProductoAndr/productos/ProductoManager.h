#ifndef PRODUCTOMANAGER_H
#define PRODUCTOMANAGER_H
#include "Producto.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ProductoManager {
private:
    string filename;

public:
    ProductoManager(const string& filename);
    bool agregarProducto(const Producto& producto);
    bool modificarProducto(const Producto& producto);
    bool eliminarProducto(int id);
    Producto buscarProductoPorId(int id);
    vector<Producto> obtenerTodosProductos();
};

#endif // PRODUCTOMANAGER_H
