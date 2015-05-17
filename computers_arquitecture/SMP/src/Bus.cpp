#include "StdAfx.h"
#include "Bus.h"

Bus* Bus::instancia = NULL;

Bus::Bus(void)
{
	numCaches=0;
	numTransBus = 0;
	numBloqTrans =0;
	numTranEstado = 0;
	aciertos = 0;
	fallos = 0;
	instLeidas = 0;
	memAccesos = 0;
	lecturas = 0;
	escrituras = 0;
	aciertos = 0;
	fallos = 0;
	for(int i = 0; i<8;i++)
	{
		usos[i] = 0;
		ultAccesoAbus[i] = 0;
		activo[i] = true;
	}
	
	for(int h = 0; h< 6; h++)
	{
		for(int j = 0; j< 6; j++)
			cambios_estado[(ESTADO_CACHE)h][(ESTADO_CACHE)j] = 0;		
	}
}

bool Bus::comparteCaches(long dirmem, int idPetidora)
{
	bool res = false;
	for(int i = 0;i<numCaches; i++)
	{
		if(caches[i]->getId()!= idPetidora) res = res || caches[i]->BuscarDirMem(dirmem);
	}
	return res;
}

Bus* Bus::getInstancia()
{
	if(instancia == NULL) instancia = new Bus();
	return instancia;
}

void Bus::RegistrarCache(Cache* cache)
{
	caches[numCaches++] = cache;
}

//true = queda por ejecutar, false = trazas finalizadas
bool Bus::realizarIteracion()
{
	flechaMensajeCache.id = -1;
	origDat = -1;
	bool peticionesBus[8]={false};
	int cachesAArbitrar[8];
	int numCachesAArbitrar = 0;
	for(int i =0;i< numCaches;i++)
		if(activo[i]) peticionesBus[i] = caches[i]->peticionBus();
		else peticionesBus[i] = false;

	for(int i=0;i<numCaches;i++)
	{
		if(activo[i]){
			if(peticionesBus[i]) cachesAArbitrar[numCachesAArbitrar++] = i;
			else if(caches[i]->ejecutar().tipo == M_VACIO)//no guardamos el mensaje, pues va a ser NULL o VACIO
			{
				activo[i] = false;
			}
		}
	}
	if(numCachesAArbitrar != 0) 
	{
		//Aplicar el algoritmo
		int elegida;
		switch(pArbitracion)
		{
		case A_ALEATORIO:
			elegida = cachesAArbitrar[rand()%numCachesAArbitrar];
			break;
		case A_LRU:
			int minimo;
			minimo = ultAccesoAbus[cachesAArbitrar[0]];
			elegida = cachesAArbitrar[0];
			for(int i = 1 ; i< numCachesAArbitrar; i++)
			{
				if( ultAccesoAbus[cachesAArbitrar[i]] < minimo)
				{
					elegida = cachesAArbitrar[i];
					minimo = ultAccesoAbus[cachesAArbitrar[i]];
				}
			}
			break;
		case A_LFU:
			float minimo2;
			minimo2 = usos[cachesAArbitrar[0]]/(float)numTransBus;
			elegida = cachesAArbitrar[0];
			for(int i = 1 ; i< numCachesAArbitrar; i++)
			{
				if(usos[cachesAArbitrar[i]]/(float)numTransBus < minimo2)
				{
					elegida = cachesAArbitrar[i];
					minimo2 = usos[cachesAArbitrar[i]]/(float)numTransBus;
				}
			}
			break;
		}
		MENSAJEBUS mensaje = caches[elegida]->ejecutar();
		numTransBus++;
		if(mensaje.tipo != M_BUSUPD)
			numBloqTrans++;
		ultAccesoAbus[elegida] = numTransBus;
		usos[elegida]++;
		flechaMensajeCache.id = caches[elegida]->getId();
		flechaMensajeCache.mensaje = mensaje;
		if(mensaje.tipo == M_BUSRDUPD)//si se produce 1 busrd y busupd son 2 mensajes realmente
		{
			numTransBus++;
			mensaje.tipo = M_BUSRD;
			for(int i = 0;i< numCaches;i++)
			{
				if(i != elegida)
				{
					caches[i]->tratarMensajeBus(mensaje);
				}
			}
			mensaje.tipo = M_BUSUPD;
			for(int i = 0;i< numCaches;i++)
			{
				if(i != elegida)
				{
					caches[i]->tratarMensajeBus(mensaje);
				}
			}
		}
		else
		{
			for(int i = 0;i< numCaches;i++)
			{
				if(i != elegida)
				{
					caches[i]->tratarMensajeBus(mensaje);
				}
			}
		}
	}
	//Vemos si ha terminado
	bool nofin = false;
	for(int i = 0; i< numCaches; i++)
	{
		nofin = nofin || activo[i];
	}
	if(!nofin)
	{
		AfxMessageBox(_T("A continuacion se realizaran las postescrituras"));
		for(int i = 0;i<numCaches;i++)
			caches[i]->postEscrituras();
	}
	return nofin;
}

void Bus::indicarProtocoloArbitracion(ARBITRACION parbi)
{
	this->pArbitracion=parbi;
}

Bus::~Bus()
{
	for(int i = 0; i<numCaches; i++)
		delete caches[i];
	instancia = NULL;
}