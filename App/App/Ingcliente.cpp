#include "Ingcliente.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;

Ingcliente::Ingcliente(string nomArch) {
	Archivo = nomArch;
}
void Ingcliente::Iniciar_sesion(Cliente* newReg) {
	string	nombre;
	int	edad;
	int	telefono;
	char genero;
	string correo;
	cout << "Nuevo datos de Usuario:\n";
	fflush(stdin);
	cout << "Nombre: ";
	getline(cin, nombre);
	cout << "Edad: ";
	cin >> edad;
	cout << "Sexo <F/M>: ";
	cin >> genero;
	cout << "Telefono : ";
	cin >> telefono;
	cin.ignore();
	cout << "Correo : ";
	getline(cin, correo);
	newReg->set_cliente(nombre, telefono, correo, edad, genero);
}
void Ingcliente::mostrar_usuario(int nroReg) {
	if (cliente != nullptr) {
		cout << endl << nroReg << ".-  " << cliente->getNombre() << "  " << cliente->getEdad() << "  " << cliente->getgenero() << " " << cliente->getTelefono() << " " << cliente->get_correo() << "  " << cliente->getEstado();
	}
	else {
		cout << "Error: Usuario no válido.\n";
	}
}
void Ingcliente::nuevo_cliente() {
	ofstream fsalida(Archivo, ios::app | ios::binary);
	cliente = new Cliente();
	Iniciar_sesion(cliente);
	cliente->guardarArchivo(fsalida);
	fsalida.close();
}
void Ingcliente::listar() {
	int c = 0;
	cout << "Usuarios: " << endl;
	cliente = new Cliente();
	ifstream fentrada(Archivo, ios::in | ios::binary);
	while (cliente->leerArchivo(fentrada) == true) {
		c++;
		if (cliente->getEstado() == 'A') {
			mostrar_usuario(c);
		}
	}
	fentrada.close();
}
int Ingcliente::buscarReg() {
	int Reg;
	cout << "Registro/Usuario a buscar :  ";
	cin >> Reg;
	cliente = new Cliente();
	ifstream fentrada(Archivo, ios::in | ios::binary);
	if (cliente->buscar(fentrada, Reg) == true) {
		mostrar_usuario(Reg);
	}
	else {
		cout << "Registro no existe\n";
		Reg = -1;
	}
	fentrada.close();
	return Reg;
}
void Ingcliente::eliminarReg() {
	int nroReg;
	nroReg = buscarReg();
	if (nroReg > 0) {
		fstream fes(Archivo, ios::in | ios::out | ios::binary);
		cliente = new Cliente();
		if (cliente->eliminar(fes, nroReg) == true) {
			cout << "Registro eliminado correctmente " << endl;
		}
		else {
			cout << "Registro no existente" << endl;
		}
		fes.close();
	}
}
void Ingcliente::modificarReg() {
	int nroReg;
	nroReg = buscarReg();
	if (nroReg > 0) {
		fstream fes(Archivo, ios::in | ios::out | ios::binary);
		cliente = new Cliente();
		Iniciar_sesion(cliente);
		if (cliente->modificar(fes, nroReg) == true) {
			cout << "modificado correctamente..\n";
		}
		else {
			cout << "Registro no existente\n";
		}
		fes.close();
	}
}