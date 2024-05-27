#include "UsuarioManager.h"
#include <fstream>
#include <iostream>

UsuarioManager::UsuarioManager(const string& filename) : filename(filename) {}

bool UsuarioManager::agregarUsuario(const Usuario& usuario) {
    ofstream file(filename, ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&usuario), sizeof(Usuario));
        file.close();
        return true;
    }
    else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return false;
    }
}

bool UsuarioManager::modificarUsuario(const Usuario& usuario) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (file.is_open()) {
        Usuario temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Usuario))) {
            if (temp.getId() == usuario.getId()) {
                file.seekp(-sizeof(Usuario), ios::cur);
                file.write(reinterpret_cast<const char*>(&usuario), sizeof(Usuario));
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

bool UsuarioManager::eliminarUsuario(int id) {
    ifstream file(filename, ios::binary);
    ofstream tempFile("temp.bin", ios::binary);

    if (file.is_open() && tempFile.is_open()) {
        Usuario temp;
        bool found = false;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Usuario))) {
            if (temp.getId() != id) {
                tempFile.write(reinterpret_cast<const char*>(&temp), sizeof(Usuario));
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

Usuario UsuarioManager::buscarUsuarioPorId(int id) {
    ifstream file(filename, ios::binary);
    Usuario temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Usuario))) {
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
    throw runtime_error("Usuario no encontrado");
}

Usuario UsuarioManager::buscarUsuarioPorEmail(const string& email) {
    ifstream file(filename, ios::binary);
    Usuario temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Usuario))) {
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
    throw runtime_error("Usuario no encontrado");
}

vector<Usuario> UsuarioManager::obtenerTodosUsuarios() {
    ifstream file(filename, ios::binary);
    vector<Usuario> usuarios;
    Usuario temp;

    if (file.is_open()) {
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Usuario))) {
            usuarios.push_back(temp);
        }
        file.close();
    }
    else {
        cerr << "No se pudo abrir el archivo para leer todos los usuarios." << endl;
    }
    return usuarios;
}
