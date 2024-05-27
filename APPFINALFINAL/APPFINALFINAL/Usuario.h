#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    int id;
    std::string nombre;
    std::string email;
    std::string contrasena;
    std::string telefono;

public:
    // Constructor
    Usuario();
    Usuario(int id, const std::string& nombre, const std::string& email, const std::string& contrasena, const std::string& telefono);

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getEmail() const;
    std::string getContrasena() const;
    std::string getTelefono() const;

    // Setters
    void setId(int id);
    void setNombre(const std::string& nombre);
    void setEmail(const std::string& email);
    void setContrasena(const std::string& contrasena);
    void setTelefono(const std::string& telefono);
};

#endif // USUARIO_H