#ifndef PRODUCTOMANAGER_H
#define PRODUCTOMANAGER_H
#include "Producto.h"
#include <iostream>
#include <string>
using namespace std;

class ProductoManager {
private:
    string Archivo;
    Producto pro;

public:
    ProductoManager();
    ProductoManager( string Archi);
    bool agregarProducto(ofstream& producto);
    void guardardatos(int id, int idEst, double precio, string name, string descrip);
    bool modificarProducto(const Producto& producto);
    bool eliminarProducto(int id);
    bool leer_archivo(ifstream& producto);
    int getBytes();
    Producto buscarProductoPorId(int id);
};

#endif // PRODUCTOMANAGER_H
