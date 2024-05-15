#include <iostream>
#include <fstream>  // Libreria para manejar el archivo
#include <string>
#include "Establecimiento.h"
using namespace std;

Establecimiento::Establecimiento() {
	Nombre = " ";
	Ubicación = " ";
	teléfono = 0;
	precio_e = 0;
	cap = 0;
	dispo = ' ';
	código = 0;
}
void Establecimiento::setEstabl(string nom, string ubi, double tel, double pre, double capa, int códig) {
	Nombre = nom;
	//código = " ";
	Ubicación = ubi;
	teléfono = tel;
	precio_e = pre;
	cap = capa;
	dispo = 'S';
	código = códig;
}
string Establecimiento::getNombre() {
	return(Nombre);
}
string Establecimiento::getUbicación() {
	return(Ubicación);
}
/*string Establecimiento::get() {

}*/
double Establecimiento::getCapacidad() {
	return(cap);

}
double Establecimiento::getTelefono() {
	return(teléfono);
}
double Establecimiento::getPrecio_e() {
	return(precio_e);
}
char Establecimiento::getDisp() {
	return(dispo);
}
int Establecimiento::getCod() {
	return(código);
}
void Establecimiento::guardarEstablecimiento(ofstream& fsalida) {
	fsalida.write(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
	fsalida.write(reinterpret_cast<char*>(&Ubicación), sizeof(Ubicación));
	fsalida.write(reinterpret_cast<char*>(&cap), sizeof(cap));
	fsalida.write(reinterpret_cast<char*>(&teléfono), sizeof(teléfono));
	fsalida.write(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
	fsalida.write(reinterpret_cast<char*>(&dispo), sizeof(dispo));

}
bool Establecimiento::leerDatos(ifstream& fentrada) {
	bool k = false;
	if (fentrada.is_open() == true) {
		fentrada.read(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
		if (fentrada.eof() == false) {
			fentrada.read(reinterpret_cast<char*>(&Ubicación), sizeof(Ubicación));
			fentrada.read(reinterpret_cast<char*>(&cap), sizeof(cap));
			fentrada.read(reinterpret_cast<char*>(&teléfono), sizeof(teléfono));
			fentrada.read(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fentrada.read(reinterpret_cast<char*>(&dispo), sizeof(dispo));
			fentrada.read(reinterpret_cast<char*>(&código), sizeof(código));
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
			fes.read(reinterpret_cast<char*>(&Ubicación), sizeof(Ubicación));
			fes.read(reinterpret_cast<char*>(&cap), sizeof(cap));
			fes.read(reinterpret_cast<char*>(&teléfono), sizeof(teléfono));
			fes.read(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fes.read(reinterpret_cast<char*>(&dispo), sizeof(dispo));
			fes.read(reinterpret_cast<char*>(&código), sizeof(código));

			dispo = 'N';
			fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.write(reinterpret_cast<char*>(&Nombre), sizeof(Nombre));
			fes.write(reinterpret_cast<char*>(&Ubicación), sizeof(Ubicación));
			fes.write(reinterpret_cast<char*>(&cap), sizeof(cap));
			fes.write(reinterpret_cast<char*>(&teléfono), sizeof(teléfono));
			fes.write(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fes.write(reinterpret_cast<char*>(&código), sizeof(código));
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
			fes.write(reinterpret_cast<char*>(&Ubicación), sizeof(Ubicación));
			fes.write(reinterpret_cast<char*>(&cap), sizeof(cap));
			fes.write(reinterpret_cast<char*>(&teléfono), sizeof(teléfono));
			fes.write(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
			fes.write(reinterpret_cast<char*>(&dispo), sizeof(dispo));
			fes.write(reinterpret_cast<char*>(&código), sizeof(código));
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
		fentrada.read(reinterpret_cast<char*>(&Ubicación), sizeof(Ubicación));
		fentrada.read(reinterpret_cast<char*>(&cap), sizeof(cap));
		fentrada.read(reinterpret_cast<char*>(&teléfono), sizeof(teléfono));
		fentrada.read(reinterpret_cast<char*>(&precio_e), sizeof(precio_e));
		fentrada.read(reinterpret_cast<char*>(&dispo), sizeof(dispo));
		fentrada.read(reinterpret_cast<char*>(&código), sizeof(código));
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
	return(sizeof(código) + sizeof(Nombre) + sizeof(Ubicación) + sizeof(cap) + sizeof(teléfono) + sizeof(precio_e) + sizeof(dispo));
}