#include "nivel.h"
#include "lista.h"
#include "torreta.h"
#include "combustible.h"
#include "config.h"
#include "fisica.h"
#include "bala.h"
#include "reactor.h"
#include <stdbool.h>
#include "planeta.h"
#include "estadio.h"
#include "particula.h"

struct nivel {
    lista_t* torretas;
    lista_t* combustibles;
    lista_t* balas;
    lista_t* planetas;
    lista_t* reactores;
    lista_t* particulas;
    base_t* base;
    estrella_t* estrella;
    figura_t* figura;
    estadio_t estadio;
    bool es_asteroide;      //Si se puede o no volar alrededor
    size_t duracion_balas;
    size_t puntaje;         //Puntaje que se obtiene al vencer el nivel
};


//CREACION Y DESTRUCCION

nivel_t* nivel_crear(figura_t *figura, estadio_t estadio, size_t duracion_de_balas, size_t puntaje) {
    nivel_t* nivel = malloc(sizeof(nivel_t));
    if (nivel == NULL) return NULL;
    nivel->torretas = lista_crear();
    if (nivel->torretas == NULL) return NULL;
    nivel->combustibles = lista_crear();
    if (nivel->combustibles == NULL) return NULL;
    nivel->balas = lista_crear();
    if (nivel->balas == NULL) return NULL;
    nivel->planetas = lista_crear();
    if (nivel->planetas == NULL) return NULL;
    nivel->reactores = lista_crear();
    if (nivel->reactores == NULL) return NULL;
    nivel->particulas = lista_crear();
    if (nivel->particulas == NULL) return NULL;
    nivel->figura = figura;
    nivel->duracion_balas = duracion_de_balas;
    nivel->puntaje = puntaje;
    nivel->es_asteroide = 0;
    nivel->estadio = estadio;
    nivel->base = NULL;
    nivel->estrella = NULL;
	return nivel;
}


void nivel_destruir(nivel_t* nivel, figura_t** figura) {
    if (figura != NULL) *figura = nivel->figura;  //devuelve un puntero a la figura
    lista_destruir(nivel->torretas, (void(*)(void*))torreta_destruir_no_ref);
    lista_destruir(nivel->combustibles, (void(*)(void*))combustible_destruir_no_ref); //Destruye todas las listas y por ultimo el nive
    lista_destruir(nivel->balas, (void(*)(void*))bala_destruir_no_ref);
    lista_destruir(nivel->planetas, (void(*)(void*))planeta_destruir_no_ref);
    lista_destruir(nivel->reactores, (void(*)(void*))reactor_destruir_no_ref);
    base_destruir(nivel->base);
    estrella_destruir(nivel->estrella);
    free(nivel);
}

void nivel_planeta_destruir(nivel_t* nivel, estadio_t estadio) {
    lista_iter_t* iter_p = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter_p)) {
        planeta_t* planeta = lista_iter_ver_actual(iter_p);
        if (planeta_get_estadio(planeta) == estadio) {
            planeta_destruir_no_ref(lista_iter_borrar(iter_p));  //Busca en la lista hasta dar con un estadio coincidente, elimina ese planeta  y termina
            break;
        }
        lista_iter_avanzar(iter_p);
    }
    lista_iter_destruir(iter_p);
}

//DE USO PROPI

planeta_t* nivel_planeta_por_estadio(nivel_t *nivel_inicio, nivel_t* nivel) {
    lista_iter_t* iter_p = lista_iter_crear(nivel_inicio->planetas);
    planeta_t* planeta;
    while (!lista_iter_al_final(iter_p)) {
        planeta = lista_iter_ver_actual(iter_p);
        if (planeta_get_estadio(planeta) == nivel_get_estadio(nivel)) {
            lista_iter_destruir(iter_p);
            return planeta;
        }
        lista_iter_avanzar(iter_p);
    }
    lista_iter_destruir(iter_p);
    return NULL;
}

//SETTERS

void nivel_set_asteroide(nivel_t* nivel, bool es_asteroide) {
    nivel->es_asteroide = es_asteroide;
}

