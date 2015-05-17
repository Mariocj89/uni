/*
 * P3.h
 *
 *  Created on: 04/11/2009
 *      Author: Mario
 */

#ifndef P3_H_
#define P3_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BYTESZ 8 //Tamaño de un char en bits

//Determina el byte donde se encuentra el bit dentro de un bitvector
#define EN_BYTE(bit)         ((bit) / BYTESZ)

//máscara del carácter que contiene al bit indicado
//por ejemplo el bit 8 está en el segundo carácter y su máscara es:
//10000000
#define MASCARA_BYTE(bit)      (1 << (BYTESZ - 1 - ((bit)  % BYTESZ)))

// numero de caracteres necesarios para contener los bits
#define BYTES_BITVECTOR(bits)   ((((bits) - 1) / BYTESZ) + 1)


#define UNOCHAR 0xFF //Byte con todos sus bits a 1

#define NUMCAMPOS 6 // N£mero de campos o atributos de la tupla
#define SEPARADOR ';' // Separador utilizado en el fichero de entrada
#define PAGINDTSZ PAGSZ
#define MAXENTRADASIND 1100// N£mero m ximo de entradas que tendr  la tabla ¡ndice
#define MAXNUMPAGDATOS 500 // N£mero m ximo de p ginas del fichero de datos
#define ACTUALIZADO 0 //Significado del valor del campo estado...
#define OBSOLETO 1 //...relativo al archivo que guarda una copia del índice simple
#define NOMFICH_DAT  "pedidos.dat"
#define NOMFICH_NDX  "pedidos.ndx"
#define NOMFICH_FTE  "pedidos.txt"
#define NOMFICH_TRA  "trans.txt"
#define NOMFICH_LOG  "log.txt"
#define UINTSZ 4
#define FLOATSZ 4
#define ERRFUERADERANGO 2
#define ERRINDICEEXHAUSTO 3
#define ERRARCHIVOEXHAUSTO 4
#define ERRCLAVEDUPLICADA 5
#define EXITO 1
#define FRACASO 0
#define HUECO 0 //Significado del valor de un bit...
#define ACTIVO 1 //...para el bitvector de página
#define CONHUECOS 0 //Significado del valor de un bit...
#define SINHUECOS 1 //...para el bitvector de la página cabecera
#define PAGSZ 1024
#define DEBUG 1

// ******************* DEFINICION DE LOS TIPOS DE DATOS
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

//La página de datos tendrá una cabecera con dos partes:
//Una parte fija:
    // Pagid
    // Ocupación
//Una parte dependiente del tamaño de página y de la tupla:
    //Vector de bits
//Para calcular este tamaño vamos a considerar que el vector
//de bits ocupa zona de datos de la página

#define CABPSZ (2*UINTSZ)
#define ZONADATOSPAGSZ (PAGSZ - CABPSZ)
    // ZONADATOSPAGSZ >= NTP * (REGSZ + 1/8)
    // ZONADATOSPAGSZ / (REGSZ + 1/8) >= NTP
    // 8*ZONADATOSPAGSZ / (8*REGSZ + 1) >= NTP

#define NUMREGPAG ( 8*ZONADATOSPAGSZ / (8*REGSZ + 1))
#define NUMMAXREG (unsigned)(MAXNUMPAGDATOS*NUMREGPAG)

//Ya podemos declarar el tamaño del bitvector
// Necesitamos un bitvector de NUMREGPAG bits, pero esto hay que
//calcularlo en número de bytes y no de bits

#if (NUMREGPAG % BYTESZ)
	#define BITVPSZ ((NUMREGPAG / BYTESZ) + 1)
#else
	#define BITVPSZ (NUMREGPAG / BYTESZ)
#endif

// Tipo del bitvector para la página de datos
typedef unsigned char BITVPT[BITVPSZ];

// Tamaño de la zona de fragmentación
#define VECTORREGSZ (NUMREGPAG*REGSZ)

#define FRAGPAGDATSZ (ZONADATOSPAGSZ - (BITVPSZ + VECTORREGSZ))

typedef struct PAGDT{
 unsigned pagid;
 unsigned ocupacion;
 BITVPT bitvector;
 REGT reg[NUMREGPAG];
 #if (FRAGPAGDATSZ)
      char frag[FRAGPAGDATSZ];
 #endif
 } PAGDT;

// El vector de bits para el fichero deber  tener un bit por cada posible
// p gina almacenada en el fichero. Como el n£mero m ximo de p ginas se
// almacena en la constante MAX_NUM_PAG_DATOS, el n£mero de bytes necesarios
// ser  el entero inmediatamente superior a MAX_NUM_PAG_DATOS/BYTE_SZ

#if (MAXNUMPAGDATOS % BYTESZ)
	#define BITVECTORFILESZ ((MAXNUMPAGDATOS / BYTESZ) + 1)
