/**
* \file puerta.h
* \brief Implementacion del header de la clase puerta
* \date 14-03-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 1
*   \b Curso 2º
*/

#ifndef PUERTA_H
#define PUERTA_H

#include "llave.h"
#include "arbol.h"
#include "colagen.h"
#include <iostream>

using namespace std;

typedef enum TipoEstado{NOCONFIGURADA,CERRADA,ABIERTA};


/**
* \class Puerta
* \brief Esta clase representa los atributos y metodos de puertas
*
* La clase puerta contendra un entero con el identificador de cada llave, usado mas
* adelante en las puertas, 2 arboles binarios de busqueda y una cola con llaves
*/
class Puerta{
 public:
  Puerta();
  Puerta(const int &alt);
  void Configurar(ColaGen <Llave*>* cop);
  bool set_combinacion();
  bool ProbarLlave(Llave *L);
  bool ProbarLlave(const Llave &L2);
  bool Abrir();
  bool Cerrar();
  Arbol <Llave*>* get_combinacion();
  Arbol <Llave*>* get_probadas();
  ColaGen <Llave*>* get_copia_combinacion();
  TipoEstado get_estado();
  void Alarma();

  friend ostream &operator<<( ostream & flujo, const Puerta &P );


  ~Puerta();

 private:
  TipoEstado estado_; //!< atributo que nos indica si la puerta esta NOCONFIGURADA(0), CERRADA(1) o ABIERTA(2)
  int altura_; //!< atributo que inidica la altura que no debe superar el arbol para poder abrir la puerta
  Arbol <Llave*>* combinacion_;  //!< atributo tipo arbol binario de busqueda que alamacena la combinacion correcta.
  Arbol <Llave*>* probadas_; //!< atributo tipo arbol binario de busqueda que almacena las llaves probadas en la puerta.
  ColaGen <Llave*>* copia_combinacion_; //!< atributo que contiene una copia de la combinacion secreta para poder reconfigur la puerta.
};




#endif // PUERTA_H
