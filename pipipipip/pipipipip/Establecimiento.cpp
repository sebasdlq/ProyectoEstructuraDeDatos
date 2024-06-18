#include "Establecimiento.h"

Establecimiento::Establecimiento() : id(0), nombre(""), email(""), contrasena(""), telefono(""), ubicacion("") {}

Establecimiento::Establecimiento(int id, const std::string& nombre, const std::string& email, const std::string& contrasena, const std::string& telefono, const std::string& ubicacion)
    : id(id), nombre(nombre), email(email), contrasena(contrasena), telefono(telefono), ubicacion(ubicacion) {}

int Establecimiento::getId() const { return id; }
std::string Establecimiento::getNombre() const { return nombre; }
std::string Establecimiento::getEmail() const { return email; }
std::string Establecimiento::getContrasena() const { return contrasena; }
std::string Establecimiento::getTelefono() const { return telefono; }
std::string Establecimiento::getUbicacion() const { return ubicacion; }

void Establecimiento::setId(int id) { this->id = id; }
void Establecimiento::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Establecimiento::setEmail(const std::string& email) { this->email = email; }
void Establecimiento::setContrasena(const std::string& contrasena) { this->contrasena = contrasena; }
void Establecimiento::setTelefono(const std::string& telefono) { this->telefono = telefono; }
void Establecimiento::setUbicacion(const std::string& ubicacion) { this->ubicacion = ubicacion; }
