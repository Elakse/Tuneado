#include "pila.h"
#include <stdlib.h>

// Definición local de la estructura de la pila.
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo ‘datos’.
};

// Tamaño mínimo del arreglo dinámico. Definido como un enum porque queda
// visible en gdb. (Heredado de maxyz :D).
enum { TAM_MIN = 16 };

pila_t *pila_crear() {
    pila_t *pila = NULL;
    void *datos = NULL;

    if (!(pila = calloc(1, sizeof(pila_t))) ||
        !(pila->datos = datos = malloc(TAM_MIN * sizeof(void *)))) {
        free(pila);
        free(datos);
        return NULL;
    }
    pila->capacidad = TAM_MIN;
    return pila;
}

void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
    return pila->cantidad == 0;
}

void *pila_ver_tope(const pila_t *pila) {
    if (pila_esta_vacia(pila))
        return NULL;
    return pila->datos[pila->cantidad - 1];
}

static bool pila_redimensionar(pila_t *pila, size_t nueva_dim) {
    // No se achica la pila por debajo del tamaño inicial.
    if (nueva_dim < TAM_MIN)
        nueva_dim = TAM_MIN;

    void *nuevo = realloc(pila->datos, nueva_dim * sizeof(void *));
    if (!nuevo)
        return false;

    pila->datos = nuevo;
    pila->capacidad = nueva_dim;
    return true;
}

bool pila_apilar(pila_t *pila, void *valor) {
    // Verifica si hay que agrandar, devuelve false si falla la redimensión.
    if (pila->cantidad == pila->capacidad &&
        !pila_redimensionar(pila, 2 * pila->capacidad)) {
        return false;
    }
    pila->datos[pila->cantidad++] = valor;
    return true;
}

void *pila_desapilar(pila_t *pila) {
    if (pila_esta_vacia(pila))
        return NULL;

    // Verifica si hay que achicar, si no puede no hace nada
    size_t capacidad = pila->capacidad;

    if (capacidad > TAM_MIN && pila->cantidad <= capacidad / 4) {
        pila_redimensionar(pila, capacidad / 2);
    }

    return pila->datos[--pila->cantidad];
}
