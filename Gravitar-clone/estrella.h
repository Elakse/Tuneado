#ifndef ESTRELLA_H
#define ESTRELLA_H
#include "figuras.h"

struct estrella;
typedef struct estrella estrella_t;

// Creacion y destruccion
estrella_t* estrella_crear(double posx, double posy, figura_t* figura);
void estrella_destruir(estrella_t* estrella);

// GETTERS
double estrella_get_posx(estrella_t* estrella);
double estrella_get_posy(estrella_t* estrella);

// SETTERS
void estrella_set_posx(estrella_t* estrella, double posx);
void estrella_set_posy(estrella_t* estrella, double posy);
bool estrella_set_figura(estrella_t* estrella, figura_t* figura);

// DIBUJADO
bool estrella_dibujar(estrella_t* estrella, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif