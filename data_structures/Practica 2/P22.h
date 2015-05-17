/*
 * P22.h
 *
 *  Created on: 27/10/2009
 *      Author: Mario
 */

#ifndef P22_H_
#define P22_H_


/***** Ficheros cabecera necesarios para la ejecuci¢n ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**** DECLARACIONES DE TIPO Y CONSTANTES AUXILIARES *****/
#define UINTSZ 4 //Tamaño del unsigned int
#define FLOATSZ 4 //Tamaño de un float
#define MAXNUMREG 5000
#define PAGSZ 1024
#define EXITO 1
#define FRACASO 0

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

typedef struct CABPAGT{
        unsigned pagid;
        unsigned ocupacion; // Número de registros que contiene
} CABPAGT;

#define CABPAGSZ (2*UINTSZ)

#define ZDPAGSZ (PAGSZ - CABPAGSZ)
//El tamaño del registro no puede ser mayor que el de la zona de datos de la página
#define MAXREGSZ ZDPAGSZ

typedef struct PAGT{
        CABPAGT cabp; // La información de la cabecera de página
        char datos[ZDPAGSZ]; // Resto de la página
        } PAGT;

typedef struct DIRPAGT{
        char no_necesario[PAGSZ]; // Ocupa toda la página
        unsigned entrada[]; // Permite acceder a cada entrada del directorio
        } DIRPAGT;

// Tipo para la pagina cabecera del fichero
typedef struct CABFILET{
   unsigned pagid;
   unsigned ocupacion;
   char nomfich[50];
   unsigned pagsz; // Tamaño de las páginas
   unsigned regsz; // Tamaño de los registros (caso de longitud fija)
   char resto[PAGSZ - 4*UINTSZ - 50];
} CABFILET;


/****** PROTOTIPOS DE FUNCIONES *****/
char AddRegAPag(PAGT *pag, char *reg, unsigned regsz);
unsigned BytesLibresPag(PAGT *pag);
char ConstruyeLvregDat (void);
char CreaFichero(char *filename,void *cabecera, unsigned cabsz);
void ImprimeReg(char *reg, unsigned regsz, FILE *fd);
char ObtenRegDePag(PAGT *pag, char *reg, unsigned *regsz, unsigned pos);
char ObtenSgteRegLongVar(FILE *fd, char *reg, unsigned *regsz);
unsigned PrimerByteLibre(PAGT *pag); //obtiene el primer byte libre de los datos
void VolcadoLvregDatAReslvregTxt(void);
unsigned ObtenerInicioDeTupla(PAGT *pag, unsigned pos);

#endif /* P22_H_ */
