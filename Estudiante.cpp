// Estudiante.cpp
#include "Estudiante.h"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstring>


/**
 * @brief Constructor por defecto de la clase Estudiante.
 *
 * Inicializa un objeto Estudiante con valores predeterminados. El `id` se establece en 0,
 * `nombreCompleto` se inicializa como una cadena vacía y `fechaMatricula` se
 * inicializa como "01/01/1970 00:00". El número de preferencias se establece en 0,
 * y la fecha y hora se configuran con los valores por defecto 1/1/1970 00:00.
 * El arreglo de preferencias se limpia.
 *
 * @return Un objeto Estudiante completamente inicializado con valores por defecto.
 */
Estudiante::Estudiante()
    : id(0),
      nombreCompleto(""),
      fechaMatricula("01/01/1970 00:00"),
      numPreferencias(0),
      dia(1), mes(1), anio(1970), hora(0), minuto(0)
{
    for (int i = 0; i < 3; i++) {
        preferencias[i].clear();
    }
}

/**
 * @brief Constructor parametrizado de la clase Estudiante.
 *
 * Inicializa un objeto Estudiante con los valores proporcionados.
 * Asigna un identificador único, nombre completo, fecha de matrícula
 * y una lista de preferencias. Se procesan un máximo de 3 preferencias,
 * y las preferencias restantes se dejan vacías si no se proporcionan.
 * Además, analiza la fecha de matrícula para separar sus componentes.
 *
 * @param id Identificador único del estudiante.
 * @param nombreCompleto Nombre completo del estudiante.
 * @param fechaMatricula Fecha de matrícula del estudiante en formato de texto.
 * @param prefs Arreglo de cadenas que contiene las preferencias del estudiante.
 * @param nPrefs Número de preferencias indicadas en el arreglo `prefs`.
 *
 * @return Un objeto Estudiante inicializado con los valores dados.
 */
Estudiante::Estudiante(int id,const std::string& nombreCompleto,const std::string& fechaMatricula,const std::string prefs[],int nPrefs)
    : id(id),
      nombreCompleto(nombreCompleto),
      fechaMatricula(fechaMatricula),
      numPreferencias(nPrefs)
{
    // Copiar hasta 3 preferencias
    for (int i = 0; i < 3; i++) {
        if (i < nPrefs) {
            preferencias[i] = prefs[i];
        } else {
            preferencias[i].clear();
        }
    }
    // Obtener campos separados de la fecha
    parsearFecha(fechaMatricula);
}

/**
 * @brief Constructor parametrizado de la clase Estudiante.
 *
 * Inicializa un objeto Estudiante utilizando los parámetros proporcionados. Establece
 * el `id`, el `nombreCompleto`, la fecha y hora de matrícula (`dia`, `mes`, `anio`, `hora`, `minuto`)
 * y copia hasta tres preferencias del arreglo `prefs` en el atributo correspondiente.
 * Si el número de preferencias proporcionadas es menor a tres, los elementos restantes
 * se inicializan como cadenas vacías. También configura la cadena `fechaMatricula`
 * utilizando el método `formatearFecha`.
 *
 * @param id Identificador único del estudiante.
 * @param nombreCompleto Nombre completo del estudiante.
 * @param dia Día registrado en la fecha de matrícula.
 * @param mes Mes registrado en la fecha de matrícula.
 * @param anio Año registrado en la fecha de matrícula.
 * @param hora Hora registrada en la fecha de matrícula.
 * @param minuto Minuto registrado en la fecha de matrícula.
 * @param prefs Arreglo de cadena de texto que contiene hasta tres preferencias del estudiante.
 * @param nPrefs Número de preferencias proporcionadas en el arreglo `prefs`.
 *
 * @return Un objeto Estudiante completamente inicializado con los valores proporcionados.
 */
Estudiante::Estudiante(int id,const std::string& nombreCompleto,int dia, int mes, int anio,int hora, int minuto,const std::string prefs[],int nPrefs):
    id(id),
    nombreCompleto(nombreCompleto),
    dia(dia),
    mes(mes),
    anio(anio),
    hora(hora),
    minuto(minuto),
    numPreferencias(nPrefs)
{
    // Copiar hasta 3 preferencias
    for (int i = 0; i < 3; i++) {
        if (i < nPrefs) {
            preferencias[i] = prefs[i];
        } else {
            preferencias[i].clear();
        }
    }
    // Construir cadena fechaMatricula
    formatearFecha();
}

