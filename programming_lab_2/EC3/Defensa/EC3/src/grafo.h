/**
* \file grafo.h
* \brief Declaracion de la clase grafo
* \date 11-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef GRAFO_H
#define GRAFO_H

/**
* \var kMaxVert
* \brief Constante con el numero maximo de vertices que tendra el grafo
*/
const int kMaxVert = 300;

/**
* \var kInfinito
* \brief Constante para tratar el valor 9999 como infinito
*/
const int kInfinito = 9999;

/**
* \var kNoValor
* \brief Constante para tratar el valor -1 como ausencia de valor
*/
const int kNoValor = -1;

#include <iostream>
#include <cstdlib>

using namespace std;

/*!
   \def kDepurarGrafos
   Variable constante utilizada para mostrar o no mensajes de depuracion de programa
 */
#define kDepurarGrafos 0

/*!
   \def DEPURAR_GRAFO_MSG
   Macro utilizada para mostrar mensajes de depuracion de programa y retener los mensajes en pantalla
 */
#define DEPURAR_GRAFO_MSG(msg) if (kDepurarGrafos){ cout<<msg; cin.get();}

/*!
   \typedef TipoNodoGrafo
   \brief Tipo referente a los nodos del grafo.(entero)
 */
typedef int TipoNodoGrafo;

/*!
   \typedef TipoArcoGrafo
   \brief Tipo referente al valor de los arcos del grafo.(entero)
 */
typedef int TipoArcoGrafo;

/*!
   \typedef TipoMatrizAdyacencia
   \brief Matriz de tamaño kMaxVer x kMaxVert de tipo TipoArcoGrafo que se usara para representar la matriz de adyacencia del grafo
 */
typedef TipoArcoGrafo TipoMatrizAdyacencia [kMaxVert][kMaxVert];

/*!
   \typedef TipoMatrizBooleana
   \brief Matriz de bool de tamaño kMaxVert x kMaxVert
 */
typedef bool TipoMatrizBooleana [kMaxVert][kMaxVert];

/*!
   \typedef TipoVectorNodos
   \brief Tipo que representa un vector estatico de nodos de tamaño kMaxVert
 */
typedef TipoNodoGrafo TipoVectorNodos[kMaxVert];

// ---------------------------------------------------------
// Para calcular los adyacentes a un nodo
#include <queue>

/*!
   \typedef TipoCjtoNodos
   \brief Cola para almacenar nodos.
 */
typedef queue<TipoNodoGrafo> TipoCjtoNodos;

/*!
   \struct TipoArco
   \brief Tipo que representa un arco, con su origen "x" y su destino "y"
 */
struct TipoArco{
  TipoNodoGrafo x; //!< Nodo de origen del arco
  TipoNodoGrafo y; //!< Nodo de destino del arco
};


int Maximo(const int &a, const int &b);
int Minimo(const int &a, const int &b);


/**
* \class Grafo
* \brief Esta clase define un grafo no dirigido valuado
*/
class Grafo
{
 public:
  Grafo(void);
  inline int get_num_nodos(void) const { return num_nodos_; } //!< Metodo que devuelve el numero de nodos del grafo
  bool EsVacio(void) const ;
  bool set_arco(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino, const int &valor);
  bool del_arco(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino);
  bool Adyacente(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino) const ;
  int  get_arco(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino) const ;
  bool set_nodo(const TipoNodoGrafo &n);
  bool del_nodo(const TipoNodoGrafo &nodo);
  void get_warshall_path(TipoMatrizBooleana &WP) const ;
  void get_floyd_path(TipoMatrizAdyacencia &FP) const ;
  void get_floyd_cost(TipoMatrizAdyacencia &FC) const ;
  int  get_pos_nodo(const TipoNodoGrafo &N) const ;

  // ------- Metodos para mostrar
  void MostrarArcos(void) const ;
  void MostrarNodos(void) const ;
  void MostrarPW(void) const ;
  void MostrarFloydC(void) const ;
  void MostrarEnProfundidad(void) const ;
  void MostrarEnAnchura(void) const ;

  // ------- Algoritmos sobre Grafos
  void Warshall(void);
  void Floyd(void);
  void Siguiente(const TipoNodoGrafo &origen, const TipoNodoGrafo destino, TipoNodoGrafo &sig) const ;//NO &destino (debido a recursividad)
  void Adyacentes(const TipoNodoGrafo &origen, TipoCjtoNodos &ady) const ;
  TipoNodoGrafo MayorGrado(int &grado) const ;
  int MasDistantes(TipoNodoGrafo &a,TipoNodoGrafo &b) const ;
  int MasCorto(TipoNodoGrafo&a, TipoNodoGrafo &b) const ;
  void ANSaltos(const TipoNodoGrafo &nodo, TipoCjtoNodos &nodos, const int &distancia) const ;
  int Excentricidad(const TipoNodoGrafo &nodo) const ;
  TipoNodoGrafo Centro() const ;
  bool ExisteCiclo(const TipoNodoGrafo &nodo) const ;

  friend ostream& operator <<(ostream &flujo, const Grafo &G);

 private:

  void ObtenerEnProf(const int &posicion, bool visitados[kMaxVert], TipoCjtoNodos &prof) const ;
  void ObtenerEnAnch(const int &posicion, bool visitados[kMaxVert], TipoCjtoNodos &anch) const ;
  int num_nodos_;              //!< Numero de nodos del grafo
  TipoVectorNodos nodos_;          //!< Vector que almacena los nodos del grafo
  TipoMatrizAdyacencia arcos_;    //!< Matriz de adyacencia, para almacenar los arcos del grafo

  TipoMatrizBooleana warshall_path_;//!< Matriz boleana de Camino (Warshall - Path)
  TipoMatrizAdyacencia floyd_cost_;//!< Matriz de Costes (Floyd - Cost)
  TipoMatrizAdyacencia floyd_path_;//!< Matriz de Camino (Floyd - Path)

};

#endif
