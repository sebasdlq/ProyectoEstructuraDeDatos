
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
        string nombre, contrase�a;

        cout << "Ingrese su nombre: ";
        getline(cin, nombre);

        cout << "Ingrese su contrase�a: ";
        getline(cin, contrase�a);

        ifstream fes(abmClientes->getArchivo(), ios::in | ios::binary);
        fes.seekg(5, ios::beg); 

        while (cliente->leerArchivo(fes)) {
            if (cliente->getNombre() == nombre && cliente->getContrasena() == contrase�a) {
                tipousuario = cliente->getEstado();
                inicio = true;
                fes.close();
                cout << "Inicio de sesi�n exitoso." << endl;
                return true;
            }
        }

       fes.close();
        cout << "Nombre o contrase�a incorrectos." << endl;
        return false;
    }

    void realizarAcciones() {
        if (!inicio) {
            cout << "Debe iniciar sesi�n primero." << endl;
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
        // Aqu� puedes agregar las acciones espec�ficas para los usuarios.
        // Por ejemplo: ver sus propios datos, cambiar su contrase�a, etc.
        // Implementar l�gica espec�fica para los usuarios aqu�
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
            cout << "5. Salir de sesi�n" << endl;
            cout << "Seleccione una opci�n: ";
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
                cout << "Saliendo de sesi�n..." << endl;
                return;
            default:
                cout << "Opci�n no v�lida. Intente de nuevo." << endl;
            }
        }
    }

    void registrarUsuario() {
        string nombre, apellido, celular, correo, contrase�a;
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

        cout << "Ingrese su contrase�a: ";
        getline(cin, contrase�a);

        cout << "Seleccione el tipo de usuario (u para comprador, v para vendedor): ";
        cin >> tipoUsuario;
        cin.ignore();

        if (tipoUsuario != 'u' && tipoUsuario != 'v') {
            cout << "Tipo de usuario no v�lido. Registro cancelado." << endl;
            return;
        }

        abmClientes->getReg_total()++; 
        unsigned short identificador = abmClientes->getReg_total();

        cliente->setClientes(identificador, tipoUsuario, nombre, apellido, celular, correo, contrase�a);

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

