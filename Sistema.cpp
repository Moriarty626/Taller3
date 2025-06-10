#include "Sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <functional>
#include <string.h>
/**
 * @brief Constructor de la clase Sistema.
 *        Inicializa las raíces del árbol binario de búsqueda (ABB) y del árbol AVL en nullptr.
 *
 * @return Una nueva instancia de la clase Sistema con las raíces de los árboles sin inicializar.
 */
Sistema::Sistema() : raizABB(nullptr), raizAVL(nullptr) {}

/**
 * @brief Destructor de la clase Sistema.
 *        Libera los recursos utilizados por la instancia de la clase Sistema.
 */
Sistema::~Sistema() {

}

static void guardarInOrderAVL(NodoAVL_Estudiantes* nodo, std::ofstream& fout) {
    if (!nodo) return;
    // subárbol izquierdo
    guardarInOrderAVL(nodo->izquierdo, fout);
    Estudiante* e = nodo->estudiante;
    // Formato: ID,Nombre,MM/DD/YYYY HH:MM,Pref1|Pref2|Pref3
    // ID y nombre
    fout << e->getId() << "," << e->getNombre() << ",";
    // Fecha
    fout << (e->getMes() < 10 ? "0" : "") << e->getMes() << "/"
         << (e->getDia() < 10 ? "0" : "") << e->getDia() << "/"
         << e->getAnio() << " ";
    // Hora
    fout << (e->getHora() < 10 ? "0" : "") << e->getHora() << ":"
         << (e->getMinuto() < 10 ? "0" : "") << e->getMinuto() << ",";
    // Preferencias
    for (int i = 0; i < e->getNumPreferencias(); ++i) {
        fout << e->getPreferencia(i);
        if (i < e->getNumPreferencias() - 1) fout << "|";
    }
    fout << "\n";
    // subárbol derecho
    guardarInOrderAVL(nodo->derecho, fout);
}


static void guardarInOrderABB(NodoABB_Instructores* nodo, std::ofstream& fout) {
    if (!nodo) return;
    // recorre subárbol izquierdo
    guardarInOrderABB(nodo->izquierdo, fout);
    // vuelca los datos del instructor
    Instructor* instr = nodo->instructor;
    fout << instr->getId() << ","
         << instr->getNombreCompleto() << ","
         << instr->getAnioIngreso() << ","
         << instr->getSueldoBase() << ","
         << instr->getTipoBaile() << "\n";
    // recorre subárbol derecho
    guardarInOrderABB(nodo->derecho, fout);
}
/**
 * @brief Guarda los datos en los archivos correspondientes.
 *
 * Este método crea y cierra los archivos "instructores.csv" y "estudiantes.csv".
 * Si los archivos no existen, el método los genera vacíos.
 */
void Sistema::guardarDatos() {
    // Guardar instructores
    std::ofstream fileIns("D:/Taller3/instructores.csv");
    if (!fileIns) {
        std::cerr << "Error al abrir instructores.csv para escritura\n";
    } else {
        guardarInOrderABB(raizABB, fileIns);
        fileIns.close();
    }

    // Guardar estudiantes
    std::ofstream fileEst("D:/Taller3/estudiantes.csv");
    if (!fileEst) {
        std::cerr << "Error al abrir estudiantes.csv para escritura\n";
    } else {
        guardarInOrderAVL(raizAVL, fileEst);
        fileEst.close();
    }
}

/**
 * @brief Muestra el menú principal del sistema y gestiona la selección de opciones por parte del usuario.
 *
 * Este método presenta un menú interactivo con diversas opciones relacionadas con la gestión
 * del sistema, como matricular estudiantes, calcular pagos, mostrar estudiantes, obtener un
 * instructor por ID, y eliminar un instructor. La interacción continúa hasta que el usuario
 * selecciona la opción para salir.
 *
 */
