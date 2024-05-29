#include "EstablecimientoManager.h"
#include <fstream>
#include <iostream>

EstablecimientoManager::EstablecimientoManager(const string& filename) : filename(filename) {}

bool EstablecimientoManager::agregarEstablecimiento(const Establecimiento& establecimiento) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&establecimiento), sizeof(Establecimiento));
        file.close();
        return true;
    }
    else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return false;
    }
}

bool EstablecimientoManager::modificarEstablecimiento(const Establecimiento& establecimiento) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (file.is_open()) {
        Establecimiento temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Establecimiento))) {
            if (temp.getId() == establecimiento.getId()) {
                file.seekp(-sizeof(Establecimiento), ios::cur);
                file.write(reinterpret_cast<const char*>(&establecimiento), sizeof(Establecimiento));
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

bool EstablecimientoManager::eliminarEstablecimiento(int id) {
    ifstream file(filename, ios::binary);
    ofstream tempFile("temp.bin", ios::binary);

    if (file.is_open() && tempFile.is_open()) {
        Establecimiento temp;
        bool found = false;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Establecimiento))) {
            if (temp.getId() != id) {
                tempFile.write(reinterpret_cast<const char*>(&temp), sizeof(Establecimiento));
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

Establecimiento EstablecimientoManager::buscarEstablecimientoPorId(int id) {
    ifstream file(filename, ios::binary);
    Establecimiento temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Establecimiento))) {
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
    throw runtime_error("Establecimiento no encontrado");
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorEmail(const string& email) {
    ifstream file(filename, ios::binary);
    Establecimiento temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Establecimiento))) {
            if (temp.getEmail() == email) {
                file.close();
                return temp;
            }
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para buscar por email." << endl;
    }
    throw runtime_error("Establecimiento no encontrado");
}

vector<Establecimiento> EstablecimientoManager::obtenerTodosEstablecimientos() {
    ifstream file(filename, ios::binary);
    vector<Establecimiento> establecimientos;
    Establecimiento temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Establecimiento))) {
            establecimientos.push_back(temp);
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para leer todos los establecimientos." << endl;
    }
    return establecimientos;
}
