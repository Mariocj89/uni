
// -------------------------------------------------------------
//   Archivo: casilla.cpp
//   Descripción: TAD para las casillas del tablero del sudoku
// -------------------------------------------------------------

#include "casilla.h"




using namespace std;

casilla CrearC (){
casilla c;
c.color=0;
c.numero=0;
return c;
}

void ponerInicialC (casilla &casi){
casi.color=1;
}

void ponerValorC(casilla &casi, int n){
	casi.numero=n;//se entiende que el color esta inicializado en normal, por lo cual no hay que cambiarlo.

}

int obtenerValorC (casilla c){
return c.numero;
}

bool obtenerSiInicialC (casilla c){
return (c.color==1);
}
