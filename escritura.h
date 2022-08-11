#ifndef ESCRITURA_H
#define ESCRITURA_H

#include "caracteres.h"
#include <stdbool.h>
#include <SDL.h>


//Dibuja un caracter en pantalla, con su esquina inferior en <posx>, <posy>, escalada por el factor <escala> y con el color <r>,<g>,<b>
//Pre: el renderer pasado debe haber sido creado con la librer�a SDL2. Los caracteres admitidos son todas las letras may�sculas, el espacio, digitos y '^','_','<','>' para representar direcciones.
void dibujar_caracter(char letra, double posx, double posy, double escala, bool r, bool g, bool b, double ventana_alto, SDL_Renderer* renderer);

//Dibuja un texto en pantalla, con su esquina inferior en <posx>, <posy>, escalada por el factor <escala> y con el color <r>,<g>,<b>
//Pre: el renderer pasado debe haber sido creado con la librer�a SDL2. Los caracteres admitidos son todas las letras may�sculas, el espacio, digitos y '^','_','<','>' para representar direcciones.
void dibujar_texto(char* texto, double posx, double posy, double escala, bool r, bool g, bool b, double ventana_alto, SDL_Renderer* renderer);


#endif
