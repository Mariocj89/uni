
#ifndef CATEGORIA_H
#define CATEGORIA_H 

#include "noticias.h"

const int MAX_ELEMENTOS = 10;

typedef Noticia   TipoDato;
typedef TipoDato  vector   [MAX_ELEMENTOS];

/**
 * Clase Categoria, es una lista con punto de interés. Sus atributos son:
 *    - elemento:  Vector de elementos almacenados
 *    - ocupacion: Numero de elementos actual
 *    - pi:        Apuntador al elemento de interes
 *    - id:        Referencia de la categoria
 *    - name:        Nombre de la categoria
 */
class categoria {

  private:
    vector  elemento;
    int     ocupacion;
    int     pi;
    char    id[MaxCadRef]; 
    char    nombre[MaxCadSec];

  public:
   /**
    * @brief Constructor de la clase categoria. Establece el numero de elementos a 0 
    * @pre 
    * @param 
    * @return 
    */
          categoria      ();
    
   /**
     * @brief Copia la categoria de una existente
     * @pre 
     * @param e: la categoria a copiar
     * @return true si la lista esta llena, false en caso contrario
    */    
    bool  Clonar      (categoria &e);
          
   /**
    * @brief Obtiene la referencia de la categoria
    * @pre 
    * @param ref: referencia de la categoria
    * @return 
    */        
    void  Obtener_Referencia(    char    ref[MaxCadRef]);
    
   /**
    * @brief Obtiene el nombre de la categoria
    * @pre 
    * @param name: nombre de la categoria
    * @return 
    */        
    void  Obtener_Nombre(    char    name[MaxCadSec]);
          
   /**
    * @brief Pone la referencia de la categoria
    * @pre 
    * @param ref: futura referencia de la categoria
    * @return 
    */        
    void  Poner_Referencia(const    char    ref[MaxCadRef]);
    
   /**
    * @brief Pone el nombre de la categoria
    * @pre 
    * @param name, futuro nombre de la categoria
    * @return 
    */        
    void  Poner_Nombre(const    char    name[MaxCadSec]);
    
   /**
    * @brief Averigua si una categoria esta vacia
    * @pre 
    * @param 
    * @return true si la categoria esta vacia, false en caso contrario
    */        
    bool  Vacia      ();
    
   /**
     * @brief Averigua si la categoria esta llena
     * @pre 
     * @param 
     * @return true si la categoria esta llena, false en caso contrario
    */    
    bool  Llena      ();
    
   /**
     * @brief Establece el punto de interes al principio de la categoria
     * @pre que la categoria esté creada
     * @param 
     * @return 
    */    
    void  Poner_Inicio     ();
    
   /**
     * @brief Establece el punto de interes al final de la categoria
     * @pre que la categoria esté creada
     * @param 
     * @return 
    */    
    void Poner_Fin ();
    
   /**
     * @brief Avanza el punto de interes de la categoria
     * @pre La categoria debe estar creada
     * @param 
     * @return 
    */    
    void  Avanzar    ();
    
   /**
     * @brief Retrocede el punto de interes de la categoria
     * @pre La categoria debe estar creada
     * @param 
     * @return 
    */    
    void  Retroceder    ();
    
   /**
     * @brief Comprueba si el punto de interes esta al final de la categoria
     * @pre 
     * @param 
     * @return true si el punto de interes esta al final de la categoria, false en caso contrario
    */    
    bool  Fin        ();
    
   /**
     * @brief Comprueba si el punto de interes esta al inicio de la categoria
     * @pre 
     * @param 
     * @return true si el punto de interes esta al inicio de la categoria, false en caso contrario
    */    
    bool  Inicio        ();
    
   /**
     * @brief Inserta un elemento en la categoria
     * @pre que la categoria no este llena
     * @param e elemento a insertar
     * @return true si se a podido insertar correctamente, false en caso contrario
    */    
    bool  Insertar   (const TipoDato &e);
    
   /**
     * @brief Devuelve el elemento apuntado por el punto de interes de la categoria
     * @pre 
     * @param e: Elemento apuntado por el punto de interes
     * @return true si en la posicion apuntada abia un dato, false en caso contrario.
    */    
    bool  Consultar  (      TipoDato &e);
    
   /**
     * @brief Borra el elemento apuntado por el punto de interes
     * @pre 
     * @param 
     * @return true si se a podido borrar correctamente, false en caso contrario
    */    
    bool  Borrar     ();
    
   /**
     * @brief Vacia la categoria
     * @pre 
     * @param 
     * @return 
    */    
    void  Vaciar     ();
};

bool Prueba_Categoria();

#endif
