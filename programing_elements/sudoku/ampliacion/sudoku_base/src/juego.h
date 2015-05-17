// -------------------------------------------------------------
//   Archivo: juego.h
//   Descripción: TAD para el tipo juego.
// -------------------------------------------------------------



#ifndef _JUEGO_H
#define _JUEGO_H
#include "tablero.h"
#include "entorno.h"

//Definicion del TAD acti


//Definicion del TAD posicion
typedef struct juego {
tablero tab;
bool jugando;
bool mostrar;
int k;
int l;
posicion activa;
bool activada;
};


//Operaciones
/**
PRE:
POST: Inicia un juego-> inicializa el tablero, carga la configuracion en el tablero, dibuja la configuracion inicial y pone el cursor en la posicion inicial.
 */
void IniciarJuego(juego &game, bool iniciado);

/**
PRE:	nos deben dar un juego previamente iniciado.
POST: Comprueba sis e puede introducir el numero, si es posible lo introduce, si no, muestra el respectivo mensaje de error, tambien controla la finalizacion del juego. Devuelve 1 si el numero se ha introducido.
 */
bool IntroducirNumeroJuego(juego &game, int n);

/**
PRE:	nos deben dar un juego previamente iniciado.
POST: Mueve el cursor una casilla hacia la izquierda teniendo en cuenta si en la casilla a la que se mueve hay algun valor, restaurando la casilla en la que se encuentra previamente 
 */
void IzquierdaJuego(juego &game);

/**
PRE:	nos deben dar un juego previamente iniciado.
POST: Mueve el cursor una casilla hacia la derecha teniendo en cuenta si en la casilla a la que se mueve hay algun valor, restaurando la casilla en la que se encuentra previamente 
 */
void DerechaJuego(juego &game);

/**
PRE:	nos deben dar un juego previamente iniciado.
POST: Mueve el cursor una casilla hacia abajo teniendo en cuenta si en la casilla a la que se mueve hay algun valor, restaurando la casilla en la que se encuentra previamente 
 */
void AbajoJuego(juego &game);

/**
PRE:	nos deben dar un juego previamente iniciado.
POST: Mueve el cursor una casilla hacia arriba teniendo en cuenta si en la casilla a la que se mueve hay algun valor, restaurando la casilla en la que se encuentra previamente 
 */
void ArribaJuego(juego &game);

/**
PRE:	nos deben dar un juego previamente iniciado.
POST: Elimina el valor de la casilla de la posicion actual, colocando el cursor en s lugar.
 */
void EliminaJuego(juego &game);

/**
PRE:	nos deben dar un juego finalizado.
POST: dependiendo de la opcion que elige el usuario, el juego se reinicia o se acaba.
 */
void JugarDeNuevo(juego &game);

/**
PRE:	
POST: Permite al usuario elegir un sudoku.
 */
void ElegirSudoku(int &sudoku, bool iniciado);

/**
PRE: deben darnos un tablero
POST: Muestra los posibles valores para la casilla actual en el entorno.
*/
void ObtenerPosiblesTablero(tablero tab);



#endif
