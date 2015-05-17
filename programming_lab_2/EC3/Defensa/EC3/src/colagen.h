/**
* \file colagen.h
* \brief Implementacion de la plantilla de la clase ColaGen
* \date 09-03-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 1
*   \b Curso 2º
*/

#ifndef COLAGEN_H
#define COLAGEN_H

#include <iostream>
using namespace std;


/******************************************************************************************************************************************************************
*************************************************************PLANTILLA DE COLA GENERICA PARA ELEMENTOS ESTATICOS***************************************************
******************************************************************************************************************************************************************/

/**
* \class ColaGen
* \brief Esta clase implementa una estructura lineal de tipo Cola generica
*
* Esta clase permite insertar elementos por el principio de la cola y extraerlos por el final
*/
template <class T>
class ColaGen{

/**
* \struct TipoNodo
* \brief Este registro representa un nodo de la cola
*/
typedef struct TipoNodo {
	T dato_;		//!< Dato que contiene cada nodo de la cola 
	TipoNodo *sig_;	//!< Puntero al siguiente nodo de la cola
};

 public:
  ColaGen ();							//!< Inicializa los datos de la cola (punteros a NULL)
  ColaGen (const ColaGen &C);					//!< Inicializa los datos de la cola por copia
  void insertar_dato (const T &dato);				//!< Inserta un dato en la cola (por el final)
  void insertar_nodo (const TipoNodo &nodo);			//!< Inserta un dato enviado en un nodo en la cola (por el final)
  T get ()const;						//!< Devuelve el dato que se encuentra en el frente de la cola
  bool borrar ();						//!< Elimina el dato que se encuentre en el frente de la cola
  ostream& mostrar () const;					//!< Muestra la cola por pantalla y guarda la informacion mostrada en un flujo
  inline bool vacia () const {return num_elementos_==0;}	//!< Devuelve verdadero si la cola está vacía
  inline int get_num_elementos () {return num_elementos_;}	//!< Devuelve el número de elementos de la cola
  ~ColaGen ();							//!< libera la memoria de la cola (OJO ¡NO DE LOS DATOS CONTENIDOS!)

 private:
  TipoNodo *frente_;		//!< Puntero al frente de la cola
  TipoNodo *fin_;		//!< Puntero al final de la cola
  int num_elementos_;		//!< Número de elementos de la cola, utilizado para realizar recorridos

};


/**
 * Constructor por defecto de la clase ColaGen, pone los punteros a NULL y num_elementos a 0
 */
template <class T>
ColaGen <T>::ColaGen()
{
  this->num_elementos_=0;
  this->frente_=NULL;
  this->fin_=NULL;
}


/**
 * Constructor por copia de la clase ColaGen
 * @param C Cola desde la que se inicializa esta clase
 */
template <class T>
ColaGen <T>::ColaGen(const ColaGen & C)
{
  frente_=NULL;
  fin_=NULL;
  TipoNodo *aux=C.frente_;
  num_elementos_=0;
  while (aux!=NULL){
    this->insertar_nodo(*aux);
    aux=aux->sig_;
  }
}


/**
 * Metodo que inserta un dato en la cola
 * @param dato dato a insertar
 */
template <class T>
void ColaGen <T>::insertar_dato(const T & dato)
{
  TipoNodo *aux=this->fin_, *nodo=new TipoNodo;
  nodo->dato_=dato;
  nodo->sig_=NULL;
  if(this->vacia()) { this->frente_=nodo; }
  else {fin_->sig_=nodo;}
  fin_=nodo;
  num_elementos_++;
}


/**
 * Metodo que inserta el dato contenido en un nodo
 * @param nodo Nodo del cual se extraera el dato para insertarlo
 */
