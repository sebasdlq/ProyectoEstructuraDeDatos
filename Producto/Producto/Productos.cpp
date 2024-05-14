// Producto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Produc.h"
#include "ABMProducto.cpp"
using namespace std;
#include <fstream>
void main()
{
    ABMProducto *aux=new ABMProducto("Produc00.dat");
    int op;
    int adm;
    do
    {
        cout << "Menu de productos" << endl;
        cout << "1.- mostrar productos" << endl;
        cout << "2.-ver pedido." << endl;
        cout << "3.salir" << endl;
        cin >> op;
        switch (op)
        {
        case 1:
            aux->listar();
            break;
        case 2:
            break;
        case 3:
            do {
                cout << "cerrando el programa" << endl;
                break;
        case 99:
            do {
                cout << endl;
                cout << "    Opciones  de administrador         " << endl;
                cout << "1.- Agregar producto." << endl;
                cout << "2.- eliminar producto." << endl;
                cout << "3.- mostrar lista de productos." << endl;
                cout << "4.-Buscar producto especifico." << endl;
                cout << "5.- Modificar producto." << endl;
                cout << "6.-salir del modo administrador." << endl;
                cin >> adm;
                switch (adm)
                {
                case 1:
                    system("cls");
                    aux->adicionarNuevo();
                    break;
                case 2:
                    system("cls");
                    aux->eliminarReg();
                    break;
                case 3:
                    system("cls");
                    aux->listar();
                    break;
                case 4:
                    system("cls");
                    aux->buscarReg();
                    break;
                case 5:
                    system("cls");
                    aux->modificarReg();
                    break;
                case 6:
                    system("cls");
                    break;
                default:
                    cout << "error de datos intente nuevamente" << endl;
                    break;
                }
            } while (adm != 6);
            break;
        default:
            cout << "error intente nuevamente" << endl;
            break;
            } while (adm != 3);
            break;
        }
    } while (op != 3);
}
