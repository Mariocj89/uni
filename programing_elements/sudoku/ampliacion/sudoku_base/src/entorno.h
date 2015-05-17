// -------------------------------------------------------------
//   Archivo: entorno.h
//   Descripción: Interfaz del entorno de la práctica SUDOKU
//   Fecha :      11-12-2007
//		  Elementos de Programación.Curso 07/08
// -------------------------------------------------------------



#ifndef _ENTORNO_H
#define _ENTORNO_H


// -------------------------------------------------------------
// Definicion de constantes necesarias
// -------------------------------------------------------------

#ifndef _Constantes
#define _Constantes

#include <ncurses.h>
#include <cstdlib>


/**
	Definición del tamaño máximo de los bloques del sudoku. 
*/
const int MAX_TAMANIO_JUEGO=3;

/**
	Definición del tamaño máximo del tablero de juego que será MAX_TAMANIO_JUEGO*MAX_TAMANIO_JUEGO;
*/
const int MAX_TAMANIO=MAX_TAMANIO_JUEGO*MAX_TAMANIO_JUEGO;

/**
	Definición de los caracteres que se utilizarán como cursores y colores 
*/
const int C_IZQ = 97;
const int C_DER = 100;
const int C_ARR = 119;
const int C_ABA = 115;

const int C_CURSOR = 88; // Carácter para escribir el cursor
const int C_VACIA = 0;   // Carácter para escribir vacio
const int COLOR_RESALTADO=2;
const int COLOR_NORMAL=1;
const int COLOR_BLANCO=5;
#endif

// -------------------------------------------------------------
// Definicion de tipos enumerados
// -------------------------------------------------------------
/**
	 Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
	 de los cursores que se ha pulsado
*/
typedef enum TipoTecla {TNada, TUno, TDos, TTres, TCuatro, TCinco, TSeis, TSiete, TOcho, TNueve, TIzquierda, TDerecha, TArriba, TAbajo, TSalir, TEliminar, TJugar, TReiniciar, TMostrar};


/**
PRE: 
POST: Devuelve verdadero si se carga correctamente la configuración del juego, falso en caso contrario. Si la configuración se lee de forma correcta se devolverá una matriz de enteros de MAX_TAMANIO*MAX_TAMANIO con la información para inicializar un tablro de sudoku de tamaño tamanio (en nuestro caso: 1, 2 o 3)
 */
bool TEntornoCargarConfiguracion(int tablero[MAX_TAMANIO][MAX_TAMANIO], int &tamanio, int sudoku);

/**
PRE: Una matriz de enteros  de MAX_TAMANIO*MAX_TAMANIO que contiene la información para inicializar el tablero del sudoku en pantalla. Además el módulo recibe el tamaño del sudoku (1, 2 o 3)
POST: Inicializa la pantalla del sudoku con la información pasada por parámetros.
*/
void TEntornoIniciarPantalla (int tablero[MAX_TAMANIO][MAX_TAMANIO], int tamanio);

/** 
  PRE: El módulo recibe las coordenadas (x,y) correctas de una casilla, así como el valor que queremos poner en una casilla, junto con su color (colorpair)
  POST: Establece en el entorno el valor de una casilla colocada en la posición x, y del tablero. Este valor se presentará del color pasado por parámetros.
 */
void TEntornoPonerCasilla(int x, int y, int colorpair, int valor);

/**
PRE: x e y son dos coordenadas válidas en el entorno, con valores entre 1 y MAX_TAMANIO. 
POST: Establece una casilla con coordenadas x,y al valor pasado por parámetros y color parpadeante. 
*/
void TEntornoActivarCasilla(int x, int y, int color, int valor);

/**
PRE: x e y son dos coordenadas válidas en el entorno, con valores entre 1 y MAX_TAMANIO. 
POST: Establece una casilla con coordenadas x,y al valor pasado por parámetros y color fijo
*/
void TEntornoDesactivarCasilla(int x, int y, int color, int valor);

/**
PRE: x e y son coordenadas válidas en el tablero
POST: Elimina del entorno el valor que existe en la casilla cuyas coordenadas son x,y
*/
void TEntornoEliminarCasilla(int x, int y);

/**
PRE: El módulo recibe una cadena de caracteres, un mensaje.
POST:Escribe el mensaje pasado por parámetros en el entorno, concretamente, en el área de mensajes, en la primera linea.
*/
void TEntornoMostrarMensaje(char *c);
	
/**
PRE:
POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado y que se deben interpretar
*/
TipoTecla TEntornoLeerTecla(void);
	
/**
PRE:
POST: Destruye el contexto del entorno gráfico.
*/
void TEntornoTerminar();

/**
PRE: El módulo recibe una cadena de caracteres, un mensaje.
POST:Escribe el mensaje pasado por parámetros en el entorno, concretamente, en el área de mensajes, en la segunda linea.
*/
void TEntornoMostrarMensaje2(char *c);

/**
PRE: El módulo recibe una cadena de caracteres, un mensaje y una altura.
POST:Escribe el mensaje pasado por parámetros en el entorno, concretamente, en el área de mensajes, a una altura definida por el usuario.
*/
void TEntornoMostrarMensajePosicion(char *c, int x);

/**
PRE: El módulo recibe una cadena de caracteres, un mensaje.
POST:Escribe el mensaje pasado por parámetros en el entorno, concretamente, en el área de mensajes, en una determinada "columna", 3a fila.
*/
void TEntornoMostrarMensaje2Posicion(char *c, int x);

#endif
