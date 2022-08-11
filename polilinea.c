#include <stdlib.h>
#include <math.h>
#include "color.h"
#include "polilinea.h"
#include "config.h"

struct polilinea{
  color_t color;
  size_t n;             //Cantidad de puntos
  float (*puntos)[2];   //Array de puntos (vectores)
};

//CREACIÓN Y DESTRUCCIÓN

polilinea_t *polilinea_crear_vacia(size_t n) {
  polilinea_t *poli=malloc(sizeof(polilinea_t));
  if(poli==NULL)    //Asigna espacio para la estructura en el heap y verifica
    return NULL;
  poli->n=n;        //Inicializa la cantidad de puntos y le asigna espacio a la polilinea en el heap
  poli->puntos=malloc(n*sizeof(float[2]));
  poli->color=color_crear(0,0,0);
  if(poli->puntos==NULL) {
    free(poli);
    return NULL;
  }
  return poli;
}

polilinea_t *polilinea_crear(const float puntos[][2], size_t n, color_t color) {
  polilinea_t *poli=polilinea_crear_vacia(n);
  if(poli==NULL)                 //Crea una polilinea vacía y verifica su creación
    return NULL;
  for(size_t i=0; i<n; i++) {
      polilinea_setear_punto(poli, i, puntos[i][0], puntos[i][1]);
  }
  poli->color=color;
  return poli;
}

void polilinea_destruir(polilinea_t *polilinea) {
  free(polilinea->puntos); //Libera primero el arreglo de puntos, luego toda la estructura
  free(polilinea);
}

//DE USO PROPIO

static double producto_interno(const double vector1[], const double vector2[], size_t n) {
    double p_interno = 0;
    for (size_t i = 0; i < n; i++) {
        p_interno += vector1[i] * vector2[i];
    };
    return p_interno;
}

static double norma(const double vector[], size_t n) {
    return sqrt(producto_interno(vector, vector, n));
}

static double distancia_punto_a_segmento(const float a[2], const float b[2], float px, float py) {
    double seg_AP[] = { px - a[0], py - a[1] };
    double seg_BA[] = { b[0] - a[0], b[1] - a[1] }; //declara y define los segmentos y calcula alpha
    double seg_BP[] = { px - b[0], py - b[1] };
    double alpha = producto_interno(seg_AP, seg_BA, 2) / producto_interno(seg_BA, seg_BA, 2);
    if (alpha <= 0)
        return norma(seg_AP, 2);
    if (alpha >= 1)
        return norma(seg_BP, 2); //dependiendo de alpha, hace la norma con el punto más cercano, segun las ecuaciones de la consigna
    double punto_cercano[2];
    punto_cercano[0] = a[0] + alpha * seg_BA[0];  //aquí primero calcula el punto cercano, el segmento con P y luego la norma
    punto_cercano[1] = a[1] + alpha * seg_BA[1];
    double seg_P_puntocercano[2] = { px - punto_cercano[0], py - punto_cercano[1] };
    return norma(seg_P_puntocercano, 2);
}

//LECTURA

polilinea_t* leer_polilinea(FILE* f) {
	uint16_t encabezado = 0;
	size_t encabezado_size = fread(&encabezado, sizeof(uint16_t), 1, f);
	if (encabezado_size < 1) return NULL;

	uint16_t color_enc = encabezado >> 13;
	color_t color = color_crear(color_enc & ROJO, color_enc & VERDE, color_enc & AZUL);

	uint16_t cant_puntos = encabezado & CANT_PUNTOS;
	polilinea_t* poli = polilinea_crear_vacia(cant_puntos);
	polilinea_setear_color(poli, color);
	for (size_t i = 0; i < cant_puntos; i++) {
		float x, y;
		if (fread(&x, sizeof(float), 1, f) != 1) {
			polilinea_destruir(poli);
			return NULL;
		}
		if (fread(&y, sizeof(float), 1, f) != 1) {
			polilinea_destruir(poli);
			return NULL;
		}
		polilinea_setear_punto(poli, i, x, y);
	}
	return poli;
}

//GETTERS

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea) {
  return polilinea->n;
}

bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y) {
  if(pos>=polilinea->n || pos<0) //Comprueba que la posición sea valida
    return false;
  *x=polilinea->puntos[pos][0];  //Asigna los valores del punto en donde apuntan los punteros dados
  *y=polilinea->puntos[pos][1];
  return true;
}

color_t polilinea_obtener_color(const polilinea_t *polilinea) {
  return polilinea->color;
}

