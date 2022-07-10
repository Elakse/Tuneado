#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <stdbool.h>

#define MASK_BIT 0x80

typedef uint8_t color_t;

//Crea un color_t según las comonentes dadas.
color_t color_crear(bool r, bool g, bool b);

//Obtiene el valor de las componentes RGB de un color_t
void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b);

#endif
