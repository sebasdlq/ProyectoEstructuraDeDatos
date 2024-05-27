#ifndef LISTAESTABLECIMIENTOS_H
#define LISTAESTABLECIMIENTOS_H

#include "Establecimiento.h"
#include "EstablecimientoManager.h"
#include <string>

using namespace std;

struct NodoEstablecimiento {
    Establecimiento establecimiento;
    NodoEstablecimiento* siguiente;

    NodoEstablecimiento(const Establecimiento& establecimiento) : establecimiento(establecimiento), siguiente(nullptr) {}
};

class ListaEstablecimientos {
private:
    NodoEstablecimiento* cabeza;

public:
    ListaEstablecimientos(const string& filename);
    ~ListaEstablecimientos();

    void agregarEstablecimiento(const Establecimiento& establecimiento);
    void imprimirEstablecimientos() const;
    NodoEstablecimiento* getCabeza() const;
};

#endif // LISTAESTABLECIMIENTOS_H
