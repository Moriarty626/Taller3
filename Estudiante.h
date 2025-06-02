//
// Created by mauri on 02-06-2025.
//

#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <iostream>

/*
  Clase que representa un estudiante de la academia de zumba.
  Contiene ID, nombre, fecha de matricula y hasta 3 preferencias de baile,
  asi como campos separados de fecha para comparaciones.
*/

class Estudiante {
private:
    int id;                             // ID unico de 4 digitos
    std::string nombreCompleto;         // Nombre y apellido
    std::string fechaMatricula;         // Formato: "MM/DD/YYYY HH:MM"
    std::string preferencias[3];        // Hasta 3 estilos de baile
    int numPreferencias;                // Numero real de preferencias (1..3)

    // Campos separados para ordenamiento por fecha
    int dia;    // 1..31
    int mes;    // 1..12
    int anio;   // p.ej. 2025
    int hora;   // 0..23
    int minuto; // 0..59

public:
    // Constructor por defecto
    Estudiante();

    // Constructor que recibe fecha como string "MM/DD/YYYY HH:MM" y array de preferencias
    // prefs debe tener al menos nPrefs elementos.
    Estudiante(int id,
               const std::string& nombreCompleto,
               const std::string& fechaMatricula,
               const std::string prefs[],
               int nPrefs);

    // Constructor que recibe fecha separada y array de preferencias
    Estudiante(int id,
               const std::string& nombreCompleto,
               int dia, int mes, int anio,
               int hora, int minuto,
               const std::string prefs[],
               int nPrefs);

    ~Estudiante();

    // Getters basicos
    int getId() const;
    const std::string& getNombre() const;
    const std::string& getFechaMatricula() const;
    int getNumPreferencias() const;
    const std::string& getPreferencia(int indice) const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinuto() const;

    /**
     * Establece un nuevo identificador para el objeto.
     *
     * Esta función permite asignar un valor entero como identificador para el objeto
     * correspondiente, reemplazando cualquier valor previamente establecido.
     *
     * @param nuevoId El nuevo identificador que se asignará al objeto.
     */
    void setId(int nuevoId);

    /**
     * Establece el nombre del estudiante.
     *
     * Esta función asigna el nombre dado al estudiante.
     *
     * @param nombre Nombre del estudiante que se desea establecer.
     */
    void setNombre(const std::string& nombre);

    /**
     * Establece la fecha de matrícula de un estudiante a partir de una cadena de texto.
     *
     * Esta función interpreta la cadena de texto proporcionada en el formato esperado para
     * asignarla como la fecha de matrícula del estudiante.
     *
     * @param fechaStr Cadena de texto que contiene la fecha de matrícula en el formato requerido.
     */
    void setFechaMatricula(const std::string& fechaStr);

    /**
     * Establece la fecha y hora de matrícula del estudiante.
     *
     * Esta función permite configurar los valores de día, mes, año, hora y minuto para asignar
     * una fecha y hora específicas a la matrícula del estudiante.
     *
     * @param dia Día de la fecha de matrícula.
     * @param mes Mes de la fecha de matrícula.
     * @param anio Año de la fecha de matrícula.
     * @param hora Hora correspondiente a la hora de matrícula.
     * @param minuto Minuto correspondiente a la hora de matrícula.
     */
    void setFechaMatricula(int dia, int mes, int anio, int hora, int minuto);

    /**
     * Establece las preferencias de un estudiante basándose en un array de cadenas proporcionado.
     *
     * Esta función configura un conjunto de preferencias asociadas a un estudiante utilizando un array de cadenas.
     * Permite definir múltiples preferencias y su cantidad correspondiente.
     *
     * @param prefs Array de cadenas que contiene las preferencias a asignar.
     * @param nPrefs Número de elementos en el array `prefs`.
     */
    void setPreferencias(const std::string prefs[], int nPrefs);

