#include <SDL.h>
#include "figuras.h"
#include "config.h"
#include "fisica.h"
#include "particula.h"

struct particula{
	double pos[2]; //pos[0] = x,  pos[1] = y
	double vel[2]; //vel[0] = vel en x,  vel[1] = vel en 
	figura_t* fig;
	size_t contador;
};

particula_t* particula_crear(double posx, double posy, double vel, double ang, size_t duracion, figura_t* figura) {
	particula_t* particula = malloc(sizeof(particula_t));
	if (particula == NULL) return NULL;
	particula->pos[0] = posx;
	particula->pos[1] = posy;
	particula->vel[0] = com_x(vel, ang);
	particula->vel[1] = com_y(vel, ang);
	particula->contador = duracion;
	particula->fig = figura;
}

void particula_destruir_no_ref(particula_t* particula) {
	free(particula);
}

double particula_get_posx(particula_t* part) {
	return part->pos[0];
}

double particula_get_posy(particula_t* part) {
	return part->pos[1];
}

bool particula_actualizar(particula_t* particula, double dt) {
	if (particula->contador != 0) {
		particula->vel[1] = computar_velocidad(particula->vel[1], -G, dt);
		particula->pos[0] = computar_posicion(particula->pos[0], particula->vel[0], dt);
		particula->pos[1] = computar_posicion(particula->pos[1], particula->vel[1], dt);  //actualiza la posicion de las balas segun su velocidad
		particula->contador--;
		return true;
	}
	return false;
}


bool particula_dibujar(particula_t* particula, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(particula->fig, particula->pos[0] * escala + tras_x, particula->pos[1] * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}