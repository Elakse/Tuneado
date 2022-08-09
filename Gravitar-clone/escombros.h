#ifndef ESCOMBROS_H
#define escombro_H

#include <stdbool.h>
#include "figuras.h"

typedef struct escombro escombro_t;

//CREACION Y DESTRUCCION

//Devuelve una escombro con las características indicadas. Devuelve NULL al fallar. <jugador> sirve para indicar si la escombro la disparo un jugador o no
//Pre: el puntero a figura debe apuntar a una figura creada. <ang> debe estar en radianes
escombro_t* escombro_crear(double posx, double posy, double vel, double ang, size_t duracion, figura_t* figura);

//Destruye el reactor y devuelve en figura un puntero a la figura anexada al reactor. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void escombro_destruir(escombro_t* escombro, figura_t** figura);

//Destruye el reactor sin devolver una referencia a la figura anexada
void escombro_destruir_no_ref(escombro_t* escombro);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

double escombro_get_posx(escombro_t* escombro);
double escombro_get_posy(escombro_t* escombro);

//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

void escombro_set_pos(escombro_t* escombro, double posx, double posy);
void escombro_set_vel(escombro_t* escombro, double velx, double vely);
bool escombro_actualizar(escombro_t* escombro, double dt);

//DIBUJO

//Dibuja una escombro en su respectiva posicion y angulo, trasladad <tras_x> y <tras_y> y escalada un factor <escala> con respecto a <centro_escala>. Devuelve false en caso de falla.
//Pre: el renderer pasado debe haber sido creado con la librería SDL2
bool escombro_dibujar(escombro_t* escombro, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif