/**
* \file persona.cpp
* \brief Implementación de la clase Persona
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "persona.h"
#include "prision.h"
#include "errorplanta.h"

/**
 * Destructor de la clase persona
 */
Persona::~ Persona()
{
  nombre_="-1";
  marca_ = '0';
  turno_= -1;
  delete ruta_;
  while(llaves_.size()>0){
    delete sacar_llave();
  }

}

/**
 * Metodo que realiza todas las acciones de la persona
 * @Return false si mover devuelve false
 */
bool Persona::Actuar()
{
  bool aux = true;
  if(turno_ <= Prision::get_instancia()->get_turno()) {
    if(turno_!=Prision::get_instancia()->get_turno()){
      turno_ = Prision::get_instancia()->get_turno();
      UsarPuerta();
      aux = Mover();
      if(aux) {
        Interactuar();
        TratarLlave();
      }
    }
  }
  return aux;
}

/**
 * Constructor parametrizado de la clase Persona
 * @param nombre nombre de la persona
 * @param marca marca de la persona
 * @param espera turno en el que comenzara a moverse
 * @param p planta en la que inicia
 * @param c celda en la que inicia
 */
Persona::Persona(const string & nombre, const char & marca, const int &espera, const int &p, const int &c)
{
  if(Prision::get_instancia()->get_numero_plantas()<=p) throw ErrorPlanta(p);
  nombre_ = nombre;
  marca_ = marca;
  ruta_= new queue<Posicion>;
  planta_=p;
  celda_=c;
  turno_= espera;
}

/**
 * Obtiene la posicion de la celda a la que debe ir la persona segun un destino(Tipo Posicion)
 * @PRE Debe existir una celda adyacente en la direccion indicada por la ruta
 * @return entero con la posicion a la celda destino
 */
int Persona::Destino() const
{
  switch(ruta_->front()){
    case NORTE: return celda_ - Prision::get_instancia()->get_ancho_planta(planta_);break;
    case SUR: return celda_ + Prision::get_instancia()->get_ancho_planta(planta_);break;
    case ESTE: return celda_+1;break;
    case OESTE: return celda_-1; break;
    default: throw string("Atencion, error en la ruta de un preso, revise el fichero inicio.txt");break; 
  }
}


/**
 * Saca una llave y la devuelve
 * @return llave sacada
 */
Llave * Persona::sacar_llave()
{
  Llave* l;
  if(llaves_.empty()) {
    l = NULL;
  }
  else {
    l= llaves_.top();
    llaves_.pop();
  }
  return l;
}

/**
 * Introduce una llave
 * @param l llave a meter
 */
void Persona::put_llave(Llave * l)
{
  llaves_.push(l);
}

/**
 * Pasa la informacion de la persona a una cadena
 * @return cadena con la informacion de la persona
 */
string Persona::P2String()
{
  string cadena;
  char aux[50]={marca_,'\0'};
  cadena+=aux;
  int max=0;
//   if(Prision::get_instancia()->get_turno()>turno_) max = Prision::get_instancia()->get_turno();
//   else max = turno_;
  sprintf(aux, ":%d:%d:",celda_,turno_);
  cadena+=aux;
  stack <Llave*> pilaux;
  Llave *l;
  while(!llaves_.empty()){
    l = llaves_.top();
    llaves_.pop();
    pilaux.push(l);
    sprintf(aux," %d" ,l->get_id());
    cadena+=aux;
  }
  while(!pilaux.empty()){//Devolvemos todas las llaves al guardia
    l = pilaux.top();
    pilaux.pop();
    llaves_.push(l);
  }
  cadena+=")";
  return cadena;
}

/**
 * Muestra la ruta por pantalla y la guarda en el Registro
 */
void Persona::MostrarRuta()
{
  cout<<"(ruta:"<<marca_<<":";
  Registro::get_instancia()->Flujo()<<"(ruta:"<<marca_<<":";
  Posicion p;
  for (int i=0;i<ruta_->size();i++){
    ruta_->push( p = ruta_->front());
    ruta_->pop();
    switch ( p ){
      case NORTE: cout<<"Norte ";Registro::get_instancia()->Escribir(" N");break;
      case SUR: cout<<"Sur ";Registro::get_instancia()->Escribir(" S");break;
      case OESTE: cout<<"Oeste ";Registro::get_instancia()->Escribir(" O");break;
      case ESTE: cout<<"Este ";Registro::get_instancia()->Escribir(" E");break;
    }
  }
    cout<<")"<<endl;
    Registro::get_instancia()->Escribir(")\n");
}
