#include "vector.h"
#include <stdlib.h>

/*
 * Funciones a completar.
 */
bool vector_guardar(vector_t *vector, size_t pos, void* valor) {
    if (pos >= vector->tam) {
        return false;
    }
    vector->datos[pos] = valor;
    return true;
}

bool vector_obtener(vector_t *vector, size_t pos, void** valor) {
    if (pos >= vector->tam) {
        return false;
    }
    *valor = vector->datos[pos];
    return true;
}

size_t vector_largo(vector_t *vector) {
    return vector->tam;
}

void vector_destruir(vector_t *vector) {
    free(vector->datos);
    free(vector);
}

/*
 * Funciones implementadas por la cátedra.
 */
vector_t *vector_crear(size_t tam) {
    vector_t *vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(void*));

    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t *vector, size_t tam_nuevo) {
    if (tam_nuevo == 0) {
        return false;  // No permitimos resize a 0.
    }

    void** datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void*));

    if (datos_nuevo == NULL) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
