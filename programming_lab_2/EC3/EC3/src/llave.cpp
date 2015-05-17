/**
* \file llave.cpp
* \brief Implementacion del los metodos de la clase Llave
* \date 13-03-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 1
*   \b Curso 2º
*/

#include "llave.h"

/**
 * Constructor por defecto de la clase llave, pone el identificador a -1
 */
Llave::Llave()
{
  this->id_=-1;
}

/**
 * Constructor parametrizado de la clase llave
 * @param i entero con el cual se va a inicializar la clase
 */
Llave::Llave(const int & i)
{
  this->id_=i;
}

/**
 * Constructor por copia de la clase llave
 * @param L tipo Llave del cual se copiaran los atributos
 */
Llave::Llave(const Llave & L)
{
  this->id_=L.id_;
}

/**
 * Metodo consultor que obtiene el identificador de la llave
 * @return identificador de la llave
 */
int Llave::get_id() const
{
  return this->id_;
}


/**
 * Modificador que inserta un valor en el identificador de la clase
 * @param a entero que se copiara como identificador de la clase
 */
void Llave::set_id(const int & a)
{
  this->id_=a;
}

/**
 * Destructor de la clase llave
 */
Llave::~ Llave()
{
}

/**
 * Sobrecarga del metodo =, asigna a la primera clase la segunda
 * @param L Segundo elemento
 * @return resultado de la asignacion(la clase actual)
 */
Llave Llave::operator =(const Llave & L)
{
  this->id_=L.id_;
  return *this;
}

/**
 * Sobrecarga del metodo <, comprueba si la primera llave es menor que la segunda
 * @param L Segundo elemento
 * @return true si el primero elemento es menor que el segundo(comparando los id_) y false en caso contrario
 */
bool Llave::operator <(const Llave & L) const
{
  return this->id_<L.id_;
}

/**
 * Sobrecarga del metodo >, comprueba si la primera llave es mayor que la segunda
 * @param L Segundo elemento
 * @return true si el primero elemento es mayor que el segundo(comparando los id_) y false en caso contrario
 */
bool Llave::operator >(const Llave & L) const
{
  return this->id_>L.id_;
}

/**
 * Sobrecarga del metodo ==, comprueba si la primera llave es igual que la segunda
 * @param L Segundo elemento
 * @return true si el primero elemento es igual que el segundo(comparando los id_) y false en caso contrario
 */
bool Llave::operator ==(const Llave & L) const
{
  return this->id_==L.id_;
}

/**
 * Sobrecarga del metodo !=, comprueba si la primera llave es distinta a la segunda
 * @param L Segundo elemento
 * @return true si el primero elemento es distinto del segundo(comparando los id_) y false en caso contrario
 */
bool Llave::operator !=(const Llave & L) const
{
  return this->id_!=L.id_;
}

/**
 * Sobrecarga de "<<", copia la informacion de la llave a un flujo
 * @param flujo flujo
 * @param L elemento del que copiamos la informacion que se insertara en el flujo
 * @return un flujo con la informacion de la clase
 */
ostream &operator<<( ostream & flujo, const Llave &L )
{
  flujo<<L.id_;
  return flujo;
}




