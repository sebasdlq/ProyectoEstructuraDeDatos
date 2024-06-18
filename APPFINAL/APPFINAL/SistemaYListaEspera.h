#ifndef SISTEMAYLISTAESPERA_H
#define SISTEMAYLISTAESPERA_H

#include <string>
#include "ClientesYMesas.h"
using namespace std;

class ListaEspera {
public:
    string nombre;
    string telefono;
    int lugares;
    int id;
    bool notificado;
    ListaEspera* siguiente;

    ListaEspera(string n, string t, int l, int i, bool notif);
};

class SistemaReservas {
private:
    Cliente* clientes;
    Mesa* mesas;
    ListaEspera* listaEspera;
    int idEspera;

    void inicializarMesas();
    void agregarMesa(string nombre, int lugares);
    void agregarListaEspera(string nombre, string telefono, int lugares);

public:
    SistemaReservas();

    void agregarCliente(string nombre, string apellido, string correo, string telefono);
    Cliente* buscarCliente(string telefono);
    void mostrarMesas();
    void mostrarListaEspera();
    void mostrarListaClientes();
    void asignarMesa(string telefono, int lugares);
    void liberarMesa(string nombreMesa);
    void eliminarDeListaEspera(int id);
};

#endif 

