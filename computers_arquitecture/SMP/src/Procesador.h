#pragma once

#include <queue>
#include "constantes.h"

using namespace std ;

typedef queue<LINEATRAZA> miCola;

class Procesador
{
public:
	Procesador(CString ficheroTraza);
	LINEATRAZA getLinea();
private:
	miCola lineas;
};
