#include "color.h"

color_t color_crear(bool r, bool g, bool b) {
  color_t c=0;
  if(r)
    c |= MASK_BIT;
  if(g)
    c |= (MASK_BIT >> 1); //Declara un color_t y asigna valores a los bits tal que c quede de la forma RGB0000
  if(b)
    c |= (MASK_BIT >> 2);
  return c;
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b) {
  if((*r = c & MASK_BIT))
    *r=255;
  if((*g = c & (MASK_BIT >> 1)))  //Verifica las componentes RGB y devuelve 255 o 0
    *g=255;
  if((*b = c & (MASK_BIT >> 2)))
    *b=255;
}
