#include "ListaProductos.h"
#include <fstream>
#include <iostream>

    ListaProductos::ListaProductos(const string& filename1) { filename = filename1;}

ListaProductos::~ListaProductos() {
    /*NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        NodoProducto* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }*/
}

void ListaProductos::introducirDatos(ProductoManager* prod) {
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
    prod->guardardatos(id, idEstablecimiento, precio, nombre, descripcion);
}

void ListaProductos::agregarProducto() {
   /* NodoProducto* nuevoNodo = new NodoProducto(producto);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;*/
   /* ofstream fsalida(nomArchivo, ios::app | ios::binary);
    cliente = new UsuarioManager(nomArchivo);
    introducirDatos(cliente);
    cliente->guardarUsuario(fsalida);
    fsalida.close();*/
    ofstream archivo(filename, ios::app | ios::binary);
    cabeza = new ProductoManager(filename);
    introducirDatos(cabeza);
    cabeza->agregarProducto(archivo);
}

/*void ListaProductos::imprimirProductos() const {
    NodoProducto* actual = cabeza;
    int n = 0;
    while (actual != nullptr) {
        n++;
        cout << n << ".- ID:" << actual->producto.getId() << ", IDEsta:"<<actual->producto.getIdEstablecimiento() << ", Nombre: " << actual->producto.getNombre() << ", Precio: " << actual->producto.getPrecio() << ", Descrip:"<<actual->producto.getDescripcion()<<"\n";
        actual = actual->siguiente;
    }
}

void ListaProductos::modificarProducto(const Producto& producto) {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        if (actual->producto.getId() == producto.getId()) {
            actual->producto = producto; // Actualizamos el producto en la lista
            ProductoManager pm(filename); // Creamos un ProductoManager para actualizar el archivo
            pm.modificarProducto(producto); // Llamamos al método modificarProducto del ProductoManager
            return;
        }
        actual = actual->siguiente;
    }
    cerr << "Producto no encontrado." << endl;
}

bool ListaProductos::eliminarProducto(int id) {
    NodoProducto* actual = cabeza;
    NodoProducto* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->producto.getId() == id) {
            if (anterior == nullptr) {
                // Si el nodo a eliminar es el primero (cabeza)
                cabeza = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual; // Liberamos la memoria del nodo eliminado

            // Actualizar el archivo usando ProductoManager
            ProductoManager pm(filename);
            return pm.eliminarProducto(id); // Llamamos al método eliminarProducto del ProductoManager
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cerr << "Producto no encontrado." << endl;
    return false;
}

Producto ListaProductos::buscarProductoPorId(int id) {
    NodoProducto* actual = cabeza;
    while (actual != nullptr) {
        if (actual->producto.getId() == id) {
            return actual->producto;
        }
        actual = actual->siguiente;
    }
    cerr << "Producto no encontrado." << endl;
    return Producto(); // Retorna un Producto vacío}*/