    /**
     * Convierte un array de números a un array de nombres de preferencias y establece la cantidad de preferencias procesadas.
     *
     * Esta función mapea valores enteros presentes en el array `numeros` a sus descripciones asociadas (por ejemplo, estilos de baile)
     * y almacena las descripciones correspondientes en el array `salidaPrefs`. También almacena el número de preferencias traducidas
     * en la referencia `nSalida`.
     *
     * @param numeros Array de números que representan preferencias específicas.
     * @param nNumeros Tamaño del array `numeros`.
     * @param salidaPrefs Array donde se almacenarán las descripciones traducidas de las preferencias.
     * @param nSalida Referencia donde se almacenará la cantidad de descripciones generadas.
     */
    static void convertirPreferenciasATexto(const int numeros[],int nNumeros,std::string salidaPrefs[],int& nSalida);

    /**
     * Obtiene las preferencias del estudiante en formato de cadena concatenada.
     *
     * Esta función toma las preferencias almacenadas en el objeto y las combina en
     * una sola cadena separada por comas. Retorna una cadena vacía si no se tienen
     * preferencias.
     *
     * @return Cadena que representa las preferencias concatenadas separadas por comas
     *         o una cadena vacía si no hay preferencias disponibles.
     */
    std::string getPreferenciasString() const;

    /**
     * Genera una representación legible de la fecha de matrícula del estudiante.
     *
     * Esta función devuelve la fecha de matrícula del estudiante formateada para desplegarse
     * de manera legible. Utiliza los valores almacenados de día, mes, año, hora y minuto
     * para construir la cadena de salida.
     *
     * @return Una cadena que contiene la fecha de matrícula formateada en un estilo legible,
     *         utilizando los datos del estudiante.
     */
    std::string getFechaDisplay() const;

    /**
     * Valida si un nombre completo cumple con ciertos criterios establecidos.
     *
     * Esta función verifica si el nombre completo proporcionado satisface
     * las reglas específicas de validación, como la presencia de caracteres alfabéticos,
     * longitud mínima y formato correcto de nombre y apellido.
     *
     * @param nombre Una cadena que representa el nombre completo a validar.
     * @return `true` si el nombre completo es válido según los criterios establecidos;
     *         `false` en caso contrario.
     */
    static bool validarNombreCompleto(const std::string& nombre);

    /**
     * Valida si una fecha específica es válida según los valores de día, mes y año proporcionados.
     *
     * Esta función verifica que el día sea válido dentro del rango correspondiente al mes y año indicados,
     * considerando años bisiestos en el caso de febrero.
     *
     * @param dia Número entero que representa el día del mes a validar.
     * @param mes Número entero que representa el mes a validar (1 a 12).
     * @param anio Número entero que representa el año a validar.
     * @return `true` si la fecha es válida; de lo contrario, `false`.
     */
    static bool validarFecha(int dia, int mes, int anio);

    /**
     * Convierte el nombre de un mes en su correspondiente número.
     *
     * Esta función toma el nombre de un mes como entrada y retorna su valor numérico
     * correspondiente, considerando enero como 1, febrero como 2, y así sucesivamente
     * hasta diciembre como 12. Si el nombre del mes no es reconocido, se devuelve un
     * valor indicador (por ejemplo, -1).
     *
     * @param nombreMes Nombre del mes en formato de cadena.
     * @return Un número entero que representa el mes (1 para enero hasta 12 para diciembre),
     *         o un valor de error si el nombre no es válido.
     */
    static int convertirMesANumero(const std::string& nombreMes);

    /**
     * Compara dos objetos de tipo Estudiante para determinar si el actual tiene un orden menor que el otro.
     *
     * Esta sobrecarga del operador `<` permite realizar comparaciones entre objetos de tipo Estudiante,
     * y puede usarse, por ejemplo, en estructuras de datos ordenadas como `std::set` o para ordenar listas.
     *
     * @param otro El objeto de tipo Estudiante con el que se hará la comparación.
     * @return true si el objeto actual tiene un orden menor que el objeto `otro`, false en caso contrario.
     */
    bool operator<(const Estudiante& otro) const;

    /**
     * Compara dos objetos de tipo Estudiante para determinar si el objeto actual
     * tiene una calificación o mérito superior al objeto proporcionado.
     *
     * Esta sobrecarga del operador `>` permite comparar dos estudiantes basándose
     * en criterios determinados, como calificaciones, experiencia o algún atributo
     * configurado para establecer un orden entre ellos.
     *
     * @param otro Referencia constante al objeto Estudiante con el cual se realizará la comparación.
     * @return true si el objeto actual tiene un valor mayor que el objeto proporcionado según el criterio de comparación, false en caso contrario.
     */
    bool operator>(const Estudiante& otro) const;

