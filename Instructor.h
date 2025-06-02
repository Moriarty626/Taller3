#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <string>
#include <iostream>

/**
 * @brief Clase que representa un instructor de la academia de zumba
 *
 * Contiene la información básica de cada instructor contratado,
 * incluyendo ID, nombre, año de ingreso, sueldo y tipo de baile que enseña.
 */
class Instructor {
private:
    int id;                      ///< ID único de 4 dígitos del instructor
    std::string nombreCompleto;  ///< Nombre y apellido del instructor
    int anioIngreso;            ///< Año desde que trabaja en la academia
    double sueldoBase;          ///< Remuneración base del instructor
    std::string tipoBaile;      ///< Tipo de baile que enseña

public:
    /**
     * @brief Constructor por defecto
     */
    Instructor();

    /**
     * @brief Constructor parametrizado
     * @param id ID único del instructor
     * @param nombreCompleto Nombre y apellido
     * @param anioIngreso Año de ingreso a la academia
     * @param sueldoBase Sueldo base del instructor
     * @param tipoBaile Tipo de baile que enseña
     */
    Instructor(int id, const std::string& nombreCompleto, int anioIngreso,
               double sueldoBase, const std::string& tipoBaile);

    /**
     * @brief Destructor
     */
    ~Instructor();

    /**
     * @brief Obtiene el ID único del instructor.
     *
     * Este valor es un identificador único de 4 dígitos asignado
     * a cada instructor al momento de su creación.
     *
     * @return El ID único del instructor.
     */
    int getId() const;

    /**
     * @brief Obtiene el nombre completo del instructor.
     *
     * Este método devuelve el atributo que almacena el nombre y apellido
     * del instructor registrado en la academia.
     *
     * @return Cadena de texto con el nombre completo del instructor.
     */
    std::string getNombreCompleto() const;

    /**
     * @brief Obtiene el año de ingreso del instructor a la academia.
     *
     * Permite conocer desde qué año trabaja el instructor en la academia.
     *
     * @return Año de ingreso del instructor.
     */
    int getAnioIngreso() const;

    /**
     * @brief Obtiene el sueldo base del instructor.
     *
     * Retorna la remuneración base asociada al instructor.
     *
     * @return Sueldo base del instructor.
     */
    double getSueldoBase() const;

    /**
     * @brief Obtiene el tipo de baile que enseña el instructor.
     *
     * Este método retorna la especialidad de baile del instructor,
     * como Salsa, Tango, Bachata, entre otros.
     *
     * @return El tipo de baile que enseña el instructor.
     */
    std::string getTipoBaile() const;


    /**
     * @brief Sets the identification number of the instructor.
     *
     * Allows assigning a unique ID to the instructor.
     *
     * @param id The identification number to be assigned to the instructor.
     */
    void setId(int id);

    /**
     * @brief Establece el nombre completo del instructor.
     *
     * Este método permite definir el nombre completo de un instructor,
     * reemplazando cualquier valor anterior asignado.
     *
     * @param nombreCompleto Una cadena de texto que representa el nombre completo del instructor.
     */
    void setNombreCompleto(const std::string& nombreCompleto);

    /**
     * @brief Establece el año de ingreso del instructor.
     *
     * Asigna el año en el que el instructor comenzó a trabajar en la academia.
     *
     * @param anioIngreso Año de ingreso que se desea asignar al instructor.
     */
    void setAnioIngreso(int anioIngreso);

    /**
     * @brief Establece el sueldo base del instructor.
     *
     * Este método permite asignar un valor al sueldo base
     * que recibe el instructor como parte de su contrato.
     *
     * @param sueldoBase El nuevo sueldo base que se desea asignar.
     */
    void setSueldoBase(double sueldoBase);

    /**
     * @brief Establece el tipo de baile que enseña el instructor.
     *
     * Permite definir o actualizar el género de baile que el instructor imparte
     * en la academia de zumba.
     *
     * @param tipoBaile El tipo de baile que se asignará al instructor.
     */
    void setTipoBaile(const std::string& tipoBaile);

    /**
     * @brief Calcula el sueldo bruto del instructor con bonificaciones
     * @param anioActual Año actual para calcular años de servicio
     * @param esTipoMasPopular Indica si su tipo de baile es el más popular
     * @return Sueldo bruto (base + bonificaciones)
     */
    double calcularSueldoBruto(int anioActual, bool esTipoMasPopular) const;

    /**
     * @brief Calcula la cotización AFP (19% del sueldo bruto)
     * @param sueldoBruto Sueldo bruto del instructor
     * @return Monto de cotización AFP
     */
    double calcularCotizacionAFP(double sueldoBruto) const;

