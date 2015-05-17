// -------------------------------------------------------------
//   Archivo: juego.h
//   Descripción: TAD para el tipo juego.
// -------------------------------------------------------------


#include "juego.h"


using namespace std;

void ElegirSudoku(int &sudoku, bool iniciado){
	if(!iniciado){
		cout<<"Elige el tamaño de el sudoku:"<<endl<<"1= 1x1"<<endl<<"2= 4x4"<<endl<<"3= 9x9"<<endl<<"Introduce una opcion."<<endl<<endl;
		cin>>sudoku;}
	else{
		TEntornoMostrarMensajePosicion("Elige el tamaño:", 12);
		TEntornoMostrarMensajePosicion("1= 1x1", 13);
		TEntornoMostrarMensajePosicion("2= 4x4", 14);
		TEntornoMostrarMensajePosicion("3= 9x9", 15);
		TEntornoMostrarMensajePosicion("Introduce una opcion.", 16);
		bool elegir=true;
		while(elegir){
			TipoTecla tecla = TEntornoLeerTecla();
			switch (tecla){

				case	TUno: sudoku=1;elegir=false;break;
				case	TDos: sudoku=2;elegir=false;break;
				case	TTres: sudoku=3;elegir=false;break;
			}
		}
	}
}


void IniciarJuego(juego &game, bool iniciado){

	int tabini[MAX_TAMANIO][MAX_TAMANIO];
	int sudoku;
	game.jugando=true;
	game.mostrar=false;
	game.activa.x=0;
	game.activa.y=0;
	game.activada=false;

	ElegirSudoku(sudoku, iniciado);

	TEntornoCargarConfiguracion(tabini, game.tab.tamanio,sudoku);
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
					{TEntornoMostrarMensaje("Debes eliminar primero");return false;}
				if (n>game.tab.tamanio*game.tab.tamanio)
					{TEntornoMostrarMensaje("Valor no permitido");return false;}
				if (ExisteEnFila(n, game.tab.tamanio*game.tab.tamanio, game.tab.tabla, game.tab.pos.y))
					{TEntornoMostrarMensaje("Ya existe en Fila");
					if(BuscarValorFila (game.tab,game.activa.x,game.activa.y, n)){
					game.activada=true;
					TEntornoPonerCasilla(game.activa.x+1,game.activa.y+1, COLOR_GREEN, n);}
					return false;}
				if (ExisteEnColumna(n, game.tab.tamanio*game.tab.tamanio, game.tab.tabla, game.tab.pos.x))
					{TEntornoMostrarMensaje("Ya existe en Columna");
					if(BuscarValorColumna (game.tab,game.activa.x,game.activa.y, n)){
					game.activada=true;
					TEntornoPonerCasilla(game.activa.x+1,game.activa.y+1, COLOR_GREEN, n);}
					return false;}
				if (ExisteEnZona(n, game.tab))
					{TEntornoMostrarMensaje("Ya existe en Zona");
					if(BuscarValorZona (game.tab,game.activa.y,game.activa.x, n)){
					game.activada=true;
					TEntornoPonerCasilla(game.activa.x+1,game.activa.y+1, COLOR_GREEN, n);}
					return false;}
				char cad1[5];
	  			if (IntroducirNumeroTablero(game.tab, n)){
//Esto se encarga de desactivar las casillas activadas por la ampliacion:
	if (obtenerSiInicialC (game.tab.tabla[game.activa.y][game.activa.x]))
		TEntornoPonerCasilla(game.activa.x+1, game.activa.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.activa.y][game.activa.x]));
	else{
		TEntornoPonerCasilla(game.activa.x+1, game.activa.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.activa.y][game.activa.x]));}
//fin del codigo para descativar las casillas.
					sprintf(cad1, "%d",n);
					TEntornoMostrarMensaje(cad1);
					TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO,C_VACIA);
					TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
					if(TableroLleno(game.tab, game.tab.tamanio))
					{TEntornoMostrarMensaje("Sudoku Completado!");
					TEntornoMostrarMensaje2("Pulse una tecla");
					cin>>game.tab.pos.x;//espera a que pulse una tecla, mejorar para que tambien valga enter
					JugarDeNuevo(game);}
					else ;
					}	
				else
					TEntornoMostrarMensaje("Debes eliminar primero");
				return true;

}

void IzquierdaJuego(juego &game){
		TEntornoMostrarMensaje("Izquierda");
	if(game.tab.pos.x>0){
			if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
				TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
			else
				TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
			game.tab.pos.x--;
			if(game.mostrar)
				ObtenerPosiblesTablero(game.tab);
			if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
				TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
			else
				TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
						}
}

void DerechaJuego(juego &game){
	TEntornoMostrarMensaje("Derecha");
if(game.tab.pos.x<game.tab.tamanio*game.tab.tamanio-1){
	if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
		TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
	else
		TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
	game.tab.pos.x++;
	if(game.mostrar)
	ObtenerPosiblesTablero(game.tab);
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
		if(game.mostrar)
			ObtenerPosiblesTablero(game.tab);
		if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
		else
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));}
}

void ArribaJuego(juego &game){
	TEntornoMostrarMensaje("Arriba");
	if(game.tab.pos.y>0){
		if (obtenerSiInicialC (game.tab.tabla[game.tab.pos.y][game.tab.pos.x]))
			TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
		else
			TEntornoPonerCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
		game.tab.pos.y--;
		if(game.mostrar)
			ObtenerPosiblesTablero(game.tab);
		if(obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x])==0)
			TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
		else
			TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, obtenerValorC(game.tab.tabla[game.tab.pos.y][game.tab.pos.x]));
}
}

void EliminaJuego(juego &game){
	TEntornoMostrarMensaje("Abajo");
	int j=(game.tab.tabla[game.tab.pos.y][game.tab.pos.x].numero);
	if (EliminarNumeroTablero(game.tab)==false)
		TEntornoMostrarMensaje("No lo puedes eliminar");
	else{
		TEntornoMostrarMensaje("Eliminar");
		TEntornoActivarCasilla(game.tab.pos.x+1, game.tab.pos.y+1, COLOR_RESALTADO, C_CURSOR);
		AniadirPosiblesTablero(game.tab,j);
		if(game.mostrar)
			ObtenerPosiblesTablero(game.tab);
			}
}

void JugarDeNuevo(juego &game){
	TEntornoMostrarMensaje("J=Jugar de nuevo,X=Salir");
	bool elegir=true;
	while(elegir){	
		TipoTecla tecla = TEntornoLeerTecla();
		switch (tecla){
			case	TJugar: IniciarJuego(game, true);
					elegir=false;
					break;
			case	TSalir: elegir=false;game.jugando=false;break;
		}
	}
}

void ObtenerPosiblesTablero(tablero tab){
	TEntornoMostrarMensaje2("Numeros Posibles:");
	int j=5;
	for(int i=1;i<=tab.tamanio*tab.tamanio;i++){
		if(ComprobarPosible(tab.tabla[tab.pos.y][tab.pos.x],i))
			{char cad1[2];
			sprintf(cad1, "%d",i);
			TEntornoMostrarMensaje2Posicion(cad1,j);
			j++;}
	}
}

