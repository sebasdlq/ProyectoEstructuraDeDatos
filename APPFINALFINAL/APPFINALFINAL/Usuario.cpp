#include "Usuario.h"

Usuario::Usuario() : id(0), nombre(""), email(""), contrasena(""), telefono("") {}

// Constructor
Usuario::Usuario(int id, const std::string& nombre, const std::string& email, const std::string& contrasena, const std::string& telefono)
    : id(id), nombre(nombre), email(email), contrasena(contrasena), telefono(telefono) {}

// Getters
int Usuario::getId() const { return id; }
std::string Usuario::getNombre() const { return nombre; }
std::string Usuario::getEmail() const { return email; }
std::string Usuario::getContrasena() const { return contrasena; }
std::string Usuario::getTelefono() const { return telefono; }

// Setters
void Usuario::setId(int id) { this->id = id; }
void Usuario::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Usuario::setEmail(const std::string& email) { this->email = email; }
void Usuario::setContrasena(const std::string& contrasena) { this->contrasena = contrasena; }
void Usuario::setTelefono(const std::string& telefono) { this->telefono = telefono; }