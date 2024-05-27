#pragma once

#include "ABMClientes.h"
#include "ABMEstablecimientos.h"    
#include <iostream>
#include <string>
#include <fstream>

#define CLIENTES_ARCHIVO "clientes"
#define ESTABLECIMIENTOS_ARCHIVO "establecimiento"

using namespace std;

class Sesion {
private:
    ABMClientes* abmClientes;
    ABMEstablecimiento* abmEstablecimientos;
    Clientes* cliente;
    Establecimiento* establecimiento;
    char tipousuario;
    bool inicio;

public:
    Sesion() : inicio(false) {
        abmClientes = new ABMClientes(CLIENTES_ARCHIVO, 'C');
        abmEstablecimientos = new ABMEstablecimiento(ESTABLECIMIENTOS_ARCHIVO, 'E');
        cliente = new Clientes();
        establecimiento = new Establecimiento();
    }

    bool iniciarSesion() {
        string correo, contraseña;
        unsigned int pos;

        cout << "Ingrese su correo: ";
        getline(cin, correo);

        cout << "Ingrese su contraseña: ";
        getline(cin, contraseña);

        //Buscar en clientes
        ifstream fes(abmClientes->getArchivo(), ios::in | ios::binary);
        fes.seekg(5, ios::beg);
        pos = abmClientes->buscarReg(correo);
        if (pos != 0) {
            tipousuario = 'C';
            fes.seekg(pos, ios::beg);
            cliente->leerArchivo(fes);
        }
        fes.close();

        if (pos != 0) {
            fes.open(abmEstablecimientos->getArchivo(), ios::in | ios::binary);
            pos = abmClientes->buscarReg(correo);
            if (pos != 0) {
                tipousuario = 'E';
                fes.seekg(pos, ios::beg);
                establecimiento->leerArchivo(fes);
            }
            fes.close();
        }

        if (pos == 0) {
            cout << "Correo o contraseña incorrectos." << endl;
            return false;
        }
        switch (tipousuario)
        {
        case 'C':
            inicio = contraseña == cliente->getContrasena();
            break;
        case 'E':
            inicio = contraseña == establecimiento->getContrasena();
            break;
        default:
            cout << "???????";
            return false;
            break;
        }
        cout << "Bienvenido ";
        if (inicio) {
            switch (tipousuario)
            {
            case 'C':
                cout << cliente->getNombre();
                break;
            case 'E':
                cout << establecimiento->getNombre();
                break;
            default:
                cout << "???????";
                return false;
                break;
            }
        }
        
        return true;
    }

    void accionesVendedor() {
        cout << "Acciones disponibles para vendedor:" << endl;
        int opcion = 0;
        while (true) {
            cout << "\nAcciones disponibles para vendedor:" << endl;
            cout << "1. Agregar comida" << endl;
            cout << "2. Modificar comida" << endl;
            cout << "3. Eliminar comida" << endl;
            cout << "4. Ver lista de comidas" << endl;
            cout << "5. Salir de sesión" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1:
                abmClientes->adicionarNuevo();
                break;
            case 2:
                abmClientes->listar();
                break;
            case 3:
             abmClientes
                break;
            case 4:
                //listadecomidas->MostrarComidas();
                break;
            case 5:
                cout << "Saliendo de sesión..." << endl;
                return;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
            }
        }
    }

    void registrarUsuario() {
        string nombre, apellido, celular, correo, contraseña;
        char tipoUsuario;

        cout << "Registro de nuevo usuario" << endl;

        cout << "Ingrese su nombre: ";
        getline(cin, nombre);

        cout << "Ingrese su apellido: ";
        getline(cin, apellido);

        cout << "Ingrese su celular: ";
        getline(cin, celular);

        cout << "Ingrese su correo: ";
        getline(cin, correo);

        cout << "Ingrese su contraseña: ";
        getline(cin, contraseña);

        cout << "Seleccione el tipo de usuario (u para comprador, v para vendedor): ";
        cin >> tipoUsuario;
        cin.ignore();

        if (tipoUsuario != 'u' && tipoUsuario != 'v') {
            cout << "Tipo de usuario no válido. Registro cancelado." << endl;
            return;
        }

       // abmClientes->getReg_total()++;
        unsigned short identificador = abmClientes->getReg_total();

        cliente->setClientes(identificador, tipoUsuario, nombre, apellido, celular, correo, contraseña);

        ofstream fsalida(abmClientes->getArchivo(), ios::out | ios::binary | ios::app);
        if (fsalida.is_open()) {
            cliente->guardarArchivo(fsalida);
            fsalida.close();
            cout << "Usuario registrado correctamente." << endl;
        }
        else {
            cout << "Error al abrir el archivo para escribir." << endl;
        }

        abmClientes->actualizarCabezera();
    }

    ~Sesion() {
        delete abmClientes;
        delete cliente;
    }
};
