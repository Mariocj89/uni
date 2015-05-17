/**
* \file registro.cpp
* \brief Implementación de la clase Registro
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "registro.h"

//inicializacion de la unica instancia que existe
Registro* Registro::instancia_ = NULL;

/**
 * Constructor de la clase registro
 */
Registro::Registro()
{
  nombre_fichero_="registro.log";
  f_out_.open(nombre_fichero_);
  if(!f_out_.good()) throw ios::failure("Error de apertura en Registro");
}

/**
 * Destructor de la clase registro
 */
Registro::~Registro()
{
}

/**
 * Obtiene la instancia de la clase
 */
Registro* Registro::get_instancia()
{
  if(instancia_==NULL) instancia_=new Registro;
  return instancia_;
}

/**
 * Metodo que escribe un mensaje en el registro
 * @param mensaje char* a mandar por el flujo
 */
void Registro::Escribir(char * mensaje)
{
  if(instancia_==NULL) instancia_=new Registro;
  f_out_<<mensaje;
  if(!f_out_.good()) throw ios::failure("Error de escritura en Registro");
}

/**
 * Metodo que escribe un mensaje en el registro
 * @param mensaje string a mandar por el flujo
 */
void Registro::Escribir(const string mensaje)
{
  if(instancia_==NULL) instancia_=new Registro;
  f_out_<<mensaje;
  if(!f_out_.good()) throw ios::failure("Error de escritura en Registro");
}

/**
 * Metodo que escribe un mensaje en el registro
 * @param mensaje int a mandar por el flujo
 */
void Registro::Escribir(const int mensaje)
{
  if(instancia_==NULL) instancia_=new Registro;
  f_out_<<mensaje;
  if(!f_out_.good()) throw ios::failure("Error de escritura en Registro");
}

/**
 * Obiene el flujo abierto por la clase
 * @return flujo abierto por la clase
 */
ostream & Registro::Flujo()
{
  if(instancia_==NULL) instancia_=new Registro;
  return f_out_;
}

/**
 * Libera toda la memoria almacenada en la instancia
 */
void Registro::Destruir()
{
  if(instancia_!=NULL){ 
    f_out_.close();
    if(!f_out_.good()) throw ios::failure("Error de cierre en Registro");
    delete instancia_;
    instancia_=NULL;
  }
}
