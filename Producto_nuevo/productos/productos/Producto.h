#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <iostream>
#include <string>
using namespace std;

class Producto {
private:
    int id;
    int idEstablecimiento;
    string nombre;
    string descripcion;
    double precio;
    char estado;
public:
    Producto();
    Producto(int id, int idEstablecimiento, const string& nombre, const string& descripcion, double precio);

    int getId() const;
    int getIdEstablecimiento() const;
    string getNombre() const;
    string getDescripcion() const;
    double getPrecio() const;
    char getEstado()const;
    void setgeneralP(int id, int idEstablecimiento, string nombre, string descripcion, double precio);
    void setId(int id);
    void setIdEstablecimiento(int idEstablecimiento);
    void setNombre(const string& nombre);
    void setDescripcion(const string& descripcion);
    void setPrecio(double precio);
    void setEstado(char estat);
};

#endif // PRODUCTO_H
