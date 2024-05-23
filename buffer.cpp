#include <iostream>
#include <cstdlib>
#include <cstring>


// Clase para la estructura de PageFrame dentro del BufferPool
class MarcoPagina
{
public:
    int numMarco;        // Número asociado a cada marco de página
    int numPagina;       // Número de página de la página presente en el marco de página
    bool flagModificado; // Indicador de modificación para determinar si la página fue modificada/escrita
    int conteoFijacion;  // Contador de fijación para marcar si la página está en uso por otros usuarios
    int bitRef;          // Bit de referencia utilizado en el algoritmo CLOCK para marcar la página que se refiere
    char *datos;         // Datos reales presentes en la página
    MarcoPagina *siguiente, *anterior; // Nodos de la lista doblemente enlazada donde cada nodo es un marco, apuntando a otros marcos

    // Constructor
    MarcoPagina()
        : numMarco(-1), numPagina(-1), flagModificado(false), conteoFijacion(0), bitRef(0),
          datos(nullptr), siguiente(nullptr), anterior(nullptr) {}

    // Destructor
    ~MarcoPagina()
    {
        delete[] datos;
    }
};

// Clase para la estructura de BM_BufferPool_Mgmt para almacenar la información de gestión
class GestionBufferPool
{
public:
    int conteoOcupado;      // Para mantener el conteo del número de marcos ocupados dentro del pool
    void *datosEstrategia;  // Para pasar parámetros para las estrategias de reemplazo de páginas
    MarcoPagina *cabeza, *cola, *inicio; // Para mantener el seguimiento de los nodos en la lista enlazada
    PageNumber *contenidoMarco; // Un arreglo de números de página para almacenar las estadísticas del número de páginas almacenadas en el marco de página
    int *conteoFijacion;     // Un arreglo de enteros para almacenar las estadísticas de conteo de fijaciones para una página
    bool *bitModificado;     // Un arreglo de booleanos para almacenar las estadísticas de los bits modificados para la página modificada
    int numLecturas;         // Para dar el número total de páginas leídas desde el buffer pool
    int numEscrituras;       // Para dar el número total de páginas escritas en el buffer pool

    // Constructor
    GestionBufferPool()
        : conteoOcupado(0), datosEstrategia(nullptr), cabeza(nullptr), cola(nullptr), inicio(nullptr),
          contenidoMarco(nullptr), conteoFijacion(nullptr), bitModificado(nullptr),
          numLecturas(0), numEscrituras(0) {}

    // Destructor
    ~GestionBufferPool()
    {
        delete[] contenidoMarco;
        delete[] conteoFijacion;
        delete[] bitModificado;
        MarcoPagina *actual = cabeza;
        while (actual != nullptr)
        {
            MarcoPagina *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
};
