/*****************************************************************************/
/*                                                                           */
/*        COMDOS - Librería de control de puertos RS232-C bajo MSDOS         */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  COMDOS.H Archivo de cabecera para COMDOS.LIB                             */
/*                                                                           */
/*  Declara la clase TCom, que proporciona métodos para la gestión de los    */
/*  circuitos de datos y de control de un puerto RS-232C.                    */
/*                                                                           */
/*  (C) 2002,2003 - Alfonso Gazo Cervero (agazo@unex.es)                     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  Histórico de cambios:                                                    */
/*                                                                           */
/*  Versión 0.11 (25/01/2005)                                                */
/*      - Adaptación de TCom al comportamiento erróneo del driver de Windows */
/*        XP al abrir el puerto                                              */
/*                                                                           */
/*  Versión 0.10 (03/11/2003)                                                */
/*      - Corrección de TCom::<< (char *)                                    */
/*      - Incorporación de los métodos AbrirPuerto y CerrarPuerto            */
/*      - Incorporación de control de existencia del hardware del puerto     */
/*      - Optimización del manejo de los Buffer FIFO de las UART             */
/*                                                                           */
/*  Versión 0.9.2 (16/12/2002):                                              */
/*      - Corrección de TCom::BPS()                                          */
/*                                                                           */
/*  Versión 0.9.1 (19/11/2002):                                              */
/*      - Incorporación de el método TCom::Puerto() para identificar el      */
/*        puerto asignado a la instancia                                     */
/*      - Corrección de TCom::EstablecerParidad(enumParidad)                 */
/*      - Implementación de TCom::BPS()                                      */
/*                                                                           */
/*  Versión 0.9.0 (04/11/2002):                                              */
/*      - Versión inicial para las prácticas de SCD/Redes Curso 2002/2003    */
/*                                                                           */
/*****************************************************************************/

#ifndef __COMDOS_H
#define __COMDOS_H

#ifndef __DOS_H
	#include <dos.h>
#endif


//
// Declaración de constantes de parámetros de funcionamiento del puerto
//

// Identificación del puerto
enum enumPuertos {
	COM1 =  0x01,   // Puerto COM1
	COM2 =  0x02,   // Puerto COM2
	COM3 =  0x03,   // Puerto COM3
	COM4 =  0x04    // Puerto COM4
};

// Descripción del tipo de paridad
enum enumParidad {
	NINGUNO = 0x00,
	IMPAR	= 0x01,
	PAR	= 0x03,
	MARCA	= 0x05,
	ESPACIO	= 0x07
};

// Descripción de los códigos de retorno devueltos al abrir o cerrar el puerto
enum enumError {
	ERR_NOERR		= 0x00, // Resultado correcto
	ERR_NOEXISTEPUERTO	= 0x01, // El puerto seleccionado no existe
	ERR_PUERTOYAABIERTO	= 0x02, // Ya hay un puerto abierto por TCom
	ERR_PUERTOCERRADO	= 0x03  // El puerto ya estaba cerrado
};

// Descripción del tipo de chip UART (sólo para método privado TipoUART)
enum enumTipoUART {
	NO_UART		= 0x00,	// No se encontró un chip UART
	INS8250		= 0x01, // UART INS8250, INS8250-B
	NS16450		= 0x02, // UART INS8250A, INST82C50A, NS16450, NS16C450
	NS16550A	= 0x03, // UART NS16550A
	NS16C552	= 0x04  // UART NS16C552
};

//
// Declaración de la clase de control
//

class TCom {
	
private:
	unsigned char estadoInstancia;

	void Inicializacion(); // Inicialización del handler de interrupciones
	enumTipoUART TipoUART(void); // Descripción del tipo de UART
	void EstablecerBufferFIFO(unsigned char); // Establecimiento tamaño FIFO
	
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
    		unsigned long 	= 9600,		// Número de bits por segundo
    		int 		= 8,		// Número de bits de datos
    		enumParidad 	= NINGUNO, 	// Tipo de paridad
    		int 		= 1 );		// Número de bits de parada
	enumError CerrarPuerto(void);	
	enumPuertos Puerto(void);

	//
	// Gestión de los parámetros de operación de los circuitos de datos
	//
	
	// Número de bits por segundo
	void EstablecerBPS(unsigned long);
	unsigned long BPS(void);
	
	// Número de bits por carácter
	void EstablecerBitsDatos(int);
	int BitsDatos(void);
	
	// Tipo de paridad
	void EstablecerParidad(enumParidad);
	enumParidad Paridad();
	
	// Número de bits de parada
	void EstablecerBitsParada(int);
	int BitsParada(void);


	//
	// Gestión de los circuitos de control
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

	TCom &operator<<(char);		// Envío de un carácter
	TCom &operator<<(char *);	// Envío de una cadena
	TCom &operator>>(char &);	// Recepción de un carácter


	//
	// Gestión de buffers
	//
	
	// Obtención del número de elementos presentes
	// en cada uno de los búffer
	int OcupacionBufferEntrada(void);
	int OcupacionBufferSalida(void);
	
	// Vaciado de los búffer
	void VaciarBufferEntrada(void);
	void VaciarBufferSalida(void);
	void VaciarBuffers(void) 
		{ VaciarBufferEntrada(), VaciarBufferSalida(); };
	
	
	//
	// Descripción de la clase
	//
	
	const char *Version(void);
	const char *Descripcion(void);
};


#endif // __COMDOS_H
