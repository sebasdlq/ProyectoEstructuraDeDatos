#pragma once
#include "Clientes.h "
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

/*           METADATA DE LAS TABLAS (5 Bytes)
-------------------------------------------------------
| Bytes|      Tipo      |  Nombre   |      Valores    |
-------------------------------------------------------
|   1  | unsigned char  | tip_tabla | 'c','o','m','r' |
|   2  | unsigned short | reg_total |   0 .. 65535    |
|   2  | unsigned short | reg_elim  |   0 .. 65535    |
-------------------------------------------------------
*/

class ABMClientes {
private:
	string tabla;
	string archivo;
	char marca;
	unsigned char tip_tabla;
	unsigned short reg_total, reg_elim;
	unsigned int reg_posicion;
	Clientes* cliente;

public:
	ABMClientes(string tabla, char marca) : tabla(tabla), archivo(tabla + ".dat"), marca(marca), reg_total(0), reg_elim(0), reg_posicion(0) {}

	string getTabla() { return tabla; }
	string getArchivo() { return archivo; }
	char getMarca() { return marca; }
	unsigned char getTip_tabla() { return tip_tabla; }
	unsigned short getReg_total() { return reg_total; }
	unsigned short getReg_elim() { return reg_elim; }
	unsigned int getReg_posicion() { return reg_posicion; }

