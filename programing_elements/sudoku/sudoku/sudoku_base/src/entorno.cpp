
// -------------------------------------------------------------
//   Archivo: entorno.h
//   Descripción: Interfaz del entorno de la práctica SUDOKU
//   Fecha :      11-12-2007
//		  Elementos de Programación.Curso 07/08
// -------------------------------------------------------------

#include "entorno.h"

#include <iostream>
#include <ncurses.h>
#include <fstream>


using namespace std;
static WINDOW *mainwin;
static WINDOW *win;
static WINDOW *msgwin;

//

void TEntornoPonerColorCasilla(int x, int y, int colorpair, int valor) ;

// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------
/**
	Definicón de constantes para posicionar los números en el tablero
*/
const int distancia=5;  // Distancia entre columnas
const int distanciay=2;  // Distancia entre filas
const int origen_x=0;  // Origen de las x
const int origen_y=2;  // Origen de las y 

/**
	Definición de una constante para determinar el tiempo de espera para leer una tecla
*/
const long Pausa = 50000;  // Este valor se puede aumentar o disminuir
						   // para que vaya a mas o menos velocidad
// -------------------------------------------------------------
// Operaciones
// -------------------------------------------------------------
// Dibuja en la pantalla el borde de un tablero con el ancho indicado
void TEntornoPintarRejilla(int f, int c) {
             // Comenzamos en la 0,0
	
	int i,j;
	int x,y;
	for (y=origen_y; y<=f*distanciay+origen_y;y++)
		for (x=origen_x;x<=c*distancia+origen_x;x++) {
						
 			//wattrset(win, 2);
			if (y==origen_y) {  // primera fila
				  if( x==origen_x) mvaddch( y, x, ACS_ULCORNER);
				  else if (x==c*distancia+origen_x) mvaddch( y, x, ACS_URCORNER);
				       else {
						if (x%distancia == 0 ) mvaddch(y, x, ACS_TTEE);
						else mvaddch(y, x,  ACS_HLINE); // HLINE
					    }
			}
			else if (y==f*distanciay+origen_y)	{// ultima fila
				  if( x==origen_x) mvaddch(y, x, ACS_LLCORNER);
				  else if (x==c*distancia+origen_x) mvaddch(y, x, ACS_LRCORNER);
				       else {
						if (x%distancia == 0 ) mvaddch(y, x, ACS_BTEE);
						else mvaddch(y, x,  ACS_HLINE);
					    }
			}
			else if (x==origen_x) {  // larearal izquierdo
				  
				  if (y%distanciay == 0 ) mvaddch(y, x, ACS_LTEE);
						else mvaddch(y, x,  ACS_VLINE);
					    
			}
			else if (x==c*distancia+origen_x)	{// lateral derecho
				  
				if (y%distanciay == 0 ) mvaddch(y, x, ACS_RTEE);
					else mvaddch(y, x,  ACS_VLINE);
				
			}
			else { // resto
                              if (x%distancia==0 &&  y%distanciay==0) mvaddch(y, x, ACS_PLUS);
			      else if (x%distancia==0) mvaddch(y, x,  ACS_VLINE);
			      else if  (y%distanciay==0) mvaddch(y, x,  ACS_HLINE);
			}
		}

	// Caja
}


bool TEntornoCargarConfiguracion(int tablero[MAX_TAMANIO][MAX_TAMANIO], int &tamanio){
	ifstream entrada;
	char cad_tamanio[10], cad[MAX_TAMANIO+1];
	bool ok=true;
	int fila=0;
	entrada.open("sudoku.cnf");
	if (entrada == 0 ){
		cout<<"Fichero de configuración no encontrado."<<endl;
		ok=false;
	}
	else {
		entrada.getline(cad_tamanio, 10);
		tamanio = atoi(cad_tamanio);
		while (!entrada.eof()){

			entrada.getline(cad, MAX_TAMANIO+1);
			if (!entrada.eof()) {
				for (int i=0;i<strlen(cad);i++) {
					tablero[fila][i]=cad[i]-48; 
				}
				fila++;			
			}
		}		
		entrada.close();
		
	}
	return ok;
}

void TEntornoIniciarPantalla (int tablero[MAX_TAMANIO][MAX_TAMANIO], int tamanio) {
  int i,j;
 
  mainwin=initscr();
  start_color();
  cbreak();
  nodelay(mainwin, TRUE);
  noecho();
  curs_set(0);
  refresh();
  wrefresh(mainwin);

  win = newwin(36,46, 0,0);  // Ventana de juego

    if(win == NULL)
    {   
        endwin();
#ifdef XCURSES
        XCursesExit();
#endif
    }    
      //Inicializar los pares de colores basicos
    init_pair(1,COLOR_YELLOW,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);    
    
    init_pair(4,COLOR_BLACK,COLOR_BLACK);
    init_pair(5,COLOR_WHITE,COLOR_BLACK);
 
   
   TEntornoPintarRejilla(tamanio*tamanio,tamanio*tamanio);
   wrefresh(win);
   refresh(); 
    
    for (i = 0; i<tamanio*tamanio; i++)
      for (j = 0; j<tamanio*tamanio; j++)      
         if (tablero[i][j]!=0)
		TEntornoPonerCasilla(j+1,i+1,5, tablero[i][j]);

  
   wrefresh(win);
   refresh(); 
  
   //Vetana de mensajes
   msgwin = newwin(19,32,2,47);  

    if(msgwin == NULL)
    {   
        endwin();
#ifdef XCURSES
        XCursesExit();
#endif
    }    
    
    box(msgwin, ACS_VLINE, ACS_HLINE);   

    mvwprintw(msgwin, 1, 4,"PRACTICA EP0708 - SUDOKU");
    
    mvwprintw(msgwin, 3, 8,"A - Izquierda");
    mvwprintw(msgwin, 4, 8,"D - Derecha");
    mvwprintw(msgwin, 5, 8,"W - Arriba");
    mvwprintw(msgwin, 6, 8,"S - Abajo");
    mvwprintw(msgwin, 7, 8,"P - Eliminar");
    mvwprintw(msgwin, 8, 8,"X - Salir");

    mvwprintw(msgwin, 10, 4,"----------------------");
   
    wrefresh(msgwin);
    refresh(); 
  
}

