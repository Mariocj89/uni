
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
     * Inserta una categoria. La categoria se pide por pantalla.
     * @pre 
     * @param
     * @return true si se a podido insertar bien false en caso contrario.
    */    
    bool  Insertar_Categoria();
    
   /**
     * Inserta una categoria. El nombre de la categoria se pide por pantalla.
     * @pre ref debe encontrarse entre S1 y S5, y no puede tomar un valor de una categoria ya existente
     * @param ref: Referencia de la categoria
     * @return true si se a podido insertar bien false en caso contrario.
    */    
    bool Insertar_Categoria(const TcadRef ref);
    
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
    
   /**
     * Inserta una noticia en la categoria determinada por Sec, un identificador de categoria. Si no existe la seccion se intentara crear.
     * @par ATENCION:
		Este modulo se ha diseñado principalmente para inicializar el blog, por lo cual, SE INSERTARA LA NOTICIA CON EL IDENTIFICADOR QUE TRAIGA y NO SE BORRARAN NOTICIAS DE LAS CATEGORIAS QUE ESTEN LLENAS PARA INSERTAR ESTA.
     * @par Si contadorN es menor que el identificador de la noticia, contadorN se sustituira por el identificador de la noticia.
     * @pre 
     * @param Not: Noticia que se va a insertar.
     * @param Sec: Identificador de la seccion en la que se va a insertar la noticia.
     * @return true si se ha insertado correctamente, false en caso contrario.
    */   
    bool Insertar_Noticia_Con_Categoria(const TipoDato &Not, const TcadRef Ref);

    
   /**
     * Inserta una noticia en la categoria determinada por Sec, un nombre de categoria. 
     * @par ATENCION:
		Este modulo se ha diseñado principalmente para inicializar el blog, por lo cual, SE INSERTARA LA NOTICIA CON EL IDENTIFICADOR QUE TRAIGA y NO SE BORRARAN NOTICIAS DE LAS CATEGORIAS QUE ESTEN LLENAS PARA INSERTAR ESTA.
     * @par Si contadorN es menor que el identificador de la noticia, contadorN se sustituira por el identificador de la noticia.
     * @pre La categoria Sec tiene que existir.
     * @param Not: Noticia que se va a insertar.
     * @param Sec: Nombre de la seccion en la que se va a insertar la noticia.
     * @return true si se ha insertado correctamente, false en caso contrario.
    */   
    bool Insertar_Noticia_Con_Categoria2(const TipoDato &Not, const TcadSec Sec);

    
   /**
     * Guarda todos los datos de el blog en un archivo binario, blog.dat.
     * @pre Debe permitirse escribir en el archivo blog.dat.
     * @return true si se ha guardado correctamente, false en caso contrario.
    */   
    bool Guardar_Binario();
    
   /**
     * Carga todos los datos en el blog de un archivo binario, blog.dat.
     * @pre Debe permitirse lectura en el archivo blog.dat y el blog debe estar VACIO.
     * @return true si se ha cargado correctamente, false en caso contrario.
    */   
    bool Iniciar_Binario();
    
   /**
     * Carga todos los datos en el blog de dos archivos de texto. Secciones.txt y Noticias.txt.
     * @pre Deben existir los 2 archivos con un encabezamiento especial, de dos lineas.
     * @return true si se ha cargado correctamente, false en caso contrario.
    */   
    bool Iniciar_Texto();
    
   /**
     * Guarda todas las noticias en HTML para visualizarlas como una pagina web.
     * @pre Se debe poder acceder a los archivos con el nombre de cada seccion.
     * @return true si se ha guardado correctamente, false en caso contrario.
    */   
    bool Crear_Html();
};

    
   /**
     * Pasa cad1 a cad2 en minusculas
     * @pre 
     * @param cad1: cadena que se quiere convertir.
     * @param cad2: cadena convertida.
     * @return
    */   
    void Pasar_Minusculas(const Tcadena3 cad1, Tcadena3 cad2);

    
   /**
     * Le quita los espacios a cad.
     * @pre 
     * @param cad: cadena a la que se le quitaran los espacios
     * @return
    */   
void Quitar_Espacios(Tcadena3 cad);

#endif
