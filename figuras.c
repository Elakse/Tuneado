#include "figuras.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "polilinea.h"
#include <stdio.h>
#include "config.h"

struct figura {
	char nombre[20];
	bool inf;
	figura_tipo_t tipo;
	size_t cant;
	polilinea_t** polis;
};

//CREACI�N, DESTRUCCI�N Y LECTURA

figura_t* figura_crear(bool inf, figura_tipo_t tipo, char* nombre) {
	figura_t* figura = malloc(sizeof(figura_t));
	if (figura == NULL) return NULL;

	figura->polis = NULL;
	figura->inf = inf;                    //Crea una figura sin polilineas
	figura->cant = 0;
	figura->tipo = tipo;

	if (strlen(nombre) < 20) {
		strcpy(figura->nombre, nombre);
	}
	else {
		free(figura);
		return NULL;
	}
	return figura;
}

void figura_destruir(figura_t* figura) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_destruir(figura->polis[i]);   //Destruye primero todas las polilineas
	}
	free(figura->polis);
	free(figura);
}

//DE USO PROPIO

bool leer_encabezado_figura(FILE* f, char nombre[], figura_tipo_t* tipo, bool* infinito, size_t* cantidad_polilineas) {
	size_t nom_size, carac_size, cant_size;

	nom_size = fread(nombre, sizeof(char), 20, f);
	if (nom_size < 20) return false;

	uint8_t carac = 0;
	carac_size = fread(&carac, sizeof(char), 1, f);
	if (carac_size < 1) return false;

	uint16_t cant = 0;
	cant_size = fread(&cant, sizeof(uint16_t), 1, f);
	if (cant_size < 1) return false;

	*cantidad_polilineas = cant;
	*infinito = (carac & INFINITO);
	*tipo = ((carac >> 1) & TIPO);
	return 1;
}

//LECTURA

figura_t* figura_leer(FILE* f) {
	bool inf;
	size_t cant;
	figura_tipo_t tipo;
	char nombre[20];
	if (!leer_encabezado_figura(f, nombre, &tipo, &inf, &cant)) return NULL;  //Lee el encabezado de la figura y la inicializa con esos parametros
	figura_t* figura = figura_crear(inf, tipo, nombre);
	for (size_t i = 0; i < cant; i++) {
		polilinea_t* poli = leer_polilinea(f);
		if (poli == NULL) {
			figura_destruir(figura);
			return NULL;
		}
		if (!figura_agregar_poli(figura, poli)) {       //Lee cada polilinea y la agrega a la figura
			figura_destruir(figura);
			polilinea_destruir(poli);
			return NULL;
		}
		polilinea_destruir(poli);
	}

	return figura;
}

//GETTERS Y SETTERS

bool figura_agregar_poli(figura_t* figura, polilinea_t* poli) {
	polilinea_t* clon = polilinea_clonar(poli);    //Agrega una copia de la polilinea pasada a la figura, actualiza cant yhace realloc
	if (clon == NULL) return false;
	polilinea_t** aux = realloc(figura->polis, sizeof(polilinea_t*) * (figura->cant + 1));
	if (aux == NULL) {
		polilinea_destruir(clon);
		return false;
	}
	figura->polis = aux;
	figura->polis[figura->cant] = clon;
	figura->cant++;
	return true;
}

bool figura_comparar_nombres(figura_t* figura, char* nombre) {
	return strcmp(figura->nombre, nombre) ? false : true;
}


figura_tipo_t figura_obtener_tipo(figura_t* figura) {
	return figura->tipo;
}

char* figura_obtener_nombre(figura_t* figura) {
	return figura->nombre;
}

polilinea_t** figura_obtener_polis(figura_t* figura){
	polilinea_t** polis = figura->polis;
	return polis;
}

double figura_obtener_x_max(figura_t* figura) {
	double max = polilinea_obtener_x_max(figura->polis[0]);
	double aux = 0;
	for (size_t i = 1; i < figura->cant; i++) {
		aux = polilinea_obtener_x_max(figura->polis[i]);
		if (aux > max)
			max = aux;
	}
	return max;
}

double figura_obtener_y_max(figura_t* figura) {
	double max = polilinea_obtener_y_max(figura->polis[0]);
	double aux;
	for (size_t i = 1; i < figura->cant; i++) {
		if ((aux = polilinea_obtener_y_max(figura->polis[i])) > max)
			max = aux;
	}
	return max;
}

double figura_obtener_x_min(figura_t* figura) {
	double min = polilinea_obtener_x_min(figura->polis[0]);
	double aux = 0;
	for (size_t i = 1; i < figura->cant; i++) {
		aux = polilinea_obtener_x_min(figura->polis[i]);
		if (aux < min)
			min = aux;
	}
	return min;
}

double figura_obtener_y_min(figura_t* figura) {
	double min = polilinea_obtener_y_min(figura->polis[0]);
	double aux;
	for (size_t i = 1; i < figura->cant; i++) {
		if ((aux = polilinea_obtener_y_min(figura->polis[i])) < min)
			min = aux;
	}
	return min;
}

double figura_obtener_ancho(figura_t* figura) {
	return fabs(figura_obtener_x_max(figura) - figura_obtener_x_min(figura));
}

double figura_obtener_alto(figura_t* figura) {
	return fabs(figura_obtener_y_max(figura) - figura_obtener_y_min(figura));
}

bool figura_es_inf(figura_t* figura) {
	return figura->inf;
}

//MOVIMIENTO Y DISTANCIA

void figura_trasladar(figura_t* figura, float dx, float dy) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_trasladar(figura->polis[i], dx, dy);
	}
}

void figura_rotar(figura_t* figura, double rad) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_rotar(figura->polis[i], rad);
	}
}

void figura_escalar(figura_t* figura, double escala) {
	for (size_t i = 0; i < figura->cant; i++) {
		polilinea_escalar(figura->polis[i], escala);
	}
}

double figura_distancia_a_punto(figura_t* figura, double px, double py) {
	double distancia = distancia_punto_a_polilinea(figura->polis[0], px, py);
	for (size_t i = 1; i < figura->cant; i++) {
		double aux = distancia_punto_a_polilinea(figura->polis[i], px, py);
		if (aux < distancia)
			distancia = aux;
	}
	return distancia;
}

//MEMORIA

figura_t* figura_clonar(figura_t* figura) {
	figura_t* figura_clon = figura_crear(figura->inf, figura->tipo, figura->nombre);
	if (figura_clon == NULL) return NULL;
	for (size_t i = 0; i < figura->cant; i++) {
		if (!figura_agregar_poli(figura_clon, figura->polis[i])) {
			figura_destruir(figura_clon);
			return NULL;
		}
	}
	return figura_clon;
}

//DIBUJADO

bool figura_dibujar(figura_t* figura, double dx, double dy, double ang, double centro, double escala, double ventana_alto, SDL_Renderer* renderer) {
	figura_t* fig = figura_clonar(figura);
	if (fig == NULL) return false;
	figura_rotar(fig, ang);
	figura_trasladar(fig, -centro, 0);
	figura_escalar(fig, escala);
	figura_trasladar(fig, centro + dx, dy);
	for (size_t i = 0; i < fig->cant; i++) {
		polilinea_dibujar(fig->polis[i], ventana_alto, renderer);
	}
	figura_destruir(fig);
	return true;
}
