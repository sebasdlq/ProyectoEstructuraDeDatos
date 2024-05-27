#ifndef LISTARESERVAS_H
#define LISTARESERVAS_H

#include "Reserva.h"
#include "ReservaManager.h"
#include <string>

using namespace std;

struct NodoReserva {
    Reserva reserva;
    NodoReserva* siguiente;

    NodoReserva(const Reserva& reserva) : reserva(reserva), siguiente(nullptr) {}
};

class ListaReservas {
private:
    NodoReserva* cabeza;

public:
    ListaReservas(const string& filename);
    ~ListaReservas();

    void agregarReserva(const Reserva& reserva);
    void imprimirReservas() const;
    NodoReserva* getCabeza() const;
};

#endif // LISTARESERVAS_H
