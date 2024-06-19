#include "ClientesYMesas.h"

Cliente::Cliente(string n, string a, string c, string t)
    : nombre(n), apellido(a), correo(c), telefono(t), siguiente(nullptr) {}

Mesa::Mesa(string n, int l)
    : nombre(n), lugares(l), estado("Libre"), cliente("-"), siguiente(nullptr) {}

