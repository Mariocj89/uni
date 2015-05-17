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
	for (int i=0;i<tamanio*tamanio;i++)
		for(int j=0;j<tamanio*tamanio;j++)
			LlenarPosible(tab.tabla[i][j],tamanio);
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
			tab.contador++;
			tab.pos.y=fila;
			tab.pos.x=i;
			EliminarPosiblesTablero(tab);}
		}		
	}
			tab.pos.y=0;
			tab.pos.x=0;
}




bool IntroducirNumeroTablero(tablero &tab, int n){

	if(obtenerValorC(tab.tabla[tab.pos.y][tab.pos.x])==0){
		ponerValorC(tab.tabla[tab.pos.y][tab.pos.x], n);
		tab.contador++;
		EliminarPosiblesTablero(tab);
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
		for(int j=z.inicio.x;j<z.final.x;j++){
			if(n==obtenerValorC(tab.tabla[i][j]))
				return true;}
	return false;
}


int ObtenerNumeroTablero(casilla tablero[MAXTAMANIO][MAXTAMANIO], posicion pos){
	return obtenerValorC(tablero[pos.y][pos.x]);

}

void EliminarPosiblesTablero(tablero &tab){
	for(int i=0;i<tab.tamanio*tab.tamanio;i++)
		{QuitarPosible(tab.tabla[tab.pos.y][i],tab.tabla[tab.pos.y][tab.pos.x].numero);
		QuitarPosible(tab.tabla[i][tab.pos.x],tab.tabla[tab.pos.y][tab.pos.x].numero);}
//el siguiente codigo recorre la zona en la que esta el cursor y elimina el numero que ocupa la posicion del cursor de los posibles de la zona.
zona z;
	z.lugar.x=tab.pos.x/tab.tamanio;
	z.lugar.y=tab.pos.y/tab.tamanio;
	z.inicio.x=z.lugar.x*tab.tamanio;
	z.inicio.y=z.lugar.y*tab.tamanio;
	z.final.x=z.inicio.x+tab.tamanio;
	z.final.y=z.inicio.y+tab.tamanio;
	for(int i=z.inicio.y;i<z.final.y;i++)
		for(int j=z.inicio.x;j<z.final.x;j++)
			QuitarPosible(tab.tabla[i][j],tab.tabla[tab.pos.y][tab.pos.x].numero);
}

void AniadirPosiblesTablero(tablero &tab, int n){
	for(int i=0;i<tab.tamanio*tab.tamanio;i++){
		if(!ExisteEnFila(n, tab.tamanio*tab.tamanio, tab.tabla, i))
			if(!ExisteEnZona(n,tab))
				AniadirPosible(tab.tabla[i][tab.pos.x],n);
		if(!ExisteEnColumna(n, tab.tamanio*tab.tamanio, tab.tabla, i))
			if(!ExisteEnZona(n,tab))
				AniadirPosible(tab.tabla[tab.pos.y][i],n);}
//el siguiente codigo recorre la zona en la que esta el cursor y añade el numero que ocupaba la posicion del cursor a los posibles de la zona.
zona z;
	z.lugar.x=tab.pos.x/tab.tamanio;
	z.lugar.y=tab.pos.y/tab.tamanio;
	z.inicio.x=z.lugar.x*tab.tamanio;
	z.inicio.y=z.lugar.y*tab.tamanio;
	z.final.x=z.inicio.x+tab.tamanio;
	z.final.y=z.inicio.y+tab.tamanio;
	for(int x=z.inicio.y;x<z.final.y;x++)
		for(int j=z.inicio.x;j<z.final.x;j++)
			if(!ExisteEnFila(n, tab.tamanio*tab.tamanio, tab.tabla, x))
				if(!ExisteEnColumna(n, tab.tamanio*tab.tamanio, tab.tabla, x))
					if(!ExisteEnZona(n,tab))
						AniadirPosible(tab.tabla[x][j],n);
}




bool BuscarValorFila (tablero tab, int &x, int &y, int n){
	int i=0;
	bool existe=false;
	while ((i<tab.tamanio*tab.tamanio)&&(!existe)){
		if (n==obtenerValorC(tab.tabla[tab.pos.y][i]))
			{y=tab.pos.y;
			x=i;
			existe=true;}
		else
			i++;
	}
return existe;
}

bool BuscarValorColumna (tablero tab, int &x, int &y, int n){
	int i=0;
	bool existe=false;
	while ((i<tab.tamanio*tab.tamanio)&&(!existe)){
		if (n==obtenerValorC(tab.tabla[i][tab.pos.x]))
			{y=i;
			x=tab.pos.x;
			existe=true;}
		else
			i++;
	}
return existe;
}

bool BuscarValorZona (tablero tab, int &x, int &y, int n){
zona z;

	z.lugar.x=tab.pos.x/tab.tamanio;
	z.lugar.y=tab.pos.y/tab.tamanio;
	z.inicio.x=z.lugar.x*tab.tamanio;
	z.inicio.y=z.lugar.y*tab.tamanio;
	z.final.x=z.inicio.x+tab.tamanio;
	z.final.y=z.inicio.y+tab.tamanio;
	for(int i=z.inicio.y;i<z.final.y;i++)
		for(int j=z.inicio.x;j<z.final.x;j++)
			if(n==obtenerValorC(tab.tabla[i][j])){
				x=i;
				y=j;
				return true;}
return false;
}




