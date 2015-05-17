/**
* \file prision.cpp
* \brief Implementacion de los metodos de la clase prision
* \date 28-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/
#include "prision.h"

Prision* Prision::instancia_ = NULL;


/**
 * Constructor de la clase prision
 */
Prision::Prision()
{
  plantas_ = new vector<Planta*>;
}

/**
 * Destructor de la clase planta
 */
Prision::~ Prision()
{
}

/**
 * Obtiene la instancia de la clase Prision, si no existe la crea.
 * @return instancia de la clase prision
 */
Prision * Prision::get_instancia()
{
  if(instancia_==NULL) instancia_ = new Prision;
  return instancia_;
}

/**
 * Inserta una planta
 * @param p planta a insertar
 */
void Prision::set_planta(Planta * p)
{
  plantas_->push_back(p);
}

/**
 * Obtiene el numero de plantas
 * @return numero de plantas
 */
int Prision::get_numero_plantas() const
{
  return plantas_->size();
}

/**
 * Extrae la planta en la posicion indicada, null si no exite
 * @param posicion posicion indicada
 * @return planta buscada
 */
Planta * Prision::get_planta(const int & posicion) const
{
  if(posicion<=plantas_->size()) return (*plantas_)[posicion];
  else return NULL;
}


/**
 * Muestra todas las plantas de la prision
 */
void Prision::MostrarPrision() const
{
  cout<<"MAPA DE LA PRISION"<<endl<<endl;
  for(int i=0;i<plantas_->size();i++){
    cout<<"Planta "<<(*plantas_)[i]->get_id();
    cout<<endl<<*(*plantas_)[i]<<endl;
  }
}

/**
 * Libera toda la memoria almacenada en la prision
 */
void Prision::Destruir()
{
  if(instancia_!=NULL){
    for(int i=0;i<plantas_->size();i++){
      delete (*plantas_)[i];
    }
    delete plantas_;
    delete instancia_;
    instancia_=NULL;
  }
}
