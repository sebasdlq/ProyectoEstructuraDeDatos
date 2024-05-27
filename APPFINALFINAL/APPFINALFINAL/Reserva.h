#ifndef RESERVA_H
#define RESERVA_H

#include <string>

using namespace std;

class Reserva {
private:
    int id;
    int idCliente;
    int idEstablecimiento;
    int idProductos[10];
    int cantidades[10];
    string horario;
    double totalPrecio;

public:
    Reserva();
    Reserva(int id, int idCliente, int idEstablecimiento, const int idProductos[10], const int cantidades[10], const string& horario, double totalPrecio);

    int getId() const;
    int getIdCliente() const;
    int getIdEstablecimiento() const;
    void getIdProductos(int idProductos[10]) const;
    void getCantidades(int cantidades[10]) const;
    string getHorario() const;
    double getTotalPrecio() const;

    void setId(int id);
    void setIdCliente(int idCliente);
    void setIdEstablecimiento(int idEstablecimiento);
    void setIdProductos(const int idProductos[10]);
    void setCantidades(const int cantidades[10]);
    void setHorario(const string& horario);
    void setTotalPrecio(double totalPrecio);
};

#endif // RESERVA_H