template <class T>
void ColaGen <T>::insertar_nodo(const TipoNodo& nodo)
{
  TipoNodo *nodo2=new TipoNodo, *aux=frente_;
  nodo2->dato_=nodo.dato_;
  nodo2->sig_=NULL;
  if(aux==NULL) {frente_=nodo2;}
  else{
    while(aux->sig_!=NULL)
      aux=aux->sig_;
    aux->sig_=nodo2;
  }
  this->fin_=nodo2;
  num_elementos_++;
}


/**
 * Obtiene el frente de la cola
 * @return devuelve el frente de la cola
 */
template <class T>
T ColaGen <T>::get() const
{
  return frente_->dato_;
}


/**
 * Elimina el frente de la cola
 * @return true si la cola no esta vacia
 */
template <class T>
bool ColaGen <T>::borrar()
{
  if (frente_==NULL) return false;
  else{
    TipoNodo *aux=frente_;
    frente_=frente_->sig_;
    delete aux; aux=NULL;
    num_elementos_--;
    return true;
  }
}



/**
 * Destructor de la clase ColaGen, elimina todo los elementos
 */
template <class T>
ColaGen <T>::~ ColaGen()
{
  TipoNodo *aux;
  while (frente_!=NULL){
    aux=frente_->sig_;
    delete frente_;
    frente_=aux;
  }
}


/**
 * Muestra la cola por Pantalla
 * @return flujo con la informacion (Aun no implementado)
 */
template <class T>
ostream& ColaGen <T>::mostrar() const
{
//   ostream flujo;
//   flujo<<"Mostrando una cola: \n";
//   if(this->vacia()) {flujo<<"La cola esta vacia. \n";}
//   else{
//     flujo<<"Frente: ";
//     TipoNodo *aux=this->frente_;
//     while(aux!=NULL){
//       flujo <<aux->dato_<<" - ";
//       aux=aux->sig_;
//     }
//   flujo<<'\n';
//   }
//   cout<<flujo;
//   return flujo;

  cout<<"Mostrando una cola: \n";
  if(this->vacia()) {cout<<"La cola esta vacia. \n";}
  else{
    cout<<"Frente: ";
    TipoNodo *aux=this->frente_;
    while(aux!=NULL){
      cout <<aux->dato_<<" - ";
      aux=aux->sig_;
    }
  cout<<'\n';
  }
}


/******************************************************************************************************************************************************************
*************************************************************PLANTILLA DE COLA GENERICA PARA ELEMENTOS DINAMICOS***************************************************
******************************************************************************************************************************************************************/
/**
* \class ColaGen
* \brief Esta clase implementa una estructura lineal de tipo Cola generica
*
* Esta clase permite insertar elementos por el principio de la cola y extraerlos por el final
*/
template <class T>
class ColaGen<T*>{

/**
* \struct TipoNodo
* \brief Este registro representa un nodo de la cola
*/
typedef struct TipoNodo {
	T* dato_;		//!< Dato que contiene cada nodo de la cola 
	TipoNodo *sig_;	//!< Puntero al siguiente nodo de la cola
};

 public:
  ColaGen ();							//!< Inicializa los datos de la cola (punteros a NULL)
  ColaGen (const ColaGen &C);					//!< Inicializa los datos de la cola por copia
  void insertar_dato (T* dato);				//!< Inserta un dato en la cola (por el final)
  void insertar_nodo (TipoNodo *nodo);			//!< Inserta un dato enviado en un nodo en la cola (por el final)
  T* get ()const;						//!< Devuelve el dato que se encuentra en el frente de la cola
  bool borrar ();						//!< Elimina el dato que se encuentre en el frente de la cola
  ostream& mostrar () const;					//!< Muestra la cola por pantalla y guarda la informacion mostrada en un flujo
  inline bool vacia () const {return num_elementos_==0;}	//!< Devuelve verdadero si la cola está vacía
  inline int get_num_elementos () {return num_elementos_;}	//!< Devuelve el número de elementos de la cola
  ~ColaGen ();							//!< libera la memoria de la cola (OJO ¡NO DE LOS DATOS CONTENIDOS!)

