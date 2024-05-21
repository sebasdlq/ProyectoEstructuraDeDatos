#pragma once
#include <iostream>
#include <fstream>
#include "Comida.h"

using namespace std;

class ListaDeComidas
{
private:
	int lastId;
	string fileName;
public:
	Comida* frente;
	Comida* final;

	ListaDeComidas(string _fileName);
	void Push(int _restaurante, string _nombre, string _descripcion, float _precio, bool guardarFile = true);
	void Push(Comida* comida, bool guardarFile=true);
	int eliminar(int id);

	void MostrarComidas();

	//Manejo De Archivos
	void guardar(Comida* guardar);
	void guardar(Comida* guardar, ofstream &ofs);
	void LeerLista();
	void EliminarDelRegistro();
};

