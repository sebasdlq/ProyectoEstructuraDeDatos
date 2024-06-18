#pragma once

// ------ INICIO 001 ------

// Para detectar la memoria libre de cualquier SO

#if defined(_WIN32)
#include <windows.h>

unsigned long long getFreeMemory() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    return statex.ullAvailPhys;
}

#elif defined(__linux__)
#include <sys/sysinfo.h>

unsigned long long getFreeMemory() {
    struct sysinfo info;
    sysinfo(&info);
    return info.freeram * info.mem_unit;
}

#elif defined(__APPLE__) && defined(__MACH__)
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>

unsigned long long getFreeMemory() {
    vm_size_t page_size;
    mach_port_t mach_port = mach_host_self();
    vm_statistics64_data_t vm_stats;
    mach_msg_type_number_t count = sizeof(vm_stats) / sizeof(natural_t);
    if (host_page_size(mach_port, &page_size) == KERN_SUCCESS &&
        host_statistics64(mach_port, HOST_VM_INFO, (host_info64_t)&vm_stats, &count) == KERN_SUCCESS) {
        return vm_stats.free_count * page_size;
    }
    return 0;
}
#endif

// ------ FIN 001 ------

// ------ INICIO 002 ------

// Para poder configurar la consola y flujo de entrada de Windows para UTF-8
// y poder escribir y visualizar UTF-8 con cmd o PowerShell

void setupConsole() {
    #if defined(_WIN32)
    // Cambiar la página de códigos de la consola a UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // Establecer la página de código de entrada a UTF-8
    SetConsoleCP(CP_UTF8);
    #endif
}

// ------ FIN 002 ------