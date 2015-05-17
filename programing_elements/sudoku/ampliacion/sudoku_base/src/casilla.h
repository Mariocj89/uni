// -------------------------------------------------------------
//   Archivo: casilla.h
//   Descripción: TAD para las casillas del tablero del sudoku
// -------------------------------------------------------------



#ifndef _CASILLA_H
#define _CASILLA_H



// -------------------------------------------------------------
// Definicion de constantes necesarias
// -------------------------------------------------------------

#include <iostream>
#include <fstream>




/**
	Definición del tamaño máximo de los bloques del sudoku. 
*/
const int MAXTAMANIOJUEGO=3;

/**
	Definición del tamaño máximo del tablero de juego que será MAX_TAMANIO_JUEGO*MAX_TAMANIO_JUEGO;
*/
const int MAXTAMANIO=MAXTAMANIOJUEGO*MAXTAMANIOJUEGO;

//Definicion del TAD posicion
typedef struct posicion {
int x;
int y;
};


//Definicion del tipo casilla, compuesto por un numero(1-9) y un estado que indica si es inicial la casilla(0-1)
typedef struct casilla{
int numero;
int color;
bool posibles[9];
};


//Operaciones
/**
PRE: deben darnos una casilla ocupada.
POST: casilla ahora es inicial.
 */
void ponerInicialC (casilla &casi);

/**
PRE: 
POST: nos devuelve una casilla vacia.
 */
casilla CrearC ();

/**
PRE: Debe darnos una casilla y el numero a introducir.
POST: la casilla queda con el numero N.
 */
void ponerValorC(casilla &casi, int n);

/**
PRE: Debe darnos una casilla.
POST: devuelve el numero almacenado en la casilla dada.
 */
int obtenerValorC (casilla c);

/**
PRE: Debe darnos una casilla.
POST: devuelve si la casilla dada contiene un valor inicial.
 */
bool obtenerSiInicialC (casilla c);

/**
PRE: Debe darnos una casilla y un entero entre 1 y tamanio².
POST: introduce un valor posible en la casilla.
 */
void AniadirPosible(casilla &casi, int n);

/**
PRE: Debe darnos una casilla y un entero entre 1 y tamanio².
POST: quita un valor posible de la casilla.
 */
void QuitarPosible(casilla &casi, int n);

/**
PRE: Debe darnos una casilla y el tamanio del sudoku)
POST: Pone todos los valores como posibles.
 */
void LlenarPosible(casilla &casi, int tamanio);

/**
PRE: Debe darnos una casilla y el tamanio del sudoku)
POST: Quita todos los valores posibles.
 */
void VaciarPosible(casilla &casi, int tamanio);

/**
PRE: Debe darnos una casilla y un entero entre 1 y tamanio*tamanio)
POST: Comprueba si el numero es posbible, devuelve true en caso verdadero y false en caso falso.
 */
bool ComprobarPosible(casilla casi, int n);



#endif
