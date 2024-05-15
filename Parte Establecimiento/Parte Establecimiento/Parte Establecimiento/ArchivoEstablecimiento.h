#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Establecimiento.h"
using namespace std;
class ArchivoEstablecimiento
{
protected:
	string nomArch;
	Establecimiento* est;
public:
	ArchivoEstablecimiento(string nomAr);
	void introducirDatos(Establecimiento* newReg);
	void mostrarEst(int nroReg);
	void adicionarNuevo();
	void listar();
	int buscarCod();
	void eliminarCod();
	void modificarCod();
};