// 1<=x<=15, 1<=y<=10
void TEntornoActivarCasilla(int x, int y, int colorpair, int valor) {

   TEntornoPonerColorCasilla(x,y,COLOR_PAIR(colorpair)|A_BLINK, valor);
   wrefresh(win);
   refresh();
}

void TEntornoPonerCasilla(int x, int y, int colorpair, int valor) {

   TEntornoPonerColorCasilla(x,y,COLOR_PAIR(colorpair), valor);
   wrefresh(win);
   refresh();
}

void TEntornoDesactivarCasilla(int x, int y, int color, int valor) {

   TEntornoPonerColorCasilla(x,y,COLOR_PAIR(color), valor);
   wrefresh(win);
   refresh();

}

void TEntornoEliminarCasilla(int x, int y) {

   TEntornoPonerColorCasilla(x,y,COLOR_PAIR(4), C_VACIA);
   wrefresh(win);
   refresh();

}

void TEntornoPonerColorCasilla(int x, int y, int colorpair, int valor) {
   char cad[5];
 
   wattrset(win, colorpair);
   
   //empiezan en 0
   x--; y--;
   sprintf(cad, "%d",valor); // convertir el valor a cadena

   switch (valor) {
	case C_VACIA: mvwprintw(win, (y*distanciay)+(distanciay/2)+origen_y, (x*distancia)+(distancia/2)+origen_x,"  "); // pintar
		break;
	case C_CURSOR:mvwprintw(win, (y*distanciay)+(distanciay/2)+origen_y, (x*distancia)+(distancia/2)+origen_x,"__"); // pintar
		break;
 	default:   
   		mvwprintw(win, (y*distanciay)+(distanciay/2)+origen_y, (x*distancia)+(distancia/2)+origen_x,cad);
   }   
   wrefresh(win);
   refresh();
}

// Muestra una cadena de 15 caracteres
void TEntornoMostrarMensaje(char *c){
   mvwprintw(msgwin, 12, 5,"               ");
   wrefresh(msgwin);
   refresh();
   mvwprintw(msgwin, 12, 5,c);
   wrefresh(msgwin);
   refresh();
}
// Retorna un tipo enumerado con la tecla pulsada
TipoTecla TEntorno_que_tecla (void)
{
	int codtecla=0;
 	TipoTecla tecla=TNada;
	int extendido=0;
	bool salir=false;


	// Si se ha pulsado una tecla
//	if (kbhit())
if (1)
	{
		// Se lee la tecla pulsada
		extendido=codtecla = getch();
		// Si el código de la tecla es 0, es una tecla especial
		// (Las teclas especiales, devuelven dos c�digos: 0 y un c�digo extendido)
		if (1)//( (codtecla==27) && (!salir) )
			{
				// Se vuelve a leer el segundo c�digo (c�digo extendido)

				//extendido = getch();
				switch (extendido)
 					{
						case C_IZQ : tecla=TIzquierda;
							     salir=true;
							     break;
						case C_DER : tecla=TDerecha;
							     salir=true;
							     break;
						case C_ARR : tecla=TArriba;
							     salir=true;
							     break;
						case C_ABA : tecla=TAbajo;
								 salir=true;
								 break;
                                                case 'X' :
						case 'x' : tecla=TSalir;
								 salir=true;
								 break;
						case 'P' :
						case 'p' : tecla=TEliminar;
								 salir=true;
								 break;
						case '1':tecla=TUno; salir=true; break;
						case '2':tecla=TDos; salir=true; break;
						case '3':tecla=TTres; salir=true; break;
						case '4':tecla=TCuatro; salir=true; break;
						case '5':tecla=TCinco; salir=true; break;
						case '6':tecla=TSeis; salir=true; break;
						case '7':tecla=TSiete; salir=true; break;
						case '8':tecla=TOcho; salir=true; break;
						case '9':tecla=TNueve; salir=true; break;
						
					}
			}
	}



	return (tecla);
}




TipoTecla TEntornoLeerTecla(void)
{
	long cont;
	TipoTecla tecla=TNada;

	for (cont=0;cont<Pausa;cont++)
		{
			if (tecla==TNada)
				tecla=TEntorno_que_tecla();
		}
	return tecla;
}

void TEntornoTerminar(){
  endwin();
}

