#!/bin/bash
# Eliminar el ejecutable anterior si existe
if [ -f sistemaReservas ]; then
    rm sistemaReservas
    echo "Eliminado el ejecutable anterior: sistemaReservas"
fi

# Eliminar todos los archivos objeto si existen
if ls *.o 1> /dev/null 2>&1; then
    rm *.o
    echo "Eliminados todos los archivos objeto anteriores"
fi

# Compilar todos los archivos .cpp
g++ -Wall -Wextra -g3 ClientesYMesas.cpp SistemaYListaEspera.cpp Supermain.cpp WhatsAppMessenger.cpp -lcurl -o sistemaReservas
echo "Compilación completada. Ejecutable generado: sistemaReservas"

