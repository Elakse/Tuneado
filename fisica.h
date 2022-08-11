#ifndef FISICA_H
#define FISICA_H


//CINEMATICA

//Computa velocidad para un instante <dt> segun <vi> velocidad inicial y <a> aceleracion
double computar_velocidad(double vi, double a, double dt);

//Computa posicion para un instante <dt> segun <vi> velocidad inicial y <a> aceleracion
double computar_posicion(double pi, double vi, double dt);

//ALGEBRA

//Extrae la componente en x de un vector degun su modulo y angulo
double com_x(double mod, double ang);

//Extrae la componente en y de un vector degun su modulo y angulo
double com_y(double mod, double ang);

//Devuelve la distancia entre dos puntos
double computar_distancia(double x1, double y1, double x2, double y2);

//Devuelve el angulo entre dos puntos
double computar_angulo(double x1, double y1, double x2, double y2);

//Devuelve el modulo de un vector
double com_modulo(double x, double y);

#endif