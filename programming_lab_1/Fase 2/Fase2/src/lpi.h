
#ifndef LISTA_H
#define LISTA_H 

#include "categoria.h"

const int Max_Categorias = 5;



/**
 * Clase LISTA con punto de interés. Sus atributos son:
 *    - elemento:  Vector de elementos almacenados
 *    - ocupacion: Numero de elementos actual 
 *    - pi:        Apuntador al elemento de interes
 */
class lista {

  private:
    categoria  elemento[Max_Categorias];
    int     ocupacion;
    int     pi;

  public:
   /**
    * Constructor de la clase lista. Establece el numero de elementos a 0 
    * @pre 
    * @param 
    * @return 
    */
          lista      ();
    
   /**
    * Obtiene la ocupacion de la lista
    * @pre 
    * @param 
    * @return el numero de categorias en la lista.
    */
    int   ocupadas   () const;
    
   /**
    * Averigua si una lista esta vacia
    * @pre 
    * @param 
    * @return true si la lista esta vacia, false en caso contrario
    */        
    bool  vacia      ();
    
   /**
     * Averigua si la lista esta llena
     * @pre 
     * @param 
     * @return true si la lista esta llena, false en caso contrario
    */    
    bool  llena      ();
    
   /**
     * Establece el punto de interes al principio de la lista
     * @pre que la lista esté creada
     * @param 
     * @return 
    */    
    void  poner_inicio     ();
    
   /**
     * Establece el punto de interes al final de la lista
     * @pre que la lista esté creada
     * @param 
     * @return 
    */    
    void poner_fin ();
    
   /**
     * Avanza el punto de interes de la lista
     * @pre La lista debe estar creada
     * @param 
     * @return 
    */    
    void  avanzar    ();
    
   /**
     * Retrocede el punto de interes de la lista
     * @pre La lista debe estar creada
     * @param 
     * @return 
    */    
    void  retroceder    ();
    
   /**
     * Comprueba si el punto de interes esta al final de la lista
     * @pre 
     * @param 
     * @return true si el punto de interes esta al final de la lista, false en caso contrario
    */    
    bool  fin        ();
    
   /**
     * Comprueba si el punto de interes esta al inicio de la lista
     * @pre 
     * @param 
     * @return true si el punto de interes esta al inicio de la lista, false en caso contrario
    */    
    bool  inicio        ();
    
   /**
     * Inserta una categoria en la lista
     * @pre que la lista no este llena
     * @param e: elemento a insertar
     * @return 
    */    
    bool  insertar   (categoria &e);
    
   /**
     * Devuelve el elemento apuntado por el punto de interes de la lista
     * @pre 
     * @param e: Elemento apuntado por el punto de interes
     * @return 
    */    
    bool  consultar  (categoria &e);
    
   /**
     * Borra el elemento apuntado por el punto de interes
     * @pre 
     * @param 
     * @return 
    */    
    bool  borrar     ();
    
   /**
     * Introduce una noticia en la categoria señalada por el pi
     * @pre 
     * @param e: la noticia a inertar
     * @return true si se a podido insertar, false en caso contrario.
    */    
    bool insertar_Noticia (const TipoDato &e);
    
   /**
     * Borrar una noticia
     * @pre 
     * @param cad: referencia de la noticia a borrar.
     * @return true si se a podido insertar, false en caso contrario.
    */    
    bool borrar_Noticia (Tcadena1 cad);
};

bool Prueba_Lista();

#endif