/**
 * @brief Destructor de la clase Estudiante.
 *
 * Realiza la limpieza de los recursos utilizados por el objeto Estudiante
 * y restablece los valores a su estado inicial. Los campos `nombreCompleto`,
 * `fechaMatricula` y el arreglo de preferencias son limpiados y sus cadenas
 * de texto se vacían. Además, los contadores y valores de fecha y hora se
 * reinician a cero.
 */
Estudiante::~Estudiante() {
    // Limpiar cadenas de texto
    nombreCompleto.clear();
    fechaMatricula.clear();
    for (int i = 0; i < 3; i++) {
        preferencias[i].clear();
    }
    // Restablecer contadores a cero (opcional)
    numPreferencias = 0;
    dia = mes = anio = hora = minuto = 0;
}

/**
 * @brief Obtiene el identificador único del estudiante.
 *
 * Retorna el valor del atributo `id`, que corresponde al identificador único
 * asignado al estudiante.
 *
 * @return El identificador único del estudiante.
 */
int Estudiante::getId() const {
    return id;
}

/**
 * @brief Obtiene el nombre completo del estudiante.
 *
 * Este método permite acceder al nombre completo asociado al estudiante.
 *
 * @return Una referencia constante a un objeto `std::string` que contiene el nombre completo del estudiante.
 */
const std::string& Estudiante::getNombre() const {
    return nombreCompleto;
}

/**
 * @brief Obtiene la fecha de matrícula del estudiante.
 *
 * Devuelve una referencia constante a la fecha de matrícula asociada con el estudiante.
 * Este valor representa el momento en que el estudiante se registró en el sistema.
 *
 * @return Una referencia constante a un objeto de tipo `std::string` que contiene la fecha de matrícula.
 */
const std::string& Estudiante::getFechaMatricula() const {
    return fechaMatricula;
}

/**
 * @brief Devuelve el número de preferencias del estudiante.
 *
 * Este método obtiene el valor actual del atributo `numPreferencias`,
 * que representa la cantidad de preferencias asociadas al estudiante.
 *
 * @return El número de preferencias asignadas al estudiante.
 */
int Estudiante::getNumPreferencias() const {
    return numPreferencias;
}

/**
 * @brief Obtiene la preferencia en la posición indicada del arreglo de preferencias.
 *
 * Este método permite acceder al nombre de la preferencia almacenada en el índice
 * especificado dentro del arreglo de preferencias del estudiante. Se asume que el
 * índice proporcionado cumple con la condición de estar en el rango permitido
 * (0 ≤ índice < número total de preferencias).
 *
 * @param indice El índice de la preferencia que se desea obtener (debe estar en
 * el rango válido de índices del arreglo de preferencias).
 * @return Una referencia constante a la cadena de texto que representa la preferencia
 * almacenada en la posición especificada por el índice.
 */
const std::string& Estudiante::getPreferencia(int indice) const {
    // Se asume 0 <= indice < numPreferencias
    return preferencias[indice];
}

/**
 * @brief Obtiene el valor del día asociado al objeto Estudiante.
 *
 * Este método devuelve el valor de la variable miembro `dia`,
 * que representa el día almacenado en el objeto Estudiante.
 *
 * @return Un entero que contiene el valor actual del día.
 */
int Estudiante::getDia() const {
    return dia;
}

/**
 * @brief Obtiene el mes asociado al estudiante.
 *
 * Este método devuelve el valor del mes almacenado en el objeto Estudiante.
 *
 * @return El mes correspondiente al estudiante en formato numérico.
 */
int Estudiante::getMes() const {
    return mes;
}

/**
 * @brief Obtiene el año asociado al objeto Estudiante.
 *
 * Este método devuelve el valor del año almacenado en el atributo `anio`,
 * que representa el periodo o año asociado al estudiante.
 *
 * @return El año actual del estudiante como un entero.
 */
int Estudiante::getAnio() const {
    return anio;
}

/**
 * @brief Obtiene la hora asociada al estudiante.
 *
 * Este método retorna el valor de la hora que está actualmente almacenada
 * como parte de los datos del objeto Estudiante.
 *
 * @return La hora asociada al estudiante como un número entero.
 */
