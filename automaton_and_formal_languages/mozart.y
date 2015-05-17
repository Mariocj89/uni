
/* Primer proyecto de Teoria de automatas y lenguajes formales
 **			====================
 **  			=======MOZART=======
 ** 			====================
 */

%{
#include <stdio.h>
#include <math.h>
#include "sonido.c"
#include "constantes.h"



extern int  yylex(void);
void yyerror(const char * s );
void pintaCadena(const char *cadena);

bool es_real = false;
int  numlinea = 1;
//necesitamos tener acceso a la escala, al tempo y al flujo de entrada del analizador lexico para poder inicializarlos
extern FILE* yyin;
extern float escala; 
extern int tempo;
%}

%union{
  int c_entero;
  float c_real;
  char c_cadena[50];
}
%type <c_real> duracion //duracion de una nota
%type <c_real> expr
%type <c_real> nota //Frencuencia(nota)
%token <c_cadena> E_CADENA  //Cadena para escribir
%token <c_cadena> ESCRIBIR //Token que indica qué hay ke escribir(cadena u expresion)
%token <c_entero> TEMPO 
%token <c_entero> ESCALA //Cambios en la escala
%token <c_real> NOTA
%token <c_real> MODIFICANOTA //Bemol o sostenido
%token <c_real> DURACION
%token <c_entero> ENTERO
%token <c_real> REAL

%left '+' '-'   /* asociativo por la izquierda, misma prioridad */
%left '*' '/'   /* asociativo por la izquierda, prioridad alta */
%left MENOSUNARIO   
%right '^'	/* asociativo por la derecha */
%%
entrada: TEMPO '\n' {setTempo($1);} inicio	
	|error '\n' inicio		{yyerrok;}
      	;

inicio:					{;}
	|linea inicio			{;}
	;

linea:	ESCRIBIR E_CADENA '\n'		{pintaCadena($2);}
	|ESCRIBIR expr '\n'		{char cadenaAux[100]; sprintf(cadenaAux, "Resultado: %g", $2); pintaCadena(cadenaAux);}
	|sonido '\n'
	|error '\n'			{yyerrok;}
	|cescala '\n'
	;

sonido:	nota duracion			{beep($1,$2);}

nota: 	NOTA				{ $$ = $1;}
	|NOTA MODIFICANOTA		{ $$ = $1 * pow(2,($2/12));}
	;

duracion: DURACION			{ $$ = $1;}
	  |DURACION '.'			{ $$ = $1 + $1*0.5;}
	  |expr				{ $$ = $1; }
	  ;

cescala:  ESCALA			{setEscala($1);}
	  |ESCALA expr			{if(!es_real) setEscala($1*$2); else printf("Error, se ha intentado subir/bajar la escala con un real. Linea: %d\n",numlinea);} 
	  ;

expr:    ENTERO                       { $$ = $1; }
       | REAL			      { $$ = $1; es_real = true;}
       | '(' expr ')'		      { $$ = $2; }
       | expr '+' expr                { $$ = $1 + $3; }
       | expr '-' expr                { $$ = $1 - $3; }
       | '-' expr  %prec MENOSUNARIO  { $$ = -$2; }
       | expr '*' expr                { $$ = $1 * $3; }
       | expr '/' expr                { $$ = $1 / $3; }
       | expr '^' expr		      { $$ = pow($1,$3); }
       ;
	
%%

char *nombreprog;       /* para los mensajes de error */

int main( int argc, char **argv )
{
     if (argc > 2) printf("Solo se esperaba un argumento, el resto no se tomara en cuenta.\n");
     if (argc == 1){
	printf("Error, debe de llamar al programa con 1 parametro.\nEj: %s fichero.mzt\n",*argv);
	return -1;
     }
     yyin = fopen(*(argv+1), "rt");
     if(!yyin){
	printf("Error, fichero pasado como parametro NO existe!\n");
	return -1;
     }
     nombreprog = *argv;
     escala = 1;
     tempo = _ALLEGRO;

     printf("\n****************************************************\n");
     printf("*      Bienvenido a MOZART!!                       *\n");
     printf("****************************************************\n\n\n");
     yyparse();
     pintaCadena("*                      Gracias por usar Mozart                                 *");
     return 0;
}


void yyerror(const char *s )             /* llamada por error sintactico de yacc */
{
	printf("%s: %s", nombreprog, s);
	printf(" linea %d\n", numlinea);
}

