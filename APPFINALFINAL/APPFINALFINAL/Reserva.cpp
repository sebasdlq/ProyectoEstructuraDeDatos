#include "Reserva.h"

Reserva::Reserva() : id(0), idCliente(0), idEstablecimiento(0), horario(""), totalPrecio(0.0) {
    fill(begin(idProductos), end(idProductos), 0);
    fill(begin(cantidades), end(cantidades), 0);
}

Reserva::Reserva(int id, int idCliente, int idEstablecimiento, const int idProductos[10], const int cantidades[10], const string& horario, double totalPrecio)
    : id(id), idCliente(idCliente), idEstablecimiento(idEstablecimiento), horario(horario), totalPrecio(totalPrecio) {
    copy(idProductos, idProductos + 10, this->idProductos);
    copy(cantidades, cantidades + 10, this->cantidades);
}

int Reserva::getId() const {
    return id;
}

int Reserva::getIdCliente() const {
    return idCliente;
}

int Reserva::getIdEstablecimiento() const {
    return idEstablecimiento;
}

void Reserva::getIdProductos(int idProductos[10]) const {
    copy(this->idProductos, this->idProductos + 10, idProductos);
}

void Reserva::getCantidades(int cantidades[10]) const {
    copy(this->cantidades, this->cantidades + 10, cantidades);
}

string Reserva::getHorario() const {
    return horario;
}

double Reserva::getTotalPrecio() const {
    return totalPrecio;
}

void Reserva::setId(int id) {
    this->id = id;
}

void Reserva::setIdCliente(int idCliente) {
    this->idCliente = idCliente;
}

void Reserva::setIdEstablecimiento(int idEstablecimiento) {
    this->idEstablecimiento = idEstablecimiento;
}

void Reserva::setIdProductos(const int idProductos[10]) {
    copy(idProductos, idProductos + 10, this->idProductos);
}

void Reserva::setCantidades(const int cantidades[10]) {
    copy(cantidades, cantidades + 10, this->cantidades);
}

void Reserva::setHorario(const string& horario) {
    this->horario = horario;
}

void Reserva::setTotalPrecio(double totalPrecio) {
    this->totalPrecio = totalPrecio;
}
