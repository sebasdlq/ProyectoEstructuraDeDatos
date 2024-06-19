#include "EstablecimientoManager.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

EstablecimientoManager::EstablecimientoManager(const std::string& filename) : cabeza(nullptr), filename(filename) {
    cargarDesdeArchivo();
}

EstablecimientoManager::~EstablecimientoManager() {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        NodoEstablecimiento* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    guardarEnArchivo();
}

bool EstablecimientoManager::agregarEstablecimiento(const Establecimiento& establecimiento) {
    NodoEstablecimiento* nuevoNodo = new NodoEstablecimiento(establecimiento);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    }
    else {
        NodoEstablecimiento* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    guardarEnArchivo();
    return true;
}

bool EstablecimientoManager::modificarEstablecimiento(const Establecimiento& establecimiento) {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        if (actual->establecimiento.getId() == establecimiento.getId()) {
            actual->establecimiento = establecimiento;
            guardarEnArchivo();
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool EstablecimientoManager::eliminarEstablecimiento(int id) {
    NodoEstablecimiento* actual = cabeza;
    NodoEstablecimiento* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->establecimiento.getId() == id) {
            if (anterior == nullptr) {
                cabeza = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            guardarEnArchivo();
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorId(int id) {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        if (actual->establecimiento.getId() == id) {
            return actual->establecimiento;
        }
        actual = actual->siguiente;
    }
    throw std::runtime_error("Establecimiento no encontrado");
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorEmail(const std::string& email) {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        if (actual->establecimiento.getEmail() == email) {
            return actual->establecimiento;
        }
        actual = actual->siguiente;
    }
    throw std::runtime_error("Establecimiento no encontrado");
}

Establecimiento EstablecimientoManager::buscarEstablecimientoPorNombre(const std::string& nombre) {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        if (actual->establecimiento.getNombre() == nombre) {
            return actual->establecimiento;
        }
        actual = actual->siguiente;
    }
    throw std::runtime_error("Establecimiento no encontrado");
}

void EstablecimientoManager::imprimirEstablecimientos() const {
    NodoEstablecimiento* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "ID: " << actual->establecimiento.getId() << ", Nombre: " << actual->establecimiento.getNombre()
            << ", Email: " << actual->establecimiento.getEmail() << ", Contrasena: " << actual->establecimiento.getContrasena()
            << ", Telefono: " << actual->establecimiento.getTelefono() << ", Ubicacion: " << actual->establecimiento.getUbicacion() << std::endl;
        actual = actual->siguiente;
    }
}

void EstablecimientoManager::cargarDesdeArchivo() {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        Establecimiento est;
        while (file.read(reinterpret_cast<char*>(&est), sizeof(Establecimiento))) {
            agregarEstablecimiento(est);
        }
        file.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para leer." << std::endl;
    }
}

void EstablecimientoManager::guardarEnArchivo() const {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        NodoEstablecimiento* actual = cabeza;
        while (actual != nullptr) {
            file.write(reinterpret_cast<const char*>(&actual->establecimiento), sizeof(Establecimiento));
            actual = actual->siguiente;
        }
        file.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
    }
}
