#include <stdio.h>
#include <stdbool.h>
#include "bala.h"
#include "fisica.h"

struct bala {
	double pos[2]; //pos[0] = x,  pos[1] = y
	double vel[2]; //vel[0] = vel en x,  vel[1] = vel en y
	bool jugador;
	figura_t* fig;
	size_t contador;  
};

bala_t* bala_crear(double posx, double posy, double vel, double ang, size_t duracion, bool jugador, figura_t* figura) {
	bala_t* bala = malloc(sizeof(bala_t));
	if (bala == NULL) return NULL;
	bala->pos[0] = posx;
	bala->pos[1] = posy;                     //crea la bala e inicializa segun los parametros pasados
	bala->vel[0] = vel*cos(ang);
	bala->vel[1] = vel*sin(ang);
	bala->fig = figura;
	bala->contador = duracion;
	bala->jugador = jugador;
	return bala;
}

void bala_destruir(bala_t* bala, figura_t** figura) {
	if (figura != NULL) *figura = bala->fig;
	free(bala);
}

void bala_destruir_no_ref(bala_t* bala) {
	bala_destruir(bala, NULL);
}


double bala_get_posx(bala_t *bala) {
	return bala->pos[0];
}
double bala_get_posy(bala_t *bala) {
	return bala->pos[1];
}
double bala_get_velx(bala_t* bala) {
	return bala->vel[0];
}
double bala_get_vely(bala_t* bala) {
	return bala->vel[1];
}

bool bala_es_de_jugador(bala_t* bala) {
	return bala->jugador;
}

void bala_set_pos(bala_t* bala, double posx, double posy) {
	bala->pos[0] = posx;
	bala->pos[1] = posy;
}
void bala_set_vel(bala_t* bala, double velx, double vely) {
	bala->vel[0] = velx;
	bala->vel[1] = vely;
}

bool bala_actualizar(bala_t *bala, double dt) {
	if (bala->contador != 0) {
		bala->pos[0] = computar_posicion(bala->pos[0], bala->vel[0], dt);
		bala->pos[1] = computar_posicion(bala->pos[1], bala->vel[1], dt);  //actualiza la posicion de las balas segun su velocidad
		bala->contador--;
		return true;
	}
	return false;
}


bool bala_dibujar(bala_t* bala, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(bala->fig, bala->pos[0] * escala + tras_x, bala->pos[1] * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false; 
	return true;
}