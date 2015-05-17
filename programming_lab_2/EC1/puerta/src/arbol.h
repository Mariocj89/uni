/**
* \file arbol.h
* \brief Declaración de la clase Árbol Binario de Búsqueda
* \author
*   \b Profesores LPII \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 07/08
*   \b Revisado en: Curso 08/09
*/

#ifndef _ARBOL_H
#define _ARBOL_H

#include <iostream>

using namespace std;

/*******************************************************************************************************
******************************Plantilla de Arboles con elementos estaticos******************************
*******************************************************************************************************/

#ifndef DEPURAR
/*!
   \def DEPURAR
   Variable constante utilizada para mostrar o no mensajes de depuración de programa
 */
#define DEPURAR 0

/*!
   \def DEPURAR_MSG
   Macro utilizada paa mostrar mensajes de depuración de programa y retener los mensajes en pantalla
 */
#define DEPURAR_MSG(msg) if (DEPURAR){ cout<<msg; }
#endif //DEPURAR



/**
* \class Arbol
* \brief Esta clase define un Árbol Binario de Búsqueda
*
*/
template <class T>
class Arbol
{
public:
  Arbol();
  Arbol(Arbol *hizq_,const T& dato,Arbol *hder_);
  Arbol *hijoIzq() const;
  Arbol *hijoDer() const;
  T raiz() const;
  bool vacio() const;
  bool insertar(const T& dato);
  bool pertenece (const T& dato) const; 
  void borrar (const T& dato);
  int Profundidad() const;
  bool EsHoja() const;
  bool EsHoja(const T& dato) const;
  int NodosNivel(const int& nivel) const;
  void NumNodos(int &hojas, int& nodos) const;
  int NumNodos(const int& nivel) const;
  int NumNodos() const;
  bool Equilibrado() const;
  Arbol<T>* Equilibrar();


  void InOrden() const;
  void PreOrden() const;
  void PostOrden() const;


  ~Arbol();
 private:
  T dato_raiz_; //!< Raiz del arbol
  Arbol <T> *hizq_, *hder_; //!< Estos atributos son las 2 ramas del arbol
  bool vacio_; //!< Indica si un arbol esta vacio(es decir, no tenemos que tener en cuenta lo que contenga)

  Arbol *borrarOrden(const T& dato);
  int maximo(const int &a,const int &b) const;
  Arbol<T>* RotarDerecha();
  Arbol<T>* RotarIzquierda();
  Arbol<T>* DobleRotarDerecha();
  Arbol<T>* DobleRotarIzquierda();
  int FactorBalanceo() const;
};


/**
* Constructor por defecto. Inicializa un objeto de tipo Arbol
* \param "" No recibe parametros
* \return Devuelve un objeto tipo Arbol inicializado
*/
template <class T>
Arbol <T>::Arbol()
{
    DEPURAR_MSG ("Entra en Arbol::Arbol"<<endl);
    vacio_ = true;
    hizq_ = NULL;
    hder_ = NULL;
    DEPURAR_MSG ("Sale de Arbol::Arbol"<<endl);
}

/**
* Constructor parametrizado. Inicializa un objeto de tipo Arbol
* \param hizq_ Hijo izquierdo del árbol a crear
* \param dato dato a insertar en la raíz
* \param hder_ Hijo derecho del árbol a crear
* \return Devuelve un objeto de tipo Arbol inicializado
*/
template <class T>
Arbol <T>::Arbol(Arbol *hizq_,const T& dato,Arbol *hder_)
{
    DEPURAR_MSG ("Entra en Arbol::Arbol(Arbol*,DatoARbol&,Arbol*): "<<dato<<endl);
    this->dato_raiz_=dato;
    if(hizq_==NULL) this->hizq_=NULL;
    else this->hizq_=new Arbol(*hizq_);
    if(hder_==NULL) this->hder_=NULL;
    else this->hder_=new Arbol(*hder_);
    this->vacio_=false;
    DEPURAR_MSG ("Sale de Arbol::Arbol(Arbol*,DatoARbol&,Arbol*)"<<endl);
}

/**
* \return Devuelve un objeto Arbol con el subárbol izquierdo
*/
template <class T>
Arbol <T> *Arbol <T>::hijoIzq() const
{
    return hizq_;
}

/**
* \return Devuelve un objeto Arbol con el subárbol derecho
*/
template <class T>
Arbol <T> *Arbol <T>::hijoDer() const
{
    return hder_;
}

/**
 * Metodo que nos devuelve el numero de nodos que tiene un nivel.
 * @param nivel nivel en el que hallar el numero de nodos
 * @return 
 */
template <class T>
int Arbol <T>::NodosNivel(const int& nivel) const
{
  if(this->vacio()) return 0;
  if(nivel==1) return 1;
  else return this->hizq_->NodosNivel(nivel-1)+this->hder_->NodosNivel(nivel-1);
}

/**
 * Comprueba si un arbol es hoja o no
 * @return true si el arbol es hoja(no tiene hijos), false en caso contrario
 */
template <class T>
bool Arbol <T>::EsHoja() const
{
  return !this->vacio_&&hder_==NULL&&hizq_==NULL;
}


/**
 * Modulo que calcula si un nodo es una hoja o no.
 * @param dato dato que buscamos
 * @return true si el nodo que buscamos es hoja, false en caso contrario o si esta vacio.
 */
