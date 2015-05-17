/**
* \file guardia.cpp
* \brief Implementación de los metodos de la clase Guardia
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "guardia.h"
#include "prision.h"

/**
 * Metodo que cierra la puerta que haya en la celda(en caso de que la haya)
 */
void Guardia::UsarPuerta()
{
  if(celda_ == Prision::get_instancia()->get_salida_planta(planta_)) {
    Prision::get_instancia()->get_planta(planta_)->CerrarPuerta();
    cout<<"Guardia: "<<marca_<<" cierra una puerta."<<endl;
  }
}

/**
 * Metodo que captura a un preso en la sala
 */
void Guardia::Interactuar()
{
  Planta* plant = Prision::get_instancia()->get_planta(planta_);
  Persona * pers;
  bool detenido = false;
  bool es_guardia = false;
  int max= plant->ocupacion(celda_);
  for(int i=0;i<max;i++){
    es_guardia = false;
    pers = plant->sacar_persona(celda_);
    for(int i=0; i < plant->get_num_guardias(); i++) es_guardia = es_guardia || (pers == plant->get_guardia(i) );
    if(!es_guardia && !detenido){
      detenido=true;
      cout<<"Guardia: "<<marca_<<" Captura a: "<<pers->get_marca()<<endl;
      Prision::get_instancia()->meter_celda_castigo(pers);
    }
    else{
      plant->set_persona(celda_,pers);
    }
  }
}

/**
 * Metodo que controla el uso de las llaves
 */
void Guardia::TratarLlave()
{
  Planta *p = Prision::get_instancia()->get_planta(planta_);
  Llave * L;
  if(!llaves_.empty() && celda_%2 == 0) {
    L= llaves_.top();
    p->set_llave(celda_,L);
    llaves_.pop();}
}

/**
 * Metodo que actualiza la ruta del guardia
 */
void Guardia::CalcularRuta()
{
  int ancho = Prision::get_instancia()->get_planta(planta_)->get_ancho();
  Planta* p = Prision::get_instancia()->get_planta(planta_);
  queue <Posicion> minimo;

  int destino;

  for(int i=0;i<4;i++){
    destino = DestinoRuta();
    p->CaminoMinimo(celda_, destino, *ruta_);
    celda_=destino;
  }
}

/**
 * Constructor por defecto de la clase guardia
 * @param nombre nombre del guardia
 * @param marca marca del guardia
 * @param espera tiempo que debe esperar el guardia para actuar
 * @param p planta en la que inicia el guardia
 * @param c celda en la que se inicia el guardia
 */
Guardia::Guardia(const string & nombre, const char & marca, const int & espera, const int &p, const int &c): Persona(nombre,marca,espera,p,c)
{
  CalcularRuta();
  Prision::get_instancia()->get_planta(planta_)->RegistrarGuardia(this);
}

/**
 * Se mueve a la siguiente celda
 * @return true si se a podido mover correctamente
 */
bool Guardia::Mover()
{
//   cin.get();
//   cout<<"Guardia se mueve : "<<celda_;
  if(ruta_->empty()) CalcularRuta();
  Persona* pers;
  Planta* p = Prision::get_instancia()->get_planta(planta_);
  for(int i=0;i<p->ocupacion(celda_);i++){
    pers = p->sacar_persona(celda_);
    if(this!=pers) p->set_persona(celda_,pers);
  }
  int destino = p->get_vecina(ruta_->front(),celda_);
  p->set_persona(destino,this);
  celda_ = destino;
  ruta_->pop();
  return true;
//   cout<<" - "<<celda_;
//   cin.get();
}

/**
 * Halla la celda a la que debera de ir el guardia.
 */
int Guardia::DestinoRuta() const
{
  Planta* p = Prision::get_instancia()->get_planta(planta_);
  if(celda_ == 0) return p->get_ancho()-1;
  if(celda_ == p->get_ancho()-1) return p->get_ancho()*p->get_alto()-1;
  if(celda_ == p->get_ancho()*p->get_alto()-1) return p->get_ancho()*(p->get_alto()-1);
  if(celda_ == p->get_ancho()*(p->get_alto()-1)) return 0;
}

/**
 * Destructor de la clase guardia
 */
Guardia::~ Guardia()
{
}

/**
 * Pasa la informacion del guardia a una cadena
 * @return cadena con la informacion de la guardia
 */
string Guardia::P2String()
{
  string cadena = "(guardia:";
  cadena+= Persona::P2String();
  return cadena;
}
