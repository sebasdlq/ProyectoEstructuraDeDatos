#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Cliente {
private:
	string nombre;
	long telefono;
	string correo;
	int edad;
	char genero;
	char estado;
public:
	Cliente();
	Cliente(string name, int tel, string add, int age, char gener);
	void set_cliente(string name, int tel, string add, int age, char gener);
	string getNombre();
	int getEdad();
	long getTelefono();
	string get_correo();
	char getgenero();
	char getEstado();
	void guardarArchivo(ofstream& fsalida);
	bool leerArchivo(ifstream& fentrada);
	bool eliminar(fstream& fes, int nroReg);
	bool modificar(fstream& fes, int nroReg);
	bool buscar(ifstream& fentrada, int nroReg);
	int getTamBytesRegistro();
};