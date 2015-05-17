/**
* \file celda.cpp
* \brief Implementacion de los metodos de la clase celda
* \date 20-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "celda.h"

/**
 * Modificador que establece la id de la celda
 * @param id id a copiar
 */
void Celda::set_id(const int & id)
{
  id_=id;
}

/**
 * Constructor de la clase celda
 */
Celda::Celda()
{
  id_=-1;
  marca_=-1;
  llaves_= new vector<Llave*>;
}

/**
 * Constructor parametrizado de la clase celda
 * @param id parametro a estabalecer como el atributo id_
 */
Celda::Celda(const int & id)
{
  id_=id;
  marca_=id;
  llaves_= new vector<Llave*>;
}

/**
 * Destructor de la clase celda
 */
Celda::~ Celda()
{
  id_=-1;
  marca_=-1;
  delete llaves_;
}

/**
 * Sobrecarga del operador <<
 * @param flujo flujo al que se introduce la informacion
 * @param C celda de la que obtener la informacion
 * @return flujo con la informacion
 */
ostream & operator <<(ostream & flujo, const Celda & C)
{
  flujo<<C.id_;
  return flujo;
}

/**
 * Inserta una llave en la celda
 * @param llave 
 */
void Celda::set_llave(Llave * llave)
{
  llaves_->push_back(llave);
}

/**
 * Obtiene la lista de llaves de la celda
 * @return lista de llaves de la celda
 */
vector< Llave * > * Celda::get_llaves() const
{
  return llaves_;
}

