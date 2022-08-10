#ifndef NIVEL_H
#define NIVEL_H

#include <stdbool.h>
#include "nave.h"
#include "figuras.h"
#include "base.h"
#include "estrella.h"
#include "planeta.h"
#include "estadio.h"

#define DISTANCIA_COLISION 4
#define DISTANCIA_ESTRELLA 20
#define DISTANCIA_RECOLECCION 50
<<<<<<< Updated upstream
#define DURACION_ESCOMBRO 2000
=======
#define DURACION_PART 300
>>>>>>> Stashed changes

typedef struct nivel nivel_t;

//Pre a todas las funciones: la torreta pasada como par�metro debi� haber sido creada.
//El TDA nivel no devolver� referencias a las figuras de los objetos agregados al destuirlo, solo podr� devolver referencia a la figura del layout
//Todas las figuras anexadas al nivel o a los objetos agregados al nivel no deben ser destruidas para el funcionamiento de funciones de dibujado y colisiones
//Se asume a las figuras centradas en 0,0 excepto por los layouts.




//CREACION Y DESTRUCCION

//Crea un nivel con el layout de la figura dada, cierta duracion de balas para aquellas que se creen en el y un puntaje. Devuelve NULL en caso de fallo
//Pre: el puntero a figura debe apuntar a una figura creada.
nivel_t* nivel_crear(figura_t* figura, estadio_t estadio, size_t duracion_de_balas, size_t puntaje);

//Destruye el nivel y devuelve en figura un puntero a la figura anexada al nivel. Si no se desea obtener ese puntero, pues ya cuenta con una referencia a esta figura, colocar NULL.
void nivel_destruir(nivel_t* nivel, figura_t** figura);


//Destruye del nivel al primer planeta que encuentre con el estadio indicado.
void nivel_planeta_destruir(nivel_t* nivel, estadio_t estadio);



//SETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

//Setea la condicion asteroide al nivel (se puede volar alrededor)
void nivel_set_asteroide(nivel_t* nivel, bool es_asteroide);

//Las funciones de agreagdo agregan los objetos indicados con las caracteristicas pasadas como parametros

bool nivel_agregar_estrella(nivel_t* nivel, double posx, double posy, figura_t* figura);
bool nivel_agregar_base(nivel_t* nivel, double posx, double posy, figura_t* figura);
bool nivel_agregar_torreta(nivel_t* nivel, double posx, double posy, double ang, figura_t* fig_base, figura_t* fig_disparando);
bool nivel_agregar_combustible(nivel_t* nivel, double posx, double posy, double ang, size_t cantidad, figura_t* figura);
bool nivel_agregar_bala(nivel_t* nivel, double posx, double posy, double vel, double ang, bool jugador, figura_t* fig_bala);
bool nivel_agregar_planeta(nivel_t* nivel, double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t estad, figura_t* fig_planeta);
bool nivel_agregar_reactor(nivel_t* nivel, double posx, double posy, double ang, size_t tiempo, figura_t* fig_react);
bool nivel_agregar_particula(nivel_t* nivel, double posx, double posy, double vel, double ang, size_t contador, figura_t* fig_parti);
void nivel_explosion_particulas(nivel_t* nivel, double posx, double posy, figura_t* fig);


//GETTERS (Se ahorran explicaciones a lo que hacen las funciones, ya que est� explicitado en sus nombres)

base_t* nivel_get_base(nivel_t* nivel);
estrella_t* nivel_get_estrella(nivel_t* nivel);
estadio_t nivel_get_estadio(nivel_t* nivel);
bool nivel_es_asteroide(nivel_t* nivel);
bool nivel_tiene_estrella(nivel_t *nivel);
bool nivel_es_inf(nivel_t * nivel);
double nivel_get_ancho(nivel_t* nivel);
double nivel_get_alto(nivel_t* nivel);

//Devuelve los maximos y minimos respectivos en los punteros dados
void nivel_get_max_min(nivel_t* nivel, double* x_max, double* y_max, double* x_min, double* y_min);
figura_t* nivel_get_figura(nivel_t* nivel);

//Devuelve el contador del reactor m�s proximo a llegar a 0
size_t nivel_get_conteo_reactor(nivel_t* nivel);

//Devuelven si el nivel posee al menos uno de esos objetos o no

bool nivel_tiene_torretas(nivel_t* nivel);
bool nivel_tiene_planetas(nivel_t* nivel);
bool nivel_tiene_reactores(nivel_t* nivel);
bool nivel_tiene_combustibles(nivel_t* nivel);
bool nivel_tiene_balas(nivel_t* nivel);

