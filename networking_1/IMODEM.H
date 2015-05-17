
#ifndef IMODEM_H
#define IMODEM_H

#include "string.h"
#include "COMDOS.H"

#include "area.h"
#include "areaman.h"
#include "string.h"
#include "time.h"
#include "dir.h"
#include "process.h"
#include "stdlib.h"


#define CONNECT 0
#define NO_CARRIER 3
#define NO_DIAL_TONE 2
#define ERROR 1
#define TRECFICH 180


class IModem{
public:
	IModem(TCom *Puerto);
	static void Iniciar();

	void PintarPuertos(char nom_puerto[5], int &bps, int &bits, char paridad[9], int &parada);

	void Procesar(char &car, int &salir);
	void Recibir();

private:

	AreaMan recepcion;
	Area informacion;
	Area opciones;
	Area puerto;
	int llamada_entrante;

	FILE *fout;
	FILE *fin;


	static void ProcesarCabecera(char linea[], int &equipoDestino,
		char carpeta[], char *nRings, char &volumen, char &modo); //Trocea una linea obteniendo los datos necesarios
	void PintarOpciones();
	void ObtenModelo();
	void ObtenNRings();
	void ObtenConfig();
	void ModificarVolumen();
	void ModificarAltavoz();
	void ModificarRings();
	void EnviarCorreoModem();
	void EnviarFichero(char filename[]);
	void EscribirFichero();



	class Modem{
	public:
		Modem(TCom *PuertoModem);
		void Enviar(char mensaje[]);
		void Enviar(char c);

		void ModificarVolumen(char &volumen);
		void ModificarAltavoz(char &altavoz);
		void ModificarRings(char *rings);
                int Recibir(char &c);
		void Recibir(char mensaje[], int seg);//Recibe una linea de respuesta

		int Llamar(const int &equipo);
                void Colgar();
		int AceptarLlamada();
		void RechazarLlamada();

	private:
		TCom *PuertoM;
		char ok_msg[10];
	};

	Modem my_modem;
};

#endif //IMODEM_H

