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
#include "prision.h"

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
  llaves_= new priority_queue<Llave*, vector<Llave*>, CompLlavesMayor>;
  personas_=new queue<Persona*>;
}

/**
 * Constructor parametrizado de la clase celda
 * @param id parametro a estabalecer como el atributo id_
 */
Celda::Celda(const int & id)
{
  id_=id;
  marca_=id;
  llaves_= new priority_queue<Llave*, vector<Llave*>, CompLlavesMayor>;
  personas_= new queue<Persona*>;
}

/**
 * Destructor de la clase celda
 */
Celda::~ Celda()
{
  //Liberamos memoria
  while(!llaves_->empty()) delete sacar_llave();
  while(!personas_->empty()) delete sacar_persona();

  id_=-1;
  marca_=-1;
  delete llaves_;
  delete personas_;
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
 * @param llave llave a insertar
 */
void Celda::set_llave(Llave * llave)
{
  llaves_->push(llave);
}

/**
 * Obtiene y saca la primera llave
 * @return llave sacada de la celda
 */
Llave * Celda::sacar_llave()
{
  if(llaves_->empty()) return NULL;
  Llave* llave_aux=llaves_->top();
  llaves_->pop();
  return llave_aux;
}

/**
 * Libera toda la memoria almacenada en la celda
 */
// void Celda::Destruir()
// {
//   while(!llaves_->empty()) delete sacar_llave();
//   while(!personas_->empty()) delete sacar_persona();
// }

/**
 * Introduce una persona en la celda
 * @param p persona a introducir a la celda
 */
void Celda::set_persona(Persona * p)
{
  personas_->push(p);
}

/**
 * Obtiene la primera persona de la celda
 * @return devuelve la primera persona de la celda
 */
Persona * Celda::get_persona() const
{
  return personas_->front();
}

/**
 * Saca y devuelve la primera persona de la celda
 * @return devuelve la primera persona de la celda
 */
Persona * Celda::sacar_persona() const
{
  if(personas_->empty()) return NULL;
  Persona* p=personas_->front();
  personas_->pop();
  return p;
}

/**
 * Obtiene la cantidad de personas que hay en una celda
 * @return numero de personas que hay en la celda
 */
int Celda::ocupacion() const
{
  return personas_->size();
}

/**
 * Realiza el algoritmo de simulacion en la celda
 * @return devuelve false si algun preso ha salido de la simulacion
 */
bool Celda::Simular()
{
  bool aux = true;
  bool continuar = true;
  int max = personas_->size();
  Persona *pers;
  for(int i=0;i<max && continuar;i++){
    pers = personas_->front();
    if(continuar = personas_->front()->get_turno() != Prision::get_instancia()->get_turno()){
      personas_->push(pers);
      personas_->pop();
      aux = aux && pers->Actuar();
    }
  }
  return aux;
}
