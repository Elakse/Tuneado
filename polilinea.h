#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <SDL.h>
#include "color.h"

#define ROJO        0x04
#define VERDE       0x02
#define AZUL        0x01
#define INFINITO    0x40
#define TIPO        0x07
#define CANT_PUNTOS 0x03FF

typedef struct polilinea polilinea_t;

//Pre a todas las funciones: la polilinea pasada como par�metro debi� haber sido creada.


//CREACI�N Y DESTRUCCION

//Crea una polilinea vac�a de tama�o <n>
polilinea_t *polilinea_crear_vacia(size_t n);

//Crea una polilinea inicializada con <puntos> de tama�o <n> y color <color>
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t color);

//Destruye la polilinea.
void polilinea_destruir(polilinea_t *polilinea);


//LECTURA

//Lee una polilinea de un archivo
//Pre: el archivo debe haber sido abierto en modo de lectura binaria
polilinea_t* leer_polilinea(FILE* f);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);

//Devuelve false en caso de falla.
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
color_t polilinea_obtener_color(const polilinea_t *polilinea);
double polilinea_obtener_x_max(const polilinea_t* polilinea);
double polilinea_obtener_y_max(const polilinea_t* polilinea);
double polilinea_obtener_x_min(const polilinea_t* polilinea);
double polilinea_obtener_y_min(const polilinea_t* polilinea);


//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

//Devuelve false en caso de falla.
bool polilinea_setear_punto(polilinea_t* polilinea, size_t pos, float x, float y);
void polilinea_setear_color(polilinea_t* polilinea, color_t color);


//MOVIMIENTO Y DISTANCIA (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

void polilinea_trasladar(polilinea_t *polilinea, float dx, float dy);

//El angulo <rad> dado debe estar en radianes
void polilinea_rotar(polilinea_t *polilinea, double rad);
void polilinea_escalar(polilinea_t* polilinea, double escala);
double distancia_punto_a_polilinea(const polilinea_t *polilinea, float px, float py);


//MEMORIA

//Devuelve una polilinea clonada. Devuelve NULL en caso de fallo.
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

//DIBUJADO


void polilinea_dibujar(polilinea_t* poli, double ventana_alto, SDL_Renderer* renderer);

#endif