int Estudiante::getHora() const {
    return hora;
}

/**
 * @brief Obtiene el minuto asociado al objeto Estudiante.
 *
 * Retorna el valor del atributo `minuto`, que representa el minuto almacenado
 * en el objeto Estudiante.
 *
 * @return El minuto almacenado en el atributo `minuto`.
 */
int Estudiante::getMinuto() const {
    return minuto;
}

/**
 * @brief Establece un nuevo valor para el identificador del estudiante.
 *
 * Este método permite asignar un nuevo valor al atributo `id` del estudiante.
 *
 * @param nuevoId El nuevo identificador a asignar al estudiante.
 */
void Estudiante::setId(int nuevoId) {
    id = nuevoId;
}

/**
 * @brief Establece el nombre completo del estudiante.
 *
 * Asigna un nuevo valor a la propiedad `nombreCompleto` del objeto Estudiante.
 *
 * @param nombre Una cadena que representa el nombre completo del estudiante.
 */
void Estudiante::setNombre(const std::string& nombre) {
    nombreCompleto = nombre;
}

/**
 * @brief Establece la fecha de matrícula del estudiante.
 *
 * Actualiza la fecha de matrícula con el valor proporcionado y la analiza
 * para asignar los valores correspondientes a los atributos internos relacionados
 * con la fecha.
 *
 * @param fechaStr Una cadena que representa la fecha de matrícula en formato válido.
 */
void Estudiante::setFechaMatricula(const std::string& fechaStr) {
    fechaMatricula = fechaStr;
    parsearFecha(fechaStr);
}

/**
 * @brief Establece la fecha y hora de matrícula del estudiante.
 *
 * Este método permite configurar la fecha y hora de matrícula del estudiante,
 * asignando valores específicos para el día, mes, año, hora y minutos.
 * Posteriormente, actualizará el formato de la fecha mediante la función `formatearFecha`.
 *
 * @param d Día de la matrícula.
 * @param m Mes de la matrícula.
 * @param a Año de la matrícula.
 * @param h Hora de la matrícula.
 * @param min Minutos de la matrícula.
 */
void Estudiante::setFechaMatricula(int d, int m, int a, int h, int min) {
    dia = d;
    mes = m;
    anio = a;
    hora = h;
    minuto = min;
    formatearFecha();
}

/**
 * @brief Establece las preferencias del estudiante.
 *
 * Este método asigna las preferencias del estudiante a partir de un arreglo de cadenas.
 * Se limita a las tres primeras preferencias. Si el número de preferencias indicadas
 * excede este límite, solo se toman en cuenta las primeras tres. Si es un número negativo,
 * no se asignan preferencias y estas son limpiadas.
 *
 * @param prefs Arreglo de cadenas que contiene las preferencias a asignar.
 * @param nPrefs Número de preferencias especificadas en el arreglo.
 *               Si es negativo, no se asignan preferencias. Si supera 3, solo las tres primeras
 *               serán consideradas.
 */
void Estudiante::setPreferencias(const std::string prefs[], int nPrefs) {
    numPreferencias = (nPrefs < 0 ? 0 : (nPrefs > 3 ? 3 : nPrefs));
    for (int i = 0; i < 3; i++) {
        if (i < numPreferencias) {
            preferencias[i] = prefs[i];
        } else {
            preferencias[i].clear();
        }
    }
}

/**
 * @brief Convierte un arreglo de números que representan preferencias en nombres de bailes.
 *
 * Este método toma un arreglo de números enteros que representan preferencias numéricas de bailes
 * y los convierte en un arreglo de cadenas con los nombres de los bailes correspondientes.
 * Solo se consideran hasta las primeras 3 preferencias válidas dentro del rango 1 a 5.
 * Las preferencias numéricas fuera de este rango son ignoradas.
 *
 * Las asociaciones de números a nombres de bailes son las siguientes:
 * 1: Bachata, 2: Reggaeton, 3: Salsa, 4: Cumbia, 5: Tango.
 *
 * @param numeros Arreglo de números enteros que indican las preferencias numéricas.
 * @param nNumeros Número de elementos en el arreglo `numeros`.
 * @param salidaPrefs Arreglo de cadenas donde se almacenarán los nombres de los bailes generados.
 * @param nSalida Referencia a un entero donde se almacenará la cantidad de nombres válidos añadidos en `salidaPrefs`.
 */