void Sistema::mostrarMenu() {
    int opcion;
    do {
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Matricular Estudiante\n";
        std::cout << "2. Calcular Pagos\n";
        std::cout << "3. Mostrar Estudiantes\n";
        std::cout << "4. Obtener Instructor por ID\n";
        std::cout << "5. Eliminar Instructor\n";
        std::cout << "6. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: matricularEstudiante(); break;
            case 2: calcularPagos(); break;
            case 3: mostrarEstudiantes(); break;
            case 4: obtenerInstructor(); break;
            case 5: eliminarInstructor(); break;
            case 6: std::cout << "Saliendo...\n"; break;
            default: std::cout << "Opcion invalida.\n"; break;
        }
    } while (opcion != 6);
}

/**
 * @brief Calcula y muestra los pagos de los instructores, incluyendo su sueldo bruto,
 *        cotización AFP y sueldo líquido, basado en la popularidad del tipo de baile
 *        entre los estudiantes y la antigüedad del instructor.
 *
 * Este método analiza las preferencias de los estudiantes almacenadas en un árbol AVL
 * para determinar el tipo de baile más popular. Posteriormente, utiliza esta información
 * para calcular los pagos de los instructores registrados en un árbol ABB.
 *
 * La información procesada incluye:
 * - Recuento de preferencias de los estudiantes por tipo de baile.
 * - Identificación del tipo de baile más popular.
 * - Cálculo del sueldo bruto, cotización AFP y sueldo líquido de cada instructor
 *   en base al año actual, el tipo de baile que enseñan y la popularidad de dicho tipo.
 *
 * El método recorre completamente el árbol AVL para contar las preferencias, y el árbol ABB
 * para calcular y mostrar los datos financieros de cada instructor.
 *
 */
void Sistema::calcularPagos() {
    // 1. Inicializar contadores por tipo de baile
    const char* tipos[] = { "Bachata", "Reggaeton", "Salsa", "Cumbia", "Tango" };
    int conteo[5] = { 0 };

    // 2. Contar preferencias recorriendo AVL
    std::function<void(NodoAVL_Estudiantes*)> contar = [&](NodoAVL_Estudiantes* nodo) {
        if (!nodo) return;
        contar(nodo->izquierdo);
        for (int i = 0; i < nodo->estudiante->getNumPreferencias(); ++i) {
            std::string pref = nodo->estudiante->getPreferencia(i);
            for (int j = 0; j < 5; ++j) {
                if (pref == tipos[j]) {
                    conteo[j]++;
                    break;
                }
            }
        }
        contar(nodo->derecho);
    };
    contar(raizAVL);

    // 3. Determinar tipo más popular
    int maxIndex = 0;
    for (int i = 1; i < 5; ++i) {
        if (conteo[i] > conteo[maxIndex]) {
            maxIndex = i;
        }
    }
    const char* tipoPopular = tipos[maxIndex];

    // 4. Mostrar pagos para cada instructor
    time_t t = time(nullptr);
    tm* tiempo = localtime(&t);
    int anioActual = 1900 + tiempo->tm_year;

    std::function<void(NodoABB_Instructores*)> recorrer = [&](NodoABB_Instructores* nodo) {
        if (!nodo) return;
        recorrer(nodo->izquierdo);

        bool esPopular = nodo->instructor->getTipoBaile() == tipoPopular;
        double bruto = nodo->instructor->calcularSueldoBruto(anioActual, esPopular);
        double afp = nodo->instructor->calcularCotizacionAFP(bruto);
        double liquido = nodo->instructor->calcularSueldoLiquido(bruto);

        std::cout << "\nInstructor: " << nodo->instructor->getNombreCompleto() << "\n";
        std::cout << "Sueldo Bruto: $" << bruto << "\n";
        std::cout << "AFP: $" << afp << "\n";
        std::cout << "Sueldo Liquido: $" << liquido << "\n";

        recorrer(nodo->derecho);
    };
    recorrer(raizABB);
}