double polilinea_obtener_x_max(const polilinea_t* polilinea) {
    double max = polilinea->puntos[0][0];
    for (size_t i = 1; i < polilinea->n; i++) {
        if (polilinea->puntos[i][0] > max)
           max = polilinea->puntos[i][0];
    }
    return max;
}

double polilinea_obtener_y_max(const polilinea_t* polilinea) {
    double max = polilinea->puntos[0][1];
    for (size_t i = 1; i < polilinea->n; i++) {
        if (polilinea->puntos[i][1] > max)
            max = polilinea->puntos[i][1];
    }
    return max;
}

double polilinea_obtener_x_min(const polilinea_t* polilinea) {
    double min = polilinea->puntos[0][0];
    for (size_t i = 1; i < polilinea->n; i++) {
        if (polilinea->puntos[i][0] < min)
            min = polilinea->puntos[i][0];
    }
    return min;
}


double polilinea_obtener_y_min(const polilinea_t* polilinea) {
    double min = polilinea->puntos[0][1];
    for (size_t i = 1; i < polilinea->n; i++) {
        if (polilinea->puntos[i][1] < min)
            min = polilinea->puntos[i][1];
    }
    return min;
}

//SETTERS

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y){
  if(pos>=polilinea->n || pos<0)  //Comprueba que la posición sea valida
    return false;
  polilinea->puntos[pos][0]=x; //Asigna los valores
  polilinea->puntos[pos][1]=y;
  return true;
}

void polilinea_setear_color(polilinea_t *polilinea, color_t color) {
  polilinea->color=color;
}

//MOVIMIENTO Y DISTANCIAS

void polilinea_trasladar(polilinea_t *polilinea, float dx, float dy) {
  for(size_t i=0; i<polilinea->n; i++) {
    polilinea->puntos[i][0] += dx;  //aumenta un dx y dy los valores de cada punto
    polilinea->puntos[i][1] += dy;
  };
}

void polilinea_rotar(polilinea_t *polilinea, double rad) {
  double x_rotado;  //declara variables para asignarle los valores rotados, luego se le asignan esos valores a la polilinea
  double y_rotado;
  double c=cos(rad);
  double s=sin(rad);
  for(size_t i=0; i<polilinea->n; i++) {
    x_rotado = polilinea->puntos[i][0]*c-polilinea->puntos[i][1]*s;
    y_rotado = polilinea->puntos[i][0]*s+polilinea->puntos[i][1]*c;
    polilinea->puntos[i][0] = x_rotado;
    polilinea->puntos[i][1] = y_rotado;
  };
}

void polilinea_escalar(polilinea_t* polilinea, double escala) {
    for (size_t i = 0; i < polilinea->n; i++) {
        polilinea->puntos[i][0] *= escala;
        polilinea->puntos[i][1] *= escala;
    }
}

double distancia_punto_a_polilinea(const polilinea_t *polilinea, float px, float py) {
  double distancia_a_polilinea = distancia_punto_a_segmento(polilinea->puntos[0],polilinea->puntos[1], px, py);
  double nueva_distancia;
  for(size_t i=1; i+1<polilinea->n; i++) {
    nueva_distancia = distancia_punto_a_segmento(polilinea->puntos[i], polilinea->puntos[i+1], px, py);
    if(nueva_distancia<distancia_a_polilinea)
      distancia_a_polilinea = nueva_distancia;
  };
  return distancia_a_polilinea;
}

//DIBUJO

void polilinea_dibujar(polilinea_t* poli, double ventana_alto, SDL_Renderer* renderer) {
    uint8_t r, g, b;
    color_a_rgb(poli->color, &r, &g, &b);
    SDL_SetRenderDrawColor(renderer, r, g, b, 0x00);
    float x1, y1, x2, y2;
    for (int i = 0; i < poli->n - 1; i++) {
        polilinea_obtener_punto(poli, i, &x1, &y1);
        polilinea_obtener_punto(poli, i + 1, &x2, &y2); //Dibuja la polilinea exactamente donde se encuentra
        SDL_RenderDrawLine(
            renderer,
            x1,
            (ventana_alto - y1),
            x2,
            (ventana_alto - y2)
        );
    }
}

//MEMORIA

polilinea_t *polilinea_clonar(const polilinea_t *polilinea) {
  return polilinea_crear((const float (*)[2])polilinea->puntos, polilinea->n, polilinea->color);  //Crea una polilinea vacía con la cantidad de puntos de la original
}
