#include "Instructor.h"
#include <algorithm>
#include <cctype>
#include <iomanip>

/**
 * @brief Bono por antigüedad para instructores con más de 5 años de servicio.
 *
 * Este bono se otorga a los instructores que han trabajado en la academia
 * por más de 5 años, como reconocimiento a su antigüedad.
 */
const double Instructor::BONO_ANTIGUEDAD = 24350.0;
/**
 * @brief Porcentaje utilizado para calcular la popularidad de un instructor.
 *
 * Este valor representa el porcentaje base que se aplica para medir
 * la popularidad del instructor, considerando métricas específicas
 * relacionadas con la interacción y la satisfacción de los estudiantes.
 */
const double Instructor::PORCENTAJE_POPULARIDAD = 0.05;

/**
 * @brief Bono otorgado a instructores especializados en clases de tango.
 *
 * Este bono está destinado a reconocer y compensar a los instructores
 * que imparten clases de tango dentro de la academia.
 */
const double Instructor::BONO_TANGO = 5600.0;

/**
 * @brief Porcentaje de contribución al AFP para los instructores.
 *
 * Representa el porcentaje fijo del salario bruto que debe ser destinado
 * al fondo de pensiones (AFP) según las regulaciones aplicables.
 */
const double Instructor::PORCENTAJE_AFP = 0.19;

/**
 * @brief Constructor por defecto de la clase Instructor.
 *
 * Inicializa un objeto de la clase Instructor con valores predeterminados,
 * incluyendo identificador, nombre completo, año de ingreso, sueldo base,
 * y tipo de baile.
 *
 * @return Una instancia de la clase Instructor inicializada con valores por defecto.
 */
Instructor::Instructor() : id(0), nombreCompleto(""), anioIngreso(0), sueldoBase(0.0), tipoBaile("") {
}

/**
 * @brief Constructor parametrizado de la clase Instructor.
 *
 * Inicializa un objeto Instructor con los valores proporcionados, asegurando
 * que el tipo de baile sea válido y normalizado.
 *
 * @param id ID único del instructor (4 dígitos).
 * @param nombreCompleto Nombre completo del instructor.
 * @param anioIngreso Año en que el instructor ingresó a la academia.
 * @param sueldoBase Sueldo base del instructor.
 * @param tipoBaile Tipo de baile que enseña el instructor, debe ser válido.
 */
Instructor::Instructor(int id, const std::string& nombreCompleto, int anioIngreso, double sueldoBase, const std::string& tipoBaile)
    : id(id),
    nombreCompleto(nombreCompleto),
    anioIngreso(anioIngreso),
    sueldoBase(sueldoBase),
    tipoBaile(normalizarTipoBaile(tipoBaile)) {}

/**
 * @brief Destructor de la clase Instructor.
 *
 * Libera los recursos asociados al objeto Instructor, limpiando cadenas
 * de texto y restableciendo campos numéricos a su valor predeterminado.
 */
Instructor::~Instructor() {
    // Limpiar cadenas de texto
    nombreCompleto.clear();
    tipoBaile.clear();
    // Restablecer campos numericos (opcional)
    id = 0;
    anioIngreso = 0;
    sueldoBase = 0.0;
}

/**
 * @brief Obtiene el identificador único del instructor.
 *
 * Este método devuelve el ID único asignado al instructor.
 *
 * @return El identificador del instructor.
 */
int Instructor::getId() const { return id; }
/**
 * @brief Obtiene el nombre completo del instructor.
 *
 * Este método retorna el nombre y apellido completos del instructor.
 *
 * @return El nombre completo del instructor como una cadena de texto.
 */
std::string Instructor::getNombreCompleto() const { return nombreCompleto; }
/**
 * @brief Obtiene el año de ingreso del instructor.
 *
 * Este método devuelve el año en que el instructor comenzó a trabajar
 * en la academia.
 *
 * @return El año de ingreso del instructor.
 */
int Instructor::getAnioIngreso() const { return anioIngreso; }
/**
 * @brief Obtiene el sueldo base del instructor.
 *
 * Devuelve el salario base asignado al instructor sin incluir bonos
 * ni otras compensaciones adicionales.
 *
 * @return El sueldo base del instructor.
 */
double Instructor::getSueldoBase() const { return sueldoBase; }
/**
 * @brief Obtiene el tipo de baile que enseña el instructor.
 *
 * Este método devuelve el estilo de baile que el instructor está calificado
 * para enseñar, como por ejemplo salsa, tango o hip-hop.
 *
 * @return El tipo de baile del instructor.
 */
std::string Instructor::getTipoBaile() const { return tipoBaile; }

/**
 * @brief Establece un nuevo ID para el instructor.
 *
 * Este método permite asignar un nuevo identificador único al instructor,
 * reemplazando cualquier valor previamente establecido.
 *
 * @param id El nuevo ID que se asignará al instructor.
 */
void Instructor::setId(int id) { this->id = id; }
/**
 * @brief Establece el nombre completo del instructor.
 *
 * Permite definir o actualizar el nombre completo del instructor en la academia.
 *
 * @param nombreCompleto El nombre completo que se asignará al instructor.
 */
void Instructor::setNombreCompleto(const std::string& nombreCompleto) {
    this->nombreCompleto = nombreCompleto;
}
/**
 * @brief Establece el año de ingreso del instructor.
 *
 * Asigna el año en que el instructor comenzó a trabajar en la academia,
 * lo cual es importante para calcular su antigüedad y bonificaciones.
 *
 * @param anioIngreso El año de ingreso que se asignará al instructor.
 */
void Instructor::setAnioIngreso(int anioIngreso) { this->anioIngreso = anioIngreso; }
/**
 * @brief Establece el sueldo base del instructor.
 *
 * Asigna un nuevo valor al sueldo base del instructor, que se utilizará
 * para calcular su remuneración total.
 *
 * @param sueldoBase El nuevo sueldo base que se asignará al instructor.
 */
void Instructor::setSueldoBase(double sueldoBase) { this->sueldoBase = sueldoBase; }
/**
 * @brief Establece el tipo de baile que enseña el instructor.
 *
 * Este método permite definir o actualizar el género de baile que el instructor imparte
 * en la academia de zumba, asegurando que el tipo de baile sea válido.
 *
 * @param tipoBaile El tipo de baile que se asignará al instructor.
 */
void Instructor::setTipoBaile(const std::string& tipoBaile) {
    this->tipoBaile = normalizarTipoBaile(tipoBaile);
}

/**
 * @brief Calcula el sueldo bruto de un instructor considerando diversos bonos.
 *
 * Este método evalúa el sueldo base del instructor y aplica incrementos al salario
 * por antigüedad, popularidad y por enseñar Tango. Cada bono se agrega en función
 * de las respectivas condiciones.
 *
 * @param anioActual El año actual utilizado para calcular la antigüedad del instructor.
 * @param esTipoMasPopular Indica si el instructor pertenece al tipo más popular.
 * @return El sueldo bruto del instructor con los bonos aplicados.
 */
double Instructor::calcularSueldoBruto(int anioActual, bool esTipoMasPopular) const {
    double sueldoBruto = sueldoBase;

    // Bono por antigüedad (más de 5 años)
    if (tieneMasDe5Anios(anioActual)) {
        sueldoBruto += BONO_ANTIGUEDAD;
    }

    // Bono por popularidad (5% del sueldo base)
    if (esTipoMasPopular) {
        sueldoBruto += sueldoBase * PORCENTAJE_POPULARIDAD;
    }

    // Bono por enseñar Tango
    if (enseniaTango()) {
        sueldoBruto += BONO_TANGO;
    }

    return sueldoBruto;
}

/**
 * @brief Calcula la cotización AFP del sueldo bruto del instructor.
 *
 * Este método calcula el monto que se debe descontar del sueldo bruto
 * del instructor para su cotización al fondo de pensiones (AFP), aplicando
 * un porcentaje fijo.
 *
 * @param sueldoBruto El sueldo bruto del instructor antes de aplicar descuentos.
 * @return El monto de la cotización AFP.
 */
double Instructor::calcularCotizacionAFP(double sueldoBruto) const {
    return sueldoBruto * PORCENTAJE_AFP;
}

