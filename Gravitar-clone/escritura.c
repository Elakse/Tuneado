#include "escritura.h"
#include "polilinea.h"
#include <stddef.h>
#include <string.h>

struct caracter{
    char letra;
    const float (*puntos)[2];
    size_t n;
};

const struct caracter caracteres[] = {
  {'A', caracter_a, sizeof(caracter_a) / (sizeof(caracter_a[0]))},
  {'B', caracter_b, sizeof(caracter_b) / (sizeof(caracter_a[0]))},
  {'C', caracter_c, sizeof(caracter_c) / (sizeof(caracter_a[0]))},
  {'D', caracter_d, sizeof(caracter_d) / (sizeof(caracter_a[0]))},
  {'E', caracter_e, sizeof(caracter_e) / (sizeof(caracter_a[0]))},
  {'F', caracter_f, sizeof(caracter_f) / (sizeof(caracter_a[0]))},
  {'G', caracter_g, sizeof(caracter_g) / (sizeof(caracter_a[0]))},
  {'H', caracter_h, sizeof(caracter_h) / (sizeof(caracter_a[0]))},
  {'I', caracter_i, sizeof(caracter_i) / (sizeof(caracter_a[0]))},
  {'J', caracter_j, sizeof(caracter_j) / (sizeof(caracter_a[0]))},
  {'K', caracter_k, sizeof(caracter_k) / (sizeof(caracter_a[0]))},
  {'L', caracter_l, sizeof(caracter_l) / (sizeof(caracter_a[0]))},
  {'M', caracter_m, sizeof(caracter_m) / (sizeof(caracter_a[0]))},
  {'N', caracter_n, sizeof(caracter_n) / (sizeof(caracter_a[0]))},
  {'O', caracter_o, sizeof(caracter_o) / (sizeof(caracter_a[0]))},
  {'P', caracter_p, sizeof(caracter_p) / (sizeof(caracter_a[0]))},
  {'Q', caracter_q, sizeof(caracter_q) / (sizeof(caracter_a[0]))},
  {'R', caracter_r, sizeof(caracter_r) / (sizeof(caracter_a[0]))},
  {'S', caracter_s, sizeof(caracter_s) / (sizeof(caracter_a[0]))},
  {'T', caracter_t, sizeof(caracter_t) / (sizeof(caracter_a[0]))},
  {'U', caracter_u, sizeof(caracter_u) / (sizeof(caracter_a[0]))},
  {'V', caracter_v, sizeof(caracter_v) / (sizeof(caracter_a[0]))},
  {'W', caracter_w, sizeof(caracter_w) / (sizeof(caracter_a[0]))},
  {'X', caracter_x, sizeof(caracter_x) / (sizeof(caracter_a[0]))},
  {'Y', caracter_y, sizeof(caracter_y) / (sizeof(caracter_a[0]))},
  {'Z', caracter_z, sizeof(caracter_z) / (sizeof(caracter_a[0]))},

  {'1', caracter_1, sizeof(caracter_1) / (sizeof(caracter_a[0]))},
  {'2', caracter_2, sizeof(caracter_2) / (sizeof(caracter_a[0]))},
  {'3', caracter_3, sizeof(caracter_3) / (sizeof(caracter_a[0]))},
  {'4', caracter_4, sizeof(caracter_4) / (sizeof(caracter_a[0]))},
  {'5', caracter_5, sizeof(caracter_5) / (sizeof(caracter_a[0]))},
  {'6', caracter_6, sizeof(caracter_6) / (sizeof(caracter_a[0]))},
  {'7', caracter_7, sizeof(caracter_7) / (sizeof(caracter_a[0]))},
  {'8', caracter_8, sizeof(caracter_8) / (sizeof(caracter_a[0]))},
  {'9', caracter_9, sizeof(caracter_9) / (sizeof(caracter_a[0]))},
  {'0', caracter_0, sizeof(caracter_0) / (sizeof(caracter_a[0]))},

  {'^', caracter_arriba, sizeof(caracter_arriba) / (sizeof(caracter_a[0]))},
  {'_', caracter_abajo, sizeof(caracter_abajo) / (sizeof(caracter_a[0]))},
  {'<', caracter_izquierda, sizeof(caracter_izquierda) / (sizeof(caracter_a[0]))},
  {'>', caracter_derecha, sizeof(caracter_derecha) / (sizeof(caracter_a[0]))},

  {' ', caracter_espacio, sizeof(caracter_espacio) / (sizeof(caracter_a[0]))},

};

const struct caracter* letra_a_caracter(char letra) {
    size_t cant = sizeof(caracteres) / sizeof(caracteres[0]);
    for (size_t i = 0; i < cant; i++) {
        if (caracteres[i].letra == letra) {
            const struct caracter* c = &caracteres[i];
            return c;
        }
    }
    return NULL;
}


void dibujar_caracter(char letra, double posx, double posy, double escala, bool r, bool g, bool b, double ventana_alto, SDL_Renderer* renderer) {
    const struct caracter* c = letra_a_caracter(letra);
    color_t color = color_crear(r, g, b);
    polilinea_t* poli = polilinea_crear(c->puntos, c->n, color);
    polilinea_escalar(poli, escala);
    polilinea_trasladar(poli, posx, posy);
    polilinea_dibujar(poli, ventana_alto, renderer);
    polilinea_destruir(poli);
}

void dibujar_texto(char* texto, double posx, double posy, double escala, bool r, bool g, bool b, double ventana_alto, SDL_Renderer* renderer) {
    size_t largo = strlen(texto);
    for (size_t i = 0; i < largo; i++) {
        dibujar_caracter(texto[i], posx + i * CARACTER_ANCHO * escala, posy, escala, r, g, b, ventana_alto, renderer);
    }
}
