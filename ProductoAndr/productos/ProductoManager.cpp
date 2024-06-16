#include "ProductoManager.h"
#include <fstream>
#include <iostream>

ProductoManager::ProductoManager(const string& filename) : filename(filename) {}

bool ProductoManager::agregarProducto(const Producto& producto) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        int id = producto.getId();
        int idEstablecimiento = producto.getIdEstablecimiento();
        size_t nombreLength = producto.getNombre().size();
        size_t descripcionLength = producto.getDescripcion().size();
        double precio = producto.getPrecio();

        file.write(reinterpret_cast<const char*>(&id), sizeof(id));
        file.write(reinterpret_cast<const char*>(&idEstablecimiento), sizeof(idEstablecimiento));
        file.write(reinterpret_cast<const char*>(&nombreLength), sizeof(nombreLength));
        file.write(producto.getNombre().c_str(), nombreLength);
        file.write(reinterpret_cast<const char*>(&descripcionLength), sizeof(descripcionLength));
        file.write(producto.getDescripcion().c_str(), descripcionLength);
        file.write(reinterpret_cast<const char*>(&precio), sizeof(precio));

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
                file.seekp(sizeof(Producto), ios::cur);
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

    if (file.is_open()) {
        while (true) {
            int id, idEstablecimiento;
            size_t nombreLength, descripcionLength;
            double precio;

            file.read(reinterpret_cast<char*>(&id), sizeof(id));
            if (file.eof()) break;
            file.read(reinterpret_cast<char*>(&idEstablecimiento), sizeof(idEstablecimiento));
            file.read(reinterpret_cast<char*>(&nombreLength), sizeof(nombreLength));
            string nombre(nombreLength, ' ');
            file.read(&nombre[0], nombreLength);
            file.read(reinterpret_cast<char*>(&descripcionLength), sizeof(descripcionLength));
            string descripcion(descripcionLength, ' ');
            file.read(&descripcion[0], descripcionLength);
            file.read(reinterpret_cast<char*>(&precio), sizeof(precio));

            productos.emplace_back(id, idEstablecimiento, nombre, descripcion, precio);
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para leer todos los productos." << endl;
    }
    return productos;
}
