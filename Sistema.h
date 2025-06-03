#ifndef SISTEMA_H
#define SISTEMA_H

#include "NodoABB_Instructores.h"
#include "NodoAVL_Estudiantes.h"
#include <string>

/**
 * @class Sistema
 * @brief Clase principal para la gestión de instructores y estudiantes de una academia de baile.
 *
 * Proporciona funcionalidades para cargar y guardar datos desde o hacia archivos CSV, además de
 * manejar un menú interactivo donde se puede gestionar la matrícula de estudiantes, calcular pagos,
 * listar estudiantes, entre otras operaciones. Internamente utiliza un Árbol Binario de Búsqueda (ABB)
 * para gestionar instructores y un Árbol AVL para estudiantes.
 */
class Sistema {
private:
    /**
     * @variable raizABB
     * @brief Puntero a la raíz del Árbol Binario de Búsqueda (ABB) de instructores.
     *
     * Gestiona y organiza la información de instructores en la estructura de Árbol Binario
     * de Búsqueda (ABB). Este puntero representa el nodo inicial del ABB, facilitando
     * operaciones como búsqueda, inserción y eliminación de instructores.
     */
    NodoABB_Instructores* raizABB;
    /**
     * @variable raizAVL
     * @brief Puntero a la raíz del Árbol AVL de estudiantes.
     *
     * Almacena y organiza los datos de los estudiantes en un Árbol AVL, permitiendo
     * mantener un orden balanceado para optimizar las operaciones de búsqueda, inserción
     * y eliminación. Este puntero apunta al nodo raíz del árbol AVL.
     */
    NodoAVL_Estudiantes* raizAVL;

public:
    /**
     * @brief Constructor de la clase Sistema.
     *
     * Inicializa una instancia del sistema, configurando las estructuras esenciales
     * de datos como los árboles binarios para la gestión de instructores y estudiantes.
     */
    Sistema();
    /**
     * @brief Destructor de la clase Sistema.
     *
     * Libera los recursos utilizados por el sistema, incluyendo la memoria asignada
     * para los árboles de instructores y estudiantes, asegurando una correcta limpieza
     * de los datos al finalizar el uso del sistema.
     */
    ~Sistema();

    /**
     * @brief Carga los datos de instructores y estudiantes desde archivos CSV a las estructuras
     *        internas del sistema.
     *
     * Este método permite inicializar el estado de los árboles de instructores (ABB) y estudiantes (AVL)
     * con la información previamente guardada en archivos CSV. El sistema procesa los datos contenidos
     * en estos archivos y los organiza en sus respectivas estructuras, facilitando su uso posterior
     * dentro del sistema.
     */
    void cargarDatos();

    /**
     * @brief Guarda los datos de instructores y estudiantes en archivos CSV.
     *
     * Este método exporta la información contenida en las estructuras internas del sistema,
     * como el Árbol Binario de Búsqueda (ABB) de instructores y el Árbol AVL de estudiantes,
     * a archivos CSV. El propósito de esta funcionalidad es asegurar la persistencia de los
     * datos al almacenarlos en un formato accesible y reutilizable.
     */
    void guardarDatos();

    /**
     * @brief Muestra el menú interactivo principal del sistema.
     *
     * Este método gestiona la interacción con el usuario mediante un menú principal,
     * presentando las diferentes opciones disponibles para administrar instructores y estudiantes.
     * A través de este menú, el usuario puede acceder a distintas funcionalidades del sistema,
     * como matricular estudiantes, calcular pagos, listar estudiantes, entre otras operaciones.
     */
    void mostrarMenu();

    /**
     * @brief Matricula a un estudiante en la academia.
     *
     * Este método se encarga de registrar los datos de un nuevo estudiante en el sistema,
     * añadiéndolo al Árbol AVL de estudiantes. Durante el proceso, se solicita al usuario
     * información relevante al estudiante y se verifica que no existan conflictos en los datos,
     * como identificadores duplicados. También garantiza que el árbol mantenga su balance
     * después de la inserción.
     */
    void matricularEstudiante();

    /**
     * @brief Calcula y muestra los pagos de los instructores.
     *
     * Este método realiza el cálculo de los pagos que deben recibir los instructores
     * basándose en su sueldo base, antigüedad y otros factores como la popularidad del
     * tipo de baile que enseñan. Luego, presenta un resumen detallado de los pagos a cada
     * instructor, incluyendo deducciones y el sueldo líquido final.
     */
    void calcularPagos();
    /**
     * @brief Muestra un listado de todos los estudiantes matriculados.
     *
     * Este método recorre el Árbol AVL de estudiantes y presenta una lista completa
     * de los estudiantes registrados en el sistema, mostrando información relevante
     * como su nombre, fecha de matrícula y preferencias de baile.
     */

    void mostrarEstudiantes();
    /**
     * @brief Muestra un listado de todos los instructores registrados.
     *
     * Este método recorre el Árbol Binario de Búsqueda (ABB) de instructores y presenta
     * una lista completa de los instructores, mostrando información relevante como su
     * nombre, tipo de baile que enseñan y otros detalles pertinentes.
     */
    void obtenerInstructor();

    /**
     * @brief Elimina un instructor del sistema.
     *
     * Este método permite al usuario eliminar un instructor del sistema, solicitando
     * el ID del instructor a eliminar. Si el ID es válido y existe en el sistema,
     * se procede a eliminarlo del Árbol Binario de Búsqueda (ABB) de instructores,
     * asegurando que la estructura del árbol se mantenga balanceada después de la eliminación.
     */
    void eliminarInstructor();

    /**
     * @brief Genera un identificador único para un estudiante o instructor.
     *
     * Este método crea un ID único basado en si el identificador es requerido
     * para un estudiante o un instructor, diferenciando entre ambos tipos.
     *
     * @param esEstudiante Indica si el identificador generado es para un estudiante (true)
     *                     o para un instructor (false).
     * @return Un entero que representa el identificador único generado.
     */
    int generarIdUnico(bool esEstudiante);

    /**
     * @brief Verifica si un ID ya existe en el sistema.
     *
     * Este método comprueba si un identificador específico ya está en uso
     * dentro del sistema, ya sea para estudiantes o instructores, evitando
     * duplicados y garantizando la unicidad de los IDs.
     *
     * @param id El identificador a verificar.
     * @param esEstudiante Indica si se está verificando un ID de estudiante (true)
     *                     o de instructor (false).
     * @return true si el ID ya existe, false en caso contrario.
     */
    bool idExiste(int id, bool esEstudiante);

    /**
     * @brief Obtiene el nombre del mes actual en formato de texto.
     *
     * Determina el mes actual basado en la fecha del sistema y devuelve el nombre correspondiente como una cadena de texto.
     *
     * @return Una cadena que representa el nombre del mes actual.
     */
    std::string obtenerMesActualTexto();
};

#endif // SISTEMA_H

