
#ifndef P21_H_
#define P21_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**** DECLARACIONES DE TIPO Y CONSTANTES AUXILIARES *****/

#define UINTSZ 4 //Tama�o del unsigned int
#define FLOATSZ 4 //Tama�o de un float
#define PAGSZ 1024 // n es el n�mero de bytes que ocupa la p�gina
#define EXITO 1
#define FRACASO 0

//Declaramos el tipo para la p�gina cabecera del archivo
typedef struct CABFILET{
   unsigned pagid;
   unsigned ocupacion;
   char nomfich[50];
   unsigned pagsz; // Tama�o de las p�ginas
   unsigned regsz; // Tama�o de los registros (caso de longitud fija)
   char resto[PAGSZ - 4*UINTSZ - 50];
} CABFILET;

typedef struct FECHAT{
 char dia, mes, anio;
 } FECHAT;

#define FECHATSZ 3

typedef struct REGT{
        char codcli[5];
        unsigned  idpedido;
        char nombre[40];
        char ciudad[15];
        FECHAT fecha;
        float importe;
} REGT;


#define REGSZ (60+UINTSZ+FECHATSZ+FLOATSZ)
//Definimos el tama�o de la cabecera para la p�gina
#define CABPAGSZ 2*UINTSZ
//Definimos el tama�o de la zona de datos de la p�gina
#define DATPAGSZ (PAGSZ - CABPAGSZ)
//Calculamos el n�mero de registros que caben en la p�gina
#define NUMREGPAG (DATPAGSZ / REGSZ)
//Y la fragmentaci�n
#define FRAGPAGSZ (DATPAGSZ % REGSZ)
//Declaramos ya el tipo de la p�gina
typedef struct PAGT{
  unsigned pagid;
  unsigned ocupacion;
  REGT reg[NUMREGPAG];
#if(FRAGPAGSZ)
  char fragmentacion[FRAGPAGSZ];
#endif
} PAGT;

char ColocaRegEnPag(PAGT *pagina, REGT reg, unsigned pos);
char ObtenRegDePag(PAGT pagina, REGT *reg, unsigned pos);
char CreaFichero(char *filename,void *cabecera, unsigned cabsz);
char ConstruirPedidosDat(void);
char ObtenSgteReg (FILE *fd, REGT *reg);
char InsertaRegistroEnPag(PAGT *pagina, REGT reg); //coloca al final
char VolcadoPedidosDatARespedTxt(void);



#endif /* P21_H_ */
