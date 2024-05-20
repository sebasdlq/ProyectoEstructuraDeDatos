#include "Comida.h"
#include <iostream>
#include <string>

using namespace std;

Comida::Comida(int _id, int _restaurante)
{
	id = _id;
	restaurante = _restaurante;
	nombre = "";
	descripcion = "";
	precio = 0.0f;

	sig = nullptr;
	ant = nullptr;
}

Comida::Comida(int _id, int _restaurante, string _nombre, string _descripcion, float _precio)
{
	id = _id;
	restaurante = _restaurante;
	nombre = _nombre;
	descripcion = _descripcion;
	precio = _precio;

	sig = nullptr;
	ant = nullptr;
}

void Comida::setNombre(string _nombre)
{
	nombre = _nombre;
}

void Comida::setDescripcion(string _descripcion)
{
	descripcion = _descripcion;
}

void Comida::setPrecio(float _precio)
{
	precio = _precio;
}

int Comida::getId()
{
	return id;
}

int Comida::getRestaurante()
{
	return restaurante;
}

string Comida::getNombre()
{
	return nombre;
}

string Comida::getDescripcion()
{
	return descripcion;
}

float Comida::getPrecio()
{
	return precio;
}

int Comida::getByteSize()
{
	return sizeof(id) + sizeof(restaurante) + sizeof(nombre) + sizeof(descripcion) + sizeof(precio);
}

bool Comida::leerUnaComida(ifstream& adm)
{
	bool k = false;
	if (adm.is_open()) {
		adm.read(reinterpret_cast<char*>(&id), sizeof(int));
		if (!adm.eof()) {
			adm.read(reinterpret_cast<char*>(&restaurante), sizeof(int));
			adm.read(reinterpret_cast<char*>(&nombre), sizeof(string));
			adm.read(reinterpret_cast<char*>(&descripcion), sizeof(string));
			adm.read(reinterpret_cast<char*>(&precio), sizeof(float));
			k = true;
		}
	}
	return k;
}
