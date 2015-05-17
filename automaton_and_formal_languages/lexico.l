%{
#include <stdlib.h>
#include <stdio.h>
#include "mozart.h"
#include "constantes.h"
extern int numlinea;
%}
%option noyywrap

%x ESC TMP

letra		[a-zA-Z]
caracter	[a-zA-Z0-9]
digito		[0-9]
natural		{digito}+
real		({natural}"."{natural}?)|({natural}?"."{natural})
numero		{real}|{natural}
lineaVacia	^[ \t]*\n
espacio		[ \t]

%%

[#].*[\n]					numlinea++; //Esto es un comentario

[Ee][Ss][Cc][Rr][Ii][Bb][Ii][Rr][ ]		{BEGIN(ESC); return ESCRIBIR;}

<ESC>{espacio}					;

<ESC>{natural}					{yylval.c_entero = atoi(yytext); return ENTERO;}

<ESC>{real}					{yylval.c_real = atof(yytext); return REAL;}

<ESC>\"[^\"\n]*\"				{strcpy(yylval.c_cadena, yytext); return E_CADENA;} //Cadena a escribir	
	
<ESC>.						{return yytext[0];}

<ESC>\n						{BEGIN(0); numlinea++; return yytext[0];}

[Tt][Ee][Mm][Pp][Oo][ ]				BEGIN(TMP); //indicacion de que viene el tempo

<TMP>[Ll][Ee][Nn][Tt][Oo]			{yylval.c_entero=_LENTO; return TEMPO;}

<TMP>[Aa][Nn][Dd][Aa][Nn][Tt][Ee]		{yylval.c_entero=_ANDANTE; return TEMPO;}

<TMP>[Aa][Ll][Ll][Ee][Gg][Rr][Oo]		{yylval.c_entero=_ALLEGRO; return TEMPO;}

<TMP>[Vv][Ii][Vv][Aa][Cc][Ee]			{yylval.c_entero=_VIVACE; return TEMPO;}

<TMP>{espacio}					;

<TMP>.*						printf("ERROR, en la linea que indica el tempo: %s\n", yytext);						

<TMP>\n						{BEGIN(0);numlinea++; return yytext[0];}

{espacio}					;

{natural}					{yylval.c_entero = atoi(yytext); return ENTERO;}

{real}						{yylval.c_real = atof(yytext); return REAL;}


[sS][Uu][Bb][Ii][Rr]				{yylval.c_entero = 1; return ESCALA;}

[Bb][Aa][Jj][Aa][Rr]				{yylval.c_entero = -1; return ESCALA;}



[Dd][Oo]					{yylval.c_real = _DO; return NOTA;}

[Rr][Ee]					{yylval.c_real = _RE; return NOTA;}

[Mm][Ii]					{yylval.c_real = _MI; return NOTA;}

[Ff][Aa]					{yylval.c_real = _FA; return NOTA;}

[Ss][Oo][Ll]					{yylval.c_real = _SOL; return NOTA;}

[Ll][Aa]					{yylval.c_real = _LA; return NOTA;}

[Ss][Ii]					{yylval.c_real = _SI; return NOTA;}

[Ss][Ii][Ll][Ee][Nn][Cc][Ii][Oo]		{yylval.c_real = 1; return NOTA;}



[Ss][Oo][Ss][Tt][Ee][Nn][Ii][Dd][Oo]		{yylval.c_real = 1; return MODIFICANOTA;}

[Bb][Ee][Mm][Oo][Ll]				{yylval.c_real = -1; return MODIFICANOTA;}



[Rr][Ee][Dd][Oo][Nn][Dd][Aa]			{yylval.c_real = _REDONDA; return DURACION;}

[Bb][Ll][Aa][Nn][Cc][Aa]			{yylval.c_real = _BLANCA; return DURACION;}

[Nn][Ee][Gg][Rr][Aa]				{yylval.c_real = _NEGRA; return DURACION;}

[Cc][Oo][Rr][Cc][Hh][Ee][Aa]			{yylval.c_real = _CORCHEA; return DURACION;}

[Ss][Ee][Mm][Ii][Cc][Oo][Rr][Cc][Hh][Ee][Aa]	{yylval.c_real = _SEMICORCHEA; return DURACION;}

[Ff][Uu][Ss][Aa]				{yylval.c_real = _FUSA; return DURACION;}

[Ss][Ee][Mm][Ii][Ff][Uu][Ss][Aa]		{yylval.c_real = _SEMIFUSA; return DURACION;}


{lineaVacia}					numlinea++;

\n						{numlinea++; return yytext[0];}

.						{return yytext[0];}

%%