/**
 * @brief Muestra información de todos los estudiantes almacenados en el árbol AVL.
 *
 * Este método realiza un recorrido en inorden sobre el árbol AVL de estudiantes,
 * permitiendo procesar los nodos en orden ascendente según las claves del árbol.
 * Durante el recorrido, imprime en la consola los detalles de cada estudiante:
 * identificador, nombre, fecha y preferencias.
 */
void Sistema::mostrarEstudiantes() {
    if (!raizAVL) {
        std::cout << "No hay estudiantes registrados.\n";
        return;
    }
    NodoAVL_Estudiantes* stack[100];
    int top = -1;
    NodoAVL_Estudiantes* curr = raizAVL;
    while (curr || top >= 0) {
        while (curr) {
            stack[++top] = curr;
            curr = curr->izquierdo;
        }
        curr = stack[top--];
        Estudiante* e = curr->estudiante;
        std::cout << "ID: " << e->getId()
                  << "  Nombre: " << e->getNombre()
                  << "  Fecha: " << e->getDia() << "/" << e->getMes() << "/" << e->getAnio()
                  << "  Hora: " << e->getHora() << ":" << (e->getMinuto() < 10 ? "0" : "") << e->getMinuto()
                  << "  Prefs: ";
        for (int i = 0; i < e->getNumPreferencias(); ++i) {
            std::cout << e->getPreferencia(i);
            if (i < e->getNumPreferencias() - 1) std::cout << "|";
        }
        std::cout << "\n";
        curr = curr->derecho;
    }
}

/**
 * @brief Busca un instructor en el Árbol Binario de Búsqueda (ABB) utilizando su ID y muestra su información.
 *
 * Solicita al usuario que ingrese un ID de instructor y realiza un recorrido del ABB para buscar
 * el nodo correspondiente. Si se encuentra el instructor, se muestra su nombre completo, sueldo base
 * y los días trabajados en el año actual. Si no se encuentra el ID, se notifica al usuario.
 *
 * El método utiliza la fecha actual para calcular los días trabajados.
 */
void Sistema::obtenerInstructor() {
    int id;
    std::cout << "Ingrese ID del instructor: ";
    std::cin >> id;

    NodoABB_Instructores* actual = raizABB;

    std::cout << "\nRecorrido:\n";
    while (actual) {
        std::cout << "ID: " << actual->instructor->getId()
                  << " - " << actual->instructor->getNombreCompleto() << "\n";

        if (id == actual->instructor->getId()) {
            time_t t = time(nullptr);
            tm* tiempo = localtime(&t);
            int anio = 1900 + tiempo->tm_year;
            int dia = tiempo->tm_yday + 1;

            std::cout << "\nEncontrado:\nNombre: " << actual->instructor->getNombreCompleto()
                      << "\nSueldo base: " << actual->instructor->getSueldoBase()
                      << "\nDias trabajados: " << actual->instructor->calcularDiasTrabajados(anio, dia) << "\n";
            return;
        }

        actual = (id < actual->instructor->getId()) ? actual->izquierdo : actual->derecho;
    }

    std::cout << "Instructor no encontrado.\n";
}


/**
 * @brief Elimina un nodo específico del Árbol Binario de Búsqueda (ABB) de instructores
 *        identificado por un ID, manteniendo la estructura del ABB.
 *
 * Este método busca y elimina el nodo correspondiente al ID proporcionado del ABB.
 * Si el nodo no tiene hijos, se elimina directamente. Si tiene un único subárbol,
 * se reemplaza por dicho subárbol. Para nodos con dos hijos, se reemplaza por su sucesor
 * en orden, manteniendo las propiedades del ABB.
 *
 * @param raiz Puntero al nodo raíz del árbol o subárbol actual.
 *             Representa el punto de inicio para la búsqueda y eliminación del nodo.
 * @param id ID del instructor a eliminar. Este valor se compara con los IDs del árbol
 *           para localizar el nodo correspondiente.
 * @return NodoABB_Instructores* Puntero a la raíz actualizada del árbol o subárbol,
 *                               reflejando los cambios realizados por la eliminación del nodo.
 */
