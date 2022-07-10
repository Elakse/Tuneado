#include <stdlib.h>
#include "lista.h"

typedef struct nodo {
    char *dato;
    struct nodo *prox;
} nodo_t;

struct lista {
    nodo_t *prim;
    size_t cant; // invariante: cant == cantidad de nodos
};

static nodo_t *nodo_crear(char *dato, nodo_t *prox) {
    nodo_t *n = malloc(sizeof(nodo_t *));
    if (n == NULL) {
        return NULL;
    }
    n->dato = dato;
    n->prox = prox;
    return n;
}

lista_t *lista_crear(void) {
    lista_t *l = malloc(sizeof(lista_t *));
    if (l == NULL) {
        return NULL;
    }
    l->prim = NULL;
    l->cant = 0;
    return l;
}

bool lista_agregar_al_final(lista_t *l, char *dato) {
    nodo_t *nuevo = nodo_crear(dato, NULL);
    if (nuevo == NULL) {
        return false;
    }

    if (l->prim == NULL) {
        // lista vacia
        l->prim = nuevo;
    } else {
        // lista no vacia
        nodo_t *act = l->prim;
        while (act->prox != NULL) {
            act = act->prox;
        }
        // act->prox es NULL
        // o sea, estamos en el ultimo nodo
        act->prox = nuevo;
    }

    l->cant++;
    return true;
}

size_t lista_largo(lista_t *l) {
    return l->cant;
}