/**
 * @brief Calcula el sueldo líquido del instructor después de descontar la cotización AFP.
 *
 * Este método toma el sueldo bruto del instructor y le resta la cotización AFP
 * para obtener el sueldo líquido que recibirá.
 *
 * @param sueldoBruto El sueldo bruto del instructor antes de aplicar descuentos.
 * @return El sueldo líquido del instructor después de descontar la cotización AFP.
 */
double Instructor::calcularSueldoLiquido(double sueldoBruto) const {
    return sueldoBruto - calcularCotizacionAFP(sueldoBruto);
}

/**
 * @brief Calcula los años de servicio del instructor.
 *
 * Este método calcula la cantidad de años que el instructor ha trabajado
 * en la academia, restando el año de ingreso del año actual.
 *
 * @param anioActual El año actual para calcular los años de servicio.
 * @return La cantidad de años trabajados por el instructor.
 */
int Instructor::calcularAniosServicio(int anioActual) const {
    return anioActual - anioIngreso;
}

/**
 * @brief Calcula los días trabajados por el instructor hasta la fecha actual.
 *
 * Este método estima la cantidad de días que el instructor ha trabajado
 * en la academia, considerando el año de ingreso y el día actual.
 *
 * @param anioActual El año actual para calcular los días trabajados.
 * @param diaActual El día actual del mes para calcular los días trabajados.
 * @return La cantidad de días trabajados por el instructor.
 */
int Instructor::calcularDiasTrabajados(int anioActual, int diaActual) const {
    int aniosCompletos = anioActual - anioIngreso - 1;
    int diasAniosCompletos = aniosCompletos * 365;

    // Aproximación: agregar días por años bisiestos
    int aniosBisiestos = aniosCompletos / 4;
    diasAniosCompletos += aniosBisiestos;

    // Agregar días del año actual
    diasAniosCompletos += diaActual;

    return diasAniosCompletos;
}

/**
 * @brief Verifica si el instructor tiene más de 5 años de servicio.
 *
 * Este método determina si el instructor ha trabajado en la academia
 * por más de 5 años, basándose en el año actual y el año de ingreso.
 *
 * @param anioActual El año actual para calcular los años de servicio.
 * @return true si el instructor tiene más de 5 años de servicio, false en caso contrario.
 */
bool Instructor::tieneMasDe5Anios(int anioActual) const {
    return calcularAniosServicio(anioActual) > 5;
}

/**
 * @brief Verifica si el instructor enseña Tango.
 *
 * Este método determina si el tipo de baile que enseña el instructor es Tango.
 *
 * @return true si el instructor enseña Tango, false en caso contrario.
 */
bool Instructor::enseniaTango() const {
    return tipoBaile == "Tango";
}

/**
 * @brief Valida si un tipo de baile es válido.
 *
 * Este método verifica si el tipo de baile proporcionado es uno de los tipos
 * válidos definidos en la academia, normalizando la entrada para asegurar
 * consistencia en la comparación.
 *
 * @param tipo Tipo de baile a validar.
 * @return true si el tipo de baile es válido, false en caso contrario.
 */
bool Instructor::validarTipoBaile(const std::string& tipo) {
    std::string tipoNormalizado = tipo;
    // Convertir primera letra a mayúscula y resto a minúscula
    if (!tipoNormalizado.empty()) {
        tipoNormalizado[0] = std::toupper(tipoNormalizado[0]);
        for (size_t i = 1; i < tipoNormalizado.length(); ++i) {
            tipoNormalizado[i] = std::tolower(tipoNormalizado[i]);
        }
    }

    return (tipoNormalizado == "Bachata" ||
            tipoNormalizado == "Reggaeton" ||
            tipoNormalizado == "Salsa" ||
            tipoNormalizado == "Cumbia" ||
            tipoNormalizado == "Tango");
}

/**
 * @brief Obtiene una lista de tipos de baile válidos.
 *
 * Este método devuelve una cadena que contiene todos los tipos de baile
 * válidos separados por comas, para facilitar la validación y selección.
 *
 * @return Una cadena con los tipos de baile válidos.
 */
std::string Instructor::obtenerTiposBaileValidos() {
    return "Bachata, Reggaeton, Salsa, Cumbia, Tango";
}

