#include "StdAfx.h"
#include "constantes.h"
#include <cmath>

/*int dirMemToBloq(long dirMem, int tamPalabra, int palabrasPorBloque)
{
	return dirMem/((tamPalabra*palabrasPorBloque)/8);
}

int dirMemToBloq(long dirMem, int bytesPorBloque)
{
	return dirMem/bytesPorBloque;
}*/

int dirMemToBloq(long dirmem,int palabrasBloque, int bloqMem)
{
	return (dirmem/palabrasBloque)%bloqMem;
}

bool buscarEtiqueta(vector<ENTRADA> vec, long etiqueta)
{
		vector<ENTRADA>::iterator p;
		p = vec.begin();
		do{
			if(p->bv != 0 && p->estado !=C_I && p->etiqueta == etiqueta) return true;
			++p;
		}while(p != vec.end());
		return false;
}

ENTRADA* obtenerBloque(vector<ENTRADA> &vec, long etiqueta)
{
		for(int i = 0; i< vec.size(); i++)
		{
			if(vec[i].bv != 0 && vec[i].etiqueta == etiqueta) return &(vec[i]);
		}
		throw "Error en obtenerBloque";
}

PROTOCOLO int2Protocolo(int num, ErrorConfig &error)
{
	switch (num)
	{
	case 1: return P_MSI;
	case 2: return P_MESI;
	case 3: return P_DRAGON;
	default: error.add(_T("Error en la configuracion del protocolo de coherencia cache!"));
	}
}

ARBITRACION int2Arbitracion(int num, ErrorConfig &error)
{
	switch (num)
	{
	case 1: return A_ALEATORIO;
	case 2: return A_LRU;
	case 3: return A_LFU;
	default: error.add(_T("Error en la configuracion del protocolo de arbitracion bus!"));
	}
}

FCORRESPONDENCIA int2Correspondencia(int num, ErrorConfig &error)
{
	switch (num)
	{
	case 1:return F_DIRECTA;
	case 2:return F_ACONJUNTOS;
	case 3:return F_TASOCIATIVA;
	default: error.add(_T("Error en la configuracion de la funcion de correspondencia cache!"));
	}
}

AREMPLAZAMIENTO int2ARemplazamiento(int num, ErrorConfig &error)
{
	switch (num)
	{
	case 0:return R_NO;
	case 1:return R_ALEATORIO;
	case 2:return R_LRU;
	case 3:return R_FIFO;
	case 4:return R_LFU;
	default: error.add(_T("Error en la configuracion del protocolo de remplazamiento cache!"));
	}
}

long double log2(const long double & x)
{
	return log(x)/log(2.0);

}