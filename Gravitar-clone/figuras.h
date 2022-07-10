#ifndef FIGURAS_H
#define FIGURAS_H
#include <stdbool.h>
#include <stdlib.h>
#include "polilinea.h"
#include <stdio.h>

struct figura;
typedef struct figura figura_t;

typedef enum {
	ICONO,
	NIVEL,
	SPRITE,
	PLANETA,
	BASE,
	COMBUSTIBLE,
	TORRETA,
	REACTOR,
} figura_tipo_t;

//Pre a todas las funciones: la figura pasada como par�metro debi� haber sido creada.



//CREACION Y DESTRUCCION

//Crea una figura con su tipo, nombre y si es infinita o no. No inicializa sus polilineas. <nombre> debe tener menos de 20 caracteres.
figura_t* figura_crear(bool inf, figura_tipo_t tipo, char* nombre);

//Destruye la figura
void figura_destruir(figura_t* figura);

//LECTURA

//Lee una figura de un archivo <f>. Devueve NULL si falla
//Pre: el archivo debe haber sido abierto en modo de lectura binaria
figura_t* figura_leer(FILE* f);

//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

polilinea_t** figura_obtener_polis(figura_t* figura);
bool figura_comparar_nombres(figura_t* figura, char* nombre);
bool figura_es_inf(figura_t* figura);
char* figura_obtener_nombre(figura_t* figura);
figura_tipo_t figura_obtener_tipo(figura_t* figura);
double figura_obtener_x_max(figura_t* figura);
double figura_obtener_y_max(figura_t* figura);
double figura_obtener_x_min(figura_t* figura);
double figura_obtener_y_min(figura_t* figura);
double figura_obtener_alto(figura_t* figura);
double figura_obtener_ancho(figura_t* figura);


//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

//Agrega una polilinea a la figura
//Pre: la polilinea debi� haber sido creada
bool figura_agregar_poli(figura_t* figura, polilinea_t* poli);



//MOVIMIENTOS Y DISTANCIAS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

void figura_trasladar(figura_t* figura, float dx, float dy);
void figura_rotar(figura_t* figura, double rad);
void figura_escalar(figura_t* figura, double escala);
double figura_distancia_a_punto(figura_t* figura, double px, double py);

//MEMORIA

//Devuelve una polilinea clonada. Devuelve NULL en caso de que falle
figura_t* figura_clonar(figura_t* figura);

//DIBUJADO

//Dibuja la figura desplazada un <dx> y <dy>, rotada <ang> y escalada con respecot a <centro> por un factor <escala>
//Pre: el renderer pasado debe haber sido creado con la librer�a SDL2. <ang> debe estar en radianes.
bool figura_dibujar(figura_t* figura, double dx, double dy, double ang, double centro, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif
