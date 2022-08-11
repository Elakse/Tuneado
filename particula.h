#ifndef PARTICULA_H
#define PARTICULA_H

typedef struct particula particula_t;


particula_t* particula_crear(double posx, double posy, double vel, double ang, size_t duracion, figura_t* figura);
void particula_destruir_no_ref(particula_t* particula);
double particula_get_posx(particula_t* part);
double particula_get_posy(particula_t* part);
bool particula_actualizar(particula_t* particula, double dt);
bool particula_dibujar(particula_t* particula, double tras_x, double tras_y, double centro_escala, double escala, double ventana_alto, SDL_Renderer* renderer);

#endif
