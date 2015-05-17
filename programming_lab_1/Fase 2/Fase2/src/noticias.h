#ifndef NOTICIAS_H
#define NOTICIAS_H

#include <fstream>
#include "fecha.h"


using namespace std;


const int MaxCad1=10;
const int MaxCad2=40;
const int MaxCad3=200;



typedef char Tcadena1[MaxCad1];
typedef char Tcadena2[MaxCad2];
typedef char Tcadena3[MaxCad3];


/**
 * Clase Noticia, guarda la informacion referente a una noticia. Sus atributos son:
 *    - Ident_N:  Cadena de caracteres que indica el identificador de la noticia.
 *    - Titulo: Cadena de caracteres que indica el titulo de la noticia.
 *    - SubTitulo: Cadena de caracteres que indica el subtitulo de la noticia.
 *    - Contenido: Cadena de caracteres que indica el subtitulo de la noticia.
 *    - Imagen: Cadena de caracteres que indica la imagen de la noticia.
 *    - Fecha: Este atributo es del tipo "fecha" y guarda la fecha de la noticia.
 */
class Noticia {
	Tcadena1 Ident_N;
	Tcadena2 Titulo;
        Tcadena2 SubTitulo;
	Tcadena3 Contenido;
	Tcadena2 Imagen;
	fecha Fecha_N;
	
public:

   /**
    * @brief Constructor por defecto de la clase Noticia. Establece el identificador con: ""; 
    * @pre 
    * @param 
    * @return 
    */
	Noticia();

   /**
    * @brief Constructor parametrizado de la clase Noticia. Establece el identificador con Id; 
    * @pre 
    * @param Id: cadena de caracteres usada para inicializar el identificador de la noticia.
    * @return 
    */
	Noticia (const Tcadena1 Id);

   /**
    * @brief Constructor por copia de la clase Noticia. Establece todos los elementos obteniendolos de J. 
    * @pre 
    * @param J: Noticia origen que se va a usar para establecer la Noticia tratada.
    * @return 
    */
	Noticia (const Noticia &J);

   /**
    * @brief Copia la clase Noticia. Establece todos los elementos obteniendolos de J. 
    * @pre J debe estar inicializada.
    * @param J: Noticia origen que se va a usar para establecer la Noticia tratada.
    * @return 
    */
	void Clonar (const Noticia &J);
        

   /**
    * @brief Pone un identificador a la noticia.
    * @pre
    * @param I: Cadena a insertar como identificador en la noticia.
    * @return 
    */
	void Poner_Identificador(Tcadena1 I);

   /**
    * @brief Pone un Titulo a la noticia.
    * @pre
    * @param T: Cadena a insertar como titulo en la noticia.
    * @return 
    */
	void Poner_Titulo(Tcadena2 T);

   /**
    * @brief Pone un Subtitulo a la noticia.
    * @pre
    * @param ST: Cadena a insertar como subtitulo en la noticia.
    * @return 
    */
	void Poner_SubTitulo(Tcadena2 ST);

   /**
    * @brief Pone un contenido a la noticia.
    * @pre
    * @param C: Cadena a insertar como contenido en la noticia.
    * @return 
    */
	void Poner_Contenido(Tcadena3 C);

   /**
    * @brief Pone una imagen a la noticia.
    * @pre
    * @param Im: Cadena a insertar como imagen en la noticia.
    * @return 
    */
	void Poner_Imagen(Tcadena2 Im);

   /**
    * @brief Pone una fecha a la noticia.
    * @pre
    * @param F: Fecha a insertar como fecha en la noticia.
    * @return 
    */
	void Poner_Fecha (const fecha &F);



   /**
    * @brief Obtiene el identificador de la noticia.
    * @pre
    * @param T: Cadena a la que se copiara el identificador de la noticia.
    * @return 
    */
	void Obtener_Identificador (Tcadena1 &T)const ;

   /**
    * @brief Obtiene el titulo de la noticia.
    * @pre
    * @param T: Cadena a la que se copiara el titulo de la noticia.
    * @return 
    */
	void Obtener_Titulo (Tcadena2 &T)const ;

   /**
    * @brief Obtiene el subtitulo de la noticia.
    * @pre
    * @param ST: Cadena a la que se copiara el subtitulo de la noticia.
    * @return 
    */
	void Obtener_SubTitulo (Tcadena2 &ST)const ;

   /**
    * @brief Obtiene la fecha de la noticia.
    * @pre
    * @param F: Fecha a la que se copiara la fecha de la noticia.
    * @return 
    */
	void Obtener_Fecha(fecha &F)const ;

   /**
    * @brief Obtiene el contenido de la noticia.
    * @pre
    * @param C: Cadena a la que se copiara el contenido de la noticia.
    * @return 
    */
	void Obtener_Contenido (Tcadena3 &C)const ;

   /**
    * @brief Obtiene la imagen de la noticia.
    * @pre
    * @param Im: Cadena a la que se copiara la imagen de la noticia.
    * @return 
    */
        void Obtener_Imagen(Tcadena2 &Im) const;



   /**
    * @brief Compara el identificador de la noticia actual, con el identificador c.
    * @pre
    * @param c: cadena a comparar con el identificador de la noticia.
    * @return  1 si c es menor, 0 si son iguales y -1 si c es mayor.
    */
        int  Comparar(Tcadena1 c) const;
        

   /**
    * @brief Muestra la noticia en pantalla.
    * @pre
    * @param
    * @return 
    */
	void Mostrar_Noticia() const;

   /**
    * @brief Guarda la noticia en un fichero
    * @pre
    * @param salida: ofstream
    * @return 
    */
	void Guardar_Noticia(ofstream &salida);

   /**
    * @brief Carga la noticia de un fichero
    * @pre
    * @param entrada: ifstream
    * @return 
    */
	void Cargar_Noticia(ifstream &entrada);


   /**
    * @brief Pide por pantalla los datos de una noticia(salco el contador) y lo inserta en la noticia.
    * @pre
    * @param contador: cadena para insertar el identificador
    * @return 
    */
	void PedirNoticia(Tcadena1  contador);

	~Noticia();

};

void Prueba_Noticias();

#endif
