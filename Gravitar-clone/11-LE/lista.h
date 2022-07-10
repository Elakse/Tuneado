#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

typedef struct lista lista_t;

lista_t *lista_crear(void);
bool lista_agregar_al_final(lista_t *, char *);
size_t lista_largo(lista_t *);

#endif