template <class T>
bool Arbol<T>::EsHoja(const T& dato) const
{
  if(this->vacio()) return false;
  if(dato_raiz_==dato)
    return this->EsHoja();
  else if(dato<dato_raiz_)
	 return this->hizq_->EsHoja(dato);
       else return this->hder_->EsHoja(dato);
}

/**
* \return Devuelve el valor almacenado en la raíz
*/
template <class T>
T Arbol <T>::raiz() const
{
    return dato_raiz_;
}

/**
* \return Devuelve true si el árbol está vacío
*/
template <class T>
bool Arbol <T>::vacio() const
{
    if(this==NULL) return true;
    else return vacio_;
}


/**
 * Metodo que halla la profundidad del arbol
 * @return profundidad del arbol
 */
template <class T>
int Arbol <T>::Profundidad() const
{
  if(this->vacio()) return 0;
  else return maximo(hder_->Profundidad(),hizq_->Profundidad())+1;
}

/**
 * Metodo que devuelve el maximo de dos enteros
 * @param a primer entero
 * @param b segundo entero
 * @return el mayor de los 2 enteros, en caso de ser iguales devuelve el segundo
 */
template <class T>
int Arbol <T>::maximo(const int &a,const int &b) const
{
  if(a>b) return a;
  else return b;
}

/**
* Inserta el valor dato en el Árbol Binario de Búsqueda
* \param dato Valor a insertar
* \return Retorna true si se insertó correctamente
*/
template <class T>
bool Arbol <T>::insertar(const T& dato)
{
    DEPURAR_MSG ("Entra en Arbol::Insertar(DatoARbol&): "<<dato<<endl);
    bool resultado=true;
    if (vacio()) {
        dato_raiz_ = dato;
		vacio_ = false;
	}
    else
    {
        if (dato_raiz_ != dato)
        {
            Arbol *aux;
            if ((dato)<(dato_raiz_))
            {
                if ((aux=hijoIzq())==NULL) {hizq_ = aux = new Arbol(NULL, dato, NULL); resultado==true;}
           	else {resultado = aux->insertar(dato);}
            }
            else
            {
                if ((aux=hijoDer())==NULL) {hder_ = aux = new Arbol(NULL, dato, NULL); resultado==true;}
           	else {resultado = aux->insertar(dato);}
            }

        }
        else
            resultado=false;
    }
    DEPURAR_MSG ("Sale de Arbol::Insertar(DatoARbol&)"<<endl);
    return resultado;
}

/**
* Indica si el valor dato existe en el Árbol Binario de Búsqueda
* \param dato Valor a insertar
* \return Devuelve true si encuentra un nodo con ese valor
*/
template <class T>
bool Arbol <T>::pertenece (const T& dato) const
{
    DEPURAR_MSG ("Entra en Arbol::pertenece(DatoARbol&): "<<dato<<endl);
    Arbol *aux;
    bool encontrado=false;
    if (!vacio())
    {
        if (dato == dato_raiz_)
            encontrado = true;
        else
        {
            if (dato < dato_raiz_)
                aux=hijoIzq();
            else
                aux = hijoDer();
            if (aux!=NULL)
                encontrado = aux->pertenece(dato);
        }
    }

    DEPURAR_MSG ("Sale de Arbol::pertenece(DatoARbol&)"<<endl);
    return encontrado;
}

/**
* Elimina el nodo que contenga el valor dato 
* \param dato Valor a eliminar
* \return No devuelve nada
*/
template <class T>
void Arbol <T>::borrar(const T& dato)
{
    DEPURAR_MSG ("Entra en Arbol::borrar(DatoARbol&): "<<dato<<endl);
    if (!vacio())
    {
		if (dato<dato_raiz_&&hizq_!=NULL) 
			hizq_ = hizq_->borrarOrden(dato);
        	else if (dato>dato_raiz_&&hder_!=NULL) 
			hder_ = hder_->borrarOrden(dato);
            	     else //En este caso el dato es el dato_raiz_
              		  if (hizq_==NULL && hder_==NULL)
                  		  vacio_ = true;
              		  else
               		     borrarOrden(dato);
    }
    DEPURAR_MSG ("Sale de Arbol::borrar(DatoARbol&)"<<endl);
}

/**
* Función privada auxiliar para realizar el borrado de un nodo. Reestructura el árbol tras el borrado
* \param dato Valor a eliminar
* \return Devuelve el árbol resultado del borrado
*/
template <class T>
Arbol <T> *Arbol <T>::borrarOrden(const T& dato)
{
    DEPURAR_MSG ("Entra en Arbol::borrarOrden(DatoARbol&): "<<dato<<endl);
    T datoaux;
    Arbol *retorno=this, *aborrar, *candidato, *antecesor;

    if (!vacio())
    {
		if (dato<dato_raiz_&&hizq_!=NULL)
			hizq_ = hizq_->borrarOrden(dato);
		else
			if (dato>dato_raiz_&&hder_!=NULL) 
				hder_ = hder_->borrarOrden(dato);
            else if(dato==dato_raiz_){
                aborrar=this;
                if ((hder_==NULL)&&(hizq_==NULL))
                { /*si es hoja*/
                    delete aborrar;
                    retorno=NULL;
                }
                else
                {
                    if (hder_==NULL)
                    { /*Solo hijo izquierdo*/
                        aborrar=hizq_;
                        datoaux=dato_raiz_;
                        dato_raiz_=hizq_->raiz();
                        hizq_->dato_raiz_ = datoaux;
                        hizq_=hizq_->hijoIzq();
                        hder_=aborrar->hijoDer();

                        retorno=this;
                    }
                    else
                        if (hizq_==NULL)
                        { /*Solo hijo derecho*/
                            aborrar=hder_;
                            datoaux=dato_raiz_;
                            dato_raiz_=hder_->raiz();
                            hder_->dato_raiz_ = datoaux;
                            hder_=hder_->hijoDer();
                            hizq_=aborrar->hijoIzq();

                            retorno=this;
                        }
                        else
                        { /* Tiene dos hijos */
                            candidato = hijoIzq();
                            antecesor = this;
                            while (candidato->hijoDer())
                            {
                                antecesor = candidato;
                                candidato = candidato->hijoDer();
                            }

                            /*Intercambio de datos de candidato*/
                            datoaux = dato_raiz_;
                            dato_raiz_ = candidato->raiz();
                            candidato->dato_raiz_=datoaux;
                            aborrar = candidato;
                            if (antecesor==this)
                                hizq_=candidato->hijoIzq();
                            else
                                antecesor->hder_=candidato->hijoIzq();
                        } //Eliminar solo ese nodo, no todo el subarbol
                    aborrar->hizq_=NULL;
                    aborrar->hder_=NULL;
                    delete aborrar;
                }
            }
    }

    DEPURAR_MSG ("Sale de Arbol::borrarOrden(DatoARbol&)"<<endl);
    return retorno;
}

/**
 * Metodo que devuelve por parametro el numero de hojas y nudos de un arbol.
 * @param hojas numero de hojas que contiene el arbol
 * @param nodos numero de nudos(nodos internos) que contiene el arbol
 * @PRE hojas y nodos deben valer 0
 */
template <class T>
void Arbol <T>::NumNodos(int &hojas, int&nodos) const
{
  if(!this->vacio())
    if(this->EsHoja()) hojas++;
    else {
      nodos++; 
      this->hder_->NumNodos(hojas, nodos);
      this->hizq_->NumNodos(hojas, nodos);
    }
}

/**
 * Devuelve el numero de nodos que contiene un arbol hasta un nivel dado
 * @param nivel ultimo nivel a contar
 * @return numero de nodos que tiene un arbol hasta el nivel "nivel"
 */
template <class T>
int Arbol <T>::NumNodos(const int& nivel) const
{
  if(this->vacio()||nivel<1) return 0;
  else return this->hder_->NumNodos(nivel-1)+this->hizq_->NumNodos(nivel-1)+1;
}

/**
 * Devuelve el numero de nodos que contiene un arbol
 * @return numero de nodos que tiene un arbol
 */
template <class T>
int Arbol <T>::NumNodos() const
{
  if(this->vacio()) return 0;
  else return hizq_->NumNodos()+hder_->NumNodos()+1;
}

/**
 * Comprueba si un arbol esta correctamente balanceado
 * @return true si el arbol esta equilibrado false en caso contrario
 */
template <class T>
bool Arbol<T>::Equilibrado() const
{
  int a=this->FactorBalanceo();
  if(this->vacio()) return true;
  else if(-2<a&&a<2) return (this->hizq_->Equilibrado()&&this->hder_->Equilibrado());
       else return false;
}

/**
 * Halla el factor de balanceo de el arbol actual
 * @return el factor de balanceo
 */
template <class T>
int Arbol<T>::FactorBalanceo() const
{
  if(!this->vacio()) return this->hizq_->Profundidad()-this->hder_->Profundidad();
  else return 0;
}

/**
 * Gira en sentido de las manecillas de reloj P(el puntero al nodo con factor de balance no permitido) alrededor de Q(Hijo izquierdo de P)
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T>* Arbol<T>::RotarDerecha()
{
  Arbol *P=this,*Q=this->hizq_;
  P->hizq_=Q->hder_;
  Q->hder_=P;
  return Q;
}

/**
 * Gira en sentido de contrario a las manecillas de reloj P(el puntero al nodo con factor de balance no permitido) alrededor de Q(Hijo izquierdo de P)
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T>* Arbol<T>::RotarIzquierda()
{
  Arbol *P=this,*Q=this->hder_;
  P->hder_=Q->hizq_;
  Q->hizq_=P;
  return Q;
}

/**
 * Rotacion a la izquierda de Q alrededor de R seguida de una rotacion  a la derecha
 * de P alrededor de R.
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T>* Arbol<T>::DobleRotarDerecha()
{
  Arbol *P=this,*Q=this->hizq_, *R=Q->hder_;
  Q->hder_=R->hizq_;
  P->hizq_=R->hder_;
  R->hizq_=Q;
  R->hder_=P;
  return R;
}

/**
 * Rotacion a la derecha de Q alrededor de R seguida de una rotacion a la izquierda
 * de P alrededor de R
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T>* Arbol<T>::DobleRotarIzquierda()
{
  Arbol *P=this,*Q=this->hder_, *R=Q->hizq_;
  Q->hizq_=R->hder_;
  P->hder_=R->hizq_;
  R->hizq_=P;
  R->hder_=Q;
  return R;
}

/**
 * Equilibra el arbol usando las funciones de rotar
 * @return retorna el arbol equilibrado
 */
template <class T>
Arbol<T>* Arbol<T>::Equilibrar()
{
  Arbol *aux=this;
  if(!this->vacio()){ //1
    hizq_=hizq_->Equilibrar();
    hder_=hder_->Equilibrar();
    if(!this->Equilibrado())   // 2
      if(this->FactorBalanceo()>0)  // 3
        if(this->hizq_->FactorBalanceo()>=0) aux=this->RotarDerecha();
	else return this->DobleRotarDerecha();
      else // 3
        if(this->hder_->FactorBalanceo()<=0) aux=this->RotarIzquierda();
	else aux=this->DobleRotarIzquierda();
    else aux=this;  // 2
    if(!aux->Equilibrado()) {aux=aux->Equilibrar();}
  }
  else {aux=this;} //1
  return aux;
}

/**
* Destructor por defecto. Destruye un objeto de tipo Arbol
* \param "" No recibe parametros
* \return No devuelve nada
*/
template <class T>
Arbol <T>::~Arbol()
{
    DEPURAR_MSG ("Entra en Arbol::~Arbol()"<<endl);
    Arbol *aux;
    if (!vacio())
    {
        if ((aux=hijoIzq())!=NULL)
            delete aux;
        if ((aux=hijoDer())!=NULL)
            delete aux;

        vacio_ = true;
    }
    DEPURAR_MSG ("Sale de Arbol::~Arbol()"<<endl);
}

/**
 * Metodo que muestra el arbol con un recorrido en profundidad inorden
 */
template <class T>
void Arbol <T>::InOrden() const
{
    Arbol <T> *aux;
    if (!this->vacio())
    {
        if (aux = this->hijoIzq())
            aux->InOrden();
        cout << this->raiz() <<endl;
        if (aux = this->hijoDer())
            aux->InOrden();
    }
}

/**
 * Metodo que muestra el arbol con un recorrido en profundidad preorden
 */
template <class T>
void Arbol <T>::PreOrden() const
{
    Arbol <T> *aux;
    if (!this->vacio())
    {

        cout << this->raiz() <<endl;
        if (aux = this->hijoIzq())
            aux->PreOrden();
        if (aux = this->hijoDer())
            aux->PreOrden();
    }
}

/**
 * Metodo que muestra el arbol con un recorrido en profundidad postorden
 */
template <class T>
void Arbol <T>::PostOrden() const
{
    Arbol <T> *aux;
    if (!this->vacio())
    {
        if (aux = this->hijoIzq())
            aux->PostOrden();
        if (aux = this->hijoDer())
            aux->PostOrden();
        cout << this->raiz() <<endl;
    }
}


/*******************************************************************************************************
******************************Plantilla de Arboles con elementos dinamicos******************************
*******************************************************************************************************/


/**
* \class Arbol
* \brief Esta clase define un Árbol Binario de Búsqueda
*
*/
template <class T>
class Arbol <T*>
{
public:
  Arbol();
  Arbol(Arbol *hizq,T* dato,Arbol *hder);
  Arbol *hijoIzq() const;
  Arbol *hijoDer() const;
  T* raiz() const;
  bool vacio() const;
  bool insertar(T* dato);
  bool pertenece (T* dato) const; 
  bool pertenece (const T &dato) const; 
  void borrar (T* dato);
  void borrar (const T &dato);
  int Profundidad() const;
  bool EsHoja() const;
  bool EsHoja(T* dato) const;
  bool EsHoja(const T &dato) const;
  int NodosNivel(const int& nivel) const;
  void NumNodos(int &hojas, int& nodos) const;
  int NumNodos(const int& nivel) const;
  int NumNodos() const;
  void Destruir();
  bool Equilibrado() const;
  Arbol<T*>* Equilibrar();


  void InOrden() const;
  void PreOrden() const;
  void PostOrden() const;
  ~Arbol();
 private:
  T* dato_raiz_;  //!< Raiz del arbol
  Arbol<T*> *hizq_, *hder_;  //!<Ramas del arbol
  bool vacio_;  //!< Boleano que indica si el arbol esta vacio(si los datos que contiene no son validos)


  Arbol *borrarOrden(T* dato);
  Arbol *borrarOrden(const T &dato);
  int maximo(const int &a,const int &b) const;
  Arbol<T*>* RotarDerecha();
  Arbol<T*>* RotarIzquierda();
  Arbol<T*>* DobleRotarDerecha();
  Arbol<T*>* DobleRotarIzquierda();
  int FactorBalanceo() const;
};


/**
* Constructor por defecto. Inicializa un objeto de tipo Arbol
* \param "" No recibe parametros
* \return Devuelve un objeto tipo Arbol inicializado
*/
template <class T>
Arbol <T*>::Arbol()
{
    DEPURAR_MSG ("Entra en Arbol::Arbol"<<endl);
    vacio_ = true;
    hizq_ = NULL;
    hder_ = NULL;
    DEPURAR_MSG ("Sale de Arbol::Arbol"<<endl);
}