void Estudiante::convertirPreferenciasATexto(const int numeros[],int nNumeros,std::string salidaPrefs[],int& nSalida)
{
    // Mapa numerico -> nombre de baile
    // 1: Bachata, 2: Reggaeton, 3: Salsa, 4: Cumbia, 5: Tango
    nSalida = 0;
    for (int i = 0; i < nNumeros && nSalida < 3; i++) {
        switch (numeros[i]) {
            case 1: salidaPrefs[nSalida++] = "Bachata";   break;
            case 2: salidaPrefs[nSalida++] = "Reggaeton"; break;
            case 3: salidaPrefs[nSalida++] = "Salsa";     break;
            case 4: salidaPrefs[nSalida++] = "Cumbia";    break;
            case 5: salidaPrefs[nSalida++] = "Tango";     break;
            default:
                // Ignorar valores fuera de 1..5
                break;
        }
    }
}

/**
 * @brief Obtiene una representación en cadena de las preferencias del estudiante.
 *
 * Este método concatena las preferencias del estudiante en una sola cadena,
 * separando cada preferencia por un carácter de barra vertical ('|').
 * Si no hay preferencias, devuelve una cadena vacía.
 *
 * @return Una cadena que contiene las preferencias del estudiante separadas por '|'.
 */
std::string Estudiante::getPreferenciasString() const {
    std::string resultado;
    for (int i = 0; i < numPreferencias; i++) {
        resultado += preferencias[i];
        if (i < numPreferencias - 1) {
            resultado += "|";
        }
    }
    return resultado;
}
/**
 * @brief Obtiene una representación legible de la fecha de matrícula del estudiante.
 *
 * Este método construye una cadena que representa la fecha de matrícula del estudiante
 * en un formato legible, utilizando los valores de día, mes y año almacenados en el objeto.
 * El formato es "DD/MM/YYYY".
 *
 * @return Una cadena que contiene la fecha de matrícula formateada.
 */
std::string Estudiante::getFechaDisplay() const {
    std::ostringstream oss;
    oss << (dia < 10 ? "0" : "") << dia << "/"
        << (mes < 10 ? "0" : "") << mes << "/"
        << anio;
    return oss.str();
}

/**
 * @brief Valida si el nombre completo del estudiante es válido.
 *
 * Este método verifica que el nombre completo contenga exactamente un espacio
 * entre el primer y segundo nombre, y que no comience ni termine con un espacio.
 * Retorna `true` si el nombre es válido, de lo contrario retorna `false`.
 *
 * @param nombre Una cadena que representa el nombre completo a validar.
 * @return `true` si el nombre completo es válido; `false` en caso contrario.
 */
bool Estudiante::validarNombreCompleto(const std::string& nombre) {
    int espacios = 0;
    int n = (int)nombre.size();
    for (int i = 0; i < n; i++) {
        if (nombre[i] == ' ') espacios++;
    }
    // Debe haber exactamente un espacio, y no comenzar ni terminar con espacio
    if (espacios != 1) return false;
    if (nombre.empty() || nombre.front() == ' ' || nombre.back() == ' ') return false;
    return true;
}

/**
 * @brief Valida si una fecha es correcta según el día, mes y año proporcionados.
 *
 * Este método verifica que la fecha especificada por los parámetros `d`, `m` y `a`
 * sea válida. Considera las reglas del calendario, incluyendo años bisiestos para febrero.
 * Retorna `true` si la fecha es válida; de lo contrario, retorna `false`.
 *
 * @param d Día del mes a validar.
 * @param m Mes del año a validar (1 a 12).
 * @param a Año a validar (debe ser mayor que 0).
 * @return `true` si la fecha es válida; `false` en caso contrario.
 */
bool Estudiante::validarFecha(int d, int m, int a) {
    if (a < 1) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;
    int diasMax = 31;
    switch (m) {
        case 2: diasMax = 28; break;
        case 4: case 6: case 9: case 11: diasMax = 30; break;
        default: diasMax = 31;
    }
    if (d > diasMax) return false;
    return true;
}