//Devuelve true si el nivel no tiene torretas ni reactores. Suma a la nave dada el puntaje del nivel.
//Pre: la nave debi� haber sido creada.
bool nivel_vencido(nivel_t* nivel, nave_t* nave);



//ACTUALIZACIONES e INTERACCIONES

//Devuelve un puntero al planeta correspondiente al estadio asociado a un nivel
//El estadio es un enumerador que marca el nivel en el que se encuentra la nave
planeta_t *nivel_planeta_por_estadio(nivel_t* nivel_inicio, nivel_t* nivel);

//Crea una bala dentro del nivel como si hubiera sido disparada por la nave (en la direccion en la que mira y con su momento) a una velocidad <vel> y a dibujarse con la figura <fig_bala>
//Devuelve false encaso de fallo.
//Pre: la nave y la figura debieron haber sido creadas.
bool nivel_nave_dispara(nivel_t* nivel, nave_t* nave, double vel, figura_t* fig_bala);

//Devuelve true si la nave colisiona con una bala seg�n DISTANCIA_COLISION. La bala es eliminada del nivel
//Pre: la nave debi� haber sido creada.
bool nivel_nave_disparada(nivel_t* nivel, nave_t* nave);

//Randomiza los disparos efectuados por las torretas de todos los niveles para toda la ejecucion del programa.
void nivel_randomizar_disparos(void);

//Hace que todas las torretas del nivel intenten disparar a la nave con cierta posibilidad <chances>/1000, un <abanico> de disparo dado en radianes y una velocidad <vel>, siempre y cuando
//la nave est� dentro del rango. Se pide tamb�n una figura para anexar a las balas dispraradas. Devuelve NULL en caso de fallo.
//Pre: la nave y la figura debieron haber sido creadas.
bool nivel_torretas_disparan_a_nave(nivel_t* nivel, nave_t* nave, double abanico, size_t chances, double rango, double vel, figura_t* fig_bala);

//Devuelve la cantidad de torretas colisionadas por balas seg�n DISTANCIA_COLISION. Tanto la bala como la torreta que colisionan son eliminadas del nivel.
size_t nivel_torretas_disparadas(nivel_t* nivel, figura_t* fig_destruccion);

//Devuelve la cantidad de combustibles recogidos por balas seg�n DISTANCIA_RECOLECCION. El combustible es eliminado del nivel.
//Pre: la nave debi� haber sido creada.
size_t nivel_nave_recoge_combustible(nivel_t* nivel, nave_t* nave);

//Actualiza todas las balas del nivel un cierto <dt>. Moviendolas y eliminandolas si su tiempo se acaba o colisionan con el layout segun DISTANCIA_COLISION
void nivel_balas_actualizar(nivel_t* nivel, double dt);

//Traslada todas las balas un cierto dx y dy
void nivel_balas_trasladar(nivel_t* nivel, double dx, double dy);

//Elimina todas las balas del nivel
void nivel_balas_vaciar(nivel_t* nivel);

//Chequea si la nave colisiona con algunos de los planetas del nivel seg�n DISTANCIA_COLISION y setea el estadio de este planeta a la nave.
//Devuelve true si la nave colision�.
bool nivel_nave_accede_planetas(nivel_t* nivel, nave_t* nave);

//Actuaiza el contador de todos los reactores, devuelve la cantidad de reactores que est�n en 0.
size_t nivel_reactores_actualizar(nivel_t* nivel);

//Devuelve la cantidad de reactores colisionados por balas seg�n DISTANCIA_COLISION. Tanto la bala como el reactor que colisionan son eliminados del nivel.
size_t nivel_reactores_disparados(nivel_t* nivel);

//Reinicia todos los reactores a su tiempo original.
void nivel_reactores_reiniciar(nivel_t* nivel);

//Hace que la nave salga del nivel en el que se encuentra
void nivel_nave_salir_planeta(nave_t* nave, nivel_t* nivel, nivel_t *nivel_entrada);

//Hace que la nave sea atraida por la estrella del nivel, devuelve true si la distancia entre ambos es menor a DISTANCIA_ESTREALLA
//Pre: el nivel tiene que tener una estrella
bool nivel_estrella_atrae_nave(nivel_t* nivel, nave_t* nave);

//Actualiza las particulas
void nivel_particulas_actualizar(nivel_t* nivel, double dt);

//DIBUJO

//Dibuja el nivel con todos sus objetos centrados en <centro> y escalados seg�n <escala>. Ejecuta diferentes rutinas de dibujado dependiendo de si la figura pasada al nivel es infinita o no.
//Pre: el renderer pasado debe haber sido creado con la librer�a SDL2
void nivel_dibujar(nivel_t* nivel, double centro, double escala, double ventana_ancho, double ventana_alto, SDL_Renderer* renderer);



#endif
