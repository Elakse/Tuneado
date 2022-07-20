#include "base.h"

struct base {
	double posx;
	double posy;
	figura_t* figura;
};

base_t* base_crear(double posx, double posy, figura_t* figura) {
	base_t* base = malloc(sizeof(base_t));
	if (base == NULL) return NULL;
	base->posx = posx;
	base->posy = posy;
	base->figura = figura;
	return base;
}

void base_destruir(base_t *base) {
	free(base);
}

double base_get_posx(base_t *base) {
	return base->posx;
}

double base_get_posy(base_t *base) {
	return base->posy;
}

void base_set_posx(base_t* base, double posx) {
	base->posx = posx;
}

void base_set_posy(base_t* base, double posy) {
	base->posy = posy;
}

bool base_set_figura(base_t* base, figura_t *figura) {
	if (figura == NULL) return false;
	base->figura = figura;
	return true;
}

void base_dibujar(base_t* base, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(base->figura, base->posx * escala + tras_x, base->posy * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}