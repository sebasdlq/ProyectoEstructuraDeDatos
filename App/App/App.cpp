#include <iostream>
#include "ListaDeComidas.h"
#include "Comida.h"

using namespace std;

int main()
{
	const string ARCHIVO_COMIDAS = "comidas.dat";

	ListaDeComidas lista(ARCHIVO_COMIDAS);
	int op;
	while (true)
	{
		cout << "\n1. Anadir";
		cout << "\n2. Mostrar";
		cout << "\n3. Eliminar";
		cin >> op;
		if (op == 1) {
			string nombre, descripcion;
			float precio;
			cout << "\nNombre: "; cin >> nombre;
			cout << "\ndescripcion: "; cin >> descripcion;
			cout << "\nprecio: "; cin >> precio;
			lista.Push(0, nombre, descripcion, precio);
		}
		else if (op == 2) {
			lista.MostrarComidas();
		}
		else if (op == 3) {
			unsigned int id;
			cout << "\nid: "; cin >> id;
			lista.eliminar(id);
		}
	}
}