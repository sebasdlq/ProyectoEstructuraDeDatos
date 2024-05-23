#include "utilitarios.h"
#include "ABMClientes.h"

#include <iostream>


using namespace std;

int validarRango(string accion, unsigned short final) {
    if (final == 0) {
        cout << "No existen registros en la tabla para " << accion << "!!!" << endl;
        return -1;
    }
    int opcion = 0;
    cout << "Ingrese el número de registro a " << accion << " : ";
    cin >> opcion;
    if (opcion < 1 || opcion > final) {
        cout << "ERROR: El número de registro debe estar entre 1 y " << final << " !!!" << endl;
        return -1;
    }
    return opcion;
}

int main() {
    /*
    setupConsole(); // setea la consola para Windows a UTF-8
    cout << "Memoria libre (bytes): " << getFreeMemory() << endl;*/

    int nroReg;
    ABMClientes* abmClient = new ABMClientes("clientes", 'c');
    abmClient->validarTabla();

    char opcion;
    do {
        cout << "\n--- Menú ---" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Modificar cliente" << endl;
        cout << "3. Eliminar cliente" << endl;
        cout << "4. Ver lista de clientes" << endl;
        cout << "5. Buscar cliente" << endl;
        cout << "6. Salir" << endl;
        cout << "Registros: " << abmClient->getReg_total() << " - " << "Eliminados: " << abmClient->getReg_elim() << endl << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case '1':
            abmClient->adicionarNuevo();
            abmClient->actualizarCabezera();
            break;
        case '2':
            nroReg = validarRango("modificar", abmClient->getReg_total());
            if (nroReg != -1) {
                unsigned int regModificar;
                regModificar = abmClient->buscarReg(nroReg, false);
                if (regModificar == 0) {
                    cout << "Error: El registro " << regModificar << " no existe!!!" << endl;
                }
                else {
                    abmClient->activarReg(regModificar);
                    abmClient->actualizarCabezera();
                }
            }
            break;
        case '3': // Eliminar
            nroReg = validarRango("eliminar", abmClient->getReg_total());
            if (nroReg != -1) {
                unsigned int regEliminar;
                regEliminar = abmClient->buscarReg(nroReg, false);
                if (regEliminar == 0) {
                    cout << "Error: El registro " << regEliminar << " no existe!!!" << endl;
                }
                else {
                    abmClient->desactivarReg(regEliminar);
                    abmClient->actualizarCabezera();
                }
            }
            break;
        case '4':  // Listar
            abmClient->listar();
            break;
        case '5':  // Buscar
            nroReg = validarRango("buscar", abmClient->getReg_total());
            if (nroReg != -1) {
                abmClient->buscarReg(nroReg, true);
            }
            break;
        case '6':
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (opcion != '6');
    return 0;
}