 private:
  TipoNodo *frente_;		//!< Puntero al frente de la cola
  TipoNodo *fin_;		//!< Puntero al final de la cola
  int num_elementos_;		//!< Número de elementos de la cola, utilizado para realizar recorridos

};


/**
 * Constructor por defecto de la clase ColaGen
 */
template <class T>
ColaGen <T*>::ColaGen()
{
  this->num_elementos_=0;
  this->frente_=NULL;
  this->fin_=NULL;
}


/**
 * Constructor por copia de la clase ColaGen
 * @param C Cola desde la cual se inicializara esta clase
 */
template <class T>
ColaGen <T*>::ColaGen(const ColaGen & C)
{
  frente_=NULL;
  fin_=NULL;
  num_elementos_=0;
  TipoNodo *aux=C.frente_;
  while (aux!=NULL){
    this->insertar_nodo(aux);
    aux=aux->sig_;
  }
}


/**
 * Inserta un dato en la cola
 * @param dato elemento que se quiere insertar en la cola
 */
template <class T>
void ColaGen <T*>::insertar_dato(T* dato)
{
  TipoNodo *aux=this->fin_, *nodo=new TipoNodo;
  nodo->dato_ = dato;
  nodo->sig_=NULL;
  if(this->vacia()) { this->frente_=nodo; }
  else {fin_->sig_=nodo;}
  fin_=nodo;
  num_elementos_++;
}


/**
 * Inserta el dato, contenido en un nodo, en la cola
 * @param nodo TipoNodo que contiene el dato que queremos insertar
 */
template <class T>
void ColaGen <T*>::insertar_nodo(TipoNodo* nodo)
{
  TipoNodo *nodo2=new TipoNodo,*aux=frente_;
  nodo2->dato_=nodo->dato_;
  nodo2->sig_=NULL;
  if(aux==NULL) {frente_=nodo2;}
  else{
    while(aux->sig_!=NULL)
      aux=aux->sig_;
    aux->sig_=nodo2;
  }
  this->fin_=nodo2;
  num_elementos_++;
}


/**
 * Obtiene el frente de la Cola
 * @return devuelve el frente de la cola
 */
template <class T>
T* ColaGen <T*>::get() const
{
  return frente_->dato_;
}


/**
 * Borra el frente de la cola
 * @return true si la cola no esta vacia, false en caso contrario
 */
template <class T>
bool ColaGen <T*>::borrar()
{
  if (frente_==NULL) return false;
  else{
    TipoNodo *aux=frente_;
    frente_=frente_->sig_;
    delete aux; aux=NULL;
    num_elementos_--;
    return true;
  }
}



/**
 * Destructor de la clase ColaGen
 */
template <class T>
ColaGen <T*>::~ ColaGen()
{
  TipoNodo *aux;
  while (frente_!=NULL){
    aux=frente_->sig_;
    delete frente_;
    frente_=aux;
  }
}


/**
 * Muestra la cola por panatalla
 * @return flujo con la informacion (Aun no implementado)
 */
template <class T>
ostream& ColaGen <T*>::mostrar() const
{
//   ostream flujo;
//   flujo<<"Mostrando una cola: \n";
//   if(this->vacia()) {flujo<<"La cola esta vacia. \n";}
//   else{
//     flujo<<"Frente: ";
//     TipoNodo *aux=this->frente_;
//     while(aux!=NULL){
//       flujo <<aux->dato_<<" - ";
//       aux=aux->sig_;
//     }
//   flujo<<'\n';
//   }
//   cout<<flujo;
//   return flujo;

  cout<<"Mostrando una cola: \n";
  if(this->vacia()) {cout<<"La cola esta vacia. \n";}
  else{
    cout<<"Frente: ";
    TipoNodo *aux=this->frente_;
    while(aux!=NULL){
      cout <<*aux->dato_<<" - ";
      aux=aux->sig_;
    }
  cout<<'\n';
  }
}



#endif //COLAGEN_H
