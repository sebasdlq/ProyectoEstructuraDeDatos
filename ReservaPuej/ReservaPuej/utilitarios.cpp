#include "utilitarios.h"
#include <cstdlib> // Para usar system("clear") o system("cls")
#include <iostream>
#include <thread> // Para usar sleep_for
#include <chrono> // Para usar chrono_literals

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sys/sysinfo.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#endif

unsigned long long getFreeMemory() {
    #if defined(_WIN32)
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    return statex.ullAvailPhys;
    #elif defined(__linux__)
    struct sysinfo info;
    sysinfo(&info);
    return info.freeram * info.mem_unit;
    #elif defined(__APPLE__) && defined(__MACH__)
    vm_size_t page_size;
    mach_port_t mach_host = mach_host_self();
    vm_statistics64_data_t vm_stats;
    mach_msg_type_number_t count = sizeof(vm_stats) / sizeof(natural_t);
    if (host_page_size(mach_host, &page_size) == KERN_SUCCESS &&
        host_statistics64(mach_host, HOST_VM_INFO, (host_info64_t)&vm_stats, &count) == KERN_SUCCESS) {
        return vm_stats.free_count * page_size;
    }
    return 0;
    #endif
}

void limpiarPantalla() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void setupConsole() {
    #if defined(_WIN32)
    // Cambiar la página de códigos de la consola a UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Establecer la página de código de entrada a UTF-8
    SetConsoleCP(CP_UTF8);
    #endif
}

void mostrarEncabezado() {
    limpiarPantalla();
    std::cout << "=================================================\n";
    std::cout << "              * Tiluchi Codeworks *              \n";
    std::cout << "=================================================\n";
    std::cout << "           by: Oxiel Contreras y Andres Osinaga  \n";
    std::cout << "=================================================\n";
    std::cout << "                 // RESERVA PUEJ \\\\                 \n";
    std::cout << "          ---- Sistema de Reservas ----           \n";
    std::cout << "=================================================\n";
    std::cout << "Descripción:\n";
    std::cout << "RESERVA PUEJ es un sistema de gestión de reservas\n";
    std::cout << "diseñado para facilitar la administración de mesas\n";
    std::cout << "y clientes en establecimientos. Permite agregar,\n";
    std::cout << "buscar y gestionar reservas de manera eficiente.\n";
    std::cout << "=================================================\n\n";
}

void pausarPantalla() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

