
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Producto {
private:
	string 	descripcion;
	int		precio;
	string	nombre;
	char	estado;		//eliminado = E, activo = A

public:
	Producto() {
		nombre = "";
		precio = 0;
		descripcion = ' ';
		estado = ' ';
	}

	Producto(string nom, int p, string des) {
		nombre = nom;
		precio = p;
		descripcion = des;
		estado = 'A';
	}

	void setProducto(string nom, int p, string des) {
		nombre = nom;
		precio = p;
		descripcion = des;
		estado = 'A';
	}

	string getNombre() {
		return(nombre);
	}

	int getprecio() {
		return(precio);
	}

	string getdescripcion() {
		return(descripcion);
	}

	char getEstado() {
		return(estado);
	}

	void guardarArchivo(ofstream& fsalida) {
		fsalida.write(reinterpret_cast<char*>(&nombre), sizeof(nombre));
		fsalida.write(reinterpret_cast<char*>(&precio), sizeof(precio));
		fsalida.write(reinterpret_cast<char*>(&descripcion), sizeof(descripcion));
		fsalida.write(reinterpret_cast<char*>(&estado), sizeof(estado));
	}

	bool leerArchivo(ifstream& fentrada) {
		bool k = false;
		if (fentrada.is_open() == true) {
			fentrada.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
			if (fentrada.eof() == false) {
				fentrada.read(reinterpret_cast<char*>(&precio), sizeof(precio));
				fentrada.read(reinterpret_cast<char*>(&descripcion), sizeof(descripcion));
				fentrada.read(reinterpret_cast<char*>(&estado), sizeof(estado));
				k = true;
			}
			else {
				//cout << endl << "Registro no existe";
			}
		}
		else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}

	bool eliminar(fstream& fes, int nroReg) {
		bool k = false;
		if (fes.is_open() == true) {
			fes.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fes.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
			if (fes.eof() == false) {
				fes.read(reinterpret_cast<char*>(&precio), sizeof(precio));
				fes.read(reinterpret_cast<char*>(&descripcion), sizeof(descripcion));
				fes.read(reinterpret_cast<char*>(&estado), sizeof(estado));

				estado = 'E';
				fes.seekp(getTamBytesRegistro() * (nroReg - 1), ios::beg);
				fes.write(reinterpret_cast<char*>(&nombre), sizeof(nombre));
				fes.write(reinterpret_cast<char*>(&precio), sizeof(precio));
				fes.write(reinterpret_cast<char*>(&descripcion), sizeof(descripcion));
				fes.write(reinterpret_cast<char*>(&estado), sizeof(estado));
				k = true;
			}
			else {
				cout << endl << "Registro no existe";
			}
		}
		else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}


	bool modificar(fstream& fes, int nroReg) {
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
				fes.write(reinterpret_cast<char*>(&precio), sizeof(precio));
				fes.write(reinterpret_cast<char*>(&descripcion), sizeof(descripcion));
				fes.write(reinterpret_cast<char*>(&estado), sizeof(estado));
				k = true;
			}
			else {
				cout << endl << "Registro no existe";
			}
		}
		else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}

	bool buscar(ifstream& fentrada, int nroReg) {
		bool k = false;
		if (fentrada.is_open() == true) {
			fentrada.seekg(getTamBytesRegistro() * (nroReg - 1), ios::beg);
			fentrada.read(reinterpret_cast<char*>(&nombre), sizeof(nombre));
			fentrada.read(reinterpret_cast<char*>(&precio), sizeof(precio));
			fentrada.read(reinterpret_cast<char*>(&descripcion), sizeof(descripcion));
			fentrada.read(reinterpret_cast<char*>(&estado), sizeof(estado));
			if (fentrada.eof() == false) {
				k = true;
			}
			else {
				//cout << endl << "Registro no XX existe";
			}
		}
		else {
			cout << endl << "Arhivo no existe";
		}
		return(k);
	}

	int getTamBytesRegistro() {
		return(sizeof(nombre) + sizeof(precio) + sizeof(descripcion) + sizeof(estado));
	}

};
