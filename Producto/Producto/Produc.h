#pragma once
#include <string>
using namespace std;
class Produc
{private:
	int precio;
	string descripcion;
	string nombre;
public:
	Produc();
	~Produc();
	void datos(int p, string d, string n);
	int getp();
	string get_d();
	string get_n();
	void agregar();
	void mostrar();
	void eliminar();
};