NodoABB_Instructores* eliminarNodoABB(NodoABB_Instructores* raiz, int id) {
    if (!raiz) return nullptr;

    if (id < raiz->instructor->getId()) {
        raiz->izquierdo = eliminarNodoABB(raiz->izquierdo, id);
    } else if (id > raiz->instructor->getId()) {
        raiz->derecho = eliminarNodoABB(raiz->derecho, id);
    } else {
        if (!raiz->izquierdo) {
            auto* temp = raiz->derecho;
            delete raiz->instructor;
            delete raiz;
            return temp;
        } else if (!raiz->derecho) {
            auto* temp = raiz->izquierdo;
            delete raiz->instructor;
            delete raiz;
            return temp;
        } else {
            NodoABB_Instructores* sucesor = raiz->derecho;
            while (sucesor->izquierdo) sucesor = sucesor->izquierdo;
            std::swap(raiz->instructor, sucesor->instructor);
            raiz->derecho = eliminarNodoABB(raiz->derecho, sucesor->instructor->getId());
        }
    }
    return raiz;
}

/**
 * @brief Elimina a un instructor identificado por su ID del árbol binario de búsqueda (ABB).
 *
 * Solicita el identificador del instructor a eliminar, verifica si existe en el sistema
 * y, de ser así, lo elimina del ABB. Si el ID no existe, muestra un mensaje indicando que
 * el instructor no fue encontrado.
 */
void Sistema::eliminarInstructor() {
    int id;
    std::cout << "Ingrese ID del instructor a eliminar: ";
    std::cin >> id;

    if (!idExiste(id, false)) {
        std::cout << "Instructor no encontrado.\n";
        return;
    }

    raizABB = eliminarNodoABB(raizABB, id);
    std::cout << "Instructor eliminado exitosamente.\n";
}

/**
 * @brief Verifica si un identificador ya existe en el sistema.
 *
 * @param id El identificador que se desea verificar.
 * @param esEstudiante Un valor booleano que indica si el identificador pertenece a un estudiante.
 * @return true si el identificador existe en el sistema, false en caso contrario.
 */
bool Sistema::idExiste(int id, bool esEstudiante) {
    if (esEstudiante) {
        std::function<bool(NodoAVL_Estudiantes*)> buscar = [&](NodoAVL_Estudiantes* nodo) {
            if (!nodo) return false;
            if (nodo->estudiante->getId() == id) return true;
            return buscar(nodo->izquierdo) || buscar(nodo->derecho);
        };
        return buscar(raizAVL);
    } else {
        NodoABB_Instructores* actual = raizABB;
        while (actual) {
            if (id == actual->instructor->getId()) return true;
            actual = id < actual->instructor->getId() ? actual->izquierdo : actual->derecho;
        }
        return false;
    }
}
// Inserta un nodo en el ABB de instructores
NodoABB_Instructores* insertarEnABB(NodoABB_Instructores* raiz, Instructor* instr) {
    if (!raiz) return new NodoABB_Instructores(instr);

    if (instr->getId() < raiz->instructor->getId())
        raiz->izquierdo = insertarEnABB(raiz->izquierdo, instr);
    else if (instr->getId() > raiz->instructor->getId())
        raiz->derecho = insertarEnABB(raiz->derecho, instr);
    return raiz;
}

// Altura del nodo
int altura(NodoAVL_Estudiantes* nodo) {
    return nodo ? nodo->altura : 0;
}

// Máximo entre dos enteros
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Rotación simple derecha
NodoAVL_Estudiantes* rotarDerecha(NodoAVL_Estudiantes* y) {
    NodoAVL_Estudiantes* x = y->izquierdo;
    NodoAVL_Estudiantes* T2 = x->derecho;
    x->derecho = y;
    y->izquierdo = T2;
    y->altura = maximo(altura(y->izquierdo), altura(y->derecho)) + 1;
    x->altura = maximo(altura(x->izquierdo), altura(x->derecho)) + 1;
    return x;
}

