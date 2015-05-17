// -------------------------------------------------------------
//   Archivo: juego.h
//   Descripción: TAD para el tipo juego.
// -------------------------------------------------------------


#include "juego.h"


using namespace std;


void IniciarJuego(juego &game){

	int tabini[MAX_TAMANIO][MAX_TAMANIO];

	game.jugando=true;



	TEntornoCargarConfiguracion(tabini, game.tab.tamanio);
	TEntornoIniciarPantalla(tabini, game.tab.tamanio);
	IniciarTablero(game.tab,game.tab.tamanio);
	CargarConfiguracionTablero(game.tab, tabini, game.tab.tamanio);



	//Se situa en la primera casilla del tablero.
	if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
	else
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
}


bool IntroducirNumeroJuego(juego &game, int n){
				if (obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])!=0)
					{TEntornoMostrarMensaje("Debes eliminar primero ");return false;}
				if (n>game.tab.tamanio*game.tab.tamanio)
					{TEntornoMostrarMensaje("Valor no permitido");return false;}
				if (ExisteEnFila(n, game.tab.tamanio*game.tab.tamanio, game.tab.tabla, game.tab.pos.y))
					{TEntornoMostrarMensaje("Ya existe en Fila");return false;}
				if (ExisteEnColumna(n, game.tab.tamanio*game.tab.tamanio, game.tab.tabla, game.tab.pos.x))
					{TEntornoMostrarMensaje("Ya existe en Columna");return false;}
				if (ExisteEnZona(n, game.tab))
					{TEntornoMostrarMensaje("Ya existe en Zona");return false;}
				char cad1[5];
	  			if (IntroducirNumeroTablero(game.tab, n)){
					sprintf(cad1, "%d",n);
					TEntornoMostrarMensaje(cad1);
					TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO,C_VACIA);
					TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
					if(TableroLleno(game.tab, game.tab.tamanio))
						{TEntornoMostrarMensaje("Sudoku Completado! Pulse una tecla para salir");
						cin>>game.tab.pos.x;//espera a que pulse una tecla, mejorar para que pulse una tecla
						game.jugando=false;}
					else ;
					}	
				else
					TEntornoMostrarMensaje("Debes eliminar primero ");
				return true;

}

void IzquierdaJuego(juego &game){
	if(game.tab.pos.x>0){
			if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
				TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
			else
				TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
			game.tab.pos.x--;
			if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
				TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
			else
				TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
						}
}

void DerechaJuego(juego &game){
if(game.tab.pos.x<game.tab.tamanio*game.tab.tamanio-1){
	if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
		TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
	else
		TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
	game.tab.pos.x++;
	if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
	else
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));}

}


void AbajoJuego(juego &game){
	if(game.tab.pos.y<game.tab.tamanio*game.tab.tamanio-1){
		if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
			TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
		else
			TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
		game.tab.pos.y++;
		if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
			TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
		else
			TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));}
}

void ArribaJuego(juego &game){
	if(game.tab.pos.y>0){
		if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
			TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
		else
			TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
		game.tab.pos.y--;
		if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
			TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
		else
			TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
}
}

void EliminaJuego(juego &game){
	if (EliminarNumeroTablero(game.tab)==false)
		TEntornoMostrarMensaje("No lo puedes eliminar");
	else{
		TEntornoMostrarMensaje("Eliminar             ");
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
			}
}


