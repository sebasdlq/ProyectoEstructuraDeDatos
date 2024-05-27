#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include "Usuario.h"
#include "UsuarioManager.h"
#include <string>

using namespace std;

struct NodoUsuario {
    Usuario usuario;
    NodoUsuario* siguiente;

    NodoUsuario(const Usuario& usuario) : usuario(usuario), siguiente(nullptr) {}
};

class ListaUsuarios {
private:
    NodoUsuario* cabeza;

public:
    ListaUsuarios(const string& filename);
    ~ListaUsuarios();

    void agregarUsuario(const Usuario& usuario);
    void imprimirUsuarios() const;
    NodoUsuario* getCabeza() const;
};

#endif // LISTAUSUARIOS_H
