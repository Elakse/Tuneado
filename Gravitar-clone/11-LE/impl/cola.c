#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *sig;
} nodo_t;

struct cola {
    nodo_t *prim;
    nodo_t *ult;
};

static nodo_t *crear_nodo(void *valor) {
    nodo_t *nodo = calloc(1, sizeof(nodo_t));
    if (nodo)
        nodo->dato = valor;
    return nodo;
}


cola_t *cola_crear() {
    return calloc(1, sizeof(cola_t));
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *nodo = crear_nodo(valor);
    if (nodo == NULL) {
        return false;
    }
    if (cola_esta_vacia(cola)) {
        cola->prim = nodo;
    }
    else {
        cola->ult->sig = nodo;
    }
    cola->ult = nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    return cola->prim->dato;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    void *valor = cola_ver_primero(cola);
    nodo_t *aux = cola->prim;
    cola->prim = cola->prim->sig;
    if (cola->prim == NULL) {
        cola->ult = NULL;
    }
    free(aux);
    return valor;
}

void cola_destruir(cola_t *cola, void destruir_dato(void *)) {
    while (!cola_esta_vacia(cola)) {
        void *dato = cola_desencolar(cola);
        if (destruir_dato) {
            destruir_dato(dato);
        }
    }
    free(cola);
}