/**
 * @brief Sobrecarga del operador menor (<) para comparar instructores.
 *
 * Compara dos objetos de tipo Instructor basándose en su ID.
 *
 * @param otro El instructor con el cual se va a comparar el objeto actual.
 * @return true si el objeto actual es considerado menor que el objeto otro,
 *         false en caso contrario.
 */
bool Instructor::operator<(const Instructor& otro) const {
    return id < otro.id;
}

/**
 * @brief Compara dos instructores en función de sus identificadores.
 *
 * Este operador determina si el identificador del instructor actual es
 * mayor que el identificador del instructor proporcionado como parámetro.
 *
 * @param otro El objeto Instructor con el que se realizará la comparación.
 * @return true si el identificador del instructor actual es mayor que el identificador del instructor proporcionado; de lo contrario, false.
 */
bool Instructor::operator>(const Instructor& otro) const {
    return id > otro.id;
}

/**
 * @brief Sobrecarga del operador de igualdad para la clase Instructor.
 *
 * Compara dos objetos de la clase Instructor verificando si tienen el mismo identificador.
 *
 * @param otro Referencia constante a otro objeto de la clase Instructor.
 * @return true si ambos objetos tienen el mismo valor de identificador, false en caso contrario.
 */
bool Instructor::operator==(const Instructor& otro) const {
    return id == otro.id;
}

/**
 * @brief Compara si un instructor es menor o igual que otro instructor.
 *
 * Este operador relacional permite comparar dos objetos de tipo Instructor
 * basado en su identificador único (id).
 *
 * @param otro El otro objeto Instructor a comparar.
 * @return true si el identificador del instructor actual es menor o igual al del otro instructor. false en caso contrario.
 */
bool Instructor::operator<=(const Instructor& otro) const {
    return id <= otro.id;
}

/**
 * @brief Compara si el identificador del instructor actual es mayor o igual
 *        al identificador de otro instructor.
 *
 * Este operador relacional permite determinar si el instructor actual tiene
 * un identificador que es mayor o igual al identificador de otro instructor.
 *
 * @param otro Instructor con el cual se compara el identificador.
 * @return true si el identificador del instructor actual es mayor o igual al
 *         identificador del otro instructor; false en caso contrario.
 */
bool Instructor::operator>=(const Instructor& otro) const {
    return id >= otro.id;
}

/**
 * @brief Sobrecarga de un operador específico para realizar una operación definida por el usuario.
 *
 * Permite personalizar el comportamiento de un operador estándar según las necesidades particulares
 * de la clase o tipo en donde se implemente.
 *
 * @param lhs El operando izquierdo utilizado en la operación del operador sobrecargado.
 * @param rhs El operando derecho utilizado en la operación del operador sobrecargado.
 * @return El resultado de la operación personalizada definida para el operador sobrecargado.
 */
std::ostream& operator<<(std::ostream& os, const Instructor& instructor) {
    os << "ID: " << instructor.id
       << ", Nombre: " << instructor.nombreCompleto
       << ", Año Ingreso: " << instructor.anioIngreso
       << ", Sueldo Base: $" << std::fixed << std::setprecision(0) << instructor.sueldoBase
       << ", Tipo Baile: " << instructor.tipoBaile;
    return os;
}

/**
 * @brief Normaliza el tipo de baile a un formato estándar.
 *
 * Este método convierte el tipo de baile a un formato donde la primera letra
 * es mayúscula y el resto son minúsculas, asegurando consistencia en la representación.
 *
 * @param tipo El tipo de baile a normalizar.
 * @return El tipo de baile normalizado.
 */
std::string Instructor::normalizarTipoBaile(const std::string& tipo) const {
    if (tipo.empty()) return tipo;

    std::string tipoNormalizado = tipo;
    // Primera letra mayúscula
    tipoNormalizado[0] = std::toupper(tipoNormalizado[0]);
    // Resto en minúscula
    for (size_t i = 1; i < tipoNormalizado.length(); ++i) {
        tipoNormalizado[i] = std::tolower(tipoNormalizado[i]);
    }

    return tipoNormalizado;
}
