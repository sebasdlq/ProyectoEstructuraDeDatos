#ifndef USUARIOMANAGER_H
#define USUARIOMANAGER_H

#include "Usuario.h"
#include <vector>
#include <string>

using namespace std;

class UsuarioManager {
private:
    string filename;

public:
    UsuarioManager(const string& filename);
    bool agregarUsuario(const Usuario& usuario);
    bool modificarUsuario(const Usuario& usuario);
    bool eliminarUsuario(int id);
    Usuario buscarUsuarioPorId(int id);
    Usuario buscarUsuarioPorEmail(const string& email);
    vector<Usuario> obtenerTodosUsuarios();
};

#endif // USUARIOMANAGER_H