// Rotación simple izquierda
NodoAVL_Estudiantes* rotarIzquierda(NodoAVL_Estudiantes* x) {
    NodoAVL_Estudiantes* y = x->derecho;
    NodoAVL_Estudiantes* T2 = y->izquierdo;
    y->izquierdo = x;
    x->derecho = T2;
    x->altura = maximo(altura(x->izquierdo), altura(x->derecho)) + 1;
    y->altura = maximo(altura(y->izquierdo), altura(y->derecho)) + 1;
    return y;
}

// Factor de equilibrio
int obtenerBalance(NodoAVL_Estudiantes* nodo) {
    return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
}

// Inserta un nodo en el AVL de estudiantes
NodoAVL_Estudiantes* insertarEnAVL(NodoAVL_Estudiantes* nodo, Estudiante* est) {
    if (!nodo) return new NodoAVL_Estudiantes(est);

    if (est->getFechaMatricula() < nodo->claveFecha)
        nodo->izquierdo = insertarEnAVL(nodo->izquierdo, est);
    else if (est->getFechaMatricula() > nodo->claveFecha)
        nodo->derecho = insertarEnAVL(nodo->derecho, est);
    else
        return nodo;

    nodo->altura = 1 + maximo(altura(nodo->izquierdo), altura(nodo->derecho));

    int balance = obtenerBalance(nodo);

    // Rotaciones
    if (balance > 1 && est->getFechaMatricula() < nodo->izquierdo->claveFecha)
        return rotarDerecha(nodo);
    if (balance < -1 && est->getFechaMatricula() > nodo->derecho->claveFecha)
        return rotarIzquierda(nodo);
    if (balance > 1 && est->getFechaMatricula() > nodo->izquierdo->claveFecha) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }
    if (balance < -1 && est->getFechaMatricula() < nodo->derecho->claveFecha) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

/**
 * @brief Carga los datos de instructores y estudiantes desde archivos CSV específicos.
 *
 * Este método lee datos de los archivos "instructores.csv" y "estudiantes.csv",
 * creando instancias de las clases Instructor y Estudiante, respectivamente.
 * Procesa las líneas de cada archivo, extrayendo y parseando información como IDs, nombres,
 * fechas, preferencias y otros atributos relevantes para inicializar los objetos.
 *
 * Los datos de los instructores incluyen ID, nombre, año de ingreso, sueldo y tipo.
 * Los datos de los estudiantes incluyen ID, nombre, fecha y preferencias.
 * Maneja hasta tres preferencias por cada estudiante separadas por el carácter '|'.
 *
 * Los archivos son cerrados tras completar la lectura y procesamiento.
 */
