#include "combustible.h"

struct combustible {
	double pos[2];
	double ang;
	figura_t* fig;
};

combustible_t* combustible_crear(double posx, double posy, double ang, figura_t* figura) {
	combustible_t* combustible = malloc(sizeof(combustible_t));
	if (combustible == NULL) return NULL;
	combustible->pos[0] = posx;
	combustible->pos[1] = posy;
	combustible->ang = ang;
	combustible->fig = figura;
	return combustible;
}

void combustible_destruir(combustible_t* combustible, figura_t** figura) {
	if (figura != NULL) *figura = combustible->fig;
	free(combustible);
}

void combustible_destruir_no_ref(combustible_t* combustible) {
	combustible_destruir(combustible, NULL);
}

double combustible_get_posx(combustible_t* combustible) {
	return combustible->pos[0];
}
double combustible_get_posy(combustible_t* combustible) {
	return combustible->pos[1];
}
double combustible_get_ang(combustible_t* combustible) {
	return combustible->ang;
}

void combustible_set_pos(combustible_t* combustible, double posx, double posy) {
	combustible->pos[0] = posx;
	combustible->pos[1] = posy;
}
void combustible_set_ang(combustible_t* combustible, double ang) {
	combustible->ang = ang;
}

double combustible_distancia_a_punto(combustible_t* combustible, double px, double py) {
	figura_t* figura = figura_clonar(combustible->fig);
	if (figura == NULL) return -1;
	figura_rotar(figura, combustible->ang);
	figura_trasladar(figura, combustible->pos[0], combustible->pos[1]);
	double distancia = figura_distancia_a_punto(figura, px, py);
	figura_destruir(figura);
	return distancia;
}

bool combustible_dibujar(combustible_t* combustible, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(combustible->fig, combustible->pos[0] * escala + tras_x, combustible->pos[1] * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}