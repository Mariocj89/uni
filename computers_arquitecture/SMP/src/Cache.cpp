#include "StdAfx.h"
#include <algorithm>
#include "Cache.h"
#include "Bus.h"

Cache::Cache(int id, int bloqCaches, FCORRESPONDENCIA funcion,int numCjtos, AREMPLAZAMIENTO algoritmo, PROTOCOLO pCoherencia , int bloqMem, int palBloque,CString ficheroTraza)
:proc(ficheroTraza)
{
	id_cache = id;
	this->nBloques = bloqCaches;
	if(numCjtos == 0) numCjtos = 1;
	if(funcion == F_DIRECTA)
	{
		bloqPorCjto = 1;
		numCjtos = bloqCaches;
	}
	else
	{
		bloqPorCjto = bloqCaches / numCjtos;
	}
	this->numCjtos = numCjtos;
	this->palBloque = palBloque;
	this->bloqMem = bloqMem;

	//Inicializacion de datos
	ENTRADA aux;
	aux.bv=0;
	aux.usados = 0;
	aux.estado = C_I;
	aux.ultimoUso = 0;
	vector<ENTRADA> vecAux;
	for(int j=0;j<bloqPorCjto;j++)
		vecAux.push_back(aux);
	for(int i=0;i<numCjtos;i++)
		datos.push_back(vecAux);
	fCorrespondencia = funcion;

	Bus::getInstancia()->RegistrarCache(this);


	fCorrespondencia = funcion;
	this->pCoherencia = pCoherencia;
	this->remplazamiento = algoritmo;
	enEspera = false;
}



int Cache::bloqueToEtiqueta(int dirbloque)
{
	return dirbloque / numCjtos;
}

int Cache::bloqueToCjto(int dirbloque)
{
	return dirbloque % numCjtos;
}

int Cache::dirToEtiqueta(long dirMem)
{
	return bloqueToEtiqueta(dirMemToBloq(dirMem,bloqMem,palBloque));
}

int Cache::dirToCjto(long dirMem)
{
	return bloqueToCjto(dirMemToBloq(dirMem,bloqMem,palBloque));
}

bool Cache::BuscarBloque(int idBloque)
{
	if(buscarEtiqueta(datos[bloqueToCjto(idBloque)],bloqueToEtiqueta(idBloque))) return true;
	return false;
}

bool Cache::IntroducirBloque(int idBloque)
{
	bool finded = false;
	for(int i = 0; i< bloqPorCjto && !finded; i++)
		if(datos[bloqueToCjto(idBloque)][i].bv == 0)
		{
			datos[bloqueToCjto(idBloque)][i].bv = 1;
			datos[bloqueToCjto(idBloque)][i].usados = 0;
			datos[bloqueToCjto(idBloque)][i].etiqueta = bloqueToEtiqueta(idBloque);
			finded = true;
		}
	if(finded) return true;//fallo forzoso

	//REMPLAZO
	//si esta en M o S hay que hacer postescritura
	int bloqdestino = 0;
	switch(remplazamiento)
	{
		case R_ALEATORIO:
			bloqdestino = rand()%bloqPorCjto;
			break;
		case R_LFU:
			bloqdestino = bloqueLFU(bloqueToCjto(idBloque));
			break;
		case R_LRU:
			bloqdestino = bloqueMasAntiguamenteUsado(bloqueToCjto(idBloque));
			break;
		case R_FIFO:
			bloqdestino = bloqueMasAntiguo(bloqueToCjto(idBloque));
			break;

	}
	//tratamiento del remplazamiento y la postescritura si necesario
	ESTADO_CACHE estado = datos[bloqueToCjto(idBloque)][bloqdestino].estado;
	if(estado == C_M || estado == C_SM)
	{
		Bus::getInstancia()->numBloqTrans++;
		Bus::getInstancia()->numTransBus++;
		Bus::getInstancia()->cambios_estado[estado][C_I]++;
		Bus::getInstancia()->numTranEstado++;
	}

	datos[bloqueToCjto(idBloque)][bloqdestino].estado = C_I;
	datos[bloqueToCjto(idBloque)][bloqdestino].bv = 1;
	datos[bloqueToCjto(idBloque)][bloqdestino].usados = 0;
	datos[bloqueToCjto(idBloque)][bloqdestino].etiqueta = bloqueToEtiqueta(idBloque);
	datos[bloqueToCjto(idBloque)][bloqdestino].ultimoUso = Bus::getInstancia()->memAccesos;
	return false;//fallo que implica la salida de un dato
}

int Cache::bloqueMasAntiguo(int idConjunto)
{
	int aux = 0;
	for(int i = 0;i<bloqPorCjto; i++)
	{
		if(datos[idConjunto][i].bv > datos[idConjunto][aux].bv) aux = i;
	}
	return aux;
}

int Cache::bloqueMasAntiguamenteUsado(int idConjunto)
{
	int aux = 0;
	for(int i = 0;i<bloqPorCjto; i++)
	{
		if(datos[idConjunto][i].ultimoUso < datos[idConjunto][aux].ultimoUso) aux = i;
	}
	return aux;
}

int Cache::bloqueLFU(int idConjunto)
{
	int aux = 0;
	for(int i = 0;i<bloqPorCjto; i++)
	{
		if(datos[idConjunto][i].bv !=0 && datos[idConjunto][i].usados/(1.0*datos[idConjunto][i].bv) < datos[idConjunto][aux].usados/(1.0*datos[idConjunto][aux].bv)) 
			aux = i;
	}
	return aux;	
}

int Cache::bloqueMasNuevo(int idConjunto)
{
	int aux = 0;
	for(int i = 0;i<bloqPorCjto; i++)
	{
		if(datos[idConjunto][i].bv < datos[idConjunto][aux].bv && datos[idConjunto][i].bv !=0) aux = i;
	}
	return aux;
}

void Cache::incrementarBV()
{
	for(int i = 0; i < numCjtos; i++)
		for(int j = 0; j < bloqPorCjto; j++)
			if(datos[i][j].bv != 0)datos[i][j].bv++;
}

MENSAJEBUS Cache::ejecutar()
{
	enEspera = false;
	if(tActual.tIns == IVACIO)
	{
		MENSAJEBUS mensajevacio;
		mensajevacio.tipo= M_VACIO;
		return mensajevacio;
	}
	//si no tiene la 
	if(!BuscarDirMem(tActual.dirMem))
	{
		IntroducirBloque(dirMemToBloq(tActual.dirMem,bloqMem,palBloque));
		MENSAJEBUS mensaje;
		mensaje.dirmem = tActual.dirMem;
		if(tActual.tIns != IESCRITURA)
			mensaje.tipo = M_BUSRD;
		else
			mensaje.tipo = M_BUSRDX;
		Bus::getInstancia()->fallos++;
	}else
	{
		Bus::getInstancia()->aciertos++;
	}
	Bus::getInstancia()->memAccesos++;
	getEntrada(tActual.dirMem)->ultimoUso = Bus::getInstancia()->memAccesos;
	getEntrada(tActual.dirMem)->usados++;
	switch(tActual.tIns)
	{
	case ICAPTURA: Bus::getInstancia()->instLeidas++;return read(tActual.dirMem);break;
	case ILECTURA: Bus::getInstancia()->lecturas++;
		return read(tActual.dirMem);break;
	case IESCRITURA:Bus::getInstancia()->escrituras++;
		return readX(tActual.dirMem);break;
	}
}

MENSAJEBUS Cache::read(long dirmem)
{
	Bus::getInstancia()->numTranEstado++;

	incrementarBV();
	MENSAJEBUS mensaje;
	mensaje.dirmem = dirmem;
	ENTRADA *entrada = getEntrada(dirmem);
	mensaje.dirmem = dirmem;
	ESTADO_CACHE estado_siguiente;
	estado_siguiente = C_NULL;
	switch (pCoherencia)
		{
		case P_MSI:
			switch(entrada->estado)
			{
			case C_I: mensaje.tipo = M_BUSRD;
				estado_siguiente = C_S;
				break;
			case C_S: mensaje.tipo= M_NULL;break;
			case C_M: mensaje.tipo= M_NULL;break;
			}
		break;
		case P_MESI:
			switch(entrada->estado)
			{
			case C_I: mensaje.tipo = M_BUSRD;
				if(Bus::getInstancia()->comparteCaches(dirmem, id_cache))
					estado_siguiente = C_S;
				else
					estado_siguiente = C_E;
				break;
			case C_S: mensaje.tipo= M_NULL;
				break;					  
			case C_E: mensaje.tipo= M_NULL;
				break;
			case C_M: mensaje.tipo= M_NULL;
				break;
			}
		break;
		case P_DRAGON:
			switch(entrada->estado)
			{
			case C_I: mensaje.tipo=M_BUSRD;
				if(Bus::getInstancia()->comparteCaches(dirmem,id_cache))
					estado_siguiente = C_SC;
				else
					estado_siguiente = C_E;
				break;
			case C_E: mensaje.tipo = M_NULL;
				break;
			case C_M: mensaje.tipo = M_NULL;
				break;
			case C_SC: mensaje.tipo = M_NULL;
				break;
			case C_SM: mensaje.tipo = M_NULL;
				break;
			}
		break;
		}
	if(estado_siguiente == C_NULL)
		estado_siguiente = entrada->estado;
	Bus::getInstancia()->cambios_estado[entrada->estado][estado_siguiente]++;
	entrada->estado = estado_siguiente;
	return mensaje;
}

MENSAJEBUS Cache::readX(long dirmem)
{
	Bus::getInstancia()->numTranEstado++;
	

	incrementarBV();
	MENSAJEBUS mensaje;
	mensaje.dirmem = dirmem;
	ENTRADA* entrada = getEntrada(dirmem);
	ESTADO_CACHE estado_siguiente;
	estado_siguiente = C_NULL;
	switch (pCoherencia)
		{
		case P_MSI:
			switch(entrada->estado)
			{
			case C_I: mensaje.tipo = M_BUSRDX;
				estado_siguiente = C_M;
				break;
			case C_S:  mensaje.tipo = M_BUSRDX;
				estado_siguiente = C_M;
				break;
			case C_M: mensaje.tipo= M_NULL;break;
			}
		break;
		case P_MESI:
			switch(entrada->estado)
			{
			case C_I: mensaje.tipo = M_BUSRDX;
				estado_siguiente = C_M;
				break;
			case C_S:  mensaje.tipo = M_BUSRDX;
				estado_siguiente = C_M;
				break;					  
			case C_E: mensaje.tipo= M_NULL;
				estado_siguiente = C_M;
				break;
			case C_M: mensaje.tipo= M_NULL;
				break;
			}
		break;
		case P_DRAGON:
			switch(entrada->estado)
			{
			case C_I: 
				if(Bus::getInstancia()->comparteCaches(dirmem,id_cache))
				{
					mensaje.tipo=M_BUSRDUPD;
					Bus::getInstancia()->numBloqTrans+=1.0/palBloque;
					estado_siguiente = C_SM;
				}
				else
					estado_siguiente = C_M;
				break;
			case C_E: estado_siguiente = C_M;mensaje.tipo = M_NULL;
				break;
			case C_M: mensaje.tipo = M_NULL;
				break;
			case C_SC: 
				if(Bus::getInstancia()->comparteCaches(dirmem,id_cache))
					estado_siguiente = C_SM;
				else
					estado_siguiente = C_M;
				mensaje.tipo = M_BUSUPD;
				Bus::getInstancia()->numBloqTrans+=1.0/palBloque;
				break;
			case C_SM:
				if(Bus::getInstancia()->comparteCaches(dirmem,id_cache))
					mensaje.tipo = M_BUSUPD;
				else
				{
					estado_siguiente = C_M;
					mensaje.tipo = M_BUSUPD;
				}
				Bus::getInstancia()->numBloqTrans+=1.0/palBloque;
				break;
			}
		break;
		}
	if(estado_siguiente == C_NULL)
		estado_siguiente = entrada->estado;
	Bus::getInstancia()->cambios_estado[entrada->estado][estado_siguiente]++;
	entrada->estado = estado_siguiente;
	return mensaje;
}

void Cache::tratarMensajeBus(MENSAJEBUS mensaje)
{
	if(!BuscarDirMem(mensaje.dirmem)) return;
	Bus::getInstancia()->origDat = this->getId();
	Bus::getInstancia()->numTranEstado++;
	ESTADO_CACHE estado_siguiente;
	estado_siguiente = C_NULL;

	ENTRADA* entrada = getEntrada(mensaje.dirmem);
	switch (pCoherencia)
		{
		case P_MSI:
			switch(entrada->estado)
			{
			case C_I: break;
			case C_S: if(mensaje.tipo == M_BUSRDX)
					  {
						  estado_siguiente = C_I;entrada->bv=0;
					  }
						
				break;
			case C_M: if(mensaje.tipo == M_BUSRD)
					  {
						  estado_siguiente = C_S;
						  Bus::getInstancia()->numTransBus++;
						  //tratar vaciado(flechas)
					  }
					  else 
					  {
						estado_siguiente = C_I;entrada->bv=0;
						//tratar vaciado(flechas)
					  }
				break;
			}
		break;
		case P_MESI:
			switch(entrada->estado)
			{
			case C_I:break;
			case C_S: if(mensaje.tipo == M_BUSRD){}
					  else 
					  {
						estado_siguiente = C_I;entrada->bv=0;
					  }
				break;					  
			case C_E: if(mensaje.tipo == M_BUSRD)
					  {
						estado_siguiente = C_S;
					  }
					  else 
					  {
						estado_siguiente = C_I;entrada->bv=0;
					  }
				break;
			case C_M: if(mensaje.tipo == M_BUSRD)
					  {
						estado_siguiente = C_S;
						Bus::getInstancia()->numTransBus++;
						//tratar vaciado(flechas)
					  }
					  else 
					  {
						estado_siguiente = C_I;entrada->bv=0;
						//tratar vaciado(flechas)
					  }
				break;
			}
		break;
		case P_DRAGON:
			switch(entrada->estado)
			{
				case C_E: if(mensaje.tipo== M_BUSRD)estado_siguiente = C_SC;break;
				case C_SC: if(mensaje.tipo== M_BUSUPD) {} break;//	TODO: ACTUALIZA = SI
				case C_SM: 
					if(mensaje.tipo== M_BUSUPD) 
					{
						estado_siguiente = C_SC;
						//TODO: ACTUAliza
					}else
					{
						//TODO: datbus
					}					   
							   break;
				case C_M: if(mensaje.tipo== M_BUSRD) 
							  estado_siguiente = C_SM;
							  //TODO: datbus
							  break;
			}
		break;
		}
	if(estado_siguiente == C_NULL)
		estado_siguiente = entrada->estado;
	Bus::getInstancia()->cambios_estado[entrada->estado][estado_siguiente]++;
	entrada->estado = estado_siguiente;
}

