
#ifndef GESTOR_H
#define GESTOR_H
#include <fstream>
#include <iostream>

#include "lpi.h"

using namespace std;


const int MAX_IDENT = 10;
typedef char Tcadena[MAX_IDENT];

/**
 * Clase GESTOR. Sus atributos son:
 *    - l. Lista
 * Es un interfaz sobre la clase lista
 */
class gestor {

  private:
    lista list;
    Tcadena1 contadorN;
    char contadorC[MaxCadRef];

    
   /**
     * Aumenta el contador de noticias contadorN.
     * @pre debe tener un valor entre N000 y N998.
     * @param
     * @return 
    */    
    void Aumentar_contadorN();
    
   /**
     * Aumenta el contador de categorias contadorC.
     * @pre debe tener un valor entre S0 y S5
     * @param
     * @return true si se a podido aumentar, false en caso contrario.
    */    
    bool Aumentar_contadorC();

    
   /**
     * Reduce el contador de categorias contadorC.
     * @pre debe tener un valor entre S0 y S5
     * @param
     * @return true si se a podido reducir, false en caso contrario.
    */    
    bool  Reducir_contadorC();

  public:
    
   /**
     * Constructor por defecto de la clase gestor, inicia los contadores. 
     * @pre 
     * @param
     * @return 
    */    
          gestor   ();

    
   /**
     * Destructor de la clase gestor. 
     * @pre 
     * @param
     * @return 
    */    
         ~gestor   ();

    
   /**
     * Inserta una noticia en orden, en una categoria especifica.
     * @pre n debe estar inicializado
     * @param n: Noticia a insertar.
     * @return true si se a podido insertar bien false en caso contrario.
    */    
    bool  Insertar (const Noticia &n);
    
   /**
     * Inserta una categoria en orden.
     * @pre 
     * @param
     * @return true si se a podido insertar bien false en caso contrario.
    */    
    bool  Insertar_Categoria();
    
   /**
     * Muestra todas las noticias por categorias y en orden.
     * @pre 
     * @param
     * @return 
    */    
    void  Mostrar  ();
    
   /**
     * Muestra todas las categorias con el numero de noticias ke tienen.
     * @pre 
     * @param
     * @return 
    */    
    void  Mostrar_Categorias();
    
   /**
     * Muestra una categoiria con una referencia especifica.
     * @pre 
     * @param ref: referencia de la seccion a mostrar.
     * @return 
    */    
    void  Mostrar_Categoria(const char ref[MaxCadRef]);
    
   /**
     * Elimina una noticia especifica
     * @pre 
     * @param ident: identificador de la noticia a borrar.
     * @return true si se a eliminado correctamente false en caso contrario.
    */    
    bool  Eliminar (Tcadena ident);
    
   /**
     * Elimina una categoria especifica
     * @pre 
     * @param ref: referencia de la categoria a borrar.
     * @return true si se a eliminado correctamente false en caso contrario.
    */    
    bool  Eliminar_Categoria(char ref[MaxCadRef]);
    
   /**
     * Busca una noticia y la muestra
     * @pre 
     * @param ident: identificador de la noticia a buscar.
     * @return true si se a encontrado false en caso contrario.
    */    
    bool  Buscar(Tcadena ident);
    
   /**
     * Guarda el blog en un archivo.
     * @pre 
     * @param nombre: donde se guardara el blog
     * @return true si se a guardado correctamente false en caso contrario.
    */    
    bool  Guardar(char nombre[20]);
    
   /**
     * Cargar un blog de un archivo.
     * @pre 
     * @param nombre: de donde se cargara el blog
     * @return true si se a cargado correctamente false en caso contrario.
    */   
    bool  Cargar(char nombre[20]);
    
   /**
     * Obtiene contadorN
     * @pre 
     * @param cad1: cadena donde se guardara contadorN
     * @return
    */   
    void  Obtener_ContadorN(Tcadena1 cad1);
    
   /**
     * Obtiene contadorC
     * @pre 
     * @param cad1: cadena donde se guardara contadorC
     * @return
    */   
    void  Obtener_ContadorC(Tcadena1 cad1);
    
   /**
     * Pide una noticia al usuario
     * @pre 
     * @param Dat: noticia donde se guardaran los datos
     * @return
    */   
    void  Pedir_Noticia(TipoDato &Dat);
    
   /**
     * Busca una cadena en el titulo subtitulo o contenido de todas las noticias y la muestra.
     * @pre 
     * @param cad1: cadena que se busca.
     * @return true si se ha encontrado alguna coincidencia, false en caso contrario.
    */   
    bool  Buscar_Cadena(Tcadena3 cad1);
};

    
   /**
     * Pasa cad1 a cad2 en minusculas
     * @pre 
     * @param cad1: cadena que se quiere convertir.
     * @param cad2: cadena convertida.
     * @return
    */   
    void Pasar_Minusculas(const Tcadena3 cad1, Tcadena3 cad2);

#endif
