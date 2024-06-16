#include "Producto.h"
#include <iostream>
Producto::Producto() : id(0), idEstablecimiento(0), nombre(""), descripcion(""), precio(0.0) {}

Producto::Producto(int id, int idEstablecimiento, const string& nombre, const string& descripcion, double precio)
    : id(id), idEstablecimiento(idEstablecimiento), nombre(nombre), descripcion(descripcion), precio(precio) {}

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