bool nivel_agregar_estrella(nivel_t* nivel, double posx, double posy, figura_t* figura) {
    estrella_t* estrella = estrella_crear(posx, posy, figura);
    if (estrella == NULL) return NULL;
    nivel->estrella = estrella;
    return true;
}

bool nivel_agregar_base(nivel_t* nivel, double posx, double posy, figura_t* figura) {
    estrella_t* base = base_crear(posx, posy, figura);
    if (base == NULL) return NULL;
    nivel->base = base;
    return true;
}

bool nivel_agregar_torreta(nivel_t *nivel, double posx, double posy, double ang, figura_t * fig_base, figura_t* fig_disparando) {
    torreta_t* t = torreta_crear(posx, posy, ang, fig_base, fig_disparando);
    if (t == NULL) return false;
    return lista_insertar_ultimo(nivel->torretas, t);
}

bool nivel_agregar_combustible(nivel_t *nivel, double posx, double posy, double ang, size_t cantidad, figura_t * figura) {
    combustible_t* c = combustible_crear(posx, posy, ang, cantidad, figura);
    if (c == NULL) return false;
    return lista_insertar_ultimo(nivel->combustibles, c);
}

bool nivel_agregar_bala(nivel_t* nivel, double posx, double posy, double vel, double ang, bool jugador, figura_t* fig_bala) {
    bala_t* b = bala_crear(posx, posy, vel, ang, nivel->duracion_balas, jugador, fig_bala);
    if (b == NULL) return false;
    return lista_insertar_ultimo(nivel->balas, b);
}

bool nivel_agregar_planeta(nivel_t* nivel, double posx, double posy, double posx_tp, double posy_tp, size_t puntaje, estadio_t estad, figura_t* fig_planeta) {
    planeta_t* p = planeta_crear(posx, posy, posx_tp, posy_tp, puntaje, estad, fig_planeta);
    if (p == NULL) return false;
    return lista_insertar_ultimo(nivel->planetas, p);
}

bool nivel_agregar_reactor(nivel_t* nivel, double posx, double posy, double ang, size_t tiempo, figura_t* fig_react) {
    reactor_t* r = reactor_crear(posx, posy, ang, tiempo, fig_react);
    if (r == NULL) return false;
    return lista_insertar_ultimo(nivel->reactores, r);
}

bool nivel_agregar_particula(nivel_t* nivel, double posx, double posy, double vel, double ang, size_t contador, figura_t* fig_parti) {
    particula_t* pa = particula_crear(posx, posy, vel, ang, contador, fig_parti);
    if (pa == NULL) return false;
    return lista_insertar_ultimo(nivel->particulas, pa);
}

void nivel_randomizar_disparos(void) {
    torreta_randomizar_disparos();
}

void nivel_explosion_particulas(nivel_t* nivel, double posx, double posy, figura_t* fig) {
    for (size_t i = 0; i <= 360; i += 30) {
        nivel_agregar_particula(nivel, posx, posy, rand() % 25 + 5, i, DURACION_PART, fig);
    }
}

//GETTERS

base_t* nivel_get_base(nivel_t* nivel) {
    return nivel->base;
}

estrella_t* nivel_get_estrella(nivel_t *nivel) {
    return nivel->estrella;
}

estadio_t nivel_get_estadio(nivel_t* nivel) {
    return nivel->estadio;
}

bool nivel_tiene_estrella(nivel_t* nivel) {
    if (nivel->estrella == NULL) return false;
    else return true;
}

bool nivel_es_asteroide(nivel_t* nivel) {
    return nivel->es_asteroide;
}

bool nivel_es_inf(nivel_t* nivel) {
    if (nivel->figura == NULL) return false;
    return figura_es_inf(nivel->figura);
}

double nivel_get_ancho(nivel_t* nivel) {
    if (nivel->figura == NULL) return -1;
    return figura_obtener_ancho(nivel->figura);
}

double nivel_get_alto(nivel_t* nivel) {
    if (nivel->figura == NULL) return -1;
    return figura_obtener_alto(nivel->figura);
}

void nivel_get_max_min(nivel_t* nivel, double* x_max, double* y_max, double* x_min, double* y_min) {
    if (nivel->figura != NULL) {
        if (x_max != NULL) *x_max = figura_obtener_x_max(nivel->figura);
        if (y_max != NULL) *y_max = figura_obtener_y_max(nivel->figura);
        if (x_min != NULL) *x_min = figura_obtener_x_min(nivel->figura);
        if (y_min != NULL) *y_min = figura_obtener_y_min(nivel->figura);
    }

}

bool nivel_tiene_torretas(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->torretas);
}

bool nivel_tiene_planetas(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->planetas);
}

bool nivel_tiene_reactores(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->reactores);
}

bool nivel_tiene_combustibles(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->combustibles);
}

bool nivel_tiene_balas(nivel_t* nivel) {
    return !lista_esta_vacia(nivel->balas);
}

figura_t* nivel_get_figura(nivel_t* nivel) {
    return nivel->figura;
}

bool nivel_vencido(nivel_t* nivel, nave_t* nave) {
    if (!nivel_tiene_torretas(nivel) && !nivel_tiene_reactores(nivel)) {
        if (nave != NULL) nave_sumar_puntos(nave, nivel->puntaje);  //Comprueba listas vacias y suma los puntos
        return true;
    }
    return false;
}

size_t nivel_get_conteo_reactor(nivel_t* nivel) {
    lista_iter_t* iter = lista_iter_crear(nivel->reactores);
    reactor_t* r = lista_iter_ver_actual(iter);
    size_t contador = reactor_get_contador(r);  //Toma el contador del primer reactor
    lista_iter_avanzar(iter);
    while (!lista_iter_al_final(iter)) {
        r = lista_iter_ver_actual(iter);
        size_t aux = reactor_get_contador(r);  //Lo compara con el resto iendo cual es el menor
        if (aux < contador) {
            contador = aux;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return contador;
}

//INTERACCIONES Y ACTUALIZACIONES

bool nivel_estrella_atrae_nave(nivel_t* nivel, nave_t* nave) {
    double est_x = estrella_get_posx(nivel->estrella);
    double est_y = estrella_get_posy(nivel->estrella);
    double nav_x = nave_get_posx(nave);
    double nav_y = nave_get_posy(nave);
    nave_setear_ang_g(nave, computar_angulo(nav_x, nav_y, est_x, est_y));
    if (computar_distancia(nav_x, nav_y, est_x, est_y) < DISTANCIA_ESTRELLA) return true;
    return false;
}

void nivel_nave_salir_planeta(nave_t* nave, nivel_t* nivel, nivel_t* nivel_entrada) {
    double planeta_x = planeta_get_posx(nivel_planeta_por_estadio(nivel_entrada, nivel));
    double planeta_y = planeta_get_posy(nivel_planeta_por_estadio(nivel_entrada, nivel));
    double base_x = base_get_posx(nivel_get_base(nivel_entrada));
    double base_y = base_get_posy(nivel_get_base(nivel_entrada));
    double angulo = computar_angulo(planeta_x, planeta_y, base_x, base_y);
    planeta_t* planeta = nivel_planeta_por_estadio(nivel_entrada, nivel);
    double ancho_fig = figura_obtener_ancho(planeta_get_fig(planeta));

    nave_setear_pos(nave, planeta_x + com_x(ancho_fig, angulo), planeta_y + com_y(ancho_fig, angulo));
    nave_setear_ang_nave(nave, angulo);
    nave_setear_vel(nave, com_x(20, angulo), com_y(20, angulo));
    nave_setear_estadio(nave, nivel_get_estadio(nivel_entrada));
}

bool nivel_nave_accede_planetas(nivel_t* nivel, nave_t* nave) {
    lista_iter_t* iter = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter)) {
        planeta_t* p = lista_iter_ver_actual(iter);
        if (planeta_distancia_a_punto(p, nave_get_posx(nave), nave_get_posy(nave)) < DISTANCIA_COLISION) {
            nave_setear_estadio(nave, planeta_get_estadio(p));
            nave_setear_pos(nave, planeta_get_posx_tp(p), planeta_get_posy_tp(p));   //Chequea colision y cambia los parametros de la nave en caso de que si
            lista_iter_destruir(iter);
            return true;
            break;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

bool nivel_nave_dispara(nivel_t* nivel, nave_t* nave, double vel, figura_t* fig_bala) {
    bala_t* b = nave_dispara(nave, vel, nivel->duracion_balas, fig_bala);
    if (b == NULL) return false;
    return lista_insertar_ultimo(nivel->balas, b);
}

bool nivel_nave_disparada(nivel_t* nivel, nave_t* nave) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        if (!bala_es_de_jugador(b) && nave_distancia_a_punto(nave, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
            bala_destruir_no_ref(lista_iter_borrar(iter));       //Chequea colision, elimina la bala y la borra de la lista en caso positivo
            lista_iter_destruir(iter);
            return true;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return false;
}

size_t nivel_nave_recoge_combustible(nivel_t* nivel, nave_t* nave) {
    size_t recogidos = 0; //contador
    lista_iter_t* iter = lista_iter_crear(nivel->combustibles);
    while (!lista_iter_al_final(iter)) {
        combustible_t* c = lista_iter_ver_actual(iter);
        if (nave_distancia_a_punto(nave, combustible_get_posx(c), combustible_get_posy(c)) < DISTANCIA_RECOLECCION) {
            combustible_destruir_no_ref(lista_iter_borrar(iter));  //Chequea cercan�a de la nave, destruye el combustible en caso positivo y aumenta el contador
            recogidos++;
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return recogidos;
}

bool nivel_torretas_disparan_a_nave(nivel_t* nivel, nave_t* nave, double abanico, size_t chances, double rango, double vel, figura_t* fig_bala) {
    lista_iter_t* iter = lista_iter_crear(nivel->torretas);
    double x_nav = nave_get_posx(nave);
    double y_nav = nave_get_posy(nave);
    while (!lista_iter_al_final(iter)) {
        torreta_t* t = lista_iter_ver_actual(iter);
        double ang = computar_angulo(torreta_get_posx(t), torreta_get_posy(t), x_nav, y_nav); //Computa el angulo de la torreta a la nave
        bala_t* bala = NULL;
        if(torreta_distancia_a_punto(t, x_nav, y_nav) < rango)  //chequea que este dentro del rango y dispara
            bala = torreta_dispara(t, ang, abanico, chances, vel, nivel->duracion_balas, fig_bala);
        if (bala != NULL)
            if (!lista_insertar_ultimo(nivel->balas, bala)) {
                lista_iter_destruir(iter);   //si el disparo es exitoso a�ade la bala al nivel
                return false;
            }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return true;
}

size_t nivel_torretas_disparadas(nivel_t* nivel, figura_t* fig_destruccion) {
    size_t disparadas = 0; //contador
    lista_iter_t* iter_t = lista_iter_crear(nivel->torretas);
    while (!lista_iter_al_final(iter_t)) { //iteracion de torretas
        bool torreta_destruida = false;  //indicador para que el iterador sepa si avanzar o no (depende se se borr� una torreta de la lista)
        torreta_t* t = lista_iter_ver_actual(iter_t);
        lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
        while (!lista_iter_al_final(iter_b)) {  //iteracion de balas
            bala_t* b = lista_iter_ver_actual(iter_b);
            if (bala_es_de_jugador(b) && torreta_distancia_a_punto(t, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
                torreta_destruida = true;
                //nivel_explosion_particulas(nivel, torreta_get_posx(t), torreta_get_posy(t), fig_destruccion);

                //figura_t* chispa_f = figura_clonar(fig_destruccion);
                //polilinea_t** chispa_p =  figura_obtener_polis(chispa_f);
                //color_t amarillo = color_crear(1, 1, 0); 
                //polilinea_setear_color(chispa_p[0], amarillo);
                nivel_explosion_particulas(nivel, bala_get_posx(b), bala_get_posy(b), fig_destruccion);

                torreta_destruir_no_ref(lista_iter_borrar(iter_t));  //Chequea para cada torreta la colision con cada bala
                bala_destruir_no_ref(lista_iter_borrar(iter_b));
                disparadas++; //contador
                break;
            }
            lista_iter_avanzar(iter_b);
        }
        lista_iter_destruir(iter_b);
        if (!torreta_destruida) lista_iter_avanzar(iter_t);
    }
    lista_iter_destruir(iter_t);
    return disparadas;
}

void nivel_balas_actualizar(nivel_t* nivel, double dt) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        if (!bala_actualizar(b, dt)) {   //mueve todas las balas y las elimina si estas murieron
            bala_destruir_no_ref(lista_iter_borrar(iter));
            continue;
        }
        if (nivel->figura != NULL && figura_distancia_a_punto(nivel->figura, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
            bala_destruir_no_ref(lista_iter_borrar(iter));  //si el nivel tiene layout, elimina aquellas balasque chocaron
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void nivel_balas_trasladar(nivel_t* nivel, double dx, double dy) {
    lista_iter_t* iter = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter)) {
        bala_t* b = lista_iter_ver_actual(iter);
        bala_set_pos(b, bala_get_posx(b) + dx, bala_get_posy(b) + dy);  //cambia la posicion de cada bala
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void nivel_balas_vaciar(nivel_t* nivel) {
    lista_destruir(nivel->balas, (void(*)(void*))bala_destruir_no_ref);  //Elmina la lista y vuelve a crearla
    nivel->balas = lista_crear();
}

void nivel_particulas_actualizar(nivel_t* nivel, double dt) {
    lista_iter_t* iter = lista_iter_crear(nivel->particulas);
    while (!lista_iter_al_final(iter)) {
        particula_t* pa = lista_iter_ver_actual(iter);
        if (!particula_actualizar(pa, dt)) {   //mueve todas las balas y las elimina si estas murieron
            particula_destruir_no_ref(lista_iter_borrar(iter));
            continue;
        }
        if (nivel->figura != NULL && figura_distancia_a_punto(nivel->figura, particula_get_posx(pa), particula_get_posy(pa)) < DISTANCIA_COLISION) {
            particula_destruir_no_ref(lista_iter_borrar(iter));  //si el nivel tiene layout, elimina aquellas balasque chocaron
            continue;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

size_t nivel_reactores_actualizar(nivel_t* nivel) {
    size_t reactores_cero = 0; //contador
    lista_iter_t* iter = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter)) {
        reactor_t* r = lista_iter_ver_actual(iter);
        if (!reactor_actualizar(r)) {
            reactor_reiniciar(r);  //actualiza cada reactor y aumenta el contador si estos estan en 0
            reactores_cero++;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return reactores_cero;
}

size_t nivel_reactores_disparados(nivel_t* nivel) {
    size_t disparados = 0; //contador
    lista_iter_t* iter_r = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter_r)) { //iteracion reactores
        bool reactor_destruido = false; //indicador de avance del iteradors
        reactor_t* r = lista_iter_ver_actual(iter_r);
        lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
        while (!lista_iter_al_final(iter_b)) { //iteracin balas
            bala_t* b = lista_iter_ver_actual(iter_b);
            if (bala_es_de_jugador(b) && reactor_distancia_a_punto(r, bala_get_posx(b), bala_get_posy(b)) < DISTANCIA_COLISION) {
                reactor_destruido = true;
                reactor_destruir_no_ref(lista_iter_borrar(iter_r));       //Si hay colision y la bala es del jugador, destruye el reactor
                bala_destruir_no_ref(lista_iter_borrar(iter_b));
                disparados++;
                break;
            }
            lista_iter_avanzar(iter_b);
        }
        lista_iter_destruir(iter_b);
        if (!reactor_destruido) lista_iter_avanzar(iter_r);
    }
    lista_iter_destruir(iter_r);
    return disparados;
}

void nivel_reactores_reiniciar(nivel_t* nivel) {
    lista_iter_t* iter = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter)) {
        reactor_t* r = lista_iter_ver_actual(iter);
        reactor_reiniciar(r);
        lista_iter_avanzar(iter);
    }
}



//DIBUJO

void nivel_dibujar(nivel_t* nivel, double centro, double escala, double ventana_ancho, double ventana_alto, SDL_Renderer* renderer) {
    double traslado = -centro;
    double ancho = 0;
    if (nivel->figura != NULL) {
        ancho = figura_obtener_ancho(nivel->figura); //obtiene el ancho para la rutina de dibujo
        if (nivel_es_inf(nivel)) {
            traslado = -centro + ventana_ancho / 2; //setea un traslado difernte si el nivel es infinito
            figura_dibujar(nivel->figura, traslado, 0, 0, centro, escala, ventana_alto, renderer);
            figura_dibujar(nivel->figura, -ancho * escala + traslado, 0, 0, centro, escala, ventana_alto, renderer);   //dibuja triplicado para dar la ilusion de infinito
            figura_dibujar(nivel->figura, ancho * escala + traslado, 0, 0, centro, escala, ventana_alto, renderer);
        }
        else {
            figura_dibujar(nivel->figura, traslado, 0, 0, centro, escala, ventana_alto, renderer); //solo dibuja una vez si no es infinito
        }
    }
    //recorre todas las listas y dibuja 1x1
    lista_iter_t* iter_b = lista_iter_crear(nivel->balas);
    while (!lista_iter_al_final(iter_b)) {
        bala_dibujar(lista_iter_ver_actual(iter_b), traslado, 0, centro, escala, ventana_alto, renderer);
        lista_iter_avanzar(iter_b);
    }
    lista_iter_t* iter_t = lista_iter_crear(nivel->torretas);
    while (!lista_iter_al_final(iter_t)) {
        torreta_dibujar(lista_iter_ver_actual(iter_t), traslado, 0, centro, escala, ventana_alto, renderer);
        lista_iter_avanzar(iter_t);
    }
    lista_iter_t* iter_p = lista_iter_crear(nivel->planetas);
    while (!lista_iter_al_final(iter_p)) {
        planeta_dibujar(lista_iter_ver_actual(iter_p), traslado, 0, centro, escala, ventana_alto, renderer);
        lista_iter_avanzar(iter_p);
    }
    lista_iter_t* iter_c = lista_iter_crear(nivel->combustibles);
    while (!lista_iter_al_final(iter_c)) {
        combustible_dibujar(lista_iter_ver_actual(iter_c), traslado, 0, centro, escala, ventana_alto, renderer);
        lista_iter_avanzar(iter_c);
    }
    lista_iter_t* iter_r = lista_iter_crear(nivel->reactores);
    while (!lista_iter_al_final(iter_r)) {
        reactor_dibujar(lista_iter_ver_actual(iter_r), traslado, 0, centro, escala, ventana_alto, renderer);
        lista_iter_avanzar(iter_r);
    }
    lista_iter_t* iter_pa = lista_iter_crear(nivel->particulas);
    while (!lista_iter_al_final(iter_pa)) {
        particula_dibujar(lista_iter_ver_actual(iter_pa), traslado, 0, centro, escala, ventana_alto, renderer);
        lista_iter_avanzar(iter_pa);
    }

    if (nivel->base != NULL && nivel->estrella != NULL) {
        base_dibujar(nivel->base, traslado, 0, centro, escala, ventana_alto, renderer);
        estrella_dibujar(nivel->estrella, traslado, 0, centro, escala, ventana_alto, renderer);
    }

    lista_iter_destruir(iter_b);
    lista_iter_destruir(iter_t);
    lista_iter_destruir(iter_p);  //elimina los iteradores
    lista_iter_destruir(iter_r);
    lista_iter_destruir(iter_c);
    lista_iter_destruir(iter_pa);
}
