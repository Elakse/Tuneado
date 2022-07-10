#include "fisica.h"
#include <math.h>
#include <stdbool.h>

double computar_velocidad(double vi, double a, double dt) {
	return dt * a + vi;
}

double computar_posicion(double pi, double vi, double dt) {
	return dt * vi + pi;
}

double com_x(double mod, double ang) {
	return mod * cos(ang);
}

double com_y(double mod, double ang) {
	return mod * sin(ang);
}

double computar_distancia(double x1, double y1, double x2, double y2) {
	double p1x = x1;
	double p2x = x2;
	double p1y = y1;
	double p2y = y2;
	double dist;
	bool orden = true;
	if (p2x < p1x) orden = false;
	if(orden) dist = sqrt((p2x - p1x) * (p2x - p1x) + (p2y - p1y) * (p2y - p1y));
	else dist = sqrt((p1x - p2x) * (p1x - p2x) + (p1y - p2y) * (p1y - p2y));
	return dist;
}

double computar_angulo(double x1, double y1, double x2, double y2) {
	return atan2(y2 - y1, x2 - x1);
}

double com_modulo(double x, double y) {
	return sqrt(x * x + y * y);
}