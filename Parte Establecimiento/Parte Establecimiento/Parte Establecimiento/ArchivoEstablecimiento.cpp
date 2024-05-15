
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "ArchivoEstablecimiento.h"
#include "Establecimiento.h"

using namespace std;


ArchivoEstablecimiento::ArchivoEstablecimiento(string nomAr) {
	nomArch = nomAr;
}

void ArchivoEstablecimiento::introducirDatos(Establecimiento* newReg) {
	//int código;
	string nombre;
	string ubicación;
	double t, p, c;
	char dispo;
	int cod;
	fflush(stdin);
	cout << endl << endl << "Introducir los siguientes datos del establecimiento --->>> :" << endl;
	cout << "Nombre : ";
	getline(cin, nombre);
	cout << "Ubicación : ";
	getline(cin, ubicación);
	cout << "Teléfono : ";
	cin >> t;
	cout << "Capacidad máxima, en sillas: ";
	cin >> c;
	cout << "Si existe un precio de entrada, indicarlo: ";
	cin >> p;
	cout << "Código del Establecimiento: ";
	cin >> cod;
	newReg->setEstabl(nombre, ubicación, t, p, c, cod);
}


void ArchivoEstablecimiento::mostrarEst(int nroReg) {
	cout << endl << nroReg << ".-  " << est->getNombre() << "  " << est->getUbicación() << "  " << est->getTelefono() << "  " << est->getCapacidad() << "  " << est->getPrecio_e() << "  " << est->getDisp();

}
void ArchivoEstablecimiento::adicionarNuevo() {
	ofstream fsalida(nomArch , ios::app | ios::binary);
	est = new Establecimiento();
	introducirDatos(est);
	est->guardarEstablecimiento(fsalida);
	fsalida.close();
}

void ArchivoEstablecimiento::listar() {
	int cr = 0;
	cout << endl << endl << "Los registros son --->>> : " << endl;
	est = new Establecimiento();
	ifstream fentrada(nomArch, ios::in | ios::binary);
	while (est->leerDatos(fentrada) == true) {
		cr++;
		if (est->getDisp() == 'S') {
			mostrarEst(cr);
		}
	}
	fentrada.close();
}

int ArchivoEstablecimiento::buscarCod() {
	int nroEst;
	cout << endl << endl << "Introducir codigo de Establecimiento a buscar :  ";
	cin >> nroEst;
	est = new Establecimiento();
	ifstream fentrada(nomArch, ios::in | ios::binary);
	if (est->buscar(fentrada, nroEst) == true) {
		mostrarEst(nroEst);
	}
	else {
		cout << endl << "Registro no existe";
		nroEst = -1;
	}
	fentrada.close();
	return(nroEst);
}

void ArchivoEstablecimiento::eliminarCod() {
	int nroReg;
	nroReg = buscarCod();
	if (nroReg > 0) {
		fstream fes(nomArch, ios::in | ios::out | ios::binary);
		est= new Establecimiento();
		if (est->eliminar(fes, nroReg) == true) {
			cout << endl << "Establecimiento eliminado correctmente " << endl;
		}
		else {
			cout << endl << "Establecimiento no existe para eliminar" << endl;
		}
		fes.close();
	}
}

void ArchivoEstablecimiento::modificarCod() {
	int nroReg;
	nroReg = buscarCod();
	if (nroReg > 0) {
		fstream fes(nomArch, ios::in | ios::out | ios::binary);
		est = new Establecimiento();
		introducirDatos(est);
		if (est->modificar(fes, nroReg) == true) {
			cout << endl << "Modificado correctamente... " << endl;
		}
		else {
			cout << endl << "Establecimiento no existe pa modificar";
		}
		fes.close();
	}

}