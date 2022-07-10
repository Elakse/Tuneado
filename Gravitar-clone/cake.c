#include "cake.h"

void cake_dibujar(double posx, double posy, double ang, double centro, double escala, double ventana_alto, SDL_Renderer* renderer) {

    // Crear figura
    figura_t* cake = figura_crear(false, SPRITE, "CAKE");

    // Crear vectores descaradamente hardcodeados
    const float poli1[9][2] = { {0, 0}, {0, 1.8}, {0.4, 1.85}, {0, 1.8}, {0.3, 1.5}, {0.6, 1.4}, {1, 1.4}, {3.1, 2.1}, {1.4, 2}, };
    const float poli2[9][2] = { {0, 0}, {0.3, -0.2}, {0.6, -0.3}, {1, -0.3}, {1, -0.3}, {3.1, 0.4}, {3.1, 0.8}, {1, 0.05}, {1, -0.3}, };
    const float poli3[5][2] = { {1, 0.6}, {3.1, 1.3}, {3.1, 1}, {1, 0.25}, {1, 0.6}, };
    const float poli4[5][2] = { {1.1, 1.2}, {1.1, 0.8}, {3.1, 1.5}, {3.1, 1.9}, {1.1, 1.2}, };
    const float poli5[7][2] = { {1, 2.2}, {1.2, 2.5}, {1, 2.7}, {1.1, 2.8}, {1.3, 2.5}, {1, 2.2}, {1, 2.2}, };
    const float poli6[16][2] = { {0.9, 2.1}, {0.9, 2.2}, {0.8, 2.3}, {0.7, 2.2}, {0.6, 2.1}, {0.5, 2}, {0.5, 1.8}, {0.6, 1.7}, {0.8, 1.6}, {1.1, 1.6}, {1.2, 1.7}, {1.3, 1.9}, {1.3, 2}, {1.2, 2.1}, {1, 2.2}, {0.9, 2.1}, };
    
    // Crear polilineas a partir de los vectores
    polilinea_t* cake1 = polilinea_crear(poli1, 9, color_crear(1, 1, 0));
    polilinea_t* cake2 = polilinea_crear(poli2, 9, color_crear(1, 1, 0));
    polilinea_t* cake3 = polilinea_crear(poli3, 5, color_crear(1, 1, 1));
    polilinea_t* cake4 = polilinea_crear(poli4, 5, color_crear(1, 1, 0));
    polilinea_t* cake5 = polilinea_crear(poli5, 7, color_crear(0, 1, 0));
    polilinea_t* cake6 = polilinea_crear(poli6, 16, color_crear(1, 0, 0));

    // Agregar polis a la figura
    figura_agregar_poli(cake, cake1);
    figura_agregar_poli(cake, cake2);
    figura_agregar_poli(cake, cake3);
    figura_agregar_poli(cake, cake4);
    figura_agregar_poli(cake, cake5);
    figura_agregar_poli(cake, cake6);

    // Dibujar cake
    figura_dibujar(cake, posx, posy, ang, centro, escala, ventana_alto, renderer);

    // Destruccion
    polilinea_destruir(cake1);
    polilinea_destruir(cake2);
    polilinea_destruir(cake3);
    polilinea_destruir(cake4);
    polilinea_destruir(cake5);
    polilinea_destruir(cake6);
    figura_destruir(cake);

}