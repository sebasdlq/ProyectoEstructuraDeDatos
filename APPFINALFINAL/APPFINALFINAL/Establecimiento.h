#ifndef ESTABLECIMIENTO_H
#define ESTABLECIMIENTO_H

#include <string>

class Establecimiento {
private:
    int id;
    std::string nombre;
    std::string email;
    std::string contrasena;
    std::string telefono;
    std::string ubicacion;

public:
    // Constructor
    Establecimiento();
    Establecimiento(int id, const std::string& nombre, const std::string& email, const std::string& contrasena, const std::string& telefono, const std::string& ubicacion);

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getEmail() const;
    std::string getContrasena() const;
    std::string getTelefono() const;
    std::string getUbicacion() const;

    // Setters
    void setId(int id);
    void setNombre(const std::string& nombre);
    void setEmail(const std::string& email);
    void setContrasena(const std::string& contrasena);
    void setTelefono(const std::string& telefono);
    void setUbicacion(const std::string& ubicacion);
};

#endif // ESTABLECIMIENTO_H
