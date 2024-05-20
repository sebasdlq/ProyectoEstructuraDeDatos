#pragma once
#include <iostream>
#include <fstream>

using namespace std;
class Comida
{
private:
	int id;
	int restaurante;
	string nombre;
	string descripcion;
	float precio;

public:
	Comida* sig;
	Comida* ant;

	Comida(int _id, int _restaurante);
	Comida(int _id, int _restaurante, string _nombre, string _descripcion, float _precio);
	//set
	void setNombre(string _nombre);
	void setDescripcion(string _descripcion);
	void setPrecio(float _precio);
	//get
	int getId();
	int getRestaurante();
	string getNombre();
	string getDescripcion();
	float getPrecio();
	int getByteSize();
	bool leerUnaComida(ifstream &adm);
};