//Lee la siguiente linea y devuelve si necesitará acceso a bus
bool Cache::peticionBus()
{
	if(!enEspera)
	{
		tActual = proc.getLinea();
	}
		enEspera = true;
		if(tActual.tIns == IVACIO)
		{
			return false;//El procesador a terminado
		}
		if(!BuscarDirMem(tActual.dirMem))
		{
			if(tActual.tIns != IESCRITURA)
				sprintf_s(textoCache,"\nPrRd\n%d",dirMemToBloq(tActual.dirMem,bloqMem,palBloque));
			else
				sprintf_s(textoCache,"\nPrWr\n%d",dirMemToBloq(tActual.dirMem,bloqMem,palBloque));
			return true;
		}
		if(tActual.tIns != IESCRITURA)
			sprintf_s(textoCache,"*\nPrRd\n%d",dirMemToBloq(tActual.dirMem,bloqMem,palBloque));
		else
			sprintf_s(textoCache,"*\nPrWr\n%d",dirMemToBloq(tActual.dirMem,bloqMem,palBloque));
		//El bloque esta en la cache
		switch (pCoherencia)
		{
		case P_MSI:
			switch(getEntrada(tActual.dirMem)->estado)
			{
			case C_I: return true;
			case C_S: if(tActual.tIns == IESCRITURA) return true;
					  else return false;
			case C_M: return false;
			}
		break;
		case P_MESI:
			switch(getEntrada(tActual.dirMem)->estado)
			{
			case C_I: return true;
			case C_S: if(tActual.tIns == IESCRITURA) return true;
					  else return false;
			case C_E: return false;
			case C_M: return false;
			}
		break;
		case P_DRAGON:
			switch(getEntrada(tActual.dirMem)->estado)
			{
			case C_I: return true;
			case C_E: return false;
			case C_M: return false;
			case C_SC: if(tActual.tIns == IESCRITURA) return true;
					  else return false;
			case C_SM: if(tActual.tIns == IESCRITURA) return true;
					  else return false;
			}
		break;
		}
		return false;
}

ENTRADA *Cache::getEntrada(long dirMem)
{
	int idBloque = dirMemToBloq(dirMem,bloqMem,palBloque);
	ENTRADA* ent =obtenerBloque(datos[bloqueToCjto(idBloque)],bloqueToEtiqueta(idBloque));
	return ent;
}

bool Cache::BuscarDirMem(long dirMem)
{
	return BuscarBloque(dirMemToBloq(dirMem,bloqMem,palBloque));
}

void Cache::postEscrituras()
{
	int i,j;
	for(i = 0;i< datos.size();i++)
	{
		for(j = 0;j< datos[i].size();j++)
		{
			if(datos[i][j].estado == C_M)
			{
				Bus::getInstancia()->numBloqTrans++;
				Bus::getInstancia()->numTransBus++;
				Bus::getInstancia()->numTranEstado++;
				switch(pCoherencia)
				{
					case P_MSI: Bus::getInstancia()->cambios_estado[datos[i][j].estado][C_S]++;
					case P_MESI: Bus::getInstancia()->cambios_estado[datos[i][j].estado][C_E]++;
					case P_DRAGON: Bus::getInstancia()->cambios_estado[datos[i][j].estado][C_E]++;
				}
			}
			if(datos[i][j].estado == C_SM)
			{
				Bus::getInstancia()->numBloqTrans++;
				Bus::getInstancia()->numTransBus++;
				Bus::getInstancia()->numTranEstado++;
				switch(pCoherencia)
				{
					case P_DRAGON: Bus::getInstancia()->cambios_estado[datos[i][j].estado][C_SC]++;
				}
			}
		}
	}
}