/**
 * @brief Convierte el nombre de un mes a su número correspondiente.
 *
 * Este método toma el nombre de un mes en formato de texto y lo convierte
 * a su representación numérica (1 para enero, 2 para febrero, etc.). Si el
 * nombre del mes no es reconocido, retorna 0.
 *
 * @param nombreMes Nombre del mes en formato de texto (por ejemplo, "enero", "febrero").
 * @return Un entero que representa el número del mes (1 a 12) o 0 si el nombre no es válido.
 */
int Estudiante::convertirMesANumero(const std::string& nombreMes) {
    // Convertir a minusculas
    std::string s;
    for (char c : nombreMes) {
        s += (char)std::tolower((unsigned char)c);
    }
    if (s == "enero")   return 1;
    if (s == "febrero") return 2;
    if (s == "marzo")   return 3;
    if (s == "abril")   return 4;
    if (s == "mayo")    return 5;
    if (s == "junio")   return 6;
    if (s == "julio")   return 7;
    if (s == "agosto")  return 8;
    if (s == "septiembre" || s == "setiembre") return 9;
    if (s == "octubre") return 10;
    if (s == "noviembre") return 11;
    if (s == "diciembre") return 12;
    return 0;
}

/**
 * @brief Sobrecarga del operador < para comparar dos objetos Estudiante.
 *
 * Este operador permite comparar dos objetos Estudiante basándose en su fecha de matrícula.
 * Retorna `true` si el objeto actual es anterior al objeto proporcionado en la comparación.
 *
 * @param otro El objeto Estudiante con el cual se realiza la comparación.
 * @return `true` si este objeto Estudiante es anterior al objeto proporcionado; de lo contrario, `false`.
 */
bool Estudiante::operator<(const Estudiante& otro) const {
    return compararFecha(otro) < 0;
}

/**
 * @brief Sobrecarga del operador > para comparar dos objetos Estudiante.
 *
 * Compara el objeto actual con otro objeto Estudiante en función de su
 * fecha de matrícula. Se considera que un Estudiante es "mayor" si su
 * fecha de matrícula es posterior a la del otro Estudiante.
 *
 * @param otro Objeto Estudiante con el que se realizará la comparación.
 * @return true si el objeto actual tiene una fecha de matrícula posterior
 *         a la del objeto proporcionado; de lo contrario, false.
 */
bool Estudiante::operator>(const Estudiante& otro) const {
    return compararFecha(otro) > 0;
}

/**
 * @brief Compara dos objetos Estudiante para verificar si son iguales.
 *
 * La comparación se realiza evaluando si la fecha de matrícula de ambos estudiantes
 * es la misma. El método utiliza la función `compararFecha` internamente, que
 * devuelve 0 cuando las fechas son iguales.
 *
 * @param otro Referencia constante al objeto Estudiante con el que se comparará.
 * @return true si ambos objetos Estudiante tienen la misma fecha de matrícula, false en caso contrario.
 */
bool Estudiante::operator==(const Estudiante& otro) const {
    return compararFecha(otro) == 0;
}

/**
 * @brief Sobrecarga del operador <= para comparar dos objetos Estudiante.
 *
 * Este operador se utiliza para determinar si el objeto actual es menor o igual
 * que otro objeto Estudiante basado en la comparación de fechas.
 *
 * @param otro Objeto Estudiante con el cual se comparará el objeto actual.
 * @return true si el objeto actual es menor o igual que el objeto proporcionado
 * como parámetro basado en la comparación de fechas, false en caso contrario.
 */
bool Estudiante::operator<=(const Estudiante& otro) const {
    int cmp = compararFecha(otro);
    return (cmp < 0 || cmp == 0);
}

/**
 * @brief Sobrecarga del operador >= para la clase Estudiante.
 *
 * Compara dos objetos Estudiante tomando en cuenta la lógica implementada
 * en el método compararFecha. Determina si el objeto actual es mayor o igual
 * que otro objeto Estudiante en función de su fecha.
 *
 * @param otro El objeto Estudiante con el que se realiza la comparación.
 * @return true si el objeto actual es mayor o igual que el objeto proporcionado,
 * de lo contrario, false.
 */
bool Estudiante::operator>=(const Estudiante& otro) const {
    int cmp = compararFecha(otro);
    return (cmp > 0 || cmp == 0);
}

