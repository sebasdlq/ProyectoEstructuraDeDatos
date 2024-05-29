#ifndef RESERVAMANAGER_H
#define RESERVAMANAGER_H

#include "Reserva.h"
#include <vector>
#include <string>

using namespace std;

class ReservaManager {
private:
    string filename;

public:
    ReservaManager(const string& filename);
    bool agregarReserva(const Reserva& reserva);
    bool modificarReserva(const Reserva& reserva);
    bool eliminarReserva(int id);
    Reserva buscarReservaPorId(int id);
    vector<Reserva> obtenerTodasReservas();
};

#endif // RESERVAMANAGER_H
