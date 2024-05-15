#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Producto.cpp"

using namespace std;


class ABMProducto {
private:
	string  nomArchivo;
	Producto* Produc;

public:

	ABMProducto(string nomArch) {
		nomArchivo = nomArch;
	}

	void introducirDatos(Producto* newReg) {
		string	nombre;
		int		precio;
		string   descripcion;
		cout << endl << endl << "Introducir los siguientes datos --->>> :" << endl;
		fflush(stdin);
		cout << "Nombre del producto : ";
		cin.ignore();
		getline(cin, nombre);
		cout << "Precio : ";
		cin >> precio;
		cout << "Descripcion del producto: ";
		cin.ignore();
		getline(cin, descripcion);
		newReg->setProducto(nombre, precio, descripcion);
	}


	void mostrarRegistro(int nroReg) {
		cout << endl << nroReg << ".-  " << Produc->getNombre() << "  " << Produc->getprecio() << "  " << Produc->getdescripcion() << "  " << Produc->getEstado();

	}
	void adicionarNuevo() {
		ofstream fsalida(nomArchivo, ios::app | ios::binary);
		Produc = new Producto();
		introducirDatos(Produc);
		Produc->guardarArchivo(fsalida);
		fsalida.close();
	}

	void listar() {
		int cr = 0;
		cout << endl << endl << "Los registros son --->>> : " << endl;
		Produc = new Producto();
		ifstream fentrada(nomArchivo, ios::in | ios::binary);
		while (Produc->leerArchivo(fentrada) == true) {
			cr++;
			if (Produc->getEstado() == 'A') {
				mostrarRegistro(cr);
			}
		}
		fentrada.close();
	}

	int buscarReg() {
		int nroReg;
		cout << endl << endl << "Introducir numero de registro a buscar :  ";
		cin >> nroReg;
		Produc = new Producto();
		ifstream fentrada(nomArchivo, ios::in | ios::binary);
		if (Produc->buscar(fentrada, nroReg) == true) {
			mostrarRegistro(nroReg);
		}
		else {
			cout << endl << "Registro no existe";
			nroReg = -1;
		}
		fentrada.close();
		return(nroReg);
	}

	void eliminarReg() {
		int nroReg;
		nroReg = buscarReg();
		if (nroReg > 0) {
			fstream fes(nomArchivo, ios::in | ios::out | ios::binary);
			Produc = new Producto();
			if (Produc->eliminar(fes, nroReg) == true) {
				cout << endl << "Registro eliminado correctmente " << endl;
			}
			else {
				cout << endl << "Registro no existe pa eliminar" << endl;
			}
			fes.close();
		}
	}

	void modificarReg() {
		int nroReg;
		nroReg = buscarReg();
		if (nroReg > 0) {
			fstream fes(nomArchivo, ios::in | ios::out | ios::binary);
			Produc = new Producto();
			introducirDatos(Produc);
			if (Produc->modificar(fes, nroReg) == true) {
				cout << endl << "modificado correctamente... " << endl;
			}
			else {
				cout << endl << "Registro no existe pa modificar";
			}
			fes.close();
		}

	}

};