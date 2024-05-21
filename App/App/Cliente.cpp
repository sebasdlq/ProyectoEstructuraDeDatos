#include "Cliente.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Cliente::Cliente() {
	nombre = "";
	correo = " ";
	telefono = 0;
	edad = 0;
	genero = ' ';
	estado = ' ';
}
Cliente::Cliente(string name, int tel, string add, int age, char gener) {
	nombre = name;
	telefono = tel;
	correo = add;
	edad = age;
	genero = gener;
	estado = 'A';
}
void Cliente::set_cliente(string name, int tel, string add, int age, char gener) {
	nombre = name;
	telefono = tel;
	correo = add;
	edad = age;
	genero = gener;
	estado = 'A';
}
string Cliente::getNombre() {
	return nombre;
}
string Cliente::get_correo() {
	return correo;
}
long Cliente::getTelefono() {
	return telefono;
}
int Cliente::getEdad() {
	return edad;
}
char Cliente::getgenero() {
	return genero;
}
char Cliente::getEstado() {
	return estado;
}
void Cliente::guardarArchivo(ofstream& fsalida) {
	fsalida.write(reinterpret_cast<char*>(&nombre), sizeof(nombre));
	fsalida.write(reinterpret_cast<char*>(&edad), sizeof(edad));
	fsalida.write(reinterpret_cast<char*>(&telefono), sizeof(telefono));
	fsalida.write(reinterpret_cast<char*>(&correo), sizeof(correo));
	fsalida.write(reinterpret_cast<char*>(&genero), sizeof(genero));
	fsalida.write(reinterpret_cast<char*>(&estado), sizeof(estado));
}
bool Cliente::leerArchivo(ifstream& fentrada) {
	bool W = false;
	if (fentrada.is_open() == true) {
		fentrada.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
		if (fentrada.eof() == false) {
			fentrada.read(reinterpret_cast<char*>(&edad), sizeof(edad));
			fentrada.read(reinterpret_cast<char*>(&telefono), sizeof(telefono));
			fentrada.read(reinterpret_cast<char*>(&correo), sizeof(correo));
			fentrada.read(reinterpret_cast<char*>(&genero), sizeof(genero));
			fentrada.read(reinterpret_cast<char*>(&estado), sizeof(estado));
			W = true;
		}
		else {
			//cout << endl << "Registro no existe";
		}
	}
	else {
		cout << endl << "Usuario no existe\n";
	}
	return W;
}
bool Cliente::eliminar(fstream& fes, int nroReg) {
	bool W = false;
	if (fes.is_open() == true) {
		fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
		fes.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
		if (fes.eof() == false) {
			fes.read(reinterpret_cast<char*>(&edad), sizeof(edad));
			fes.read(reinterpret_cast<char*>(&genero), sizeof(genero));
			fes.read(reinterpret_cast<char*>(&estado), sizeof(estado));

			estado = 'E';
			fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.write(reinterpret_cast<char*>(&nombre), sizeof(nombre));
			fes.write(reinterpret_cast<char*>(&edad), sizeof(edad));
			fes.write(reinterpret_cast<char*>(&genero), sizeof(genero));
			fes.write(reinterpret_cast<char*>(&estado), sizeof(estado));
			W = true;
		}
		else {
			cout << endl << "Registro no existe\n";
		}
	}
	else {
		cout << endl << "Arhivo no existe\n";
	}
	return W;
}
bool Cliente::modificar(fstream& fes, int nroReg) {
	bool k = false;
	if (fes.is_open() == true) {
		string nomAux;
		nomAux = nombre;
		fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
		fes.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
		if (fes.eof() == false) {
			nombre = nomAux;
			estado = 'A';
			fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.write(reinterpret_cast<char*>(&nombre), sizeof(nombre));
			fes.write(reinterpret_cast<char*>(&edad), sizeof(edad));
			fes.write(reinterpret_cast<char*>(&telefono), sizeof(telefono));
			fes.write(reinterpret_cast<char*>(&correo), sizeof(correo));
			fes.write(reinterpret_cast<char*>(&genero), sizeof(genero));
			fes.write(reinterpret_cast<char*>(&estado), sizeof(estado));
			k = true;
		}
		else {
			cout << endl << "Registro no existe\n";
		}
	}
	else {
		cout << endl << "Arhivo no existe\n";
	}
	return k;
}
bool Cliente::buscar(ifstream& fentrada, int nroReg) {
	bool k = false;
	if (fentrada.is_open() == true) {
		fentrada.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
		fentrada.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
		fentrada.read(reinterpret_cast<char*>(&edad), sizeof(edad));
		fentrada.read(reinterpret_cast<char*>(&telefono), sizeof(telefono));
		fentrada.read(reinterpret_cast<char*>(&correo), sizeof(correo));
		fentrada.read(reinterpret_cast<char*>(&genero), sizeof(genero));
		fentrada.read(reinterpret_cast<char*>(&estado), sizeof(estado));
		if (fentrada.eof() == false) {
			k = true;
		}
		else {
			//cout << endl << "Registro no XX existe";
		}
	}
	else {
		cout << "Arhivo no existe\n";
	}
	return k;
}
int Cliente::getTamBytesRegistro() {
	return (sizeof(nombre) + sizeof(edad) + sizeof(telefono) + correo.size() + 1 + sizeof(genero) + sizeof(estado));
}