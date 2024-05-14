// Parte Establecimiento.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Establecimiento.h"
#include "ArchivoEstablecimiento.h"

int main()
{
    ArchivoEstablecimiento* lug = new ArchivoEstablecimiento("Est00.dat");
    int op;
    do {
        cout << endl;
        cout << "Menu de administracion" << endl;
        cout << "1.- Agregar Establecimiento." << endl;
        cout << "2.- eliminar Establecimiento." << endl;
        cout << "3.- Mostrar Establecimiento" << endl;
        cout << "4.-Buscar Establecimiento" << endl;
        cout << "5.- Modificar Estbalecimiento" << endl;
        cout << "6.-salir del menu" << endl;
        cin >> op;
        switch (op)
        {
        case 1:
            system("cls");
            lug->adicionarNuevo();
            break;
        case 2:
            system("cls");
            lug->eliminarCod();
            break;
        case 3:
            system("cls");
            lug->listar();
            break;
        case 4:
            system("cls");
            lug->buscarCod();
            break;
        case 5:
            system("cls");
            lug->modificarCod();
        case 6:
            system("cls");
            break;
        default:
            cout << "error de datos intente nuevamente" << endl;
            break;
        }
    } while (op != 6);
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