/**
 * @brief Sobrecarga del operador de asignación.
 *
 * Permite asignar los valores de un objeto a otro del mismo tipo. Esta sobrecarga asegura
 * que los valores relevantes de todos los miembros del objeto original son copiados al
 * objeto destino de forma adecuada, garantizando la integridad de los datos.
 *
 * @param other Referencia constante al objeto desde el cual se realizará la asignación.
 * @return Una referencia al objeto actual después de que se haya completado la asignación.
 */
std::ostream& operator<<(std::ostream& os, const Estudiante& est) {
    os << "ID: " << est.id
       << ", Nombre: " << est.nombreCompleto
       << ", Fecha: " << est.fechaMatricula
       << ", Preferencias: " << est.getPreferenciasString();
    return os;
}

/**
 * @brief Convierte una cadena de texto que representa una fecha y hora al formato interno del objeto.
 *
 * Este método analiza una cadena de entrada con el formato "MM/DD/YYYY HH:MM" para llenar
 * los valores internos de día, mes, año, hora y minuto del objeto. En caso de que el formato
 * proporcionado no sea válido, los valores se inicializan con los valores por defecto:
 * 01/01/1970 00:00.
 *
 * El análisis separa la fecha (MM/DD/YYYY) y la hora (HH:MM) mediante `std::istringstream`.
 * Los delimitadores usados son caracteres '/' y ':'. Si alguna parte no puede analizarse
 * correctamente, los componentes de fecha y hora se reestablecen a los valores predeterminados.
 *
 * @param fechaStr Una cadena de texto con el formato esperado "MM/DD/YYYY HH:MM".
 */
void Estudiante::parsearFecha(const std::string& fechaStr) {
    // Formato esperado: "MM/DD/YYYY HH:MM"
    // Usamos stringstream para separar
    std::istringstream iss(fechaStr);
    std::string parteFecha, parteHora;
    if (!(iss >> parteFecha >> parteHora)) {
        // Formato invalido, asignar defaults
        dia = mes = 1;
        anio = 1970;
        hora = minuto = 0;
        return;
    }
    // ParteFecha = "MM/DD/YYYY"
    int m=0, d=0, a=0;
    char c1, c2;
    std::istringstream pf(parteFecha);
    pf >> m >> c1 >> d >> c2 >> a;
    dia = d; mes = m; anio = a;
    // ParteHora = "HH:MM"
    int h=0, min=0;
    char c3;
    std::istringstream ph(parteHora);
    ph >> h >> c3 >> min;
    hora = h; minuto = min;
}

/**
 * @brief Formatea la fecha de matrícula del estudiante en una cadena legible.
 *
 * Este método construye una cadena que representa la fecha de matrícula del estudiante
 * en el formato "MM/DD/YYYY HH:MM". Utiliza manipuladores de flujo para asegurar que los
 * números de mes, día, hora y minuto tengan dos dígitos cuando sea necesario.
 */
void Estudiante::formatearFecha() {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << mes << "/"
        << std::setw(2) << std::setfill('0') << dia << "/"
        << anio << " "
        << std::setw(2) << std::setfill('0') << hora << ":"
        << std::setw(2) << std::setfill('0') << minuto;
    fechaMatricula = oss.str();
}

/**
 * @brief Compara la fecha de matrícula de dos objetos Estudiante.
 *
 * Este método compara la fecha de matrícula del objeto actual con la de otro objeto Estudiante.
 * La comparación se realiza en el orden de año, mes, día, hora y minuto. Devuelve un entero
 * que indica si la fecha del objeto actual es anterior, posterior o igual a la del otro objeto.
 *
 * @param otro El objeto Estudiante con el cual se comparará la fecha.
 * @return Un entero que indica el resultado de la comparación:
 *         -1 si la fecha del objeto actual es anterior,
 *          1 si es posterior,
 *          0 si ambas fechas son iguales.
 */
int Estudiante::compararFecha(const Estudiante& otro) const {
    if (anio < otro.anio) return -1;
    if (anio > otro.anio) return 1;
    if (mes < otro.mes) return -1;
    if (mes > otro.mes) return 1;
    if (dia < otro.dia) return -1;
    if (dia > otro.dia) return 1;
    if (hora < otro.hora) return -1;
    if (hora > otro.hora) return 1;
    if (minuto < otro.minuto) return -1;
    if (minuto > otro.minuto) return 1;
    return 0;
}