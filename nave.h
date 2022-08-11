#ifndef NAVE_H
#define NAVE_H

#include "bala.h"
#include <stdbool.h>
#include "estadio.h"

typedef struct nave nave_t;

//Pre a todas las funciones: la nave pasada como par�metro debi� haber sido creada.
//Para el funcionamiento de funciones de dibujado y dstancia, la figura anexada al reactor a la hora de crearlo, no debe ser destruida.
//Las figuras anexadas se consideran con un centro en 0,0


//CREACION Y DESTRUCCION

//Devuelve una nave con las caracter�sticas indicadas. Devuelve NULL al fallar.
//Pre: el puntero a figura debe apuntar a una figura creada. <ang> debe estar en radianes
nave_t* nave_crear(size_t vidas, size_t fuel, size_t puntos, estadio_t estadio, figura_t* fig_base, figura_t* fig_thruster_on);

//Destruye la nave y devuelve en figura un puntero a la figura anexada a la nave. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void nave_destruir(nave_t* nave, figura_t** fig_base, figura_t** fig_thruster_on);


//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

void nave_setear_pos(nave_t *nave, double px, double py);
void nave_setear_vel(nave_t *nave, double vx, double vy);
void nave_setear_vely(nave_t *nave, double vy);
void nave_setear_velx(nave_t *nave, double vx);
void nave_setear_estadio(nave_t* nave, estadio_t estadio);
void nave_setear_vidas(nave_t* nave, size_t vidas);

//Setea el angulo al que apunta la nave.
//Pre <ang> debe estar en radianes.
void nave_setear_ang_nave(nave_t* nave, double ang);

//Setea la aceleracion propia de la nave
void nave_setear_a_thrust(nave_t* nave, float a);

//Setea el angulo al que apuntar� la gravedad de la nave
//Pre <ang> debe estar en radianes.
void nave_setear_ang_g(nave_t *nave, double ang);


//SUMA Y RESTA DE PARAMETROS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

void nave_restar_vida(nave_t* nave);
void nave_sumar_vida(nave_t* nave);
void nave_sumar_puntos(nave_t* nave, size_t puntos);
void nave_restar_puntos(nave_t* nave, size_t puntos);
void nave_sumar_combustible(nave_t* nave, size_t fuel);
void nave_restar_combustible(nave_t* nave, size_t fuel);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

double nave_get_posx(nave_t *nave);
double nave_get_posy(nave_t *nave);
size_t nave_get_vidas(nave_t* nave);
estadio_t nave_get_estadio(nave_t* nave);
double nave_get_ang(nave_t* nave);
double nave_get_vel(nave_t* nave);
double nave_get_velx(nave_t* nave);
double nave_get_vely(nave_t* nave);
size_t nave_get_fuel(nave_t* nave);
size_t nave_get_puntos(nave_t* nave);


//MOVIMIENTO Y INTERACCIONES

//Gira la nave un cierto angulo
//Pre <ang> debe estar en radianes.
void nave_girar_der(nave_t* nave, double ang);

//Gira la nave un cierto angulo
//Pre <ang> debe estar en radianes.
void nave_girar_izq(nave_t* nave, double ang);

//Modifica la posici�n de la nave seg�n su velocidad, y su velocidad segun la aceleracion. Todo esto para un instante pr�ximo <dt>
void nave_mover(nave_t* nave, double dt);

//Devuelve la distancia del borde de la nave a cierto punto. Devuelve -1 en caso de fallo.
double nave_distancia_a_punto(nave_t* nave, double x, double y);

//Devuelve la distancia de la posicion de la nave a cierta figura.
double nave_distancia_a_figura(nave_t* nave, figura_t* figura);

//Crea una bala disparada en direccion a donde apunta la nave. Con una velocidad base <vel> a�adida al momento de la nave. Se le debe pasar tambi�n la duracion de la bala y su figura.
//Devuelve NULL en caso de fallo.
//Pre: el puntero a figura debe apuntar a una figura creada.
bala_t* nave_dispara(nave_t* nave, double vel, size_t duracion_disparo, figura_t* bala_fig);

//Resta una vida a la nave, la devuelve al estadio INICIO y la mueve a posx posy. Setea su velocidad a 0 y su direccion a PI/2
void nave_matar(nave_t* nave, double posx, double posy);

//DIBUJO

//Dibuja una nave en su respectiva posicion y angulo, trasladada <tras_x> y <tras_y> y escalada un factor <escala> con respecto a <centro_escala>. Devuelve false en caso de falla.
//Pre: el renderer pasado debe haber sido creado con la librer�a SDL2
bool nave_dibujar(nave_t* nave, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif
