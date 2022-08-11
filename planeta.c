#include "fisica.h"
#include <string.h>
#include "planeta.h"
#include "escritura.h"
#include "config.h"

struct planeta {
	double pos[2];     //Posicion del planeta
	double pos_tp[2];  //Posiciones de tp (es una posicion de referencia a la que el usuario podr� tpear los objetos si estos entran al planeta)
	estadio_t estadio; //Caracteriza al planeta y permite que interactue con las naves
	figura_t* fig;     //Figura con la que se dibujar� el planeta
	size_t puntaje;    //Puntaje a mostrar al ser dibujado
};

//CREACION Y DESTRUCCION

planeta_t* planeta_crear(double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t nivel, figura_t* planeta_fig) {
	planeta_t* planeta = malloc(sizeof(planeta_t));
	if (planeta == NULL) return NULL;
	planeta->pos[0] = posx; planeta->pos[1] = posy;
	planeta->pos_tp[0] = posx_tp; planeta->pos_tp[1] = posy_tp;
	planeta->estadio = nivel;
	planeta->fig = planeta_fig;
	planeta->puntaje = puntaje;
	return planeta;
}

void planeta_destruir(planeta_t* planeta, figura_t** figura) {
	if (figura != NULL) *figura = planeta->fig;
	free(planeta);
}

void planeta_destruir_no_ref(planeta_t* planeta) {
	planeta_destruir(planeta, NULL);
}

//DE USO PROPIO

static char* itoa_(size_t num, char* cadena) {
    if (num == 0) {
        cadena[1] = '\0';
        cadena[0] = '0';
        return cadena;
    }
    size_t a = num;
    size_t digitos_cant = 0;                  //Copiamos la misma funcion desde el main
    while (a != 0) {
        digitos_cant++;
        a /= 10;
    }
    cadena[digitos_cant--] = '\0';
    while (num != 0) {
        size_t digito = num % 10;
        num /= 10;
        cadena[digitos_cant] = 48 + digito;
        if (digitos_cant != 0) digitos_cant--;
    }
    return cadena;
}

//GETTERS

estadio_t planeta_get_estadio(planeta_t* planeta) {
	return planeta->estadio;
}

figura_t* planeta_get_fig(planeta_t* planeta) {
	return planeta->fig;
}

double planeta_get_posx(planeta_t* planeta) {
	return planeta->pos[0];
}

double planeta_get_posy(planeta_t* planeta) {
	return planeta->pos[1];
}

double planeta_get_posx_tp(planeta_t* planeta) {
	return planeta->pos_tp[0];
}

double planeta_get_posy_tp(planeta_t* planeta) {
	return planeta->pos_tp[1];
}

size_t planeta_get_puntaje(planeta_t* planeta) {
	return planeta->puntaje;
}

//DISTANCIAS

double planeta_distancia_a_punto(planeta_t* planeta, double px, double py) {
	figura_t* figura = figura_clonar(planeta->fig);
	if (figura == NULL) return -1;
	figura_trasladar(figura, planeta->pos[0], planeta->pos[1]);     //copia la figura, la traslada a su posicion y chequea distancia
	double distancia = figura_distancia_a_punto(figura, px, py);
	figura_destruir(figura);
	return distancia;
}



//DIBUJO

bool planeta_dibujar(planeta_t* planeta, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer) {
	if (!figura_dibujar(planeta->fig, planeta->pos[0] * escala + tras_x, planeta->pos[1] * escala + tras_y, 0, centro_escala, escala, ventana_alto, renderer))
		return false;                //Dibuja el planeta junto al texto con su puntaje
	char buffer[20];
	dibujar_texto(itoa_(planeta_get_puntaje(planeta), buffer), planeta->pos[0] * escala + tras_x - 60, planeta->pos[1] * escala + tras_y + 10, 1.5, 0, 1, 1, VENTANA_ALTO, renderer);
	return true;
}
