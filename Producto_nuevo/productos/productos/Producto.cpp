#include "Producto.h"
#include <iostream>
Producto::Producto() : id(0), idEstablecimiento(0), nombre(""), descripcion(""), precio(0), estado(' ') {}

Producto::Producto(int id, int idEstablecimiento, const string& nombre, const string& descripcion, double precio)
    : id(id), idEstablecimiento(idEstablecimiento), nombre(nombre), descripcion(descripcion), precio(precio), estado('A') {}

int Producto::getId() const {
    return id;
}

int Producto::getIdEstablecimiento() const {
    return idEstablecimiento;
}

string Producto::getNombre() const {
    return nombre;
}

string Producto::getDescripcion() const {
    return descripcion;
}

double Producto::getPrecio() const {
    return precio;
}

char Producto::getEstado() const {
    return estado;
}
void Producto::setgeneralP(int id, int idEstablecimiento, string nombre, string descripcion, double precio) {
    this->id = id;
    this->idEstablecimiento = idEstablecimiento;
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->precio = precio;
    this->estado = 'A';
}
void Producto::setId(int id) {
    this->id = id;
}

void Producto::setIdEstablecimiento(int idEstablecimiento) {
    this->idEstablecimiento = idEstablecimiento;
}

void Producto::setNombre(const string& nombre) {
    this->nombre = nombre;
}

void Producto::setDescripcion(const string& descripcion) {
    this->descripcion = descripcion;
}

void Producto::setPrecio(double precio) {
    this->precio = precio;
}

void Producto::setEstado(char estat) {
    this->estado = estat;
}