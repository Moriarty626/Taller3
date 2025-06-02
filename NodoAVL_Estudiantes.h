#ifndef NODOAVL_ESTUDIANTES_H
#define NODOAVL_ESTUDIANTES_H

#include <string>
#include "Estudiante.h"

/**
 * @class NodoAVL_Estudiantes
 *
 * @brief Representa un nodo en un árbol AVL utilizado para almacenar objetos de tipo Estudiante.
 *
 * Esta clase implementa un nodo en un árbol AVL que almacena un puntero a un objeto
 * Estudiante. También contiene punteros a sus hijos izquierdo y derecho, así como
 * un atributo para registrar la altura del nodo y una clave derivada de la fecha
 * de matrícula utilizada para ordenar los nodos dentro del árbol.
 */
class NodoAVL_Estudiantes {
public:
    Estudiante* estudiante;     // Puntero al objeto Estudiante
    NodoAVL_Estudiantes* izquierdo;
    NodoAVL_Estudiantes* derecho;
    int altura;                 // Altura del nodo en el AVL
    std::string claveFecha;     // Repetir fechaMatricula para orden (MM/DD/YYYY HH:MM)

    /**
     * @brief Constructor de la clase NodoAVL_Estudiantes.
     *
     * Inicializa un nodo AVL con un puntero a un objeto Estudiante.
     * Los punteros a los hijos izquierdo y derecho se establecen en nullptr,
     * la altura se inicializa en 1, y la clave de fecha se establece
     * a partir de la fecha de matrícula del estudiante.
     *
     * @param est Puntero al objeto Estudiante que se almacenará en el nodo.
     */
    NodoAVL_Estudiantes(Estudiante* est);


};

#endif // NODOAVL_ESTUDIANTES_H
