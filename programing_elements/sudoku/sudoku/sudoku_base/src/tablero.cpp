// -------------------------------------------------------------
//   Archivo: casilla.cpp
//   Descripción: TAD para las casillas del tablero del sudoku
// -------------------------------------------------------------

#include "tablero.h"



using namespace std;



void IniciarTablero(tablero &tab,int tamanio){
	tab.pos.x=0;
	tab.pos.y=0;
	tab.contador=0;
	for (int i=0;i<tamanio*tamanio;i++)
		for(int j=0;j<tamanio*tamanio;j++){
			tab.tabla[i][j]=CrearC();
		}

}

bool TableroLleno(tablero tab,int tamanio){

return (tab.contador==tamanio*tamanio*tamanio*tamanio);

}

void CargarConfiguracionTablero(tablero &tab, int tabini[MAXTAMANIO][MAXTAMANIO], int tamanio){
	tab.tamanio=tamanio;
	for(int fila=0;fila<tab.tamanio*tab.tamanio;fila++){
		for (int i=0;i<tab.tamanio*tab.tamanio;i++) {
			tab.tabla[fila][i].numero=tabini[fila][i];
			if(tabini[fila][i]!=0){
			ponerInicialC (tab.tabla[fila][i]);
			tab.contador++;}
		}		
	}
}




bool IntroducirNumeroTablero(tablero &tab, int n){

	if(obtenerValorC(tab.tabla[tab.pos.y][tab.pos.x])==0){
		ponerValorC(tab.tabla[tab.pos.y][tab.pos.x], n);
		tab.contador++;
		return true;}
	else
		return false;
}

bool EliminarNumeroTablero(tablero &tab){
	if (!obtenerSiInicialC (tab.tabla[tab.pos.y][tab.pos.x])){
		ponerValorC(tab.tabla[tab.pos.y][tab.pos.x], 0);
		tab.contador--;
		return true;}

	else
		return false;
}

bool ExisteEnColumna(int n, int max, casilla tablero[MAXTAMANIO][MAXTAMANIO], int columna){
int i=0;
bool existe=false;
while ((i<max)&&(!existe)){
if (n==obtenerValorC(tablero[i][columna]))
existe=true;
else
i++;
}
return existe;
}

bool ExisteEnFila(int n, int max, casilla tablero[MAXTAMANIO][MAXTAMANIO], int fila){
int i=0;
bool existe=false;
while ((i<max)&&(!existe)){
if (n==obtenerValorC(tablero[fila][i]))
existe=true;
else
i++;
}
return existe;
}


bool ExisteEnZona(int n, tablero tab){
zona z;

z.lugar.x=tab.pos.x/tab.tamanio;
z.lugar.y=tab.pos.y/tab.tamanio;
z.inicio.x=z.lugar.x*tab.tamanio;
z.inicio.y=z.lugar.y*tab.tamanio;
z.final.x=z.inicio.x+tab.tamanio;
z.final.y=z.inicio.y+tab.tamanio;
for(int i=z.inicio.y;i<z.final.y;i++)
	for(int j=z.inicio.x;j<z.final.x;j++)
		if(n==obtenerValorC(tab.tabla[i][j]))
		return true;
return false;
}


int ObtenerNumeroTablero(casilla tablero[MAXTAMANIO][MAXTAMANIO], posicion pos){
return obtenerValorC(tablero[pos.y][pos.x]);

}

