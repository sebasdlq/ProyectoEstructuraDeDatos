#include "Establecimiento.h"
#include "EstablecimientoManager.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void menu() {
    cout << "1. Agregar Establecimiento" << endl;
    cout << "2. Modificar Establecimiento" << endl;
    cout << "3. Eliminar Establecimiento" << endl;
    cout << "4. Listar Establecimientos" << endl;
    cout << "5. Buscar Establecimiento por ID" << endl;
    cout << "6. Buscar Establecimiento por Email" << endl;
    cout << "7. Buscar Establecimiento por Nombre" << endl;
    cout << "8. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    EstablecimientoManager manager("establecimientos.bin");

    int opcion;
    do {
        menu();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int id;
            string nombre, email, contrasena, telefono, ubicacion;
            cout << "Ingrese ID: ";
            cin >> id;
            cout << "Ingrese Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese Email: ";
            getline(cin, email);
            cout << "Ingrese Contrasena: ";
            getline(cin, contrasena);
            cout << "Ingrese Telefono: ";
            getline(cin, telefono);
            cout << "Ingrese Ubicacion: ";
            getline(cin, ubicacion);

            Establecimiento est(id, nombre, email, contrasena, telefono, ubicacion);
            if (manager.agregarEstablecimiento(est)) {
                cout << "Establecimiento agregado correctamente." << endl;
            }
            else {
                cout << "Error al agregar el establecimiento." << endl;
            }
            break;
        }
        case 2: {
            int id;
            string nombre, email, contrasena, telefono, ubicacion;
            cout << "Ingrese ID del Establecimiento a modificar: ";
            cin >> id;
            cout << "Ingrese Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese Email: ";
            getline(cin, email);
            cout << "Ingrese Contrasena: ";
            getline(cin, contrasena);
            cout << "Ingrese Telefono: ";
            getline(cin, telefono);
            cout << "Ingrese Ubicacion: ";
            getline(cin, ubicacion);

            Establecimiento est(id, nombre, email, contrasena, telefono, ubicacion);
            if (manager.modificarEstablecimiento(est)) {
                cout << "Establecimiento modificado correctamente." << endl;
            }
            else {
                cout << "Error al modificar el establecimiento." << endl;
            }
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese ID del Establecimiento a eliminar: ";
            cin >> id;
            if (manager.eliminarEstablecimiento(id)) {
                cout << "Establecimiento eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar el establecimiento." << endl;
            }
            break;
        }
        case 4: {
            manager.imprimirEstablecimientos();
            break;
        }
        case 5: {
            int id;
            cout << "Ingrese ID del Establecimiento a buscar: ";
            cin >> id;
            try {
                Establecimiento est = manager.buscarEstablecimientoPorId(id);
                cout << "ID: " << est.getId() << ", Nombre: " << est.getNombre()
                    << ", Email: " << est.getEmail() << ", Contrasena: " << est.getContrasena()
                    << ", Telefono: " << est.getTelefono() << ", Ubicacion: " << est.getUbicacion() << endl;
            }
            catch (const runtime_error& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 6: {
            string email;
            cout << "Ingrese Email del Establecimiento a buscar: ";
            cin.ignore();
            getline(cin, email);
            try {
                Establecimiento est = manager.buscarEstablecimientoPorEmail(email);
                cout << "ID: " << est.getId() << ", Nombre: " << est.getNombre()
                    << ", Email: " << est.getEmail() << ", Contrasena: " << est.getContrasena()
                    << ", Telefono: " << est.getTelefono() << ", Ubicacion: " << est.getUbicacion() << endl;
            }
            catch (const runtime_error& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 7: {
            string nombre;
            cout << "Ingrese Nombre del Establecimiento a buscar: ";
            cin.ignore();
            getline(cin, nombre);
            try {
                Establecimiento est = manager.buscarEstablecimientoPorNombre(nombre);
                cout << "ID: " << est.getId() << ", Nombre: " << est.getNombre()
                    << ", Email: " << est.getEmail() << ", Contrasena: " << est.getContrasena()
                    << ", Telefono: " << est.getTelefono() << ", Ubicacion: " << est.getUbicacion() << endl;
            }
            catch (const runtime_error& e) {
                cerr << e.what() << endl;
            }
            break;
        }
        case 8: {
            cout << "Saliendo del programa." << endl;
            break;
        }
        default: {
            cout << "Opcion no valida. Intente de nuevo." << endl;
            break;
        }
        }
    } while (opcion != 8);

    return 0;
}
