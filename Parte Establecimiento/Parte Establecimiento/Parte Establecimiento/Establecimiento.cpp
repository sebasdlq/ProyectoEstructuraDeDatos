#include <iostream>
#include <fstream>  // Libreria para manejar el archivo
#include <string>
#include "Establecimiento.h"
using namespace std;

Establecimiento::Establecimiento() {
	Nombre = " ";
	Ubicaci�n = " ";
	tel�fono = 0;
	precio_e = 0;
	cap = 0;
	dispo = ' ';
	c�digo = 0;
}
void Establecimiento::setEstabl(string nom, string ubi, double tel, double pre, double capa, int c�dig) {
	Nombre = nom;
	//c�digo = " ";
	Ubicaci�n = ubi;
	tel�fono = tel;
	precio_e = pre;
	cap = capa;
	dispo = 'S';
	c�digo = c�dig;
}
string Establecimiento::getNombre() {
	return(Nombre);
}
string Establecimiento::getUbicaci�n() {
	return(Ubicaci�n);
}
/*string Establecimiento::get() {

}*/
double Establecimiento::getCapacidad() {
	return(cap);

}
double Establecimiento::getTelefono() {
	return(tel�fono);
}
double Establecimiento::getPrecio_e() {
	return(precio_e);
}
char Establecimiento::getDisp() {
	return(dispo);
}
int Establecimiento::getCod() {
	return(c�digo);
}
void Establecimiento::guardarEstablecimiento(ofstream& fsalida) {
	fsalida.write(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
	fsalida.write(reinterpret_cast<char*>(&Ubicaci�n), sizeof(Ubicaci�n));
	fsalida.write(reinterpret_cast<char*>(&cap), sizeof(cap));
	fsalida.write(reinterpret_cast<char*>(&tel�fono), sizeof(tel�fono));
	fsalida.write(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
	fsalida.write(reinterpret_cast<char*>(&dispo), sizeof(dispo));

}
bool Establecimiento::leerDatos(ifstream& fentrada) {
	bool k = false;
	if (fentrada.is_open() == true) {
		fentrada.read(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
		if (fentrada.eof() == false) {
			fentrada.read(reinterpret_cast<char*>(&Ubicaci�n), sizeof(Ubicaci�n));
			fentrada.read(reinterpret_cast<char*>(&cap), sizeof(cap));
			fentrada.read(reinterpret_cast<char*>(&tel�fono), sizeof(tel�fono));
			fentrada.read(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fentrada.read(reinterpret_cast<char*>(&dispo), sizeof(dispo));
			fentrada.read(reinterpret_cast<char*>(&c�digo), sizeof(c�digo));
			k = true;
		}
		else {
			cout << endl << "Establecimiento no existe";
		}
	}
	else {
		cout << endl << "Arhivo no existe";
	}
	return(k);
}
bool Establecimiento::eliminar(fstream& fes, int nroReg) {
	bool k = false;
	if (fes.is_open() == true) {
		fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
		fes.read(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
		if (fes.eof() == false) {
			fes.read(reinterpret_cast<char*>(&Ubicaci�n), sizeof(Ubicaci�n));
			fes.read(reinterpret_cast<char*>(&cap), sizeof(cap));
			fes.read(reinterpret_cast<char*>(&tel�fono), sizeof(tel�fono));
			fes.read(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fes.read(reinterpret_cast<char*>(&dispo), sizeof(dispo));
			fes.read(reinterpret_cast<char*>(&c�digo), sizeof(c�digo));

			dispo = 'N';
			fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.write(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
			fes.write(reinterpret_cast<char*>(&Ubicaci�n), sizeof(Ubicaci�n));
			fes.write(reinterpret_cast<char*>(&cap), sizeof(cap));
			fes.write(reinterpret_cast<char*>(&tel�fono), sizeof(tel�fono));
			fes.write(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fes.write(reinterpret_cast<char*>(&c�digo), sizeof(c�digo));
			k = true;
		}
		else {
			cout << endl << "Codigo no existe";
		}
	}
	else {
		cout << endl << "Arhivo no existe";
	}
	return(k);
}
bool Establecimiento::modificar(fstream& fes, int nroReg) {
	bool k = false;
	if (fes.is_open() == true) {
		string nomAux;
		nomAux = Nombre;
		fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
		fes.read(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
		if (fes.eof() == false) {
			Nombre = nomAux;
			dispo = 'S';
			fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.write(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
			fes.write(reinterpret_cast<char*>(&Ubicaci�n), sizeof(Ubicaci�n));
			fes.write(reinterpret_cast<char*>(&cap), sizeof(cap));
			fes.write(reinterpret_cast<char*>(&tel�fono), sizeof(tel�fono));
			fes.write(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fes.write(reinterpret_cast<char*>(&dispo), sizeof(dispo));
			fes.write(reinterpret_cast<char*>(&c�digo), sizeof(c�digo));
			k = true;
		}
		else {
			cout << endl << "Codigo no existe";
		}
	}
	else {
		cout << endl << "Arhivo no existe";
	}
	return(k);
}
bool Establecimiento::buscar(ifstream& fentrada, int nroReg) {
	bool k = false;
	if (fentrada.is_open() == true) {
		fentrada.read(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
		fentrada.read(reinterpret_cast<char*>(&Ubicaci�n), sizeof(Ubicaci�n));
		fentrada.read(reinterpret_cast<char*>(&cap), sizeof(cap));
		fentrada.read(reinterpret_cast<char*>(&tel�fono), sizeof(tel�fono));
		fentrada.read(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
		fentrada.read(reinterpret_cast<char*>(&dispo), sizeof(dispo));
		fentrada.read(reinterpret_cast<char*>(&c�digo), sizeof(c�digo));
		if (fentrada.eof() == false) {
			k = true;
		}
		else {
			cout << endl << "Codigo no XX existe";
		}
	}
	else {
		cout << endl << "Arhivo no existe";
	}
	return(k);
}
int Establecimiento::getTamBytesRegistro() {
	return(sizeof(c�digo) + sizeof(Nombre) + sizeof(Ubicaci�n) + sizeof(cap) + sizeof(tel�fono) + sizeof(precio_e) + sizeof(dispo));
}