#else
	#define BITVECTORFILESZ (MAXNUMPAGDATOS / BYTESZ)
#endif

// Vector de bits para el fichero
typedef unsigned char BITVECTORFILE[BITVECTORFILESZ];

// Se define el tipo para la p gina cabecera del fichero de datos
#define FRAGCABDATOS (PAGSZ - 4*UINTSZ - BITVECTORFILESZ - 50)

typedef struct CABFILEDT{
 unsigned pagid;
 unsigned ocupacion; // Número de páginas de datos asignadas al fichero
 BITVECTORFILE bitvector; //Vector de bits que almacena el estado de cada página del fichero.
 char nombrefichero[50];
 unsigned pagsz; // Tamaño de las páginas
 unsigned regsz; // Tamaño de los registros (caso de longitud fija)
 #if (FRAGCABDATOS)
 char resto[FRAGCABDATOS];
 #endif
} CABFILEDT; //Tipo página cabecera fichero datos

typedef struct ENTRADAINDICET{
 unsigned idpedido; // Valor de clave
 unsigned pagid; // Identificador de p gina
 unsigned posreg; // Posición del registro dentro de la p gina
 } ENTRADAINDICET;

#define ENTRADAINDICETSZ (3*UINTSZ)

//Tipo para el índice simple
typedef ENTRADAINDICET IST[NUMMAXREG];

#define NUMENTRADASPAG (PAGSZ - 2*UINTSZ)/ENTRADAINDICETSZ
#define FRAGPAGIND ((PAGSZ - 2*UINTSZ)%ENTRADAINDICETSZ)

typedef struct PAGIT{
 unsigned pagid;
 unsigned ocupacion;
 ENTRADAINDICET entrada[NUMENTRADASPAG];
 #if (FRAGPAGINDICE)
	 char frag[FRAGPAGINDICE];
 #endif
 } PAGIT;

// Tipo para la página cabecera del archivo para la salvaguarda del índice
#define FRAGCABINDICE	(PAGSZ - 5*UINTSZ - 50)

typedef struct CABFILEIT{
 unsigned pagid;
 unsigned ocupacion; // Ocupacion en número de páginas del fichero índice
 unsigned numentradas; // Número de entradas que contiene actualmente el índice simple
 char nombrefichero[50];
 unsigned pagsz; // Tamaño de las páginas
 unsigned entsz; // Tamaño de los entradas
 #if (FRAGCABINDICE)
  char frag[FRAGCABINDICE];
 #endif
} CABFILEIT;//Tipo página cabecera fichero índice



//************************ PROTOTIPOS DE FUNCIONES
void ActivaBit(unsigned char *bitv, unsigned numbits, unsigned bit);
char AperturaSistema(void);
char BorraRegistro (unsigned idpedido);
char BuscaEnIndice (unsigned clave, unsigned *pos);
char BuscaRegistro(unsigned clave, REGT *reg);
void CargaIS(FILE *fi);
void CierreSistema (void);
void ClearAllBitvector (unsigned char *bitv, unsigned numbits);
void CreaFichero (const char *filename, void *pag, long pgsz);
void CreaFicheroSistema (void);
void DesactivaBit(unsigned char *bitv, unsigned numbits, unsigned bit);
char EliminaEntradaIS(unsigned pos);
char EsBitActivo (unsigned char *bitv, unsigned numbits, unsigned bit);
char EscribePagina (void *pag, long pgsz, unsigned pagid, FILE *fd);
char GeneraPedidosDat (void);
char InsertaEntradaISOrden (ENTRADAINDICET ent);
char InsertaEntradaISPos(ENTRADAINDICET ent, unsigned pos);
char InsertaRegistro (REGT reg);
char LeePagina (void *pagina, long pg_sz, unsigned pagid, FILE *fd);
char LocalizaDestinoRegistro (PAGDT *pag, unsigned *posreg);
unsigned NBAChar(unsigned char c);
unsigned NumeroBitsActivos (unsigned char *bitv, unsigned numbits);
char ObtenSgteReg (FILE *fd, REGT *reg);
char ObtenSgteTr(FILE *fd, char *trcode, REGT *reg);
unsigned PrimerBitActivo (unsigned char *bitv, unsigned numbits);
unsigned PrimerBitNoActivo (unsigned char *bitv, unsigned numbits);
void ProcesaTrans(void);
void ReconstruyeIS(void);
char *RegistroAString(REGT reg);
char SalvaguardaIS (char *filename);
void SetAllBitvector(unsigned char * bitv, unsigned numbits);
void TestPrincipal(void);
FECHAT TraduceFecha (char *fuente);
unsigned char ValorBit(unsigned char *bitv, unsigned numbits, unsigned bit);


#endif /* P3_H_ */
