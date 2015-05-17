#if !defined (_P4_H)
#define _P4_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define NUMCAMPOS 6 // N£mero de campos o atributos de la tupla
#define SEPARADOR ';' // Separador utilizado en el fichero de entrada
#define PAGSZ 2048 // Tama¤o de las p ginas de datos
#define PAGISZ 512
#define MAXENTRADASIND 1100// N£mero m ximo de entradas que tendr  la tabla ¡ndice
#define MAXNUMPAGDATOS 500 // N£mero m ximo de p ginas del fichero de datos
#define ACTUALIZADO 0 //Significado del valor del campo estado...
#define OBSOLETO 1 //...relativo al archivo que guarda una copia del índice simple
#define NOMFICH_DAT  "pedidos.dat"
#define NOMFICH_NDX  "pedidos.ndx"
#define NOMFICH_FTE  "pedidos.txt"
#define NOMFICH_TRA  "trans.txt"
#define NOMFICH_LOG  "log.txt"
#define NOMFICH_SAL  "encontrados.txt"
#define UINTSZ 4
#define FLOATSZ 4
#define ERRFUERADERANGO 2
#define ERRINDICEEXHAUSTO 3
#define ERRARCHIVOEXHAUSTO 4
#define ERRCLAVEDUPLICADA 5
#define EXITO 1
#define FRACASO 0
#define INTERNO 0
#define HOJA 1
#define DESBORDE 6
#define ASCENSO 7
#define HECHO 8
#define DEBUG 0


// ******************* DEFINICION DE LOS TIPOS DE DATOS PARA LAS TUPLAS
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

#define FRAGCABDATOS (PAGSZ - 5*UINTSZ  - 50)

typedef struct CABFILEDT{
 unsigned pagid;
 unsigned ocupacion; // Número de páginas de datos asignadas al fichero
 char nombrefichero[50];
 unsigned pagsz; // Tamaño de las páginas
 unsigned regsz; // Tamaño de los registros (caso de longitud fija)
 unsigned ultima; //Apuntador a la última página de la secuencia
 #if (FRAGCABDATOS)
 char frag[FRAGCABDATOS];
 #endif
} CABFILEDT; //Tipo página cabecera fichero datos

#define CABPSZ (4*UINTSZ)
#define ZONADATOSPAGSZ (PAGSZ - CABPSZ)
#define NUMREGPAG (ZONADATOSPAGSZ / REGSZ)
#define FRAGPAGDATSZ (ZONADATOSPAGSZ % REGSZ)

typedef struct PAGDT{
 unsigned pagid;
 unsigned ocupacion;
 unsigned anterior;
 unsigned siguiente;
 REGT reg[NUMREGPAG];
 #if (FRAGPAGDATSZ)
      char frag[FRAGPAGDATSZ];
 #endif
 } PAGDT;

#define SEPSZ UINTSZ
#define APSZ UINTSZ
#define ZDPAGINDSZ (PAGISZ - 3*UINTSZ)
#define ORDEN ((ZDPAGINDSZ+SEPSZ)/(APSZ+SEPSZ))
#define FRAGPAGINDICE (ZDPAGINDSZ - ORDEN*APSZ - (ORDEN-1)*SEPSZ)

typedef struct PAGIT{
 unsigned pagid;
 unsigned ocupacion;
 unsigned altura;
 unsigned sep[ORDEN-1];
 unsigned ap[ORDEN];
 #if (FRAGPAGINDICE)
	 char frag[FRAGPAGINDICE];
 #endif
 } PAGIT;

#define FRAGCABINDICE	(PAGISZ - 5*UINTSZ - 50)

typedef struct CABFILEIT{
 unsigned pagid;
 unsigned ocupacion; // Ocupacion en número de páginas del fichero índice
 unsigned raiz; // pagid de la página raíz del árbol
 unsigned orden; // Orden del árbol
 char nombrefichero[50];
 unsigned pagsz; // Tamaño de las páginas
 #if (FRAGCABINDICE)
  char frag[FRAGCABINDICE];
 #endif
} CABFILEIT;//Tipo página cabecera fichero índice

typedef struct RANGOT{
	unsigned min;
	unsigned max;
}RANGOT;

//************************ PROTOTIPOS DE FUNCIONES
void AperturaSistema(void);
char BuscaRango (unsigned min, unsigned max);
char BuscaReg (unsigned idpedido, REGT *reg);
void CierreSistema(void);
void CreaFicherosSistema (void);
char CreaRaiz(unsigned sep,unsigned api,unsigned apd);
char DividePagInd (unsigned sep, unsigned ap, PAGIT *pagd, unsigned *sepa, unsigned *apa);
char DividePagSec (REGT reg, PAGDT *pagd, unsigned pos, unsigned *sep, unsigned *ap);
char EscribePagina (void *pag, long pgsz, unsigned pagid, FILE *fd);
void GeneraArbolBMas (void);
char InsertaEnPagInd (unsigned sep, unsigned ap, PAGIT *pag);
char InsertaEnPagSec (REGT reg, PAGDT *pag, unsigned pos);
char InsertaReg (REGT reg);
char InsertaRegR (REGT reg, PAGIT *pagact, unsigned *sepa, unsigned *apa);
char LeePagina (void *pagina, long pg_sz, unsigned pagid, FILE *fd);
unsigned ObtenDirDescenso (unsigned idpedido, PAGIT *pag);
char ObtenRegDePag (unsigned idpedido, PAGDT *pag, REGT *reg, unsigned *pos);
char ObtenSgteReg (FILE *fd, REGT *reg);
char ObtenSgteTr(FILE *fd, char *trcode, REGT *reg, RANGOT *rango);
void ProcesaTrans(void);
char *RegistroAString(REGT reg);
void TestPrincipal(void);
FECHAT TraduceFecha (char *fuente);

#endif
