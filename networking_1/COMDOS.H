/*****************************************************************************/
/*                                                                           */
/*        COMDOS - Librer�a de control de puertos RS232-C bajo MSDOS         */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  COMDOS.H Archivo de cabecera para COMDOS.LIB                             */
/*                                                                           */
/*  Declara la clase TCom, que proporciona m�todos para la gesti�n de los    */
/*  circuitos de datos y de control de un puerto RS-232C.                    */
/*                                                                           */
/*  (C) 2002,2003 - Alfonso Gazo Cervero (agazo@unex.es)                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  Hist�rico de cambios:                                                    */
/*                                                                           */
/*  Versi�n 0.11 (25/01/2005)                                                */
/*      - Adaptaci�n de TCom al comportamiento err�neo del driver de Windows */
/*        XP al abrir el puerto                                              */
/*                                                                           */
/*  Versi�n 0.10 (03/11/2003)                                                */
/*      - Correcci�n de TCom::<< (char *)                                    */
/*      - Incorporaci�n de los m�todos AbrirPuerto y CerrarPuerto            */
/*      - Incorporaci�n de control de existencia del hardware del puerto     */
/*      - Optimizaci�n del manejo de los Buffer FIFO de las UART             */
/*                                                                           */
/*  Versi�n 0.9.2 (16/12/2002):                                              */
/*      - Correcci�n de TCom::BPS()                                          */
/*                                                                           */
/*  Versi�n 0.9.1 (19/11/2002):                                              */
/*      - Incorporaci�n de el m�todo TCom::Puerto() para identificar el      */
/*        puerto asignado a la instancia                                     */
/*      - Correcci�n de TCom::EstablecerParidad(enumParidad)                 */
/*      - Implementaci�n de TCom::BPS()                                      */
/*                                                                           */
/*  Versi�n 0.9.0 (04/11/2002):                                              */
/*      - Versi�n inicial para las pr�cticas de SCD/Redes Curso 2002/2003    */
/*                                                                           */
/*****************************************************************************/

#ifndef __COMDOS_H
#define __COMDOS_H

#ifndef __DOS_H
	#include <dos.h>
#endif


//
// Declaraci�n de constantes de par�metros de funcionamiento del puerto
//

// Identificaci�n del puerto
enum enumPuertos {
	COM1 =  0x01,   // Puerto COM1
	COM2 =  0x02,   // Puerto COM2
	COM3 =  0x03,   // Puerto COM3
	COM4 =  0x04    // Puerto COM4
};

// Descripci�n del tipo de paridad
enum enumParidad {
	NINGUNO = 0x00,
	IMPAR	= 0x01,
	PAR	= 0x03,
	MARCA	= 0x05,
	ESPACIO	= 0x07
};

// Descripci�n de los c�digos de retorno devueltos al abrir o cerrar el puerto
enum enumError {
	ERR_NOERR		= 0x00, // Resultado correcto
	ERR_NOEXISTEPUERTO	= 0x01, // El puerto seleccionado no existe
	ERR_PUERTOYAABIERTO	= 0x02, // Ya hay un puerto abierto por TCom
	ERR_PUERTOCERRADO	= 0x03  // El puerto ya estaba cerrado
};

// Descripci�n del tipo de chip UART (s�lo para m�todo privado TipoUART)
enum enumTipoUART {
	NO_UART		= 0x00,	// No se encontr� un chip UART
	INS8250		= 0x01, // UART INS8250, INS8250-B
	NS16450		= 0x02, // UART INS8250A, INST82C50A, NS16450, NS16C450
	NS16550A	= 0x03, // UART NS16550A
	NS16C552	= 0x04  // UART NS16C552
};

//
// Declaraci�n de la clase de control
//

class TCom {
	
private:
	unsigned char estadoInstancia;

	void Inicializacion(); // Inicializaci�n del handler de interrupciones
	enumTipoUART TipoUART(void); // Descripci�n del tipo de UART
	void EstablecerBufferFIFO(unsigned char); // Establecimiento tama�o FIFO
	
public:
	//
	// Constructores / Destructores
	//
	
	TCom(void);
   	~TCom(void);

	//
	// Apertura y Cierre del puerto
	//
	
	enumError AbrirPuerto (	
		enumPuertos,			// Idenfificador del puerto
    		unsigned long 	= 9600,		// N�mero de bits por segundo
    		int 		= 8,		// N�mero de bits de datos
    		enumParidad 	= NINGUNO, 	// Tipo de paridad
    		int 		= 1 );		// N�mero de bits de parada
	enumError CerrarPuerto(void);	
	enumPuertos Puerto(void);

	//
	// Gesti�n de los par�metros de operaci�n de los circuitos de datos
	//
	
	// N�mero de bits por segundo
	void EstablecerBPS(unsigned long);
	unsigned long BPS(void);
	
	// N�mero de bits por car�cter
	void EstablecerBitsDatos(int);
	int BitsDatos(void);
	
	// Tipo de paridad
	void EstablecerParidad(enumParidad);
	enumParidad Paridad();
	
	// N�mero de bits de parada
	void EstablecerBitsParada(int);
	int BitsParada(void);


	//
	// Gesti�n de los circuitos de control
	//
	
	// Data Terminal Ready (lectura y escritura)
	int EstadoDTR(void);
	void ActivarDTR(void);
	void DesactivarDTR(void);

	// Request To Send (lectura y escritura)
	int EstadoRTS(void);
	void ActivarRTS(void);
	void DesactivarRTS(void);
	
	// Data Set Ready (solo lectura)
	int EstadoDSR(void);
	
	// Clear To Send (solo lectura)
	int EstadoCTS(void);
	
	// Ring Indicator (solo lectura)
	int EstadoRI(void);
	
	// Data Carrier Detect (solo lectura)
	int EstadoDCD(void);


	//
	// Sobrecarga de operadores
	//

	TCom &operator<<(char);		// Env�o de un car�cter
	TCom &operator<<(char *);	// Env�o de una cadena
	TCom &operator>>(char &);	// Recepci�n de un car�cter


	//
	// Gesti�n de buffers
	//
	
	// Obtenci�n del n�mero de elementos presentes
	// en cada uno de los b�ffer
	int OcupacionBufferEntrada(void);
	int OcupacionBufferSalida(void);
	
	// Vaciado de los b�ffer
	void VaciarBufferEntrada(void);
	void VaciarBufferSalida(void);
	void VaciarBuffers(void) 
		{ VaciarBufferEntrada(), VaciarBufferSalida(); };
	
	
	//
	// Descripci�n de la clase
	//
	
	const char *Version(void);
	const char *Descripcion(void);
};


#endif // __COMDOS_H
