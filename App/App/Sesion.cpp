
#include "ABMClientes.h"
#include <iostream>
#include <string>
#include <fstream>
#include "ListaDeComidas.h"

using namespace std;

class Sesion {
private:
    ABMClientes* abmClientes;
    Clientes* cliente;
    char tipousuario;
    bool inicio;
    ListaDeComidas* listadecomidas;

public:
    Sesion(string tabla, char marca) : inicio(false) {
        abmClientes = new ABMClientes(tabla, marca);
        cliente = new Clientes();
    }

    bool iniciarSesion() {
        string nombre, contraseña;

        cout << "Ingrese su nombre: ";
        getline(cin, nombre);

        cout << "Ingrese su contraseña: ";
        getline(cin, contraseña);

        ifstream fes(abmClientes->getArchivo(), ios::in | ios::binary);
        fes.seekg(5, ios::beg); 

        while (cliente->leerArchivo(fes)) {
            if (cliente->getNombre() == nombre && cliente->getContrasena() == contraseña) {
                tipousuario = cliente->getEstado();
                inicio = true;
                fes.close();
                cout << "Inicio de sesión exitoso." << endl;
                return true;
            }
        }

       fes.close();
        cout << "Nombre o contraseña incorrectos." << endl;
        return false;
    }

    void realizarAcciones() {
        if (!inicio) {
            cout << "Debe iniciar sesión primero." << endl;
            return;
        }

        if (tipousuario == 'u') {
            accionesUsuario();
        }
        else if (tipousuario == 'v') {
            accionesVendedor();
        }
        else {
            cout << "Tipo de usuario desconocido." << endl;
        }
    }

    void accionesUsuario() {
        cout << "Acciones disponibles para usuario:" << endl;
        // Aquí puedes agregar las acciones específicas para los usuarios.
        // Por ejemplo: ver sus propios datos, cambiar su contraseña, etc.
        // Implementar lógica específica para los usuarios aquí
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
                
                break;
            case 2:
               
                break;
            case 3:
                listadecomidas->eliminar();
                break;
            case 4:
                listadecomidas->MostrarComidas();
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

        abmClientes->getReg_total()++; 
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

