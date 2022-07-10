#ifndef CAKE_H
#define CAKE_H

#include "figuras.h"
#include "polilinea.h"
#include <SDL.h>

void cake_dibujar(double posx, double posy, double ang, double centro, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif CAKE_H