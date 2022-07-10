#ifndef COMBUSTIBLE_H
#define COMBUSTIBLE_H
#include "figuras.h"

typedef struct combustible combustible_t;

//CREACION Y DESTRUCCION
combustible_t* combustible_crear(double posx, double posy, double ang, figura_t* figura);
void combustible_destruir(combustible_t* combustible, figura_t** figura);
void combustible_destruir_no_ref(combustible_t* combustible);

//GETTERS
double combustible_get_posx(combustible_t* combustible);
double combustible_get_posy(combustible_t* combustible);
double combustible_get_ang(combustible_t* combustible);


//SETTERS
void combustible_set_pos(combustible_t* combustible, double posx, double posy);
void combustible_set_ang(combustible_t* combustible, double ang);


//DISTANCIA
double combustible_distancia_a_punto(combustible_t* combustible, double px, double py);

//DIBUJAR
bool combustible_dibujar(combustible_t* combustible, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif