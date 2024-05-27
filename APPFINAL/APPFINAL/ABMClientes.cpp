#include "ABMClientes.h"

unsigned int ABMClientes::buscarReg(string correo, bool imprimir)
{
	reg_posicion = 0;
	cliente = new Clientes();
	ifstream fentrada(archivo, ios::in | ios::binary);
	if (cliente->buscar(fentrada, correo)) {
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