	// Función para generar un nombre de archivo aleatorio
	string generateRandomFilename(const string& baseName) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(10000, 99999);
		stringstream ss;
		ss << baseName << "-" << dis(gen) << ".dat";
		return ss.str();
	}

	// Función para inicializar un archivo con la estructura definida
	void initializeFile(const string& filename, const char& marca) {
		tip_tabla = marca;
		reg_total = 0;
		reg_elim = 0;

		ofstream file(filename, ios::binary);

		file.write(reinterpret_cast<char*>(&tip_tabla), sizeof(tip_tabla));
		file.write(reinterpret_cast<char*>(&reg_total), sizeof(reg_total));
		file.write(reinterpret_cast<char*>(&reg_elim), sizeof(reg_elim));
		file.close();
		cout << "Archivo " << filename << " creado con la estructura correcta.\n";
	}

	void validarTabla() {
		string filename = archivo;
		ifstream file(filename, ios::binary);

		if (file) {
			// Leer la estructura del archivo
			file.read(reinterpret_cast<char*>(&tip_tabla), sizeof(tip_tabla));
			file.read(reinterpret_cast<char*>(&reg_total), sizeof(reg_total));
			file.read(reinterpret_cast<char*>(&reg_elim), sizeof(reg_elim));

			if (tip_tabla != marca || reg_total < 0 || reg_elim < 0 || reg_elim > reg_total) {
				cout << "Estructura del archivo " << filename << " inválido o datos corruptos.\n";
				// Generar nuevo nombre de archivo y renombrar el archivo actual
				string newFilename = generateRandomFilename(tabla);
				rename(filename.c_str(), newFilename.c_str());
				cout << "Archivo antiguo renombrado a: " << newFilename << endl;

				// Crear un nuevo archivo
				initializeFile(filename, marca);
			}
			else {
				cout << "Archivo existente " << filename << " es válido.\n";
			}
			file.close();
		}
		else {
			cout << "Archivo " << filename << " no existe, creando uno nuevo...\n";
			initializeFile(filename, marca);
		}
	}

	void printCentered(const string& text, int width) {
		int len = static_cast<int>(text.length());
		int padding = (width - len) / 2;
		if (padding > 0) {
			cout << setw(padding + len) << text << setw(width - padding - len) << "";
		}
		else {
			cout << text;
		}
	}

	void imprimirRegistro() {
		cout << "|" << left << setw(5) << setfill(' ') << cliente->getIdentificador();
		cout << "|" << left << setw(3) << setfill(' ') << cliente->getEstado();
		cout << "|" << left << setw(20) << setfill(' ') << cliente->getNombre();
		cout << "|" << left << setw(20) << setfill(' ') << cliente->getApellido();
		cout << "|" << setw(20) << setfill(' ') << cliente->getCelular();
		cout << "|" << left << setw(32) << setfill(' ') << cliente->getCorreo() << "|" << endl;
		cout << "|" << left << setw(32) << setfill(' ') << cliente->getContraseña() << "|" << endl;
	}

	void imprimirLinea(int largo, char caracter) {
		cout << setw(largo) << setfill(caracter) << "" << endl;
	}

	void imprimirEncabezado() {
		cout << endl;
		imprimirLinea(107, '-');
		cout << "| Id. |Est|       Nombre       |      Apellido      |       Celular      |            Correo              |" << endl;
		imprimirLinea(107, '-');
	}

	void listar() {
		cliente = new Clientes();
		ifstream fentrada(archivo, ios::in | ios::binary);
		fentrada.seekg(5, ios::beg); // salta al Byte 5, obviando mi cabecera para poder imprimir correctamente
		imprimirEncabezado();
		while (cliente->leerArchivo(fentrada) == true) {
			if (cliente->getEstado() == 'A') {
				imprimirRegistro();
			}
		}
		imprimirLinea(107, '-');
		fentrada.close();
	}

	void adicionarNuevo() {
		reg_total++; //modificamos el contador de registros
		unsigned short identificador = reg_total;
		unsigned char estado = 'A';
		string nombre, apellido, celular, correo,contraseña;

		cout << endl << endl << "Introducir los siguientes datos --->>> :" << endl;
		fflush(stdin);
		cin.ignore(); // Limpiar el buffer del cin

		cout << "Nombre : ";
		getline(cin, nombre);

		cout << "Apellido : ";
		getline(cin, apellido);

		cout << "Celular : ";
		getline(cin, celular);

		cout << "Correo : ";
		getline(cin, correo);

		cout << "Contraseña :";
		getline(cin, contraseña);

		cliente = new Clientes();
		cliente->setClientes(identificador, estado, nombre, apellido, celular, correo,contraseña);

		ofstream fsalida(archivo, ios::out | ios::binary | ios::app);

		if (fsalida.is_open()) {
			cliente->guardarArchivo(fsalida);
			fsalida.close();
			cout << "Contacto agregado correctamente." << endl;
		}
		else {
			cout << "Error al abrir el archivo para escribir." << endl;
		}
	}

	void actualizarCabezera() {
		fstream fes(archivo, ios::in | ios::out | ios::binary);
		cliente->actualizarMetaData(fes, reg_total, reg_elim);
		fes.close();
	}

	unsigned int buscarReg(int registro, bool imprimir) {
		reg_posicion = 0;
		cliente = new Clientes();
		ifstream fentrada(archivo, ios::in | ios::binary);
		if (cliente->buscar(fentrada, registro) == true) {
			reg_posicion = fentrada.tellg(); // capturamos la posicion de Byte de este registro en el archivo

			cliente->leerArchivo(fentrada);
			if (fentrada.eof()) { cout << endl << "Registro no existe"; }

			if (imprimir) {
				imprimirEncabezado();
				imprimirRegistro();
				imprimirLinea(107, '-');
			}
		}
		fentrada.close();
		return(reg_posicion);
	}

	void desactivarReg(unsigned int posicion) {
		fstream file(archivo, ios::in | ios::out | ios::binary);
		if (file.is_open()) {
			if (cliente->modificarEstado(file, posicion, 'E')) {
				cout << "Contacto eliminado correctamente." << endl;
				reg_elim++; //modificamos el contador de registros eliminados
			}
			else {
				cout << "Error al eliminar el contacto." << endl;
			}
			file.close();
		}
		else {
			cout << "Error al abrir el archivo para eliminarlo." << endl;
		}
	}

	void activarReg(unsigned int posicion) {
		fstream file(archivo, ios::in | ios::out | ios::binary);
		if (file.is_open()) {
			if (cliente->modificarEstado(file, posicion, 'A')) {
				cout << "Contacto modificado correctamente." << endl;
				reg_elim--; //modificamos el contador de registros eliminados
			}
			else {
				cout << "Error al modificar el contacto." << endl;
			}
			file.close();
		}
		else {
			cout << "Error al abrir el archivo para modificarlo." << endl;
		}
	}
};

