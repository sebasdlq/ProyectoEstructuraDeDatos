#include "Clientes.h"

bool Clientes::buscar(ifstream& fentrada, string correo)
{
    bool k = false;
    if (fentrada.is_open()) {
        unsigned short tamano;
        fentrada.seekg(6, ios::beg); // saltamos la cabezera
        leerArchivo(fentrada);
        while (this->correo != correo);
        {
            if (fentrada.eof()) return false;
            leerArchivo(fentrada);
        }
        fentrada.seekg(-getTamBytesRegistro(), ios::cur); //volvemos 1 registro atras          
        if (this->correo == correo) { k = true; }
    }
    else {
        cout << endl << "Archivo no existe";
    }
    return k;
}
