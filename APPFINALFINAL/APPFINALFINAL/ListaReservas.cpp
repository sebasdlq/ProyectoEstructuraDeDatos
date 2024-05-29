#include "ListaReservas.h"
#include <iostream>

ListaReservas::ListaReservas(const string& filename) : cabeza(nullptr) {
    ReservaManager reservaManager(filename);
    vector<Reserva> reservas = reservaManager.obtenerTodasReservas();

    for (const Reserva& reserva : reservas) {
        agregarReserva(reserva);
    }
}

ListaReservas::~ListaReservas() {
    NodoReserva* actual = cabeza;
    while (actual != nullptr) {
        NodoReserva* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaReservas::agregarReserva(const Reserva& reserva) {
    NodoReserva* nuevoNodo = new NodoReserva(reserva);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
}

void ListaReservas::imprimirReservas() const {
    NodoReserva* actual = cabeza;
    while (actual != nullptr) {
        cout << "ID: " << actual->reserva.getId() << ", Cliente ID: " << actual->reserva.getIdCliente()
            << ", Establecimiento ID: " << actual->reserva.getIdEstablecimiento() << ", Total: " << actual->reserva.getTotalPrecio() << endl;
        actual = actual->siguiente;
    }
}

NodoReserva* ListaReservas::getCabeza() const {
    return cabeza;
}
