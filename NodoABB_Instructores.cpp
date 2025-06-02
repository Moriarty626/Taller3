#include "NodoABB_Instructores.h"


/**
 * @brief Construye un nuevo nodo para el Árbol Binario de Búsqueda (ABB) de instructores.
 *
 * Inicializa un nodo del ABB asociando un objeto Instructor proporcionado, con sus punteros
 * a hijos izquierdo y derecho establecidos en nullptr.
 *
 * @param inst Puntero al objeto Instructor que será almacenado en el nodo. Este parámetro
 *             contiene los datos específicos del instructor que estarán vinculados al nodo.
 * @return No retorna un valor, dado que es un constructor.
 */
NodoABB_Instructores::NodoABB_Instructores(Instructor* inst)
    : instructor(inst),
      izquierdo(nullptr),
      derecho(nullptr)
{

}

