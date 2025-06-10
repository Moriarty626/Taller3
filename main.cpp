#include <iostream>
#include "Sistema.h"

int main() {
    Sistema sistema;
    sistema.cargarDatos();
    sistema.mostrarMenu();
    sistema.guardarDatos();
    return 0;
}