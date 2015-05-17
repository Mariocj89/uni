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
#include "errorplanta.h"

Prision* Prision::instancia_ = NULL;


/**
 * Constructor de la clase prision
 */
Prision::Prision()
{
  plantas_ = new vector<Planta*>;
  turno_ = 0;
  n_presos_ = 0;
}

/**
 * Destructor de la clase planta
 */
Prision::~ Prision()
{
  if(instancia_!=NULL){
  Registro::get_instancia()->Destruir();
    for(int i=0;i<plantas_->size();i++){
      delete (*plantas_)[i];
    }
    delete plantas_;
    instancia_ = NULL;
  }
  while(!fugados_.empty()){
    delete fugados_.front();
    fugados_.pop_front();
  }
  while(!celda_castigo_.empty()){
    delete celda_castigo_.front();
    celda_castigo_.pop_front();
  }
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
  if(p->get_id()!=plantas_->size()) throw ErrorPlanta(p->get_id());
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
// void Prision::Destruir()
// {
//   if(instancia_!=NULL){
//     for(int i=0;i<plantas_->size();i++){
//       delete (*plantas_)[i];
//     }
//     delete plantas_;
//     delete instancia_;
//     instancia_ = NULL;
//   }
// }

/**
 * Inserta una persona en la prision
 * @PRE si se inserta un preso por primera vez, debe aumentarse el contador de presos en la carcel
 * @param planta planta en la que insertarla
 * @param pos celda en la que insertarla
 * @param p persona a insertar
 */
void Prision::set_persona(const int &planta, const int &pos, Persona * p)
{
  if(plantas_->size()<=planta) throw ErrorPlanta(planta);
  (*plantas_)[planta]->set_persona(pos,p);
}


/**
 * Obtiene la ocupacion de una celda 
 * @param planta planta en la que se encuentra la celda buscada
 * @param celda celda buscada
 * @return ocupacion de la celda buscada (-1 si error)
 */
int Prision::ocupacion_celda(const int & planta, const int &celda) const
{
  if(plantas_->size()<=planta) return -1;
  return (*plantas_)[planta]->ocupacion(celda);
}

/**
 * Obtiene y borra la primera persona de la celda indicada
 * @param planta planta indicada
 * @param celda celda indicada
 * @return primera persona de la planta (NULL si no hay)
 */
Persona * Prision::sacar_persona(const int & planta, const int celda)
{
  if(plantas_->size()<=planta) return NULL;
  return (*plantas_)[planta]->sacar_persona(celda);
}

/**
 * Obtiene la primera persona de la celda indicada
 * @param planta planta indicada
 * @param celda celda indicada
 * @return primera persona de la planta (NULL si no hay)
 */
Persona * Prision::get_persona(const int & planta, const int & celda) const
{
  if(plantas_->size()<=planta) return NULL;
  return (*plantas_)[planta]->get_persona(celda);
}

/**
 * Obtiene el ancho de una planta indicada
 * @param planta planta de la que obtener el ancho
 * @return ancho de la planta indicada(-1 en caso de error)
 */
int Prision::get_ancho_planta(const int &planta) const
{
  if(plantas_->size()<=planta) return -1;
  return (*plantas_)[planta]->get_ancho();
}

/**
 * Obtiene la entrada de la planta indicada
 * @param planta planta de la que obtener la posicion de la entrada
 * @return posicion de la entrada (-1 si error)
 */
int Prision::get_entrada_panta(const int & planta) const
{
  if(plantas_->size()<=planta) return -1;
  return (*plantas_)[planta]->get_entrada();
}

/**
 * Obtiene la salida de la planta indicada
 * @param planta planta de la que obtener la posicion de la salida
 * @return posicion de la salida (-1 si error)
 */
int Prision::get_salida_planta(const int & planta) const
{
  if(plantas_->size()<=planta) return -1;
  return (*plantas_)[planta]->get_salida();
}

/**
 * Mete un preso en la celda de castigo
 * @param p persona a insertar
 */
void Prision::meter_celda_castigo(Persona * p)
{
  p->set_celda(kNumCeldaCastigo);
  celda_castigo_.push_back(p);
}


/**
 * Obtiene el alto de la planta indicada
 * @param planta planta de la que obtener el alto
 * @return alto de la planta (-1 si error)
 */
int Prision::get_alto_planta(const int & planta) const
{
  if(plantas_->size()<=planta) return -1;
  return (*plantas_)[planta]->get_alto();
}


/**
 * Inicia la simulacion
 */
void Prision::IniciarSimulacion()
{
  bool continuar = true;
  list <Persona*>::iterator it;
  MostrarTodos();
  while(continuar){
    //Se realiza el turno
    for(int i=plantas_->size()-1; i>=0; i--){
      continuar = continuar && (*plantas_)[i]->Simular() && n_presos_ > celda_castigo_.size()  && turno_<=500;
    }
    if(continuar) {
      cout<<"------------------------------Turno: "<<turno_<<" ------------------------------"<<endl;
      Registro::get_instancia()->Flujo()<<"(turno:"<<turno_<<")"<<endl;
    }
    else {
      cout<<"------------------------------ Fin de la Simulacion ------------------------------"<<endl;
      Registro::get_instancia()->Flujo()<<"(findelasimulacion)"<<endl;
    }

    //Mostramos la celda de castigo:
    cout<<"(celdacastigo:"<<kNumCeldaCastigo<<")"<<endl;
    Registro::get_instancia()->Flujo()<<"(celdacastigo:"<<kNumCeldaCastigo<<")"<<endl;
    it=celda_castigo_.begin();
    while(it!=celda_castigo_.end()){
      cout<<(*it)->P2String()<<endl;
      Registro::get_instancia()->Flujo()<<(*it)->P2String()<<endl;
      it++;
    }
    //Mostramos la planta
    for(int i=plantas_->size()-1; i>=0; i--){
      (*plantas_)[i]->Pintar();
    }
    turno_++;
  }
  //Mostramos los presos fugados
  cout<<"(presosfugados:)"<<endl;
  Registro::get_instancia()->Flujo()<<"(presosfugados)"<<endl;
  it=fugados_.begin();
  while(it!=fugados_.end()){
    cout<<(*it)->P2String()<<endl;
    Registro::get_instancia()->Flujo()<<(*it)->P2String()<<endl;
    it++;
  }
}

/**
 * Mete un preso en la lista que almacena los presos que se ha fugado
 * @param p presos fugados
 */
void Prision::meter_en_fugados(Persona * p)
{
  fugados_.push_back(p);
}

/**
 * Muestra todas las personas de la prision
 */
void Prision::MostrarTodos()
{
  Persona *p;
  Planta *plant;
  //Mostramos los presos
  plant = plantas_->back();
  for(int i=0; i<plant->ocupacion(0);i++){
    plant->set_persona(0,p = plant->sacar_persona(0));
    p->MostrarRuta();
  }
  //Mostramos los guaridas
  for(int i=plantas_->size()-1; i>=0; i--){
    plant = (*plantas_)[i];
    int ultima_celda = plant->get_alto()*plant->get_ancho()-1;
    for(int i=0; i<plant->ocupacion(ultima_celda);i++){
      plant->set_persona(ultima_celda,p = plant->sacar_persona(ultima_celda));
      p->MostrarRuta();
    }
  }
}
