#include <iostream>
#include <string>
#include "SistemaYListaEspera.h"
#include "WhatsAppMessenger.h"
using namespace std;

ListaEspera::ListaEspera(string n, string t, int l, int i, bool notif)
    : nombre(n), telefono(t), lugares(l), id(i), notificado(notif), siguiente(nullptr) {}

SistemaReservas::SistemaReservas() : clientes(nullptr), mesas(nullptr), listaEspera(nullptr), idEspera(1) {
    inicializarMesas();
}

void SistemaReservas::inicializarMesas() {
    string nombresMesas[] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10"};
    int lugaresMesas[] = {4, 4, 2, 6, 8, 3, 5, 4, 2, 7};
    for (int i = 0; i < 10; ++i) {
        agregarMesa(nombresMesas[i], lugaresMesas[i]);
    }
}

void SistemaReservas::agregarCliente(string nombre, string apellido, string correo, string telefono) {
    Cliente* nuevo = new Cliente(nombre, apellido, correo, telefono);
    nuevo->siguiente = clientes;
    clientes = nuevo;
}

Cliente* SistemaReservas::buscarCliente(string telefono) {
    Cliente* actual = clientes;
    while (actual != nullptr) {
        if (actual->telefono == telefono) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void SistemaReservas::agregarMesa(string nombre, int lugares) {
    Mesa* nueva = new Mesa(nombre, lugares);
    nueva->siguiente = mesas;
    mesas = nueva;
}

void SistemaReservas::mostrarMesas() {
    Mesa* actual = mesas;
    cout << "Mesas Disponibles:\n";
    cout << "Nombre\tLugares\tEstado\tCliente\n";
    while (actual != nullptr) {
        cout << actual->nombre << "\t" << actual->lugares << "\t" << actual->estado << "\t" << actual->cliente << endl;
        actual = actual->siguiente;
    }
    cout << endl;
}

void SistemaReservas::mostrarListaClientes() {
    Cliente* actual = clientes;
    cout << "Lista de Clientes:\n";
    cout << "Nombre\tApellido\tCorreo\tTelefono\n";
    while (actual != nullptr) {
        cout << actual->nombre << "\t" << actual->apellido << "\t" << actual->correo << "\t" << actual->telefono << endl;
        actual = actual->siguiente;
    }
    cout << endl;
}

void SistemaReservas::agregarListaEspera(string nombre, string telefono, int lugares) {
    ListaEspera* nuevo = new ListaEspera(nombre, telefono, lugares, idEspera++, false);
    if (listaEspera == nullptr) {
        listaEspera = nuevo;
    } else {
        ListaEspera* actual = listaEspera;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void SistemaReservas::mostrarListaEspera() {
    ListaEspera* actual = listaEspera;
    cout << "Lista de Espera:\n";
    cout << "ID\tTelefono\tNombre\tLugares\tNotificado\n";
    while (actual != nullptr) {
        cout << actual->id << "\t" << actual->telefono << "\t" << actual->nombre << "\t" << actual->lugares << "\t" << (actual->notificado ? "Si" : "No") << endl;
        actual = actual->siguiente;
    }
    cout << endl;
}

void SistemaReservas::asignarMesa(string telefono, int lugares) {
    Cliente* cliente = buscarCliente(telefono);
    if (cliente == nullptr) {
        cout << "Cliente no encontrado.\n";
        return;
    }

    Mesa* actual = mesas;
    bool mesaEncontrada = false;
    cout << "Mesas disponibles con " << lugares << " lugares:\n";
    while (actual != nullptr) {
        if (actual->lugares == lugares && actual->estado == "Libre") {
            cout << "Mesa: " << actual->nombre << endl;
            mesaEncontrada = true;
        }
        actual = actual->siguiente;
    }

    if (!mesaEncontrada) {
        cout << "No hay mesas disponibles con " << lugares << " lugares. ¿Desea esperar en la lista de espera? (s/n): ";
        char respuesta;
        cin >> respuesta;
        if (respuesta == 's') {
            agregarListaEspera(cliente->nombre, telefono, lugares);
            cout << "Agregado a la lista de espera.\n";
           // mostrarListaEspera();
        }
        return;
    }

    string nombreMesa;
    cout << "Ingrese el nombre de la mesa que desea asignar: ";
    cin >> nombreMesa;

    actual = mesas;
    while (actual != nullptr) {
        if (actual->nombre == nombreMesa && actual->lugares == lugares && actual->estado == "Libre") {
            actual->estado = "Ocupado";
            actual->cliente = cliente->nombre + " " + cliente->apellido;  // Establecer el nombre del cliente
            cout << "Mesa " << actual->nombre << " asignada a " << cliente->nombre << " " << cliente->apellido << endl;

            // Eliminar el cliente de la lista de espera si existe
            ListaEspera* espera = listaEspera;
            ListaEspera* anterior = nullptr;
            while (espera != nullptr) {
                if (espera->telefono == telefono) {
                    if (anterior == nullptr) {
                        listaEspera = espera->siguiente;
                    } else {
                        anterior->siguiente = espera->siguiente;
                    }
                    delete espera;
                    break;
                }
                anterior = espera;
                espera = espera->siguiente;
            }

//            mostrarMesas();
//            mostrarListaEspera();
            return;
        }
        actual = actual->siguiente;
    }

    cout << "Mesa no válida o ya ocupada.\n";
}

void SistemaReservas::liberarMesa(string nombreMesa) {
    Mesa* actual = mesas;
    while (actual != nullptr) {
        if (actual->nombre == nombreMesa) {
            actual->estado = "Libre";
            actual->cliente = "-";  // Limpiar el nombre del cliente
            cout << "Mesa " << actual->nombre << " ahora está libre.\n";
//            mostrarMesas();

            ListaEspera* espera = listaEspera;
            while (espera != nullptr) {
                if (espera->lugares <= actual->lugares && !espera->notificado) {
                    cout << "Notificando a " << espera->nombre << " que su mesa está lista.\n";
                    espera->notificado = true;

                    // Para enviar WSP
                    WhatsAppMessenger messenger;
                    string celularCliente, texto, respuesta;
                    celularCliente = "591" + espera->telefono;
                    texto = "Hola " + espera->nombre + "!, su mesa esta lista, por favor presentarse en recepción en 5 minutos o su mesa será dispuesta. Gracias!!!";
                    respuesta = messenger.sendMessage(celularCliente, texto);
                    //cout << "La respuesta fue: " << respuesta << endl;
                    break;
                }
                espera = espera->siguiente;
            }
//            mostrarListaEspera();
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Mesa no encontrada.\n";
}

void SistemaReservas::eliminarDeListaEspera(int id) {
    ListaEspera* actual = listaEspera;
    ListaEspera* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->id == id) {
            if (anterior == nullptr) {
                listaEspera = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            // Para enviar WSP
            WhatsAppMessenger messenger;
            string celularCliente, texto, respuesta;
            celularCliente = "591" + actual->telefono;
            texto = "Hola " + actual->nombre + "!, lamentamos informarle que su mesa ha sido reasignada a otro cliente por tiempo de espera excedido. Apersonarse nuevamente a Recepción";
            respuesta = messenger.sendMessage(celularCliente, texto);
            //cout << "La respuesta fue: " << respuesta << endl;

            delete actual;
            cout << "Cliente con ID " << id << " eliminado de la lista de espera.\n";
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cout << "Cliente no encontrado en la lista de espera.\n";
}

