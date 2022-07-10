#ifndef PLANETA_H
#define PLANETA_H

#include "nave.h"
#include "figuras.h"

typedef struct planeta planeta_t;

//Pre a todas las funciones: el planeta pasado como parámetro debió haber sido creado.
//Para el funcionamiento de funciones de dibujado y dstancia, la figura anexada al reactor a la hora de crearlo, no debe ser destruida.
//Las figuras anexadas se consideran con un centro en 0,0



//CREACIÓN y DESTRUCCIÓN

//Crea un planeta con las características dadas.  <posx_tp>, <posy_tp>, <nivel> y <puntaje> son parametros que serviran (según como el usuario desee usarlos) para la interaccion del planeta con otros objetos
//Devuelve NULL en caso de falla
//Pre: el puntero a figura debe apuntar a una figura creada.
planeta_t* planeta_crear(double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t nivel, figura_t* planeta_fig);

//Destruye el planeta y devuelve en figura un puntero a la figura anexada al planeta. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void planeta_destruir(planeta_t* planeta, figura_t** figura);

//Destruye el reactor sin devolver una referencia a la figura anexada
void planeta_destruir_no_ref(planeta_t* planeta);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que está explicitado en sus nombres)

estadio_t planeta_get_estadio(planeta_t* planeta);
figura_t* planeta_get_fig(planeta_t* planeta);
double planeta_get_posx(planeta_t* planeta);
double planeta_get_posy(planeta_t* planeta);
double planeta_get_posx_tp(planeta_t* planeta);
double planeta_get_posy_tp(planeta_t* planeta);
size_t planeta_get_puntaje(planeta_t* planeta);


//DISTANCIA

//Calcula la distancia de un punto a los bordes del planeta. Devuelve -1 en caso de falla.
double planeta_distancia_a_punto(planeta_t* planeta, double px, double py);


//DIBUJO

//Dibuja un planeta en su respectiva posicion, trasladado <tras_x> y <tras_y> y escalada un factor <escala> con respecto a <centro_escala>. Devuelve false en caso de falla.
//Pre: el renderer pasado debe haber sido creado con la librería SDL2
bool planeta_dibujar(planeta_t* planeta, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif
