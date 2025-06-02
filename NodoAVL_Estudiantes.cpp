#include "NodoAVL_Estudiantes.h"

/**
 * @brief Constructor de la clase NodoAVL_Estudiantes.
 *
 * Inicializa un nodo AVL con un puntero a un objeto Estudiante.
 * Los punteros izquierdo y derecho se establecen en nullptr, la
 * altura se fija en 1 y la clave de fecha se inicializa con la
 * fecha de matrícula del estudiante.
 *
 * @param est Puntero al objeto Estudiante que representa al estudiante
 * asociado con el nodo.
 * @return No retorna ningún valor ya que es un constructor.
 */
NodoAVL_Estudiantes::NodoAVL_Estudiantes(Estudiante* est)
    : estudiante(est),
      izquierdo(nullptr),
      derecho(nullptr),
      altura(1),
      claveFecha(est->getFechaMatricula())
{

}


