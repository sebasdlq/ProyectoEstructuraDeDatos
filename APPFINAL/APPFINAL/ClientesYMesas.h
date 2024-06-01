#ifndef CLIENTESYMESAS_H
#define CLIENTESYMESAS_H

#include <string>
using namespace std;

class Cliente {
public:
    string nombre;
    string apellido;
    string correo;
    string telefono;
    Cliente* siguiente;

    Cliente(string n, string a, string c, string t);
};

class Mesa {
public:
    string nombre;
    int lugares;
    string estado;
    string cliente;  // Nombre del cliente que ocupa la mesa
    Mesa* siguiente;

    Mesa(string n, int l);
};

#endif // CLIENTESYMESAS_H

