#include "SistemaYListaEspera.h"
#include "utilitarios.h"
#include <iostream> // Añadir esta línea
using namespace std; // Añadir esta línea
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
int main() {
    setupConsole(); // setea la consola para Windows a UTF-8
    limpiarPantalla();
    SistemaReservas sistema;
    
    // Modificar con la opcion de cargar desde el archivo
    sistema.agregarCliente("Oxiel", "Contreras", "oxiel.jr@gmail.com", "71631007");
    sistema.agregarCliente("Karen", "Infantas", "karen@gmail.com", "77377003");
    sistema.agregarCliente("Enrique", "Contreras", "oxiel.contreras@gmail.com", "67898117");
    sistema.agregarCliente("Sebastian", "De La Quintana", "sdelaqui@gmail.com", "76047629");
    sistema.agregarCliente("Marco", "Mojica", "marco@gmail.com", "70805950");

    int opcion;
    do {
        sistema.mostrarMesas();
        sistema.mostrarListaEspera();
        
        cout << "----- Sistema de Reservas -----\n";
        cout << "1. Mostrar mesas\n";
        cout << "2. Mostrar lista de espera\n";
        cout << "3. Buscar cliente\n";
        cout << "4. Agregar cliente\n";
        cout << "5. Asignar mesa a cliente\n";
        cout << "6. Liberar mesa\n";
        cout << "7. Eliminar cliente de lista de espera\n";
        cout << "8. Mostrar lista de clientes\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                 limpiarPantalla();
                sistema.mostrarMesas();
                
                break;
            case 2:
                limpiarPantalla();
                sistema.mostrarListaEspera();
                break;
            case 3: {
                limpiarPantalla();
                string telefono;
                cout << "Ingrese el telefono del cliente: ";
                cin >> telefono;
                Cliente* cliente = sistema.buscarCliente(telefono);
                if (cliente != nullptr) {
                    cout << "Cliente encontrado: " << cliente->nombre << " " << cliente->apellido << endl;
                } else {
                    cout << "Cliente no encontrado.\n";
                }
                break;
            }
            case 4: {
                limpiarPantalla();
                string nombre, apellido, correo, telefono;
                cout << "Nombre: ";
                cin >> nombre;
                cout << "Apellido: ";
                cin >> apellido;
                cout << "Correo: ";
                cin >> correo;
                cout << "Telefono: ";
                cin >> telefono;
                sistema.agregarCliente(nombre, apellido, correo, telefono);
                break;
            }
            case 5: {
                 limpiarPantalla();
                string telefono;
                int lugares;
                cout << "Ingrese el telefono del cliente: ";
                cin >> telefono;
                cout << "Ingrese el número de lugares que desea: ";
                cin >> lugares;
                sistema.asignarMesa(telefono, lugares);
               
                break;
            }
            case 6: {
                 limpiarPantalla();
                string nombreMesa;
                cout << "Ingrese el nombre de la mesa a liberar: ";
                cin >> nombreMesa;
                sistema.liberarMesa(nombreMesa);
                break;
            }
            case 7: {
                limpiarPantalla();
                int id;
                cout << "Ingrese el ID del cliente a eliminar de la lista de espera: ";
                cin >> id;
                sistema.eliminarDeListaEspera(id);
               
                break;
            }
            case 8:
                limpiarPantalla();
                sistema.mostrarListaClientes();
                break;
            case 9:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opción no válida. Intente de nuevo.\n";
        }
        
        // sistema.mostrarMesas();
        // sistema.mostrarListaEspera();
        //system("clear");

    } while (opcion != 9);

    return 0;
}

