
#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <vector>

#include "ErrorConfig.h"

using namespace std;

//definiciones del estado actual del bloque la cache, abarca los 3 protocolos
typedef enum ESTADO_CACHE {C_M, C_E, C_S, C_I, C_SC, C_SM, C_NULL };

//Entrada de un bloque de memoria en cache
struct ENTRADA 
{
	int bv;	//se usa como contador en LFU y LRU
	int usados; //para LFU
	long etiqueta;
	ESTADO_CACHE estado;
};

//linea de un fichero de traza
typedef enum TINSTRUCCION {ICAPTURA, INOVALIDO, ILECTURA, IESCRITURA, IVACIO};
struct LINEATRAZA
{
	TINSTRUCCION tIns;
	long dirMem;
};

typedef enum TIPOMENSAJEBUS {M_NULL,M_BUSRD,M_BUSRDX,M_VACIO,M_BUSUPD,M_BUSRDUPD};
//Mensaje que manda una cache a traves del bus
struct MENSAJEBUS
{
	TIPOMENSAJEBUS tipo;
	int dirmem;//en algunos casos se mandara una dirmem
};

//definiciones de los enumerados para la configuracion
typedef enum PROTOCOLO {P_NINIT, P_MSI, P_MESI, P_DRAGON };
typedef enum ARBITRACION {A_NINIT, A_ALEATORIO, A_LRU, A_LFU };
typedef enum FCORRESPONDENCIA {F_NINIT, F_DIRECTA, F_ACONJUNTOS, F_TASOCIATIVA };
typedef enum AREMPLAZAMIENTO {R_NO, R_ALEATORIO, R_LRU, R_FIFO, R_LFU };

//int dirMemToBloq(long dirMem, int tamPalabra, int palabrasPorBloque);
//int dirMemToBloq(long dirMem, int bytesPorBloque);
int dirMemToBloq(long dirmem,int palabrasBloque, int bloqMem);

bool buscarEtiqueta(vector<ENTRADA> vec, long etiqueta);
ENTRADA *obtenerBloque(vector<ENTRADA> &vec, long etiqueta);


PROTOCOLO int2Protocolo(int num, ErrorConfig &error);
ARBITRACION int2Arbitracion(int num, ErrorConfig &error);
FCORRESPONDENCIA int2Correspondencia(int num, ErrorConfig &error);
AREMPLAZAMIENTO int2ARemplazamiento(int num, ErrorConfig &error);

long double log2(const long double & x);


#endif CONSTANTES_H