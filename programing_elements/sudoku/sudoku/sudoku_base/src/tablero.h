// -------------------------------------------------------------
//   Archivo: casilla.h
//   Descripción: TAD que agrupa un acumulador (indica el numero
//		de casillas ocupadas), una matriz, el tamaño de
//		el sudoku y una posicion.
// -------------------------------------------------------------


#ifndef _TABLERO_H
#define _TABLERO_H

#include "casilla.h"





// -------------------------------------------------------------
// Definicion de constantes necesarias
// -------------------------------------------------------------








//Definicion del TAD tablero
typedef struct tablero {
int contador;
posicion pos;
casilla tabla[MAXTAMANIO][MAXTAMANIO];
int tamanio;
};

//Definicion del TAD Zona
typedef struct zona {
posicion lugar;
posicion inicio;
posicion final;
};


//OPERACIONES

/**
PRE: 
POST: cambia el vector de manera que todas sus casillas estan vacias, con color=0, pone el contador a 0 y la posicion en 0,0.
 */
void IniciarTablero(tablero &tab, int tamanio);

/**
PRE: nos deben dar una variable de tipo tablero y un entero.
POST: devuelve true si el tablero esta lleno y false en caso contrario.
 */
bool TableroLleno(tablero tab,int tamanio);

/**
PRE: 
POST: Devuelve verdadero si se carga correctamente la configuración del juego, falso en caso contrario. Si la configuración se lee de forma correcta se devolverá una matriz de enteros de MAX_TAMANIO*MAX_TAMANIO con la información para inicializar un tablro de sudoku de tamaño tamanio (en nuestro caso: 1, 2 o 3)
 */
void CargarConfiguracionTablero(tablero &tab, int tabini[MAXTAMANIO][MAXTAMANIO], int tamanio);



/**
PRE: nos deben dar una variable de tipo tablero.
POST: devuelve true si se a podido introducir el valor y cabia el vector, introduciendo el valor en la posicion determinada por tablero.pos.
 */
bool IntroducirNumeroTablero(tablero &tab, int n);

/**
PRE: nos deben dar una variable de tipo tablero.
POST: devuelve true si se a podido eliminar el valor y cambia el vector, eliminando el valor en la posicion determinada por tablero.pos.
 */
bool EliminarNumeroTablero(tablero &tab);


/**
PRE: valor y max debe ser entero positivo.
POST: Devuelve true si el valor se encuentra en la fila.
*/
bool ExisteEnFila(int valor, int max, casilla tablero[MAXTAMANIO][MAXTAMANIO], int fila);


/**
PRE: valor y max debe ser entero positivo.
POST: Devuelve true si el valor se encuentra en la columna.
*/
bool ExisteEnColumna(int n, int max, casilla tablero[MAXTAMANIO][MAXTAMANIO], int columna);

/**
PRE: n debe ser un entero positivo de 1 al valor maximo permitido.
POST: Devuelve true si el valor existe en la zona.
*/
bool ExisteEnZona(int n, tablero tab);

/**
PRE: deben darnos una tabla de celdas tipo casilla y una posicion de tipo posicion.
POST: devuelve el numero almacenado en la posicion dada de la tabla dada.
*/
int ObtenerNumeroTablero(casilla tablero[MAXTAMANIO][MAXTAMANIO], posicion pos);


#endif