    /**
     * @brief Calcula el sueldo líquido (bruto - AFP)
     * @param sueldoBruto Sueldo bruto del instructor
     * @return Sueldo líquido
     */
    double calcularSueldoLiquido(double sueldoBruto) const;

    /**
     * @brief Calcula los años de servicio del instructor
     * @param anioActual Año actual
     * @return Cantidad de años trabajados
     */
    int calcularAniosServicio(int anioActual) const;

    /**
     * @brief Calcula los días trabajados (asume que empezó el 1 de enero)
     * @param anioActual Año actual
     * @param diaActual Día actual del año (1-365/366)
     * @return Cantidad total de días trabajados
     */
    int calcularDiasTrabajados(int anioActual, int diaActual) const;

    /**
     * @brief Verifica si el instructor tiene más de 5 años de servicio
     * @param anioActual Año actual
     * @return true si tiene más de 5 años, false en caso contrario
     */
    bool tieneMasDe5Anios(int anioActual) const;

    /**
     * @brief Verifica si el instructor enseña Tango
     * @return true si enseña Tango, false en caso contrario
     */
    bool enseniaTango() const;

    /**
     * @brief Valida si un tipo de baile es válido
     * @param tipo Tipo de baile a validar
     * @return true si es válido, false en caso contrario
     */
    static bool validarTipoBaile(const std::string& tipo);

    /**
     * @brief Obtiene todos los tipos de baile válidos
     * @return String con los tipos de baile separados por comas
     */
    static std::string obtenerTiposBaileValidos();


    /**
     * @brief Sobrecarga del operador menor (<) para comparar instructores.
     *
     * Compara dos objetos de tipo Instructor basándose en un criterio
     * determinado, como el ID o cualquier otro atributo relevante del instructor.
     *
     * @param otro El instructor con el cual se va a comparar el objeto actual.
     * @return true si el objeto actual es considerado menor que el objeto otro,
     *         false en caso contrario.
     */
    bool operator<(const Instructor& otro) const;

    /**
  * @brief Sobrecarga del operador menor (>) para comparar instructores.
  *
  * Compara dos objetos de tipo Instructor basándose en un criterio
  * determinado, como el ID o cualquier otro atributo relevante del instructor.
  *
  * @param otro El instructor con el cual se va a comparar el objeto actual.
  * @return true si el objeto actual es considerado menor que el objeto otro,
  *         false en caso contrario.
  */
    bool operator>(const Instructor& otro) const;

    /**
     * @brief Compara dos objetos de tipo Instructor para verificar si son iguales.
     *
     * Esta sobrecarga del operador de igualdad compara las propiedades internas
     * de dos objetos Instructor para determinar si representan la misma entidad.
     *
     * @param otro El objeto Instructor con el que se realizará la comparación.
     * @return true si ambos objetos Instructor son iguales; de lo contrario, false.
     */
    bool operator==(const Instructor& otro) const;

    /**
     * @brief Compara si un Instructor es menor o igual que otro.
     *
     * Este operador permite evaluar si un Instructor es menor
     * o igual a otro en base a ciertos criterios de comparación
     * definidos en la clase.
     *
     * @param otro El otro objeto Instructor con el cual se realizará la comparación.
     * @return true si el Instructor actual es menor o igual al otro, false en caso contrario.
     */
    bool operator<=(const Instructor& otro) const;

    /**
     * @brief Compara si un instructor tiene mayor o igual antigüedad que otro.
     *
     * Este operador permite comparar dos objetos de la clase Instructor
     * en función de su antigüedad en la academia.
     *
     * @param otro El instructor con el cual se realiza la comparación.
     * @return true si el instructor actual tiene mayor o igual antigüedad que el instructor dado, false en caso contrario.
     */
    bool operator>=(const Instructor& otro) const;

    /**
     * @brief Sobrecarga del operador << para imprimir instructor
     */
    friend std::ostream& operator<<(std::ostream& os, const Instructor& instructor);

    // Constantes para bonificaciones
    static const double BONO_ANTIGUEDAD;        ///< Bono por más de 5 años (24.350)
    static const double PORCENTAJE_POPULARIDAD; ///< Bono por popularidad (5%)
    static const double BONO_TANGO;             ///< Bono por enseñar Tango (5.600)
    static const double PORCENTAJE_AFP;         ///< Porcentaje AFP (19%)

private:
    /**
     * @brief Normaliza el tipo de baile (primera letra mayúscula, resto minúscula)
     * @param tipo Tipo de baile a normalizar
     * @return Tipo de baile normalizado
     */
    std::string normalizarTipoBaile(const std::string& tipo) const;
};

#endif // INSTRUCTOR_H
