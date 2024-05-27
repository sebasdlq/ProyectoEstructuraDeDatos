#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Establecimiento
{
private:
    unsigned short identificador;
    unsigned char  estado;
    string nombre;
    string celular;
    string correo;
    string contrasena;
    string ubicacion;
public:
    Establecimiento() : identificador(0), estado('A'), nombre(""), celular(""), correo(""), contrasena(""), ubicacion("") {}

    Establecimiento(unsigned short iden, unsigned char esta, string nomb, string celu, string corr, string contra, string ubi)
        : identificador(iden), estado(esta), nombre(nomb), celular(celu), correo(corr), contrasena(contra), ubicacion(ubi) {}

    unsigned short getIdentificador() const { return identificador; }
    void setIdentificador(unsigned short iden) { identificador = iden; }

    unsigned char  getEstado() const { return estado; }
    void setEstado(unsigned char esta) { estado = esta; }

    string getNombre() const { return nombre; }
    void setNombre(string nomb) { nombre = nomb; }

    string getCelular() const { return celular; }
    void setCelular(string celu) { celular = celu; }

    string getCorreo() const { return correo; }
    void setCorreo(string corr) { correo = corr; }

    string getContrasena() const { return contrasena; }
    void setContrasena(string contra) { contrasena = contra; }

    string getUbicacion() const { return ubicacion; }
    void setUbicacion (string ubi) { ubicacion = ubi; }

    void setEstablecimiento(unsigned short iden, unsigned char esta, string nomb, string celu, string corr, string contra, string ubi) {
        identificador = iden;
        estado = esta;
        nombre = nomb;
        celular = celu;
        correo = corr;
        contrasena = contra;
        ubicacion = ubi;
    }

    void imprimirCliente() const {
        if (estado == 'A') {
            cout << "Identificador: " << identificador << endl;
            cout << "Estado: " << estado << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Celular: " << celular << endl;
            cout << "Correo: " << correo << endl;
            cout << "Contraseña" << contrasena << endl;
            cout << "Ubicacion" << ubicacion << endl;
        }
    }

    bool leerArchivo(ifstream& fentrada) {
        bool k = false;
        if (fentrada.is_open()) {

            fentrada.read(reinterpret_cast<char*>(&identificador), sizeof(identificador));

            if (fentrada.eof()) return false;

            unsigned short tamano;
            fentrada.read(reinterpret_cast<char*>(&tamano), sizeof(tamano));

            fentrada.read(reinterpret_cast<char*>(&estado), sizeof(estado));

            unsigned short nombreSize;
            fentrada.read(reinterpret_cast<char*>(&nombreSize), sizeof(nombreSize));
            nombre.resize(nombreSize);
            fentrada.read(&nombre[0], nombreSize);

            unsigned short celularSize;
            fentrada.read(reinterpret_cast<char*>(&celularSize), sizeof(celularSize));
            celular.resize(celularSize);
            fentrada.read(&celular[0], celularSize);

            unsigned short correoSize;
            fentrada.read(reinterpret_cast<char*>(&correoSize), sizeof(correoSize));
            correo.resize(correoSize);
            fentrada.read(&correo[0], correoSize);

            unsigned short contrasenaSize;
            fentrada.read(reinterpret_cast<char*>(&contrasenaSize), sizeof(contrasenaSize));
            contrasena.resize(contrasenaSize);
            fentrada.read(&contrasena[0], contrasenaSize);

            unsigned short ubicacionSize;
            fentrada.read(reinterpret_cast<char*>(&ubicacionSize), sizeof(ubicacionSize));
            ubicacion.resize(ubicacionSize);
            fentrada.read(&ubicacion[0], ubicacionSize);

            if (!fentrada.eof()) {
                k = true;
            }
        }
        else {
            cout << endl << "Archivo no existe";
        }
        return k;
    }

    unsigned short getTamBytesRegistro() const {
        return (sizeof(identificador) + sizeof(estado) + nombre.size() + celular.size() + correo.size() + contrasena.size()
            + (sizeof(identificador) * 6) + ubicacion.size());			 
    }

    void guardarArchivo(ofstream& fsalida) const {
        fsalida.write(reinterpret_cast<const char*>(&identificador), sizeof(identificador));

        unsigned short tamano = getTamBytesRegistro(); // conseguir el tamano del registro total
        fsalida.write(reinterpret_cast<const char*>(&tamano), sizeof(tamano));

        fsalida.write(reinterpret_cast<const char*>(&estado), sizeof(estado));

        unsigned short nombreSize = nombre.size();
        fsalida.write(reinterpret_cast<const char*>(&nombreSize), sizeof(nombreSize));
        fsalida.write(nombre.c_str(), nombreSize);

        unsigned short celularSize = celular.size();
        fsalida.write(reinterpret_cast<const char*>(&celularSize), sizeof(celularSize));
        fsalida.write(celular.c_str(), celularSize);

        unsigned short correoSize = correo.size();
        fsalida.write(reinterpret_cast<const char*>(&correoSize), sizeof(correoSize));
        fsalida.write(correo.c_str(), correoSize);

        unsigned short contrasenaSize = contrasena.size();
        fsalida.write(reinterpret_cast<const char*>(&contrasenaSize), sizeof(contrasenaSize));
        fsalida.write(contrasena.c_str(), contrasenaSize);

        unsigned short ubicacionSize = ubicacion.size();
        fsalida.write(reinterpret_cast<const char*>(&ubicacionSize), sizeof(ubicacionSize));
        fsalida.write(contrasena.c_str(), ubicacionSize);
    }

    void actualizarMetaData(fstream& fes, unsigned short& total, unsigned short& eliminado) const {
        if (fes.is_open()) {
            fes.seekp(1, ios::beg); //nos vamos al 2 Byte del archivo para registrar reg_total  
            fes.write(reinterpret_cast<const char*>(&total), sizeof(total));
            fes.write(reinterpret_cast<const char*>(&eliminado), sizeof(eliminado));
        }
    }

    bool buscar(ifstream& fentrada, int nroReg) {
        bool k = false;
        if (fentrada.is_open()) {
            unsigned short tamano;
            fentrada.seekg(6, ios::beg); // saltamos la cabezera
            if (fentrada.eof()) return false;
            fentrada.read(reinterpret_cast<char*>(&identificador), sizeof(identificador));
            while (identificador != nroReg)
            {
                fentrada.read(reinterpret_cast<char*>(&tamano), sizeof(tamano));
                fentrada.seekg(tamano - 4, ios::cur); // avanza al siguiente registro
                if (fentrada.eof()) return false;
                fentrada.read(reinterpret_cast<char*>(&identificador), sizeof(identificador));
            }
            fentrada.seekg(-2, ios::cur); //volvemos 2 bytes para atras            
            if (identificador == nroReg) { 
                k = true; 
            }
        }
        else {
            cout << endl << "Archivo no existe";
        }
        return k;
    }
    bool buscar(ifstream& fentrada, string correo);

    bool modificarEstado(fstream& fes, unsigned int posicion, char nuevoEstado) {
        bool k = false;
        if (fes.is_open()) {
            fes.seekp(posicion + 4, ios::beg); // Avanzamos 4 bytes adicionales al inicio del registro, osea al byte 5
            estado = nuevoEstado;
            fes.write(reinterpret_cast<const char*>(&estado), sizeof(estado));
            k = true;
        }
        else {
            cout << endl << "Archivo no existe";
        }
        return k;

    }
};

