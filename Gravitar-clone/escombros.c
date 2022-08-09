#include <stdio.h>
#include <stdbool.h>
#include "escombros.h"
#include "fisica.h"

struct escombro {
	double pos[2]; //pos[0] = x,  pos[1] = y
	double vel[2]; //vel[0] = vel en x,  vel[1] = vel en y
	figura_t* fig;
	size_t contador;
};

escombro_t* escombro_crear(double posx, double posy, double vel, double ang, size_t duracion, figura_t* figura) {
	escombro_t* escombro = malloc(sizeof(escombro_t));
	if (escombro == NULL) return NULL;
	escombro->pos[0] = posx;
	escombro->pos[1] = posy;                     //crea la escombro e inicializa segun los parametros pasados
	escombro->vel[0] = vel * cos(ang);
	escombro->vel[1] = vel * sin(ang);
	escombro->fig = figura;
	escombro->contador = duracion;
	return escombro;
}

void escombro_destruir(escombro_t* escombro, figura_t** figura) {
	if (figura != NULL) *figura = escombro->fig;
	free(escombro);
}

void escombro_destruir_no_ref(escombro_t* escombro) {
	escombro_destruir(escombro, NULL);
}

double escombro_get_posx(escombro_t* escombro) {
	return escombro->pos[0];
}
double escombro_get_posy(escombro_t* escombro) {
	return escombro->pos[1];
}

void escombro_set_pos(escombro_t* escombro, double posx, double posy) {
	escombro->pos[0] = posx;
	escombro->pos[1] = posy;
}
void escombro_set_vel(escombro_t* escombro, double velx, double vely) {
	escombro->vel[0] = velx;
	escombro->vel[1] = vely;
}



bool escombro_actualizar(escombro_t* escombro, double dt) {
	if (escombro->contador != 0) {
		escombro->pos[0] = computar_posicion(escombro->pos[0], escombro->vel[0], dt);
		escombro->pos[1] = computar_posicion(escombro->pos[1], escombro->vel[1], dt);  //actualiza la posicion de las escombros segun su velocidad
		escombro->contador--;
		return true;
	}
	return false;
}


bool escombro_dibujar(escombro_t* escombro, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(escombro->fig, escombro->pos[0] * escala + tras_x, escombro->pos[1] * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}