#include "ListaDeComidas.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Comida.h"

using namespace std;

ListaDeComidas::ListaDeComidas(string _fileName)
{
	fileName = _fileName;

	frente = nullptr;
	final = nullptr;

	
	LeerLista();

	if (final != nullptr) {
		lastId = final->getId() + 1;
	}
	else {
		lastId = 0;
	}

}


void ListaDeComidas::Push(int _restaurante, string _nombre, string _descripcion, float _precio, bool guardarFile)
{
	Comida* newComida = new Comida(lastId++, _restaurante, _nombre, _descripcion, _precio);
	if (frente == nullptr) {
		frente = newComida;
		final = newComida;
	}
	else {
		newComida->ant = final;
		final->sig = newComida;
		final = newComida;
	}
	if (guardarFile)
		guardar(newComida);
}

void ListaDeComidas::Push(Comida* comida, bool guardarFile)
{
	if (frente == nullptr) {
		frente = comida;
		final = comida;
	}
	else {
		comida->ant = final;
		final->sig = comida;
		final = comida;
	}
	if (guardarFile)
		guardar(comida);
}

int ListaDeComidas::eliminar(int id)
{
	Comida* actual = frente;
	while (actual != nullptr) {
		if (actual->getId() == id) {
			//Eliminar Registro
			if (actual == frente) {
				frente = actual->sig;
				actual->sig = nullptr;
			}
			else if (actual == final)
			{
				final = actual->ant;
				actual->ant->sig = nullptr;
				actual->ant = nullptr;
			}else {
				actual->sig->ant = actual->ant;
				actual->ant->sig = actual->sig;
				actual->ant = nullptr;
				actual->sig = nullptr;
			}
			EliminarDelRegistro();
			return 0;
		}
		actual = actual->sig;
	}
	cerr << "Registro no existe \n";
	return -1;//No se logro eliminar
}

void ListaDeComidas::MostrarComidas()
{
	Comida* actual = frente;
	while (actual != nullptr)
	{
		cout << "\nid: " << actual->getId();
		cout << "\nrest: " << actual->getRestaurante();
		cout << "\nprecio: " << actual->getPrecio();
		actual = actual->sig;
	}
}

void ListaDeComidas::guardar(Comida* guardar)
{
	int id = guardar->getId();
	int restautante = guardar->getRestaurante();
	string nombre = guardar->getNombre();
	string descripcion = guardar->getDescripcion();
	float precio = guardar->getPrecio();
	ofstream adm(fileName, ios::app | ios::binary);
	adm.write(reinterpret_cast<char*>(&id), sizeof(int));
	adm.write(reinterpret_cast<char*>(&restautante), sizeof(int));
	adm.write(reinterpret_cast<char*>(&nombre), sizeof(string));
	adm.write(reinterpret_cast<char*>(&descripcion), sizeof(string));
	adm.write(reinterpret_cast<char*>(&precio), sizeof(float));
}

void ListaDeComidas::guardar(Comida* guardar, ofstream& ofs)
{
	int id = guardar->getId();
	int restautante = guardar->getRestaurante();
	string nombre = guardar->getNombre();
	string descripcion = guardar->getDescripcion();
	float precio = guardar->getPrecio();
	ofs.write(reinterpret_cast<char*>(&id), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&restautante), sizeof(int));
	ofs.write(reinterpret_cast<char*>(&nombre), sizeof(string));
	ofs.write(reinterpret_cast<char*>(&descripcion), sizeof(string));
	ofs.write(reinterpret_cast<char*>(&precio), sizeof(float));
}

void ListaDeComidas::LeerLista() {

	ifstream adm;
	adm.open(fileName, ios::in | ios::binary);
	Comida* actual = new Comida(0, 0);
	while (actual->leerUnaComida(adm)) {
		Push(actual, false);
		actual = new Comida(0, 0);
	}
	actual = NULL;
	adm.close();
}

void ListaDeComidas::EliminarDelRegistro()
{
	//Elimina reescribiendo el archivo sin el registro eliminado
	ofstream ofs(fileName, ios::trunc | ios::binary | ios::out);
	Comida* actual = frente;
	while (actual != nullptr)
	{
		guardar(actual, ofs);
		actual = actual->sig;
	}
}
