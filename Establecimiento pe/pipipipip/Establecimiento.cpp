#include "Establecimiento.h"
#include <iostream>
#include <fstream>

// Constructor
Establecimiento::Establecimiento() : id(0) {}

Establecimiento::Establecimiento(int id, const std::string& nombre, const std::string& email, const std::string& contrasena, const std::string& telefono, const std::string& ubicacion)
    : id(id), nombre(nombre), email(email), contrasena(contrasena), telefono(telefono), ubicacion(ubicacion) {}

// Getters
int Establecimiento::getId() const { return id; }
std::string Establecimiento::getNombre() const { return nombre; }
std::string Establecimiento::getEmail() const { return email; }
std::string Establecimiento::getContrasena() const { return contrasena; }
std::string Establecimiento::getTelefono() const { return telefono; }
std::string Establecimiento::getUbicacion() const { return ubicacion; }

// Setters
void Establecimiento::setId(int id) { this->id = id; }
void Establecimiento::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Establecimiento::setEmail(const std::string& email) { this->email = email; }
void Establecimiento::setContrasena(const std::string& contrasena) { this->contrasena = contrasena; }
void Establecimiento::setTelefono(const std::string& telefono) { this->telefono = telefono; }
void Establecimiento::setUbicacion(const std::string& ubicacion) { this->ubicacion = ubicacion; }

// Serialización
void Establecimiento::guardarEnStream(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    size_t size = nombre.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(nombre.c_str(), size);
    size = email.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(email.c_str(), size);
    size = contrasena.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(contrasena.c_str(), size);
    size = telefono.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(telefono.c_str(), size);
    size = ubicacion.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size));
    os.write(ubicacion.c_str(), size);
}

void Establecimiento::cargarDeStream(std::istream& is) {
    is.read(reinterpret_cast<char*>(&id), sizeof(id));
    size_t size;
    char* buffer;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    is.read(buffer, size);
    buffer[size] = '\0';
    nombre = buffer;
    delete[] buffer;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    is.read(buffer, size);
    buffer[size] = '\0';
    email = buffer;
    delete[] buffer;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    is.read(buffer, size);
    buffer[size] = '\0';
    contrasena = buffer;
    delete[] buffer;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    is.read(buffer, size);
    buffer[size] = '\0';
    telefono = buffer;
    delete[] buffer;
    is.read(reinterpret_cast<char*>(&size), sizeof(size));
    buffer = new char[size + 1];
    is.read(buffer, size);
    buffer[size] = '\0';
    ubicacion = buffer;
    delete[] buffer;
}

std::istream& operator>>(std::istream& is, Establecimiento& establecimiento) {
    is.read(reinterpret_cast<char*>(&establecimiento.id), sizeof(establecimiento.id));
    is >> std::ws;
    std::getline(is, establecimiento.nombre, '\0');
    std::getline(is, establecimiento.email, '\0');
    std::getline(is, establecimiento.contrasena, '\0');
    std::getline(is, establecimiento.telefono, '\0');
    std::getline(is, establecimiento.ubicacion, '\0');
    return is;
}

std::ostream& operator<<(std::ostream& os, const Establecimiento& establecimiento) {
    os.write(reinterpret_cast<const char*>(&establecimiento.id), sizeof(establecimiento.id));
    os.write(establecimiento.nombre.c_str(), establecimiento.nombre.size() + 1);
    os.write(establecimiento.email.c_str(), establecimiento.email.size() + 1);
    os.write(establecimiento.contrasena.c_str(), establecimiento.contrasena.size() + 1);
    os.write(establecimiento.telefono.c_str(), establecimiento.telefono.size() + 1);
    os.write(establecimiento.ubicacion.c_str(), establecimiento.ubicacion.size() + 1);
    return os;
}
