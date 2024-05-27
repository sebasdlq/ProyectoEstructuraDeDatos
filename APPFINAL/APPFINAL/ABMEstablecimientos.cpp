#include "ABMEstablecimientos.h"

unsigned int ABMEstablecimiento::buscarReg(string correo, bool imprimir)
{
	reg_posicion = 0;
	establecimeinto = new Establecimiento();
	ifstream fentrada(archivo, ios::in | ios::binary);
	if (establecimeinto->buscar(fentrada, correo)) {
		reg_posicion = fentrada.tellg(); // capturamos la posicion de Byte de este registro en el archivo

		establecimeinto->leerArchivo(fentrada);
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
