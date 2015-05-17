/**
* \file preso.cpp
* \brief Implementación de los metodos de la clase Preso
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "preso.h"
#include "prision.h"

/**
 * Metodo que intenta abrir una puerta (si la hay)
 */
void Preso::UsarPuerta()
{
  if(celda_ == Prision::get_instancia()->get_salida_planta(planta_)) {
    ProbarLlaves();
  }
}

/**
 * Metodo que roba una llave al primer guardia de la sala (si lo hay)
 */
void Preso::Interactuar()
{
  Planta* plant = Prision::get_instancia()->get_planta(planta_);
  Persona *pers;
  Llave *l;
  bool robada=false;
  for(int i=0;i<plant->ocupacion(celda_);i++){
    pers = plant->sacar_persona(celda_);
    if(typeid(*pers)!=typeid(Preso) && !robada){
      robada=true;
      if(l = pers->sacar_llave()) this->put_llave(l);
    }
    plant->set_persona(celda_,pers);
  }
}

/**
 * Metodo que recoge una llave de la celda (si la hay)
 */
void Preso::TratarLlave()
{
  Llave *l = Prision::get_instancia()->get_planta(planta_)->sacar_llave(celda_);
  if(l!=NULL) llaves_.push(l);
}

/**
 * Metodo que actualiza la ruta del preso
 */
void Preso::CalcularRuta()
{
  bool visitados[kMaxVert]={false};
  stack<Posicion>* pilaux = new stack<Posicion>;
  CalcularRutaRecursivo(celda_,pilaux,visitados);

  while(!pilaux->empty()){
    ruta_->push(pilaux->top());
    pilaux->pop();
  }
  delete pilaux;
}

/**
 * Constructor parametrizado de la clase Preso
 * @param nombre nombre del preso
 * @param marca marca del preso
 * @param espera turnos que el preso debe esperar antes de actuar
 * @param orientacion[] orientacion para calcular la ruta del preso
 * @param p planta en la que inicia el preso
 * @param c celda en la que inicia el preso
 */
Preso::Preso(const string & nombre, const char & marca, const int & espera,
             const Posicion orientacion[4], const int &p, const int &c): Persona(nombre,marca,espera,p,c)
{
  bool marcados[4]={false};
  orientacion_ = new queue<Posicion>;
  for (int i=0;i<4;i++){
    if(marcados[orientacion[i]]) throw string("Atencion, error en la ruta de un preso, revise el fichero inicio.txt");
    orientacion_->push(orientacion[i]);
    marcados[orientacion[i]]=true;
  }

  CalcularRuta();
}

/**
 * Usa todas las llaves que tiene para intentar abrir la puerta
 * @PRE el preso en encuentra en la celda de la puerta
 * @return true si consige abrir la puerta false en caso contrario
 */
bool Preso::ProbarLlaves()
{
  if(!llaves_.empty()&&Prision::get_instancia()->get_planta(planta_)->EstadoPuerta()==CERRADA){
    Llave *l;
    Prision::get_instancia()->get_planta(planta_)->ProbarLlave(l = llaves_.top());
    llaves_.pop();
    Prision::get_instancia()->get_planta(planta_)->AbrirPuerta();
  }
  if(Prision::get_instancia()->get_planta(planta_)->EstadoPuerta()==ABIERTA) {
    cout<<"Preso: "<<marca_<<" abre una puerta."<<endl;
    return true;
  }
}

/**
 * Mueve a la siguiente celda o si hay una puerta abierta, cambia de planta.
 * \return true si a pasado a otra celda, false si ha conseguido escapar de la carcel
 */
bool Preso::Mover()
{
  Persona* pers;
  Posicion orientacion;
  Planta* p = Prision::get_instancia()->get_planta(planta_);

  if(celda_  == p->get_salida()){
    if(p->EstadoPuerta() == ABIERTA){
      for(int i=0;i<p->ocupacion(celda_);i++){
        pers = p->sacar_persona(celda_);
        if(this!=pers) p->set_persona(celda_,pers);
      }
      if(planta_ == 0) {
        celda_ = 1111;
        Prision::get_instancia()->meter_en_fugados(pers);
        return false;
      }
      p = Prision::get_instancia()->get_planta(planta_-1);
      int destino = p->get_entrada();
      p->set_persona(destino,this);
      celda_ = destino;
      planta_--;
    }
  }
  else{
    for(int i=0;i<p->ocupacion(celda_);i++){
      pers = p->sacar_persona(celda_);
      if(this!=pers) p->set_persona(celda_,pers);
    }
    orientacion = ruta_->front();
    int destino = p->get_vecina(orientacion,celda_);
    p->set_persona(destino,this);
    celda_ = destino;
    ruta_->pop();
  }
  return true;
}

/**
 * Metodo recursivo para calcular la ruta
 * @param posicion posicion de la que se parte
 * @param pilaux pila con la ruta
 * @param visitados[] celdas visitadas
 * @return true si se ha llegado a la salida
 */
bool Preso::CalcularRutaRecursivo(const int & posicion, stack<Posicion>* pilaux, bool visitados[])
{
  TipoNodoGrafo w;
  Posicion orientacion;
  Planta *p = Prision::get_instancia()->get_planta(planta_);
  
  if(posicion == p->get_salida())
    if(planta_ <= 0){
     return true;
    }
    else {
      planta_--;
      Planta *p = Prision::get_instancia()->get_planta(planta_);
      for (int i=0;i<p->get_alto()*p->get_ancho();i++) visitados[i]=false;
      bool aux = CalcularRutaRecursivo(p->get_entrada(),pilaux, visitados);
      planta_++;//al final, dejamos la planta correcta
      return aux;
    }


  for(int i=0;i<4;i++){
    w = p->get_vecina(orientacion_->front(),posicion);
    orientacion_->push(orientacion_->front());
    orientacion_->pop();
    if(p->Accesible(posicion, w)) {
      visitados[posicion]=true;
      if(!visitados[w]) {
        if(w-posicion == 1) {orientacion = ESTE;}
        if(w-posicion == -1) {orientacion = OESTE;}
        if(w-posicion == -p->get_ancho()) {orientacion = NORTE;}
        if(w-posicion == p->get_ancho()) {orientacion = SUR;}
        if(this->CalcularRutaRecursivo(w,pilaux,visitados)){
          pilaux->push(orientacion);
          return true;
        }
      }
    }
  }
  return false;
}

/**
 * Destructor de la clase preso
 */
Preso::~ Preso()
{
  delete orientacion_;
}

/**
 * Pasa la informacion del preso a una cadena
 * @return cadena con la informacion de la preso
 */
string Preso::P2String()
{
  string cadena = "(preso:";
  cadena+= Persona::P2String();
  return cadena;
}



