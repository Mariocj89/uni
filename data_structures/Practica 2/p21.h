
#ifndef P21_H_
#define P21_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**** DECLARACIONES DE TIPO Y CONSTANTES AUXILIARES *****/

#define UINTSZ 4 //Tamaño del unsigned int
#define FLOATSZ 4 //Tamaño de un float
#define PAGSZ 1024 // n es el número de bytes que ocupa la página
#define EXITO 1
#define FRACASO 0

//Declaramos el tipo para la página cabecera del archivo
typedef struct CABFILET{
   unsigned pagid;
   unsigned ocupacion;
   char nomfich[50];
   unsigned pagsz; // Tamaño de las páginas
   unsigned regsz; // Tamaño de los registros (caso de longitud fija)
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
//Definimos el tamaño de la cabecera para la página
#define CABPAGSZ 2*UINTSZ
//Definimos el tamaño de la zona de datos de la página
#define DATPAGSZ (PAGSZ - CABPAGSZ)
//Calculamos el número de registros que caben en la página
#define NUMREGPAG (DATPAGSZ / REGSZ)
//Y la fragmentación
#define FRAGPAGSZ (DATPAGSZ % REGSZ)
//Declaramos ya el tipo de la página
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
