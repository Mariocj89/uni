#if !defined (_P5_H)
#define _P5_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define BYTESZ 8 //Tama�o de un char en bits

//Determina el byte donde se encuentra el bit dentro de un bitvector
#define EN_BYTE(bit)         ((bit) / BYTESZ)

//m�scara del car�cter que contiene al bit indicado
//por ejemplo el bit 8 est� en el segundo car�cter y su m�scara es:
//10000000
#define MASCARA_BYTE(bit)      (1 << (BYTESZ - 1 - ((bit)  % BYTESZ)))

/* numero de caracteres necesarios para contener los bits */
#define BYTES_BITVECTOR(bits)   ((((bits) - 1) / BYTESZ) + 1)


#define UNOCHAR 0xFF //Byte con todos sus bits a 1

#define USZ 4 //Tama�o del tipo unsigned � int
#define LSZ 4 //Tama�o del tipo long
#define FSZ 4 //Tama�o del tipo float
#define BYTESZ 8 // Tama�o de un byte
#define NUMCAMPOS 6 // N�mero de campos o atributos de la tupla
#define SEPARADOR ';' // Separador utilizado en el fichero de entrada
#define PAGSZ 2048 // Tama�o de las p�ginas de datos
#define MAXNUMREG 3000 //N�mero m�ximo de registros activos esperados
#define NOMFICH_DAT  "pedidos.dat"
#define NOMFICH_FTE  "pedidos.txt"
#define NOMFICH_TRA  "trans.txt"
#define NOMFICH_LOG  "log.txt"
#define EXITO 0x01
#define FRACASO 0x00
#define FICHEROLLENO 0x02
#define ERRFUERADERANGO 0x03
#define FACTORCARGA ((float)0.7)

// ******************* DEFINICION DE LOS TIPOS DE DATOS PARA LAS TUPLAS
typedef struct FECHAT{
 char dia, mes, anio;
 } FECHAT;

#define FECHATSZ 3
typedef unsigned int CLAVET; //Por si deseamos variar el tipo de la clave primaria del registro
#define CLAVETSZ USZ

typedef struct REGT{
 char                   codcli[5];
 CLAVET                 idpedido; //Clave primaria
 char                   nombre[40];
 char                   ciudad[15];
 FECHAT                 fecha;
 float                  importe;
 } REGT;

#define REGSZ (60 + CLAVETSZ + FECHATSZ + FSZ) //Tama�o del registor

// *************** DEFINICION DE TIPOS Y CONSTANTES PARA LAS PAGINAS DEL
// *************** FICHERO DE DATOS

//La p�gina de datos tendr� una cabecera con dos partes:
//Una parte fija:
    // Pagid
    // Ocupaci�n
//Una parte dependiente del tama�o de p�gina y de la tupla:
    //Vector de bits
//Para calcular este tama�o vamos a considerar que el vector
//de bits ocupa zona de datos de la p�gina

#define CABPAGSZ (2*USZ)
#define ZDPSZ (PAGSZ - CABPAGSZ) //Zona de datos de la p�gina
//Vamos a considerar que cada tupla lleva asociado un bit extra
//que ocupar� 1/8 del bitvector. Con este dato ya podemos derivar
//el n�mero de tuplas por p�gina (NRP) de la f�rmula:
    // ZDPSZ >= NRP * (REGSZ + 1/8)
    // ZDPSZ / (REGSZ + 1/8) >= NRP
    // 8*ZDPSZ / (8*REGSZ + 1) >= NRP

#define NRP ( 8*ZDPSZ / (8*REGSZ + 1))

//Ya conocemos el n�mero de registos por p�gina
//ahora podemos saber el n�mero m�nimo de p�ginas
//para el fichero hash
#define NMINPAG (MAXNUMREG*NRP)

//El factor de carga del fichero hash nos dir�
//cuantas p�ginas va a tener definitivamente el fichero

//Podemos declarar el tama�o del bitvector
//Necesitamos un bitvector de NRP bits, pero esto hay que
//calcularlo en n�mero de bytes y no de bits

#if (NRP % BYTESZ)
        #define BITVPSZ ((NRP / BYTESZ) + 1)
#else
        #define BITVPSZ (NRP / BYTESZ)
#endif

typedef char BITVP[BITVPSZ];

#define FRAGPAG (ZDPSZ - BITVPSZ - NRP*REGSZ)

typedef struct PAGT{
 unsigned pagid;
 unsigned ocupacion;
 BITVP          bitv;
 REGT           reg[NRP];
 #if (FRAGPAG)
      char frag[FRAGPAG];
 #endif
 } PAGT; //Tipo para las p�ginas del fichero hash


// Se define el tipo para la p�gina cabecera del fichero de datos
#define FRAGCABDATOS (PAGSZ - 4*USZ - LSZ - 50)

typedef struct CABFILET{
 unsigned pagid;
 unsigned ocupacion; // N�mero de p�ginas de datos asignadas al fichero
 unsigned long nregactivos; //N�mero de registros activos del fichero
 char           filename[50];
 unsigned pagsz; // Tama�o de las p�ginas
 unsigned regsz; // Tama�o de los registros (caso de longitud fija)
 #if (FRAGCABDATOS)
 char resto[FRAGCABDATOS];
 #endif
} CABFILET;

//************************ PROTOTIPOS DE FUNCIONES
void ActivaBit(unsigned char *bitv, unsigned numbits, unsigned bit);
char AperturaSistema(void);
char BorraRegistro(unsigned idpedido);
char BuscaRegEnPag(unsigned idpedido, PAGT *pag, unsigned *pos,char *lapida);
char BuscaRegistro(unsigned idpedido, REGT *reg, unsigned *pagid, char *lapida, unsigned *intentos);
char CargaFicheroHash(void);
char CierreSistema(void);
char CreaFicheroHash(void);
void DesactivaBit(unsigned char *bitv, unsigned numbits, unsigned bit);
char EsBitActivo (unsigned char *bitv, unsigned numbits, unsigned bit);
char EscribePagina (void *pag, long pgsz, unsigned pagid, FILE *fd);
char EsPrimo(unsigned long val);
unsigned long Hash(unsigned clave);
char InsertaRegistro(REGT reg);
char LeePagina (void *pag, long pgsz, unsigned pagid, FILE *fd);
float LongitudMediaBusqueda();
unsigned NBAChar(unsigned char c);
unsigned NumeroBitsActivos (unsigned char *bitv, unsigned numbits);
char ObtenSgteReg (FILE *fd, REGT *reg);
char ObtenSgteTr(FILE *fd, char *trcode, REGT *reg);
unsigned PrimerBitActivo (unsigned char *bitv, unsigned numbits);
unsigned PrimerBitNoActivo (unsigned char *bitv, unsigned numbits);
unsigned long PrimoMasCercano(unsigned long val);
void ProcesaTrans(void);
char *RegistroAString(REGT reg);
char SlotBorrado(PAGT *pag, unsigned slot);
void TestPrincipal(void);
FECHAT TraduceFecha (char *fuente);

#endif
