/**
* \file planta.h
* \brief Declaracion de la clase planta
* \date 20-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/


#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <stack>

#include "celda.h"
#include "grafo.h"
#include "puerta.h"
#include "genaleatorios.h"
#include "errorpuerta.h"
#include "errornumerollaves.h"
#include "errortamanio.h"
#include "registro.h"

#ifndef PLANTA_H
#define PLANTA_H



/*!
   \var kDepurarPlanta
   Variable constante utilizada para mostrar o no mensajes de depuracion de programa
 */
const int kDepurarPlanta=0;

/*!
   \var kMaxLlavesPorCelda
   Variable constante utilizada para mostrar o no mensajes de depuracion de programa
 */
const int kMaxLlavesPorCelda=5;

/*!
   \enum Posicion
   Tipo que representa los puntos cardinales
 */
typedef enum Posicion{NORTE, SUR, OESTE, ESTE};

/**
* \class Planta
* \brief Esta representa una planta de la prision
*/
class Planta
{
 public:
  Planta(const int &identificador, const int &ancho, const int &alto, const int &entrada, const int &salida, const int &n_llaves, const int &altura_control);
  ~Planta();
  int get_id() const;
  friend ostream& operator<<(ostream &salida, const Planta &p);
  void Destruir();

 private:
  int id_; //!< identificador de la planta.
  int ancho_; //!< ancho de la planta
  int alto_; //!< alto de la planta
  int entrada_; //!< entrada de la planta
  int salida_; //!< salida de la planta
  Grafo grafo_;  //!< grafo que controla los caminos de la planta
  Puerta *puerta_;  //!< puntero a puerta de la planta
  vector <Celda*> celdas_;  //!< vector que almacena punteros a todas las celdas.

  void IniciarParedes();
  void GenerarAtajos();
  bool HayAtajo(const Posicion &p,const int &id) const;
  bool ParedValida(const Posicion &p,const int &id) const;
  bool GeneraAtajo(const Posicion &p, const int &id) ;
  int get_vecina(const Posicion &p, const int &id) const;
  void ColocarLlaves(queue <Llave*> &llaves);
  void PrepararLlaves(const int &n_llaves, ColaGen<Llave*> *configuracion, queue<Llave*> &llaves);
  bool RutaRecursivo(const int &posicion, bool visitados[kMaxVert],list<Posicion> &ruta, int ultimo_movimiento) const;
  void ObtenerMasVisitadas(int frecuencia[kMaxVert]) const;
  void VisitadosRecursivo(const int &posicion, bool visitados[kMaxVert], stack < int > ruta, int frecuencia[kMaxVert]) const;
  void MostrarRutaEscape();
  void CalcularRuta(list<Posicion> &ruta) const;
};

#endif //de PLANTA_H
