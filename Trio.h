#ifndef TRIO_H
#define TRIO_H
#include "listaD.h"

using namespace std;

struct trio{
	string tipo;
	int porcentaje;
	listaD<listaD<int> > puntos;
};
#endif
