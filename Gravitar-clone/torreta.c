#include "torreta.h"
#include "fisica.h"
#include "config.h"
#include <stdlib.h>
#include <time.h>

struct torreta {
	double pos[2];             //pos[0] = x pos[1] = y
	double ang;
	bool disparando;           //será true si la ultima vez que la torreta intentó disparar, disparó, volverá a su estado false si no lo hizo
	figura_t* torreta_fig;     //Figura base de la torreta
	figura_t* disparando_fig;  //Figura al disparar
};



//CREACION Y DESTRUCCION

torreta_t* torreta_crear(double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando) {
	torreta_t* torreta = malloc(sizeof(torreta_t));
	if (torreta == NULL) return NULL;
	torreta->pos[0] = posx;
	torreta->pos[1] = posy;
	torreta->ang = ang;
	torreta->torreta_fig = fig_base;
	torreta->disparando_fig = fig_disparando;
	torreta->disparando = false;
	return torreta;
}
void torreta_destruir(torreta_t* torreta, figura_t** fig_base, figura_t** fig_disparando) {
	if (fig_base != NULL) *fig_base = torreta->torreta_fig;
	if (fig_disparando != NULL) *fig_disparando = torreta->disparando_fig;
	free(torreta);
}

void torreta_destruir_no_ref(torreta_t* torreta) {
	torreta_destruir(torreta, NULL, NULL);
}

//GETTERS

figura_t* torreta_get_fig(torreta_t* torreta) {
	return torreta->torreta_fig;
}
double torreta_get_posx(torreta_t* torreta) {
	return torreta->pos[0];
}
double torreta_get_posy(torreta_t* torreta) {
	return torreta->pos[1];
}
double torreta_get_ang(torreta_t* torreta) {
	return torreta->ang;
}

//SETTERS

void torreta_set_pos(torreta_t* torreta, double posx, double posy) {
	torreta->pos[0] = posx;
	torreta->pos[1] = posy;
}
void torreta_set_ang(torreta_t* torreta, double ang) {
	torreta->ang = ang;
}

void torreta_randomizar_disparos(void) {
	srand(time(NULL)); //randomiza la seed
}

//ACCIONES Y DISTANCIAS

escombro_t** torreta_explota(torreta_t* torreta) {

}

bala_t* torreta_dispara(torreta_t* torreta, double ang, double rango, size_t chances, double vel, size_t duracion_disparo, figura_t* bala_fig) {
	int factor;
	while ((factor = -100 + rand() % 201) == 0);     
	double ang_final = ang + rango / factor;          //Al ang dado le suma el rango didivido por un factor aleatorio
	double torreta_alto = figura_obtener_alto(torreta->torreta_fig);
	if (rand() % 1000 < chances) {    
		bala_t* bala = bala_crear(torreta->pos[0] + com_x(torreta_alto, PI/2 + torreta->ang),
								  torreta->pos[1] + com_y(torreta_alto, PI/2 + torreta->ang), vel, ang_final, duracion_disparo, false, bala_fig);
		torreta->disparando = true;   //Crea una bala si se dan las chances en la punta de la torreta
		return bala;
	}
	else
		torreta->disparando = false;
	return NULL;

}

double torreta_distancia_a_punto(torreta_t* torreta, double px, double py) {
	figura_t* figura = figura_clonar(torreta->torreta_fig);
	if (figura == NULL) return -1;
	figura_rotar(figura, torreta->ang);                             //Copia la figura, la mueve y rota a la posicion y chequea distancias
	figura_trasladar(figura, torreta->pos[0], torreta->pos[1]);
	double distancia = figura_distancia_a_punto(figura, px, py);
	figura_destruir(figura);
	return distancia;
}

//DIBUJO

bool torreta_dibujar(torreta_t* torreta, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	figura_t* fig_a_dibujar;
	if (torreta->disparando)
		fig_a_dibujar = torreta->disparando_fig;             //decide como dibujar segun si la torreta dispara o no
	else
		fig_a_dibujar = torreta->torreta_fig;
	if (!figura_dibujar(fig_a_dibujar, torreta->pos[0] * escala + tras_x, torreta->pos[1] * escala + tras_y, torreta->ang, centro_escala, escala, ventana_alto, renderer))
		return false;
	return true;
}