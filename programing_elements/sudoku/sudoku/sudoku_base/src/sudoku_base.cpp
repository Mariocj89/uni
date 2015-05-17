

//juegocpp-linea 54:Mejorar

#include "juego.h"


using namespace std;


int main() {
	juego game;
	IniciarJuego(game);

 	while(game.jugando){		
		TipoTecla tecla = TEntornoLeerTecla();
		switch (tecla)
		
		{


			case TUno:case TDos:case TTres:case TCuatro:case TCinco:case TSeis:case TSiete:case TOcho:case TNueve:
				IntroducirNumeroJuego(game, tecla);break;


			case TIzquierda:TEntornoMostrarMensaje("Izquierda            ");
				IzquierdaJuego(game);break;


			case TDerecha:  TEntornoMostrarMensaje("Derecha            ");
				DerechaJuego(game);break;


			case TArriba: TEntornoMostrarMensaje("Arriba             ");
				ArribaJuego(game);break;


			case TAbajo: TEntornoMostrarMensaje("Abajo             ");
				AbajoJuego(game);break;


			case TEliminar: EliminaJuego(game);break;

			case TSalir: game.jugando=false; break;
			
		}
	
		
	}
	TEntornoTerminar();
	
}

