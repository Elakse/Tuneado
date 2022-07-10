#include "reactor.h"

struct reactor {
	double pos[2];   // x = pos[0], y = pos[1]
	double ang;		 
	figura_t* fig;   //!= NULL
	size_t tiempo;
	size_t contador; // <= tiempo
};

reactor_t* reactor_crear(double posx, double posy, double ang, size_t tiempo, figura_t* figura) {
	reactor_t* reactor = malloc(sizeof(reactor_t));
	if (reactor == NULL) return NULL;
	reactor->pos[0] = posx;
	reactor->pos[1] = posy;
	reactor->ang = ang;
	reactor->tiempo = tiempo;
	reactor->contador = tiempo;
	reactor->fig = figura;
	return reactor;
}

void reactor_destruir(reactor_t* reactor, figura_t ** figura) {
	if (figura != NULL) *figura = reactor->fig;
	free(reactor);
}

void reactor_destruir_no_ref(reactor_t* reactor) {
	reactor_destruir(reactor, NULL);
}

double reactor_get_posx(reactor_t* reactor) {
	return reactor->pos[0];
}
double reactor_get_posy(reactor_t* reactor) {
	return reactor->pos[1];
}
double reactor_get_ang(reactor_t* reactor) {
	return reactor->ang;
}

size_t reactor_get_contador(reactor_t* reactor) {
	return reactor->contador;
}

void reactor_set_pos(reactor_t* reactor, double posx, double posy) {
	reactor->pos[0] = posx;
	reactor->pos[1] = posy;
}
void reactor_set_ang(reactor_t* reactor, double ang) {
	reactor->ang = ang;
}

bool reactor_actualizar(reactor_t* reactor) {
	if (reactor->contador != 0) {
		reactor->contador--;
		return true;
	}
	return false;
}

void reactor_reiniciar(reactor_t* reactor) {
	reactor->contador = reactor->tiempo;
}

double reactor_distancia_a_punto(reactor_t* reactor, double px, double py) {
	figura_t* figura = figura_clonar(reactor->fig);
	if (figura == NULL) return -1;
	figura_rotar(figura, reactor->ang);
	figura_trasladar(figura, reactor->pos[0], reactor->pos[1]);         //copia la figura, la traslada a su posicion y chequea distancia
	double distancia = figura_distancia_a_punto(figura, px, py);
	figura_destruir(figura);
	return distancia;
}

bool reactor_dibujar(reactor_t* reactor, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(reactor->fig, reactor->pos[0] * escala + tras_x, reactor->pos[1] * escala + tras_y, reactor->ang, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}