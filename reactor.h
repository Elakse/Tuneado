#ifndef REACTOR_H
#define REACTOR_H

#include "figuras.h"

typedef struct reactor reactor_t;

//Pre a todas las funciones: el reactor pasado como parámetro debió haber sido creado.
//Para el funcionamiento de funciones de dibujado y dstancia, la figura anexada al reactor a la hora de crearlo, no debe ser destruida.
//Las figuras anexadas se consideran con un centro en 0,0



//CREACION Y DESTRUCCION

//Devuelve un reactor con las características indicadas y un contador seteado en tiempo. Devuelve NULL al fallar.
//Pre: el puntero a figura debe apuntar a una figura creada. <ang> debe estar en radianes
reactor_t* reactor_crear(double posx, double posy, double ang, size_t tiempo, figura_t* figura);

//Destruye el reactor y devuelve en figura un puntero a la figura anexada al reactor. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void reactor_destruir(reactor_t* reactor, figura_t ** figura);

//Destruye el reactor sin devolver una referencia a la figura anexada
void reactor_destruir_no_ref(reactor_t* reactor);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

double reactor_get_posx(reactor_t* reactor);
double reactor_get_posy(reactor_t* reactor);
double reactor_get_ang(reactor_t* reactor);
size_t reactor_get_contador(reactor_t* reactor);


//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

void reactor_set_pos(reactor_t* reactor, double posx, double posy);
void reactor_set_ang(reactor_t* reactor, double ang);


//ACTUALIZACION

//Actualiza el contador del reactor.
//Devuelve true si el tiempo del reactor todavía no se agotó, devuelve false en caso contrario
bool reactor_actualizar(reactor_t* reactor);

//Reinicia el contador del reactor a su estado inicial.
void reactor_reiniciar(reactor_t* reactor);


//DISTANCIAS

//Devuelve la distancia del punto dado al reactor
double reactor_distancia_a_punto(reactor_t* reactor, double px, double py);

//DIBUJO

//Dibuja un reactor en su respectiva posicion y angulo, trasladad <tras_x> y <tras_y> y escalada un factor <escala> con respecto a <centro_escala>. Devuelve false en caso de falla.
//Pre: el renderer pasado debe haber sido creado con la librería SDL2
bool reactor_dibujar(reactor_t* reactor, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif



