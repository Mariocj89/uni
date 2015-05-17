#pragma once

#include <vector>

#include "constantes.h"
#include "Procesador.h"

using namespace std;

class Cache
{
public:
	Cache(int id, int bloqCaches, FCORRESPONDENCIA funcion,int numCjtos, AREMPLAZAMIENTO algoritmo, PROTOCOLO pCoherencia, int bloqMem, int palBloque,CString ficheroTraza);
	MENSAJEBUS ejecutar();
	bool peticionBus();
	bool BuscarDirMem(long dirMem);
	inline int getId(){return id_cache;}
	void tratarMensajeBus(MENSAJEBUS mensaje);
	void postEscrituras();

		char textoCache[100];

private:
	int id_cache;
	vector<vector<ENTRADA>> datos;
	int nBloques;
	int numCjtos;
	int bloqPorCjto;
	int bloqMem;
	int palBloque;
	PROTOCOLO pCoherencia;
	FCORRESPONDENCIA fCorrespondencia;
	AREMPLAZAMIENTO remplazamiento;
	Procesador proc;

	bool enEspera;
	LINEATRAZA tActual;



	bool BuscarBloque(int idBloque);
	ENTRADA *getEntrada(long dirMem);
	bool IntroducirBloque(int idBloque);

	int dirToEtiqueta(long dirmem);
	int dirToCjto(long dirmem);
	int bloqueToEtiqueta(int dirbloque);
	int bloqueToCjto(int dirbloque);
	int bloqueMasAntiguo(int idConjunto);
	int bloqueMasNuevo(int idConjunto);
	int bloqueLFU(int idConjunto);
	MENSAJEBUS read(long dirmem);
	MENSAJEBUS readX(long dirmem);
	

	void incrementarBV();
};