/**
* Constructor parametrizado. Inicializa un objeto de tipo Arbol
* \param hizq Hijo izquierdo del árbol a crear
* \param dato dato a insertar en la raíz
* \param hder Hijo derecho del árbol a crear
* \return Devuelve un objeto de tipo Arbol inicializado
*/
template <class T>
Arbol <T*>::Arbol(Arbol *hizq,T* dato,Arbol *hder)
{
    DEPURAR_MSG ("Entra en Arbol::Arbol(Arbol*,DatoARbol&,Arbol*): "<<dato<<endl);
    if(dato!=NULL) {
    this->dato_raiz_=dato;
    this->vacio_=false;
    }
    else {dato_raiz_=NULL;
          vacio_=true;}
    if(hizq==NULL) this->hizq_=NULL;
    else this->hizq_=hizq;
    if(hder==NULL) this->hder_=NULL;
    else this->hder_=hder;
    DEPURAR_MSG ("Sale de Arbol::Arbol(Arbol*,DatoARbol&,Arbol*)"<<endl);
}

/**
* \return Devuelve un objeto Arbol con el subárbol izquierdo
*/
template <class T>
Arbol <T*> *Arbol <T*>::hijoIzq() const
{
    return hizq_;
}

/**
* \return Devuelve un objeto Arbol con el subárbol derecho
*/
template <class T>
Arbol <T*> *Arbol <T*>::hijoDer() const
{
    return hder_;
}

/**
* \return Devuelve el valor almacenado en la raíz
*/
template <class T>
T* Arbol <T*>::raiz() const
{
    return dato_raiz_;
}

/**
 * Metodo que nos devuelve el numero de nodos que tiene un nivel.
 * @param nivel nivel en el que hallar el numero de nodos
 * @return 
 */
template <class T>
int Arbol <T*>::NodosNivel(const int& nivel) const
{
  if(this->vacio()) return 0;
  if(nivel==1) return 1;
  else return this->hizq_->NodosNivel(nivel-1)+this->hder_->NodosNivel(nivel-1);
}

/**
 * Comprueba si un arbol es hoja o no
 * @return true si el arbol es hoja(no tiene hijos), false en caso contrario
 */
template <class T>
bool Arbol <T*>::EsHoja() const
{
  return !this->vacio_&&hder_==NULL&&hizq_==NULL;
}

/**
 * Modulo que calcula si un nodo es una hoja o no.
 * @param dato puntero a dato que buscamos
 * @return true si el nodo que buscamos es hoja, false en caso contrario o si esta vacio.
 */
template <class T>
bool Arbol<T*>::EsHoja(T* dato) const
{
  if(this->vacio()) return false;
  if(*dato_raiz_==*dato)
    return this->EsHoja();
  else if(*dato<*dato_raiz_)
	 return this->hizq_->EsHoja(dato);
       else return this->hder_->EsHoja(dato);
}

/**
 * Modulo que calcula si un nodo es una hoja o no.
 * @param dato dato que buscamos
 * @return true si el nodo que buscamos es hoja, false en caso contrario o si esta vacio.
 */
template <class T>
bool Arbol<T*>::EsHoja(const T &dato) const
{
  if(this->vacio()) return false;
  if(*dato_raiz_==dato)
    return this->EsHoja();
  else if(dato<*dato_raiz_)
	 return this->hizq_->EsHoja(dato);
       else return this->hder_->EsHoja(dato);
}

/**
* \return Devuelve true si el árbol está vacío
*/
template <class T>
bool Arbol <T*>::vacio() const
{
    if(this==NULL) return true;
    return vacio_;
}

/**
* Inserta el valor dato en el Árbol Binario de Búsqueda
* \param dato Valor a insertar
* \return Retorna true si se insertó correctamente
*/
template <class T>
bool Arbol <T*>::insertar(T* dato)
{
    DEPURAR_MSG ("Entra en Arbol::Insertar(DatoARbol*): "<<dato<<endl);
    bool resultado=true;
    if (vacio()) {
        dato_raiz_ =dato;
		vacio_ = false;
	}
    else
    {
        if (*dato_raiz_ != *dato)
        {
            Arbol *aux;
            if ((*dato)<(*dato_raiz_))
            {
                if ((aux=hijoIzq())==NULL) {hizq_ = aux = new Arbol(NULL, dato, NULL); resultado==true;}
           	else {resultado = aux->insertar(dato);}
            }
            else
            {
                if ((aux=hijoDer())==NULL) {hder_ = aux = new Arbol(NULL, dato, NULL); resultado==true;}
           	else {resultado = aux->insertar(dato);}
            }

        }
        else
            resultado=false;
    }
    DEPURAR_MSG ("Sale de Arbol::Insertar(DatoARbol*)"<<endl);
    return resultado;
}

/**
* Indica si el valor dato existe en el Árbol Binario de Búsqueda
* \param dato puntero a el valor buscado
* \return Devuelve true si encuentra un nodo con ese valor
*/
template <class T>
bool Arbol <T*>::pertenece (T* dato) const
{
    DEPURAR_MSG ("Entra en Arbol::pertenece(DatoARbol&): "<<dato<<endl);
    Arbol *aux;
    bool encontrado=false;
    if (!vacio())
    {
        if (*dato == *dato_raiz_)
            encontrado = true;
        else
        {
            if (*dato < *dato_raiz_)
                aux=hijoIzq();
            else
                aux = hijoDer();
            if (aux!=NULL)
                encontrado = aux->pertenece(dato);
        }
    }

    DEPURAR_MSG ("Sale de Arbol::pertenece(DatoARbol&)"<<endl);
    return encontrado;
}

/**
* Indica si el valor dato existe en el Árbol Binario de Búsqueda
* \param dato Valor buscado
* \return Devuelve true si encuentra un nodo con ese valor
*/
template <class T>
bool Arbol <T*>::pertenece (const T &dato) const
{
    DEPURAR_MSG ("Entra en Arbol::pertenece(DatoARbol&): "<<dato<<endl);
    Arbol *aux;
    bool encontrado=false;
    if (!vacio())
    {
        if (dato == *dato_raiz_)
            encontrado = true;
        else
        {
            if (dato < *dato_raiz_)
                aux=hijoIzq();
            else
                aux = hijoDer();
            if (aux!=NULL)
                encontrado = aux->pertenece(dato);
        }
    }

    DEPURAR_MSG ("Sale de Arbol::pertenece(DatoARbol&)"<<endl);
    return encontrado;
}


/**
* Elimina el nodo que contenga el valor dato 
* \param dato puntero a el valor a eliminar
* \return No devuelve nada
*/
template <class T>
void Arbol <T*>::borrar(T* dato)
{
    DEPURAR_MSG ("Entra en Arbol::borrar(DatoARbol*): "<<dato<<endl);
    if (!vacio())
    {
		if (*dato<*dato_raiz_&&hizq_!=NULL) 
			hizq_ = hizq_->borrarOrden(dato);
        	else if (*dato>*dato_raiz_&&hder_!=NULL) 
			hder_ = hder_->borrarOrden(dato);
            	     else //En este caso el dato es el dato_raiz_
              		  if (hizq_==NULL && hder_==NULL)
				  vacio_ = true;
              		  else
               		     borrarOrden(dato);
    }
    DEPURAR_MSG ("Sale de Arbol::borrar(DatoARbol*)"<<endl);
}

/**
* Elimina el nodo que contenga el valor dato 
* \param dato valor a eliminar
* \return No devuelve nada
*/
template <class T>
void Arbol <T*>::borrar(const T &dato)
{
    DEPURAR_MSG ("Entra en Arbol::borrar(DatoARbol*): "<<dato<<endl);
    if (!vacio())
    {
		if (dato<*dato_raiz_&&hizq_!=NULL) 
			hizq_ = hizq_->borrarOrden(dato);
        	else if (dato>*dato_raiz_&&hder_!=NULL) 
			hder_ = hder_->borrarOrden(dato);
            	     else //En este caso el dato es el dato_raiz_
              		  if (hizq_==NULL && hder_==NULL)
				  vacio_ = true;
              		  else
               		     borrarOrden(dato);
    }
    DEPURAR_MSG ("Sale de Arbol::borrar(DatoARbol*)"<<endl);
}


/**
* Función privada auxiliar para realizar el borrado de un nodo. Reestructura el árbol tras el borrado
* \param dato puntero a el Valor a eliminar
* \return Devuelve el árbol resultado del borrado
*/
template <class T>
Arbol <T*> *Arbol <T*>::borrarOrden(T* dato)
{
    DEPURAR_MSG ("Entra en Arbol::borrarOrden(DatoARbol&): "<<dato<<endl);
    T* datoaux;
    Arbol *retorno=this, *aborrar, *candidato, *antecesor;

    if (!vacio())
    {
		if (*dato<*dato_raiz_&&hizq_!=NULL)
			hizq_ = hizq_->borrarOrden(dato);
		else
			if (*dato>*dato_raiz_&&hder_!=NULL) 
				hder_ = hder_->borrarOrden(dato);
            else if(*dato==*dato_raiz_){
                aborrar=this;
                if ((hder_==NULL)&&(hizq_==NULL))
                { /*si es hoja*/
                    delete aborrar;
                    retorno=NULL;
                }
                else
                {
                    if (hder_==NULL)
                    { /*Solo hijo izquierdo*/
                        aborrar=hizq_;
                        datoaux=dato_raiz_;
                        dato_raiz_=hizq_->raiz();
                        hizq_->dato_raiz_ = datoaux;
                        hizq_=hizq_->hijoIzq();
                        hder_=aborrar->hijoDer();

                        retorno=this;
                    }
                    else
                        if (hizq_==NULL)
                        { /*Solo hijo derecho*/
                            aborrar=hder_;
                            datoaux=dato_raiz_;
                            dato_raiz_=hder_->raiz();
                            hder_->dato_raiz_ = datoaux;
                            hder_=hder_->hijoDer();
                            hizq_=aborrar->hijoIzq();

                            retorno=this;
                        }
                        else
                        { /* Tiene dos hijos */
                            candidato = hijoIzq();
                            antecesor = this;
                            while (candidato->hijoDer())
                            {
                                antecesor = candidato;
                                candidato = candidato->hijoDer();
                            }

                            /*Intercambio de datos de candidato*/
                            datoaux = dato_raiz_;
                            dato_raiz_ = candidato->raiz();
                            candidato->dato_raiz_=datoaux;
                            aborrar = candidato;
                            if (antecesor==this)
                                hizq_=candidato->hijoIzq();
                            else
                                antecesor->hder_=candidato->hijoIzq();
                        } //Eliminar solo ese nodo, no todo el subarbol
                    aborrar->hizq_=NULL;
                    aborrar->hder_=NULL;
                    delete aborrar;
                }
            }
    }

    DEPURAR_MSG ("Sale de Arbol::borrarOrden(DatoARbol&)"<<endl);
    return retorno;
}