    /**
     * Compara si dos objetos de la clase Estudiante son iguales.
     *
     * Esta operación determina la igualdad entre el objeto actual y otro objeto
     * tipo Estudiante basado en sus atributos internos.
     *
     * @param otro Referencia constante al objeto de tipo Estudiante a comparar.
     * @return true si ambos objetos son considerados iguales, false en caso contrario.
     */
    bool operator==(const Estudiante& otro) const;

    /**
     * Compara dos objetos de tipo Estudiante y evalúa si el objeto actual es menor o igual que el objeto proporcionado.
     *
     * Esta sobrecarga del operador `<=` permite realizar comparaciones entre dos instancias de Estudiante,
     * determinando si el objeto actual es menor o igual al otro basado en criterios internos específicos de la clase.
     *
     * @param otro El objeto de tipo Estudiante con el que se desea realizar la comparación.
     * @return true si el objeto actual es menor o igual que el objeto `otro`, false en caso contrario.
     */
    bool operator<=(const Estudiante& otro) const;

    /**
     * Compara dos objetos de tipo Estudiante para determinar si este objeto es mayor o igual que otro.
     *
     * La comparación se realiza en función de criterios internos del objeto Estudiante, como podrían ser calificaciones,
     * identificadores o cualquier otra propiedad relevante según su implementación interna.
     *
     * @param otro Referencia constante al objeto Estudiante con el cual se realiza la comparación.
     * @return true si este objeto Estudiante es mayor o igual que el objeto proporcionado; de lo contrario, false.
     */
    bool operator>=(const Estudiante& otro) const;


    /**
     * Realiza una sobrecarga del operador para un tipo definido por el usuario.
     *
     * Este operador personalizado permite comparar, asignar, sumar, restar, o cualquier otra operación
     * específica implementada en la clase o estructura correspondiente, dependiendo de la implementación detallada.
     *
     * @param lhs Operando izquierdo en la operación del operador sobrecargado.
     * @param rhs Operando derecho en la operación del operador sobrecargado.
     * @return Resultado de la operación entre los operandos proporcionados.
     */
    friend std::ostream& operator<<(std::ostream& os, const Estudiante& est);

private:
    /**
     * Analiza una cadena de texto que representa una fecha y realiza su procesamiento.
     *
     * Esta función toma una fecha en formato de texto proporcionada en `fechaStr`, valida su estructura
     * y puede realizar operaciones adicionales como la conversión a un formato interno específico o el almacenamiento
     * para uso posterior.
     *
     * @param fechaStr Cadena de texto que contiene la fecha a ser analizada.
     */
    void parsearFecha(const std::string& fechaStr);

    /**
     * Formatea y establece la fecha de matrícula del estudiante.
     *
     * Esta función genera una cadena formateada que representa la fecha y hora de matrícula
     * del estudiante. Incluye día, mes, año, hora y minuto en un formato estándar,
     * asegurando que los valores tengan dos dígitos cuando sea necesario.
     * La fecha resultante se almacena en el atributo de fecha de matrícula.
     */
    void formatearFecha();

    /**
     * Compara las fechas de dos objetos de tipo Estudiante.
     *
     * Este método realiza una comparación entre las fechas asociadas al objeto actual
     * y al objeto recibido como argumento. La comparación contempla año, mes, día, hora y minuto
     * en ese orden, devolviendo un valor que indica la relación entre ambas fechas.
     *
     * @param otro El objeto Estudiante con el cual se comparará la fecha.
     * @return Un entero que indica el resultado de la comparación:
     *         -1 si la fecha del objeto actual es anterior a la del objeto recibido.
     *          1 si la fecha del objeto actual es posterior a la del objeto recibido.
     *          0 si ambas fechas son iguales.
     */
    int compararFecha(const Estudiante& otro) const;
};

#endif // ESTUDIANTE_H
