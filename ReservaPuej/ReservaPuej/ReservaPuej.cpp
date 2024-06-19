#include "menu.h"
#include "ListaProductos.h"
#include "utilitarios.h" // Incluir utilitarios.h para mostrarEncabezado y pausarPantalla
#include <iostream>
#include <thread> // Para usar sleep_for
#include <chrono> // Para usar chrono_literals

using namespace std;

int main() {
    int opcionMenu;
    bool salir = false;

    while (!salir) {
        mostrarEncabezado();
        cout << "Seleccione el menú que desea ejecutar:\n";
        cout << "1. Sistema de Reservas\n";
        cout << "2. Gestión de Productos\n";
        cout << "3. Gestion de Establecimientos\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcionMenu;

        switch (opcionMenu) {
        case 1:
            menuSistemaReservas();
            pausarPantalla();
            break;
        case 2: {
            ListaProductos* producto = new ListaProductos("Producto.dat");
            mostrarMenu(producto);
            delete producto; // Liberar memoria
            pausarPantalla();
            break;
        }
        case 3: {
            menuEstablecimientos();
            pausarPantalla();
            break;
        }
        case 4:
            salir = true;
            cout << "Saliendo del programa...\n";
            this_thread::sleep_for(chrono::seconds(2)); // Pausa para mostrar el mensaje
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
            this_thread::sleep_for(chrono::seconds(2)); // Pausa para mostrar el mensaje
            break;
        }

        if (!salir) {
            limpiarPantalla();
        }
    }

    return 0;
}