/**
* Función privada auxiliar para realizar el borrado de un nodo. Reestructura el árbol tras el borrado
* \param dato Valor a eliminar
* \return Devuelve el árbol resultado del borrado
*/
template <class T>
Arbol <T*> *Arbol <T*>::borrarOrden(const T &dato)
{
    DEPURAR_MSG ("Entra en Arbol::borrarOrden(DatoARbol&): "<<dato<<endl);
    T* datoaux;
    Arbol *retorno=this, *aborrar, *candidato, *antecesor;

    if (!vacio())
    {
		if (dato<*dato_raiz_&&hizq_!=NULL)
			hizq_ = hizq_->borrarOrden(dato);
		else
			if (dato>*dato_raiz_&&hder_!=NULL) 
				hder_ = hder_->borrarOrden(dato);
            else if(dato==*dato_raiz_){
                aborrar=this;
                if ((hder_==NULL)&&(hizq_==NULL))
                { /*si es hoja*/
                    delete aborrar;
                    retorno=NULL;
                }
                else
                {
                    if (hder_==NULL)
                    { /*Solo hijo izquierdo*/
                        aborrar=hizq_;
                        datoaux=dato_raiz_;
                        dato_raiz_=hizq_->raiz();
                        hizq_->dato_raiz_ = datoaux;
                        hizq_=hizq_->hijoIzq();
                        hder_=aborrar->hijoDer();

                        retorno=this;
                    }
                    else
                        if (hizq_==NULL)
                        { /*Solo hijo derecho*/
                            aborrar=hder_;
                            datoaux=dato_raiz_;
                            dato_raiz_=hder_->raiz();
                            hder_->dato_raiz_ = datoaux;
                            hder_=hder_->hijoDer();
                            hizq_=aborrar->hijoIzq();

                            retorno=this;
                        }
                        else
                        { /* Tiene dos hijos */
                            candidato = hijoIzq();
                            antecesor = this;
                            while (candidato->hijoDer())
                            {
                                antecesor = candidato;
                                candidato = candidato->hijoDer();
                            }

                            /*Intercambio de datos de candidato*/
                            datoaux = dato_raiz_;
                            dato_raiz_ = candidato->raiz();
                            candidato->dato_raiz_=datoaux;
                            aborrar = candidato;
                            if (antecesor==this)
                                hizq_=candidato->hijoIzq();
                            else
                                antecesor->hder_=candidato->hijoIzq();
                        } //Eliminar solo ese nodo, no todo el subarbol
                    aborrar->hizq_=NULL;
                    aborrar->hder_=NULL;
                    delete aborrar;
                }
            }
    }

    DEPURAR_MSG ("Sale de Arbol::borrarOrden(DatoARbol&)"<<endl);
    return retorno;
}

/**
 * Metodo que halla la profundidad del arbol
 * @return profundidad del arbol
 */
template <class T>
int Arbol <T*>::Profundidad() const
{
  if(this->vacio()) return 0;
  else return maximo(hder_->Profundidad(),hizq_->Profundidad())+1;
}

/**
 * Metodo que devuelve el maximo de dos enteros
 * @param a primer entero
 * @param b segundo entero
 * @return el mayor de los 2 enteros, en caso de ser iguales devuelve el segundo
 */
template <class T>
int Arbol <T*>::maximo(const int &a,const int &b) const
{
  if(a>b) return a;
  else return b;
}

/**
 * Metodo que muestra el arbol con un recorrido en profundidad inorden
 */
template <class T>
void Arbol <T*>::InOrden() const
{
    Arbol <T*> *aux;
    if (!this->vacio())
    {
        if (aux = this->hijoIzq())
            aux->InOrden();
        cout << *this->raiz() <<endl;
        if (aux = this->hijoDer())
            aux->InOrden();
    }
}

/**
 * Metodo que muestra el arbol con un recorrido en profundidad preorden
 */
template <class T>
void Arbol <T*>::PreOrden() const
{
    Arbol <T*> *aux;
    if (!this->vacio())
    {
        cout << *this->raiz() <<endl;
        if (aux = this->hijoIzq())
            aux->PreOrden();
        if (aux = this->hijoDer())
            aux->PreOrden();
    }
}

/**
 * Metodo que muestra el arbol con un recorrido en profundidad postorden
 */
template <class T>
void Arbol <T*>::PostOrden() const
{
    Arbol <T*> *aux;
    if (!this->vacio())
    {
        if (aux = this->hijoIzq())
            aux->PostOrden();
        if (aux = this->hijoDer())
            aux->PostOrden();
        cout << *this->raiz() <<endl;
    }
}

/**
 * Metodo que devuelve por parametro el numero de hojas y nudos de un arbol.
 * @param hojas numero de hojas que contiene el arbol
 * @param nodos numero de nudos(nodos internos) que contiene el arbol
 * @PRE hojas y nodos deben valer 0
 */
template <class T>
void Arbol <T*>::NumNodos(int &hojas, int&nodos) const
{
  if(!this->vacio())
    if(this->EsHoja()) hojas++;
    else {
      nodos++; 
      this->hder_->NumNodos(hojas, nodos);
      this->hizq_->NumNodos(hojas, nodos);
    }
}

/**
 * Devuelve el numero de nodos que contiene un arbol hasta un nivel dado
 * @param nivel ultimo nivel a contar
 * @return numero de nodos que tiene un arbol hasta el nivel "nivel"
 */
