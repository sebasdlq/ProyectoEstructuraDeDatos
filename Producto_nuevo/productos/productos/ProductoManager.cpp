#include "ProductoManager.h"
#include <fstream>
#include <iostream>

using namespace std;
ProductoManager::ProductoManager() { Archivo = " "; }

ProductoManager::ProductoManager(string Archi) { Archivo = Archi; }

bool ProductoManager::agregarProducto(ofstream& producto) {
    ofstream file(Archivo, ios::binary | ios::app);
    if (file.is_open()) {
        int id = pro.getId();
        int idEstablecimiento = pro.getIdEstablecimiento();
        size_t nombreLength = pro.getNombre().size();
        size_t descripcionLength = pro.getDescripcion().size();
        double precio = pro.getPrecio();

        producto.write(reinterpret_cast<const char*>(&id), sizeof(id));
        producto.write(reinterpret_cast<const char*>(&idEstablecimiento), sizeof(idEstablecimiento));
        producto.write(reinterpret_cast<const char*>(&nombreLength), sizeof(nombreLength));
        producto.write(pro.getNombre().c_str(), nombreLength);
        producto.write(reinterpret_cast<const char*>(&descripcionLength), sizeof(descripcionLength));
        producto.write(pro.getDescripcion().c_str(), descripcionLength);
        producto.write(reinterpret_cast<const char*>(&precio), sizeof(precio));

        producto.close();
        return true;
    }
    else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return false;
    }
}
void ProductoManager::guardardatos(int id, int idEst, double precio, string name, string descrip) {
    pro.setgeneralP(id, idEst, name, descrip, precio);
}

bool ProductoManager::leer_archivo(ifstream& producto){
    bool k = false;
    int id1 = pro.getId();
    int idEst = pro.getIdEstablecimiento();
    string nom = pro.getNombre();
    string descrip = pro.getDescripcion();
    double precio = pro.getPrecio();
    char estat = pro.getEstado();
    if (producto.is_open() == true) {
        producto.read(reinterpret_cast<char*>(&id1), sizeof(id1));
        if (producto.eof() == false) {
            producto.read(reinterpret_cast<char*>(&idEst), sizeof(idEst));
            producto.read(reinterpret_cast<char*>(&nom), sizeof(nom));
            producto.read(reinterpret_cast<char*>(&descrip), sizeof(descrip));
            producto.read(reinterpret_cast<char*>(&precio), sizeof(precio));
            producto.read(reinterpret_cast<char*>(&estat), sizeof(estat));
            k = true;
        }
        else {
            cerr << endl << "Registro no existe";
        }
    }
    else {
        cerr << endl << "Arhivo no existe";
    }
    return(k);
}

bool ProductoManager::modificarProducto(const Producto& producto) {
    fstream file("Producto.dat", ios::binary | ios::in | ios::out);
    if (file.is_open()) {
        Producto temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Producto))) {
            if (temp.getId() == producto.getId()) {
                file.seekp(-static_cast<int>(sizeof(Producto)), ios::cur);
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
    ifstream file(Archivo, ios::binary | ios::in | ios:: out);
    ofstream tempFile("temp.bin", ios::binary | ios::in | ios::out);

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
        remove(Archivo.c_str());
        rename("temp.bin", Archivo.c_str());
        return found;
    }
    else {
        cerr << "No se pudo abrir el archivo para eliminar." << endl;
        return false;
    }
}

Producto ProductoManager::buscarProductoPorId(int id) {
    ifstream file(Archivo, ios::binary);
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
    cerr << "Producto no encontrado" << endl;
    return Producto(); // Retorna un Producto vacío
}
int ProductoManager::getBytes() {
    return(sizeof(pro.getNombre()) + sizeof(pro.getId()) + sizeof(pro.getIdEstablecimiento()) + sizeof(pro.getDescripcion()) + sizeof(pro.getPrecio()) + sizeof(pro.getEstado()));
}