/**
 * \file cargador.h
 * \brief Práctica 2006-2007. Declaracion de la clase Cargador
 * \author
 *   \b Profesores LPII \n
 *   \b Asignatura Laboratorio de Programación II \n
 *   \b Curso 07/08 -- Revisado en Curso 08/09
 */

#ifndef CARGADOR_H
#define CARGADOR_H

#include "fichero.h"
#include "prision.h"
#include "preso.h"
#include "guardia.h"

/*!
   \def DEPURAR
   Variable constante utilizada para mostrar o no mensajes de depuración de programa
 */
#define DEPURAR 0

/*!
   \def DEPURAR_MSG
   Macro utilizada para mostrar mensajes de depuración de programa y retener los mensajes en pantalla
 */
//#define DEPURAR_MSG(msg) if (DEPURAR){ cout<<msg; cin.get();}
#define DEPURAR_MSG(msg) if (DEPURAR){ cout<<msg;}


/**
* \def NUMELTOSCONF 
  Indica el número de líneas de configuración diferentes que puede haber en el fichero
*/
#define NUMELTOSCONF 3

using namespace std;

/**
* \class Cargador
* \brief La misión de esta clase es cargar el sistema con los elementos del fichero de configuración
*/
class Cargador
{
    typedef struct DatoMapeo
    {
        char nombre[50];
        int numCampos;
    };

    /**
     * \var mapeo 
     * \brief Vector de Mapeo. Asigna a cada nombre de elemento un valor numérico (posición en el vector) y contiene el número de campos de configuración para cada elemento 
    */
    static DatoMapeo mapeo[NUMELTOSCONF];

    Prision* prision;

    int queElemento(string elto);
    void crearPlanta(int numCampos, string vCampos[kMaxCampos]);
    void crearPreso(int numCampos, string vCampos[kMaxCampos]);
    void crearGuarda(int numCampos, string vCampos[kMaxCampos]);
    
public:
    Cargador(Prision* p);
    void crear(string elto, int numCampos, string vCampos[kMaxCampos]);
};

#endif
