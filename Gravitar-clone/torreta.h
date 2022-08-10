#ifndef TORRETA_H
#define TORRETA_H

#include "figuras.h"
#include "bala.h"
#include "escombros.h"

typedef struct torreta torreta_t;

//Pre a todas las funciones: la torreta pasada como par�metro debi� haber sido creada.
//Para el funcionamiento de funciones de dibujado y dstancia, la figura anexada al reactor a la hora de crearlo, no debe ser destruida.
//Las figuras anexadas se consideran con un centro en 0,0

//CREACION Y DESTRUCCION

//Devuelve una torreta con las caracter�sticas indicadas. Devuelve NULL al fallar.
//Pre: el puntero a figura debe apuntar a una figura creada. <ang> debe estar en radianes
torreta_t* torreta_crear(double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando);

//Destruye el reactor y devuelve en figura un puntero a la figura anexada al reactor. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void torreta_destruir(torreta_t* torreta, figura_t** fig_base, figura_t** fig_disparando);

//Destruye el reactor sin devolver una referencia a la figura anexada
void torreta_destruir_no_ref(torreta_t* torreta);



//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

figura_t* torreta_get_fig(torreta_t* torreta);
double torreta_get_posx(torreta_t* torreta);
double torreta_get_posy(torreta_t* torreta);
double torreta_get_ang(torreta_t* torreta);


//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

void torreta_set_pos(torreta_t* torreta, double posx, double posy);
void torreta_set_ang(torreta_t* torreta, double ang);

//ACCIONES Y DISTANCIAS

//Randomiza los disparos que se efectuaran durante la ejecuci�n del programa. De no usar la funcion los disparos ser�n siempre los mismos cada vez que se inicie el programa.
void torreta_randomizar_disparos(void);

//Dispara una bala_t en un angulo <ang>, con un abanico <rango>, probabilidad de <chances>/1000, cierta velocidad <vel>. Se debe indicar tambi�n la duracion del disparo y la figura de la bala.
//Devuelve el puntero a la bala disparada, o NULL en caso de no disparar nada.
//Pre: <bala_fig> debe apuntar a una figura creada. <ang> debe estar en radianes.
bala_t* torreta_dispara(torreta_t* torreta, double ang, double rango, size_t chances, double vel, size_t duracion_disparo, figura_t* bala_fig);

//Devuelve la distancia de un punto a los bordes de la torreta. Devuelve -1 en caso de falla.
double torreta_distancia_a_punto(torreta_t* torreta, double px, double py);

//DIBUJO

//Dibuja una torreta en su respectiva posicion y angulo, trasladad <tras_x> y <tras_y> y escalada un factor <escala> con respecto a <centro_escala>. Devuelve false en caso de falla.
//Pre: el renderer pasado debe haber sido creado con la librer�a SDL2
bool torreta_dibujar(torreta_t* torreta, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif
