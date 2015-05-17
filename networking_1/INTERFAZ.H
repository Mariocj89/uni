

#ifndef INTERFAZ_H
#define INTERFAZ_H

#include "string.h"
#include "COMDOS.H"
//#include "stdio.h"
#include "dir.h"
#include "process.h"
#include "area.h"

class Interfaz{
public:
	Interfaz();
	static void Iniciar();

	void MostrarEstados(TCom &Puerto);
	void PintarPuertos(char nom_puerto[5], int &bps, int &bits, char paridad[9], int &parada);

	void Enviar(TCom &Puerto, int &salir, char car, int &contador);
	void Envio(char caracter);
	void Recepcion(char caracter);
	void Informacion(char mensaje[]);
	void RecibirFichero(TCom &Puerto, int &salir, int &contador);
	void EnviarCorreo(TCom &Puerto, int &salir, int &contador);
	/*void DistribuirCorreo(TCom &Puerto, int &salir, int &contador);
	void RecibirCorreo(TCom &Puerto, int &salir, int &contador); */

private:
	Area envio;
	Area recepcion;
	Area informacion;
	Area puerto;
	Area control;
	Area opciones;

	FILE *fichero;

	void PintarControl();
	int EnviarFichero(TCom &Puerto, int &salir, int &contador, char filename[]);





};




#endif //INTERFAZ_H