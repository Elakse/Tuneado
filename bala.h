#ifndef BALA_H
#define BALA_H

#include <stdbool.h>
#include "figuras.h"

typedef struct bala bala_t;

//CREACION Y DESTRUCCION

//Devuelve una bala con las características indicadas. Devuelve NULL al fallar. <jugador> sirve para indicar si la bala la disparo un jugador o no
//Pre: el puntero a figura debe apuntar a una figura creada. <ang> debe estar en radianes
bala_t* bala_crear(double posx, double posy, double vel, double ang, size_t duracion, bool jugador, figura_t* figura);

//Destruye el reactor y devuelve en figura un puntero a la figura anexada al reactor. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void bala_destruir(bala_t* bala, figura_t** figura);

//Destruye el reactor sin devolver una referencia a la figura anexada
void bala_destruir_no_ref(bala_t* bala);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

double bala_get_posx(bala_t *bala);
double bala_get_posy(bala_t *bala);
double bala_get_vely(bala_t *bala);
double bala_get_velx(bala_t * bala);
bool bala_es_de_jugador(bala_t *bala);


//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

void bala_set_pos(bala_t *bala, double posx, double posy);
void bala_set_vel(bala_t *bala, double velx, double vely);
bool bala_actualizar(bala_t* bala, double dt);

//DIBUJO

//Dibuja una bala en su respectiva posicion y angulo, trasladad <tras_x> y <tras_y> y escalada un factor <escala> con respecto a <centro_escala>. Devuelve false en caso de falla.
//Pre: el renderer pasado debe haber sido creado con la librería SDL2
bool bala_dibujar(bala_t* bala, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif