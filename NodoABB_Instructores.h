#ifndef NODOABB_INSTRUCTORES_H
#define NODOABB_INSTRUCTORES_H

#include <string>
#include "Instructor.h"

/**
 * @class NodoABB_Instructores
 * @brief Representa un nodo en un Árbol Binario de Búsqueda (ABB) para instructores.
 *
 * Esta clase encapsula la estructura de un nodo en un ABB, que incluye un puntero
 * a un objeto `Instructor` y punteros a los nodos hijos izquierdo y derecho.
 * Proporciona un constructor para inicializar el nodo con un instructor y un destructor
 * para liberar los recursos asociados.
 */
class NodoABB_Instructores {
public:
    /**
    * @variable instructor
    * @brief Puntero a un objeto Instructor asociado a este nodo.
    *
    * Representa los datos del instructor almacenados dentro del nodo actual del Árbol Binario de Búsqueda (ABB).
    * Este puntero facilita el almacenamiento y la recuperación de información específica del instructor.
    */
    Instructor* instructor;

    /**
    * @variable izquierdo
    * @brief Puntero al nodo hijo izquierdo en el Árbol Binario de Búsqueda (ABB).
    *
    * Representa el subárbol izquierdo del nodo actual en la jerarquía del ABB.
    * Este puntero se utiliza para recorrer o gestionar los nodos que son menores
    * en valor comparados con el nodo actual, manteniendo la propiedad del ABB.
    */
    NodoABB_Instructores* izquierdo;

    /**
    * @variable derecho
    * @brief Puntero al nodo hijo derecho en el Árbol Binario de Búsqueda (ABB).
    *
    * Representa el subárbol derecho del nodo actual dentro de la jerarquía del ABB.
    * Este puntero se utiliza para navegar o gestionar los nodos que tienen valores mayores
    * que el valor del nodo actual, manteniendo las propiedades del ABB.
    */
    NodoABB_Instructores* derecho;

    /**
    * @brief Construye un nuevo objeto NodoABB_Instructores con el instructor proporcionado.
    *
    * Inicializa un nodo en el Árbol Binario de Búsqueda (ABB) para instructores, asociando
    * el objeto instructor especificado con el nodo y estableciendo sus nodos hijos en nulo.
    *
    * @param inst Puntero a un objeto Instructor que se almacenará en el nodo.
    *             Este parámetro representa los datos del instructor que gestionará el nodo.
    */
    NodoABB_Instructores(Instructor* inst);

    /**
    * @brief Destructor de NodoABB_Instructores.
    *
    * Libera los recursos asociados con el nodo, incluyendo el objeto instructor
    * asociado y cualquier memoria o recurso asignado dinámicamente.
    * Garantiza la liberación adecuada de los nodos hijos si es necesario, manteniendo
    * prácticas seguras de gestión de memoria para el Árbol Binario de Búsqueda.
    */
    ~NodoABB_Instructores();

    /**
 * @brief Obtiene el puntero al instructor almacenado.
 */
    Instructor* getInstructor() const {
        return instructor;
    }

    /**
     * @brief Obtiene el hijo izquierdo.
     */
    NodoABB_Instructores* getIzquierdo() const {
        return izquierdo;
    }

    /**
     * @brief Obtiene el hijo derecho.
     */
    NodoABB_Instructores* getDerecho() const {
        return derecho;
    }

    /**
     * @brief Establece el hijo izquierdo.
     */
    void setIzquierdo(NodoABB_Instructores* ptr) {
        izquierdo = ptr;
    }

    /**
     * @brief Establece el hijo derecho.
     */
    void setDerecho(NodoABB_Instructores* ptr) {
        derecho = ptr;
    }

};



#endif // NODOABB_INSTRUCTORES_H
