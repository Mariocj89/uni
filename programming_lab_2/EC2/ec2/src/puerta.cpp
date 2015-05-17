/**
* \file puerta.cpp
* \brief Implementacion de los metodos de la clase puerta
* \date 14-03-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/
#include "puerta.h"


/**
 * Constructor por defecto de la clase Puerta
 */
Puerta::Puerta()
{
  this->estado_=NOCONFIGURADA;
  this->combinacion_=new Arbol<Llave*>;
  this->copia_combinacion_=new ColaGen <Llave*>;
  this->probadas_=new Arbol<Llave*>;
  this->altura_=10;
}

/**
 * Constructor parametrizado de la clase Puerta
 * @param alt parametro que se copiara al atributo altura_
 */
Puerta::Puerta(const int &alt)
{
  this->estado_=NOCONFIGURADA;
  this->combinacion_=new Arbol<Llave*>;
  this->copia_combinacion_=new ColaGen <Llave*>;
  this->probadas_=new Arbol<Llave*>;
  this->altura_=alt;
}

/**
 * Copia de una cola a copia_combinacion_ todas las llaves
 * @param cop parametro desde el cual se va a copiar
 */
void Puerta::Configurar(ColaGen< Llave *> * cop)
{
  Llave* L;
  for(int i=0;i<cop->get_num_elementos();i++){
    L=cop->get();
    cop->borrar();
    cop->insertar_dato(L);
    this->copia_combinacion_->insertar_dato(L);
  }
  this->estado_=ABIERTA;
    
}

/**
 * Copia la combinacion desde copia_combinacion_
 * @return true si en copia_combinacion_ hay datos, false en caso contrario
 */
bool Puerta::set_combinacion()
{
  if(this->copia_combinacion_->vacia()) return false;
  else{
    if(this->combinacion_!=NULL) delete this->combinacion_;
    this->combinacion_=new Arbol <Llave*>;
    Llave* L;
    for( int i=0;i<this->copia_combinacion_->get_num_elementos();i++){
      L=this->copia_combinacion_->get();
      this->copia_combinacion_->borrar();
      this->copia_combinacion_->insertar_dato(L);
      this->combinacion_->insertar(L);
    }
    this->combinacion_=this->combinacion_->Equilibrar();
    this->estado_=ABIERTA;
    return true;
  }
}

/**
 * Prueba una llave: intenta insertarla en probadas, si no puede(por que ya se encuentra en probadas) llama al metodo de alerta,
 * si no se encuentra en probadas pero si en combinacion, la elimina de combinacion, la inserta en probadas y devuelve true
 * y si no se enceutra en ninguna de las 2, la inserta en probadas y devuelve false
 * @param L puntero a llavellave que queremos probar
 * @return true si pertenece a la combinacion y no ha sido probada previamente, false si no se encuentra en la combinacion o a sido probada previamente.
 */
bool Puerta::ProbarLlave(Llave *L)
{
  if(!this->probadas_->insertar(L)){//no se inserta la llave
    this->Alarma();
    return false;
  }
  else{//se inserta correctamente la llave
    if(this->combinacion_->pertenece(L)){//La llave forma parte de la combinacion
      this->combinacion_->borrar(L);
      this->combinacion_=this->combinacion_->Equilibrar();
      return true;
    }
    else{//La llave no forma parte de la combinacion
      return false;
    }
  }
}

/**
 * Prueba una llave: intenta insertarla en probadas, si no puede(por que ya se encuentra en probadas) llama al metodo de alerta,
 * si no se encuentra en probadas pero si en combinacion, la elimina de combinacion, la inserta en probadas y devuelve true
 * y si no se enceutra en ninguna de las 2, la inserta en probadas y devuelve false
 * @param L2 llave que queremos probar
 * @return true si pertenece a la combinacion y no ha sido probada previamente, false si no se encuentra en la combinacion o a sido probada previamente.
 */
bool Puerta::ProbarLlave(const Llave & L2)
{
  Llave *L=new Llave(L2);
  if(!this->probadas_->insertar(L)){//no se inserta la llave
    this->Alarma();
    return false;
  }
  else{//se inserta correctamente la llave
    if(this->combinacion_->pertenece(L)){//La llave forma parte de la combinacion
      this->combinacion_->borrar(L);
      this->combinacion_=this->combinacion_->Equilibrar();
      return true;
    }
    else{//La llave no forma parte de la combinacion
      return false;
    }
  }
  delete L;
}

/**
 * Intenta abrir una puerta comprobando si se cumplen las condiciones. 
 * @return true si se consigue abrir correctamente, false en caso contrario
 */
bool Puerta::Abrir()
{
  if(this->combinacion_->Profundidad()<this->altura_&&this->estado_==CERRADA){
    int hojas=0,nudos=0;
    this->combinacion_->NumNodos(hojas,nudos);
    if(nudos>hojas)  {this->estado_=ABIERTA; return true;}
    else {return false;}
  }
  else {return false;}
}

/**
 * Metodo que cierra la puerta, copiando la configuracion desde copia_configuracion_ a configuracion_ y borra el arbol de probadas_
 * @return true si esta abierta y se cierra, false en otro caso
 */
bool Puerta::Cerrar()
{
  if(this->estado_==ABIERTA){
    this->set_combinacion();
    this->estado_=CERRADA;
    delete this->probadas_;
    this->probadas_=new Arbol <Llave*>;
    return true;
  }
  else {return false;}
}

/**
 * Obtiene el atributo combinacion_, que es un arbol
 * @return arbol con combinacion_
 */
Arbol< Llave * > * Puerta::get_combinacion()
{
  return combinacion_;
}

/**
 * Obtiene el atributo probadas_, que es un arbol
 * @return arbol con probadas_
 */
Arbol< Llave * > * Puerta::get_probadas()
{
  return probadas_;
}

/**
 * Obtiene copia_combinacion
 * @return cola generica de punteros a llaves con copia_combinacion_
 */
ColaGen< Llave * > * Puerta::get_copia_combinacion()
{
  return copia_combinacion_;
}

/**
 * Devuelve el estado de la puerta (0-NOCONFIGURAR, 1-CERRADA, 2-ABIERTA)
 * @return Tipoestado con la informacion
 */
TipoEstado Puerta::get_estado()
{
  return estado_;
}

/**
 * Destructor de la clase Puerta
 */
Puerta::~ Puerta()
{
  this->estado_=NOCONFIGURADA;
  if(combinacion_!=NULL) delete combinacion_;
  if(probadas_!=NULL) delete probadas_;
  if(copia_combinacion_!=NULL) delete copia_combinacion_;
}

/**
 * Metodo en respuesta a que se han probado 2 veces la misma llave
 */
void Puerta::Alarma()
{
  cout<<"ATENCION, Se ha probado 2 veces la misma llave!!!!\n";
}

/**
 * Sobrecarga del operador <<
 * @param flujo flujo al que se le pasara la informacion
 * @param P Puerta a mostrar
 * @return flujo con los datos
 */
ostream &operator<<( ostream & flujo, const Puerta &P )
{
  flujo<<"La puerta esta: ";
  switch(P.estado_){
    case NOCONFIGURADA: flujo<<"NO CONFIGURADA. \n"; break;
    case CERRADA:  flujo <<"CERRADA. \n"; break;
    case ABIERTA:  flujo <<"ABIERTA. \n"; break;
  }  
  return flujo;
}



