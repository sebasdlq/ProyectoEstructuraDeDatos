#ifndef SESION_H
#define SESION_H

#include "ListaUsuarios.h"
#include "ListaEstablecimientos.h"

using namespace std;

class Sesion {
public:
    NodoUsuario* buscarUsuarioPorEmail(ListaUsuarios& listaUsuarios, const string& email);
    NodoEstablecimiento* buscarEstablecimientoPorEmail(ListaEstablecimientos& listaEstablecimientos, const string& email);
};

#endif // SESION_H

