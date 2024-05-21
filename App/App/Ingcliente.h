#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "Cliente.h"
using namespace std;

class Ingcliente {
private:
	string Archivo;
	Cliente* cliente;
public:
	Ingcliente(string nomArch);
	void Iniciar_sesion(Cliente* newReg);
	void mostrar_usuario(int nroReg);
	void nuevo_cliente();
	void listar();
	int buscarReg();
	void eliminarReg();
	void modificarReg();
};