#include "EstablecimientoManager.h"
#include <iostream>
#include <stdexcept>

EstablecimientoManager::EstablecimientoManager(const std::string& filename) : filename(filename) {
    numEstablecimientos = 0;
    establecimientos = nullptr;
    cargarDesdeArchivo();
}

EstablecimientoManager::~EstablecimientoManager() {
    guardarEnArchivo();
    delete[] establecimientos;
}

bool EstablecimientoManager::agregarEstablecimiento(const Establecimiento& establecimiento) {
    Establecimiento* nuevosEstablecimientos = new Establecimiento[numEstablecimientos + 1];
    for (int i = 0; i < numEstablecimientos; ++i) {
        nuevosEstablecimientos[i] = establecimientos[i];
    }
    nuevosEstablecimientos[numEstablecimientos] = establecimiento;
    delete[] establecimientos;
    establecimientos = nuevosEstablecimientos;
    ++numEstablecimientos;
    guardarEnArchivo();
    return true;
}

bool EstablecimientoManager::modificarEstablecimiento(const Establecimiento& establecimiento) {
    for (int i = 0; i < numEstablecimientos; ++i) {
        if (establecimientos[i].getId() == establecimiento.getId()) {
            establecimientos[i] = establecimiento;
            guardarEnArchivo();
            return true;
        }
    }
    return false;
}

bool EstablecimientoManager::eliminarEstablecimiento(int id) {
    for (int i = 0; i < numEstablecimientos; ++i) {
        if (establecimientos[i].getId() == id) {
            Establecimiento* nuevosEstablecimientos = new Establecimiento[numEstablecimientos - 1];
            for (int j = 0; j < i; ++j) {
                nuevosEstablecimientos[j] = establecimientos[j];
            }
            for (int j = i; j < numEstablecimientos - 1; ++j) {
                nuevosEstablecimientos[j] = establecimientos[j + 1];
            }
            delete[] establecimientos;
            establecimientos = nuevosEstablecimientos;
            --numEstablecimientos;
            guardarEnArchivo();
            return true;
        }
    }
    return false;
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorId(int id) {
    for (int i = 0; i < numEstablecimientos; ++i) {
        if (establecimientos[i].getId() == id) {
            return establecimientos[i];
        }
    }
    throw std::runtime_error("Establecimiento no encontrado");
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorEmail(const std::string& email) {
    for (int i = 0; i < numEstablecimientos; ++i) {
        if (establecimientos[i].getEmail() == email) {
            return establecimientos[i];
        }
    }
    throw std::runtime_error("Establecimiento no encontrado");
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorNombre(const std::string& nombre) {
    for (int i = 0; i < numEstablecimientos; ++i) {
        if (establecimientos[i].getNombre() == nombre) {
            return establecimientos[i];
        }
    }
    throw std::runtime_error("Establecimiento no encontrado");
}

void EstablecimientoManager::imprimirEstablecimientos() const {
    for (int i = 0; i < numEstablecimientos; ++i) {
        std::cout << "ID: " << establecimientos[i].getId() << ", Nombre: " << establecimientos[i].getNombre()
            << ", Email: " << establecimientos[i].getEmail() << ", Contrasena: " << establecimientos[i].getContrasena()
            << ", Telefono: " << establecimientos[i].getTelefono() << ", Ubicacion: " << establecimientos[i].getUbicacion() << std::endl;
    }
}

void EstablecimientoManager::cargarDesdeArchivo() {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        if (!(file.read(reinterpret_cast<char*>(&numEstablecimientos), sizeof(numEstablecimientos)))) {
            std::cerr << "Error leyendo el número de establecimientos desde el archivo." << std::endl;
            return;
        }

        if (numEstablecimientos > 0) {
            delete[] establecimientos; // Eliminar cualquier dato existente para evitar fugas de memoria
            establecimientos = new Establecimiento[numEstablecimientos];
            for (int i = 0; i < numEstablecimientos; ++i) {
                establecimientos[i].cargarDeStream(file);
                if (file.fail()) {
                    std::cerr << "Error leyendo un establecimiento desde el archivo." << std::endl;
                    return;
                }
            }
        }
        file.close();
        std::cout << "Datos cargados correctamente desde el archivo: " << filename << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
    }
}

void EstablecimientoManager::guardarEnArchivo() const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        if (!(file.write(reinterpret_cast<const char*>(&numEstablecimientos), sizeof(numEstablecimientos)))) {
            std::cerr << "Error escribiendo el número de establecimientos en el archivo." << std::endl;
            return;
        }
        for (int i = 0; i < numEstablecimientos; ++i) {
            establecimientos[i].guardarEnStream(file);
            if (file.fail()) {
                std::cerr << "Error escribiendo un establecimiento en el archivo." << std::endl;
                return;
            }
        }
        file.close();
        std::cout << "Datos guardados correctamente en el archivo: " << filename << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
    }
}
