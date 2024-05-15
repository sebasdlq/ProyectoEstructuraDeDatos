#pragma once
#include <iostream>
#include <fstream>
#include <string>
#define MAX 100;
using namespace std;
struct Horarios {
	int hora_e, hora_s;
};
class Establecimiento
{
protected:
	/*string*/int código;
	string Nombre;
	string Ubicación;
	//Horarios Horario[MAX];
	double teléfono, precio_e, cap;
	char dispo;
public:
	Establecimiento();
	void setEstabl(string nom, string ubi, double tel, double pre, double cap, int códig);
	string getNombre();
	string getUbicación();
	//Horarios getSexo();
	double getTelefono();
	double getPrecio_e();
	double getCapacidad();
	char getDisp();
	int getCod();
	void guardarEstablecimiento(ofstream& fsalida);
	bool leerDatos(ifstream& fentrada);
	bool eliminar(fstream& fes, int nroReg);
	bool modificar(fstream& fes, int nroReg);
	bool buscar(ifstream& fentrada, int nroReg);
	int getTamBytesRegistro();
};

