#include "menu.h"
#include "SistemaYListaEspera.h"
#include "ListaProductos.h"
#include "Establecimiento.h"
#include "EstablecimientoManager.h"
#include "utilitarios.h"
#include <iostream>
using namespace std;

void menuSistemaReservas() {
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
                break;
        }

    } while (opcion != 9);
}

void mostrarMenu(ListaProductos* producto) {
    int op = 0;

    do {
        cout << "1.-Agregar productos\n";
        cout << "2.-Mostrar productos\n";
        cout << "3.-Modificar productos\n";
        cout << "4.-Eliminar productos\n";
        cout << "0.-Salir\n";
        cout << "Ingrese una opción: ";
        cin >> op;

        switch (op) {
        case 1: {
            // Capturar datos del nuevo producto
            int id, idEstablecimiento;
            string nombre, descripcion;
            double precio;

            cout << "Ingrese ID del producto: ";
            cin >> id;
            cout << "Ingrese ID del establecimiento: ";
            cin >> idEstablecimiento;
            cin.ignore(); // Limpiar el buffer de entrada
            cout << "Ingrese nombre del producto: ";
            getline(cin, nombre);
            cout << "Ingrese descripción del producto: ";
            getline(cin, descripcion);
            cout << "Ingrese precio del producto: ";
            cin >> precio;

            // Crear un objeto Producto con los datos capturados
            Producto nuevoProducto(id, idEstablecimiento, nombre, descripcion, precio);

            // Agregar el producto a la lista
            producto->agregarProducto(nuevoProducto);
            break;
        }
        case 2: {
            producto->imprimirProductos();
            break;
        }
        case 3: {
            // Modificar producto
            int idModificar;
            cout << "Ingrese ID del producto a modificar: ";
            cin >> idModificar;

            // Buscar el producto por ID
            Producto productoModificar = producto->buscarProductoPorId(idModificar);
            if (productoModificar.getId() == 0) {
                break; // Producto no encontrado
            }

            // Capturar nuevos datos del producto
            int nuevoIdEstablecimiento;
            string nuevoNombre, nuevaDescripcion;
            double nuevoPrecio;

            cout << "Ingrese nuevo ID del establecimiento: ";
            cin >> nuevoIdEstablecimiento;
            cin.ignore(); // Limpiar el buffer de entrada
            cout << "Ingrese nuevo nombre del producto: ";
            getline(cin, nuevoNombre);
            cout << "Ingrese nueva descripción del producto: ";
            getline(cin, nuevaDescripcion);
            cout << "Ingrese nuevo precio del producto: ";
            cin >> nuevoPrecio;

            // Actualizar los datos del producto
            productoModificar.setIdEstablecimiento(nuevoIdEstablecimiento);
            productoModificar.setNombre(nuevoNombre);
            productoModificar.setDescripcion(nuevaDescripcion);
            productoModificar.setPrecio(nuevoPrecio);

            // Modificar el producto en la lista y en el archivo
            producto->modificarProducto(productoModificar);
            break;
        }
        case 4: {
            // Eliminar producto
            int idEliminar;
            cout << "Ingrese ID del producto a eliminar: ";
            cin >> idEliminar;

            // Eliminar el producto de la lista y del archivo
            if (producto->eliminarProducto(idEliminar)) {
                cout << "Producto eliminado correctamente." << endl;
            }
            else {
                cerr << "No se pudo eliminar el producto." << endl;
            }
            break;
        }
        case 0:
            cout << "Vaya bien\n";
            break;
        default:
            cout << "Escriba bien\n";
            break;
        }
    } while (op != 0);
}

//Establecimientos

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

void menuEstablecimientos()
{
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
}