template <class T>
int Arbol <T*>::NumNodos(const int& nivel) const
{
  if(this->vacio()||nivel<1) return 0;
  else return this->hder_->NumNodos(nivel-1)+this->hizq_->NumNodos(nivel-1)+1;
}

/**
 * Devuelve el numero de nodos que contiene un arbol
 * @return numero de nodos que tiene un arbol
 */
template <class T>
int Arbol <T*>::NumNodos() const
{
  if(this->vacio()) return 0;
  else return hizq_->NumNodos()+hder_->NumNodos()+1;
}

/**
* Metodo que destruye todos los objetos del arbol, libera la memoria relativa a los objetos del arbol,
* pero NO BORRA EL ARBOL ni los objtetos eliminados del arbol anteriormente
* \return No devuelve nada
*/
template <class T>
void Arbol <T*>::Destruir()
{
    DEPURAR_MSG ("Entra en Arbol::Destruir()"<<endl);
    Arbol *aux;
    if (!vacio())
    {
        if ((aux=hijoIzq())!=NULL)
            {aux->Destruir();hizq_=NULL;}
        if ((aux=hijoDer())!=NULL)
            {aux->Destruir();hder_=NULL;}
        delete dato_raiz_;
        dato_raiz_=NULL;


    }
    DEPURAR_MSG ("Sale de Arbol::Destruir()"<<endl);
}

/**
 * Comprueba si un arbol esta correctamente balanceado
 * @return true si el arbol esta equilibrado false en caso contrario
 */
template <class T>
bool Arbol<T*>::Equilibrado() const
{
  int a=this->FactorBalanceo();
  if(this->vacio()) return true;
  else if(-2<a&&a<2) return (this->hizq_->Equilibrado()&&this->hder_->Equilibrado());
       else return false;
}

/**
 * Halla el factor de balanceo de el arbol actual
 * @return el factor de balanceo
 */
template <class T>
int Arbol<T*>::FactorBalanceo() const
{
  if(!this->vacio()) return this->hizq_->Profundidad()-this->hder_->Profundidad();
  else return 0;
}

/**
 * Gira en sentido de las manecillas de reloj P(el puntero al nodo con factor de balance no permitido) alrededor de Q(Hijo izquierdo de P)
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T*>* Arbol<T*>::RotarDerecha()
{
  Arbol *P=this,*Q=this->hizq_;
  P->hizq_=Q->hder_;
  Q->hder_=P;
  return Q;
}

/**
 * Gira en sentido de contrario a las manecillas de reloj P(el puntero al nodo con factor de balance no permitido) alrededor de Q(Hijo izquierdo de P)
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T*>* Arbol<T*>::RotarIzquierda()
{
  Arbol *P=this,*Q=this->hder_;
  P->hder_=Q->hizq_;
  Q->hizq_=P;
  return Q;
}

/**
 * Rotacion a la izquierda de Q alrededor de R seguida de una rotacion  a la derecha
 * de P alrededor de R.
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T*>* Arbol<T*>::DobleRotarDerecha()
{
  Arbol *P=this,*Q=this->hizq_, *R=Q->hder_;
  Q->hder_=R->hizq_;
  P->hizq_=R->hder_;
  R->hizq_=Q;
  R->hder_=P;
  return R;
}

/**
 * Rotacion a la derecha de Q alrededor de R seguida de una rotacion a la izquierda
 * de P alrededor de R
 * @return retorna el arbol rotado
 */
template <class T>
Arbol<T*>* Arbol<T*>::DobleRotarIzquierda()
{
  Arbol *P=this,*Q=this->hder_, *R=Q->hizq_;
  Q->hizq_=R->hder_;
  P->hder_=R->hizq_;
  R->hizq_=P;
  R->hder_=Q;
  return R;
}

/**
 * Equilibra el arbol usando las funciones de rotar
 * @return retorna el arbol equilibrado
 */
template <class T>
Arbol<T*>* Arbol<T*>::Equilibrar()
{
  Arbol *aux=this;
  if(!this->vacio()){ //1
    hizq_=hizq_->Equilibrar();
    hder_=hder_->Equilibrar();
    if(!this->Equilibrado())   // 2
      if(this->FactorBalanceo()>0)  // 3
        if(this->hizq_->FactorBalanceo()>=0) aux=this->RotarDerecha();
	else return this->DobleRotarDerecha();
      else // 3
        if(this->hder_->FactorBalanceo()<=0) aux=this->RotarIzquierda();
	else aux=this->DobleRotarIzquierda();
    else aux=this;  // 2
    if(!aux->Equilibrado()) {aux=aux->Equilibrar();}
  }
  else {aux=this;} //1
  return aux;
}


/**
* Destructor por defecto. Destruye un objeto de tipo Arbol
* \param "" No recibe parametros
* \return No devuelve nada
*/
template <class T>
Arbol <T*>::~Arbol()
{
    DEPURAR_MSG ("Entra en Arbol::~Arbol()"<<endl);
    Arbol *aux;
    if (!vacio())
    {
        if ((aux=hijoIzq())!=NULL)
            {delete aux; hizq_=NULL;}
        if ((aux=hijoDer())!=NULL)
            {delete aux; hder_=NULL;}
        vacio_ = true;
    }
    DEPURAR_MSG ("Sale de Arbol::~Arbol()"<<endl);
}

#endif
