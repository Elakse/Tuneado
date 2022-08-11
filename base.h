#ifndef BASE_H
#define BASE_H
#include "figuras.h"

struct base;
typedef struct base base_t;

// Creacion y destruccion
base_t* base_crear(double posx, double posy, figura_t* figura);
void base_destruir(base_t *base);

// GETTERS
double base_get_posx(base_t* base);
double base_get_posy(base_t* base);

// SETTERS
void base_set_posx(base_t* base, double posx);
void base_set_posy(base_t* base, double posy);
bool base_set_figura(base_t* base, figura_t* figura);

// DIBUJADO
void base_dibujar(base_t* base, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif