/**
 * \file fichero.h
 * \brief Declaracion de la clase FicheroCarga
 * \date 09/04/09
 * \author
 *   \b Nombre: Mario \n
 *   \b Apellidos: Corchero Jimenez \n
 *   \b Asignatura Laboratorio de Programacion II \n
 */

#ifndef FICHERO_H
#define FICHERO_H

#include <fstream>
#include <iostream>
#include <cstring>



/**
* \var kMaxCampos
* \brief Constante con el numero maximo de campos de una linea del fichero de configuracion
*/
const int kMaxCampos = 8;

/*!
   \def kDepurarFichero
   Variable constante utilizada para mostrar o no mensajes de depuracion de programa
 */
#define kDepurarFichero 0

/*!
   \def DEPURAR_FICHERO_MSG
   Macro utilizada para mostrar mensajes de depuración de programa y retener los mensajes en pantalla
 */
#define DEPURAR_FICHERO_MSG(msg) if (kDepurarFichero){ cout<<msg; cin.get();}


using namespace std;

/**
* \class FicheroCarga
* \brief Esta clase carga el sistema con los elementos indicados en el fichero de configuración
*/
class FicheroCarga{
 
 public:
  FicheroCarga(string nombre);
  void ProcesarFichero();
  void ProcesarDatos(int numCampos,string vCampos[kMaxCampos]);
  //~FicheroCarga();
 private:
  ifstream f_in_;  //!< atributo que contiene el flujo de entrada utilizado para extraer informacion del fichero.
  string nombre_fichero_;  //!< atributo que contiene el nombre del fichero, se inicializa con el constructor.
  int TrocearLinea(string linea,string vCampos[kMaxCampos]);

};
#endif