void Sistema::cargarDatos() {
    // Instructores
    std::ifstream fileIns("D:/Taller3/instructores.csv");
    if (!fileIns) {
        std::cerr << "Error al abrir instructores.csv\n";
    } else {
        std::string line;
        while (std::getline(fileIns, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string field, nombre, tipo;
            int id, anioIngreso;
            double sueldo;
            std::getline(ss, field, ','); id = std::stoi(field);
            std::getline(ss, nombre, ',');
            std::getline(ss, field, ','); anioIngreso = std::stoi(field);
            std::getline(ss, field, ','); sueldo = std::stod(field);
            std::getline(ss, tipo);
            Instructor* instr = new Instructor(id, nombre, anioIngreso, sueldo, tipo);
            raizABB = insertarEnABB(raizABB, instr);
        }
        fileIns.close();
    }
    // Estudiantes
    std::ifstream fileEst("D:/Taller3/estudiantes.csv");
    if (!fileEst) {
        std::cerr << "Error al abrir estudiantes.csv\n";
        return;
    }
    std::string line2;
    while (std::getline(fileEst, line2)) {
        if (line2.empty()) continue;
        std::stringstream ss(line2);
        std::string field, nombre, fecha, prefs;
        int id, dia, mes, anio, hora, minuto;
        std::getline(ss, field, ','); id = std::stoi(field);
        std::getline(ss, nombre, ',');
        std::getline(ss, fecha, ',');
        std::getline(ss, prefs);
        // Parse fecha "MM/DD/YYYY HH:MM"
        char sep;
        std::stringstream fs(fecha);
        fs >> mes >> sep >> dia >> sep >> anio >> hora >> sep >> minuto;
        // Parse preferencias
        std::string arrPref[3]; int nPref = 0;
        std::stringstream ps(prefs);
        while (nPref < 3 && std::getline(ps, field, '|')) {
            arrPref[nPref++] = field;
        }
        Estudiante* est = new Estudiante(id, nombre, dia, mes, anio, hora, minuto, arrPref, nPref);
        raizAVL = insertarEnAVL(raizAVL, est);
    }
    fileEst.close();
}


/**
 * @brief Registra un nuevo estudiante en el sistema.
 *
 * Solicita al usuario los datos personales y las preferencias del estudiante, valida
 * la información ingresada, y genera un identificador único para el nuevo estudiante.
 * Finalmente, crea una nueva instancia de la clase Estudiante en base a los datos
 * proporcionados.
 *
 * La validación incluye:
 * - Verificar que el nombre cumple con el formato establecido.
 * - Verificar que la fecha ingresada es válida.
 * - Verificar que se hayan ingresado preferencias únicas y válidas.
 *
 * Si cualquiera de las validaciones falla, la operación termina y se notifica al usuario.
 *
 * La implementación pendiente incluye la inserción del estudiante en el árbol AVL de
 * datos del sistema.
 */
void Sistema::matricularEstudiante() {
    std::string nombre;
    std::cout << "Nombre completo (Nombre Apellido): ";
    std::getline(std::cin, nombre);

    if (!Estudiante::validarNombreCompleto(nombre)) {
        std::cout << "Error: nombre invalido.\n";
        return;
    }

    int dia, hora, minuto, anio;
    std::string mesStr;
    std::cout << "Dia: "; std::cin >> dia;
    std::cout << "Mes (nombre o numero): "; std::cin >> mesStr;
    std::cout << "Hora (0-23): "; std::cin >> hora;
    std::cout << "Minuto (0-59): "; std::cin >> minuto;

    time_t t = time(nullptr);
    tm* tiempo = localtime(&t);
    anio = 1900 + tiempo->tm_year;

    int mes = 0;
    if (isdigit(mesStr[0])) {
        mes = std::stoi(mesStr);
    } else {
        mes = Estudiante::convertirMesANumero(mesStr);
    }

    if (!Estudiante::validarFecha(dia, mes, anio)) {
        std::cout << "Error: fecha invalida.\n";
        return;
    }

    std::cout << "Preferencias (1-5 separadas por coma): ";
    std::cin.ignore();
    char buffer[50];
    std::cin.getline(buffer, 50);

    int numeros[3];
    int nNumeros = 0;
    char* token = strtok(buffer, ",");
    while (token != nullptr && nNumeros < 3) {
        int valor = std::atoi(token);

        // Verifica duplicado
        bool duplicado = false;
        for (int i = 0; i < nNumeros; ++i) {
            if (numeros[i] == valor) {
                duplicado = true;
                break;
            }
        }

        if (!duplicado && valor >= 1 && valor <= 5) {
            numeros[nNumeros++] = valor;
        }

        token = strtok(nullptr, ",");
    }

    if (nNumeros == 0) {
        std::cout << "Error: preferencias invalidas.\n";
        return;
    }

    std::string preferencias[3];
    int nPrefs = 0;
    Estudiante::convertirPreferenciasATexto(numeros, nNumeros, preferencias, nPrefs);

    // Generar ID único
    int id;
    do {
        id = rand() % 10000;
    } while (idExiste(id, true));

    Estudiante* nuevo = new Estudiante(id, nombre, dia, mes, anio, hora, minuto, preferencias, nPrefs);
    raizAVL = insertarEnAVL(raizAVL, nuevo);
    std::cout << "Estudiante matriculado con ID: " << id << "\n";
}



