
/**
Extensiones al proyecto:
-Jugar de nuevo al finalizar. Completado!
-Poder escribir en 2 lineas dentro del entorno. Completado!
-Mi nombre en el entorno. Completado!
-Eleccion del sudoku. Completado!
-Poder reiniciar el juego en cualquier momento a traves de una tecla.Completado!
-juego.cpp Linea 78, mejorar.
-Doble linea por zonas.
-Aparezcan los numeros que se pueden introducir. Completado!
-La ampliacion anterior puede activarse y desactivarse por una tecla. Completado!
-Si no se puede introducir un numero por que ya existe en una columna, fila o region, debe indicar cual es el numero que no permite introducirlo.Completado!
*/

#include "juego.h"


using namespace std;


int main() {
	juego game;
	bool iniciado;
	IniciarJuego(game, false);
 	while(game.jugando){		
		TipoTecla tecla = TEntornoLeerTecla();
//Esto se encarga de desactivar las casillas activadas por la ampliacion: Si quieres que te quede el numero resaltado solo hay que copiar este fragmento de codigo a los modulos del TAD juego correspondiente, preo creo que es mas util asi. He doblado la variable time para que tarde el doble en desaparecer el color.
while(game.activada){//Es importante este while pues si no haria esto continuamente y ademas de ser operaciones inutiles, si tenemos el cursor sobre un numero que tiene la posicion game.activa, no parpadeara mas que una vez.
	if (obtenerSiInicialC (game.tab.tabla[game.activa.y][game.activa.x]))
		TEntornoPonerCasilla(game.activa.x+1, game.activa.y+1, COLOR_BLANCO, obtenerValorC(game.tab.tabla[game.activa.y][game.activa.x]));
	else{
		TEntornoPonerCasilla(game.activa.x+1, game.activa.y+1, COLOR_NORMAL, obtenerValorC(game.tab.tabla[game.activa.y][game.activa.x]));}
game.activada=false;
}
//fin del codigo para descativar las casillas.
		switch (tecla)
		
		{


			case TUno:case TDos:case TTres:case TCuatro:case TCinco:case TSeis:case TSiete:case TOcho:case TNueve:
				IntroducirNumeroJuego(game, tecla);

				break;


			case TIzquierda:IzquierdaJuego(game);break;


			case TDerecha:  DerechaJuego(game);break;


			case TArriba:	ArribaJuego(game);break;


			case TAbajo:	AbajoJuego(game);break;


			case TEliminar: EliminaJuego(game);break;

			case TSalir: game.jugando=false; break;

			case TReiniciar: IniciarJuego(game, true);break;

			case TMostrar: game.mostrar=(!game.mostrar);break;
			
		}
	
		
	}
	TEntornoTerminar();
	
}

