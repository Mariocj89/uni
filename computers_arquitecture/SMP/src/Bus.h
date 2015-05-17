#pragma once

#include "Cache.h"
#include <map>

class Bus
{
public:
	void RegistrarCache(Cache* cache);
	bool comparteCaches(long dirmem, int idPetidora);
	static Bus* getInstancia();
	bool realizarIteracion();
	void indicarProtocoloArbitracion(ARBITRACION pArbi);
	~Bus();


	//variable de cambio de estado
	map<ESTADO_CACHE,map<ESTADO_CACHE,int>> cambios_estado;

	// numero de transiciones de estado
	int numTransBus;
	// numero de bloques tranferidos
	float numBloqTrans;
	// numero de transicioes de estado
	int numTranEstado;
	//aciertos en cache
	int aciertos;
	//fallos en cache
	int fallos;
	//lectura de instruccion
	int instLeidas;
	//accesos a memoria
	int memAccesos;
	//lecturas
	int lecturas;
	//escrituras
	int escrituras;
	//caches activas, con traza pendiente
	bool activo[8];
	Cache* caches[8];

	//Origen del bloque que necesita la cache. -1 = memoria
	int origDat;

	//variable para la actualizacion de la flecha del mensje bus de la cache
	struct TipoFlechaMensajeCache{int id; MENSAJEBUS mensaje;};
	struct TipoFlechaMensajeCache flechaMensajeCache;

private:
	Bus(void);
	int usos[8];
	int ultAccesoAbus[8];
	int numCaches;
	static Bus* instancia;
	ARBITRACION pArbitracion;
};
