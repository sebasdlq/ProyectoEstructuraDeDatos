#include <iostream>
#include <string>
#include <fstream>
#include "ListaProductos.h"
using namespace std;

int main() {
    ListaProductos* producto = new ListaProductos("Producto.dat");
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
            cout << "Escribi bien\n";
            break;
        }
    } while (op != 0);

    delete producto; // Liberar memoria
    return 0;
}
