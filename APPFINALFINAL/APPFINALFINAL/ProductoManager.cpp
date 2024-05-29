#include "ProductoManager.h"
#include <fstream>
#include <iostream>

ProductoManager::ProductoManager(const string& filename) : filename(filename) {}

bool ProductoManager::agregarProducto(const Producto& producto) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&producto), sizeof(Producto));
        file.close();
        return true;
    }
    else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return false;
    }
}

bool ProductoManager::modificarProducto(const Producto& producto) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (file.is_open()) {
        Producto temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Producto))) {
            if (temp.getId() == producto.getId()) {
                file.seekp(-sizeof(Producto), ios::cur);
                file.write(reinterpret_cast<const char*>(&producto), sizeof(Producto));
                file.close();
                return true;
            }
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para modificar." << endl;
    }
    return false;
}

bool ProductoManager::eliminarProducto(int id) {
    ifstream file(filename, ios::binary);
    ofstream tempFile("temp.bin", ios::binary);

    if (file.is_open() && tempFile.is_open()) {
        Producto temp;
        bool found = false;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Producto))) {
            if (temp.getId() != id) {
                tempFile.write(reinterpret_cast<const char*>(&temp), sizeof(Producto));
            }
            else {
                found = true;
            }
        }
        file.close();
        tempFile.close();
        remove(filename.c_str());
        rename("temp.bin", filename.c_str());
        return found;
    }
    else {
        cerr << "No se pudo abrir el archivo para eliminar." << endl;
        return false;
    }
}

Producto ProductoManager::buscarProductoPorId(int id) {
    ifstream file(filename, ios::binary);
    Producto temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Producto))) {
            if (temp.getId() == id) {
                file.close();
                return temp;
            }
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para buscar por ID." << endl;
    }
    throw runtime_error("Producto no encontrado");
}

vector<Producto> ProductoManager::obtenerTodosProductos() {
    ifstream file(filename, ios::binary);
    vector<Producto> productos;
    Producto temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Producto))) {
            productos.push_back(temp);
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para leer todos los productos." << endl;
    }
    return productos;
}
