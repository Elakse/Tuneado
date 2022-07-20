#include "estrella.h"

struct estrella {
	double posx;
	double posy;
	figura_t* figura;
};

estrella_t* estrella_crear(double posx, double posy, figura_t* figura) {
	estrella_t* estrella = malloc(sizeof(estrella_t));
	if (estrella == NULL) return NULL;
	estrella->posx = posx;
	estrella->posy = posy;
	estrella->figura = figura;
	return estrella;
}

void estrella_destruir(estrella_t* estrella) {
	free(estrella);
}

double estrella_get_posx(estrella_t* estrella) {
	return estrella->posx;
}

double estrella_get_posy(estrella_t* estrella) {
	return estrella->posy;
}

void estrella_set_posx(estrella_t* estrella, double posx) {
	estrella->posx = posx;
}

void estrella_set_posy(estrella_t* estrella, double posy) {
	estrella->posy = posy;
}

bool estrella_set_figura(estrella_t* estrella, figura_t* figura) {
	if (figura == NULL) return false;
	estrella->figura = figura;
	return true;
}

bool estrella_dibujar(estrella_t* estrella, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(estrella->figura, estrella->posx * escala + tras_x, estrella->posy * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}