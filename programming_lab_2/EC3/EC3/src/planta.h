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
#include "guardia.h"

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

#ifndef ENUM_POSICION
#define ENUM_POSICION
/*!
   \enum Posicion
   Tipo que representa los puntos cardinales
 */
typedef enum Posicion{NORTE, SUR, OESTE, ESTE};
#endif //ENUMPOSICION

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
  void Pintar() const;
  friend ostream& operator<<(ostream &salida, const Planta &p);
//   void Destruir();
  void set_persona(const int pos, Persona * p);
  Persona* get_persona(const int &pos) const;
  Persona* sacar_persona(const int &pos);
  void set_llave(const int &celda, Llave* llave);
  Llave* sacar_llave(const int &celda);
  int ocupacion(const int &pos) const;
  int get_ancho() const;
  int get_alto() const;
  inline bool Accesible(const int &origen, const int &destino) const {return grafo_.Adyacente(origen,destino);}/** Comprueba si dos accesibles entre si*/
  inline void set_id(const int &id) {id_ = id;} /** Asigna un nuevo id a la planta \n* @param id nuevo id*/
  inline int get_entrada() const { return entrada_;} /** Devuelve la entrada de la planta*/
  inline int get_salida() const { return salida_;} /** Devuelve la salida de la planta*/
  inline bool ProbarLlave(Llave * llave) {puerta_->ProbarLlave(llave);} /**Prueba una llave en la puerta \n *@param llave llave a probar*/
  inline bool AbrirPuerta() {return puerta_->Abrir();} /**Intenta abrir la puerta de la planta \n *@return true si se abre, false en caso contrario*/
  inline bool CerrarPuerta() {return puerta_->Cerrar();} /**Cierra la puerta de la planta \n *@return true si se ha cerrado correctamente,false en caso contrario*/
  inline TipoEstado EstadoPuerta() {return puerta_->get_estado();} /**Obtiene el estado de la puerta \n *@return estado de la puerta*/
  void CaminoMinimo(const int &origen, const int &destino, queue<Posicion> &camino) const;
  int get_vecina(const Posicion &p, const int &id) const;
  bool Simular();
  void RegistrarGuardia(Guardia *g);
  int get_num_guardias() const;
  Guardia* get_guardia(const int &numero) const;
  

 private:
  int id_; //!< identificador de la planta.
  int ancho_; //!< ancho de la planta
  int alto_; //!< alto de la planta
  int entrada_; //!< entrada de la planta
  int salida_; //!< salida de la planta
  Grafo grafo_;  //!< grafo que controla los caminos de la planta
  Puerta *puerta_;  //!< puntero a puerta de la planta
  vector <Celda*> celdas_;  //!< vector que almacena punteros a todas las celdas.
  int n_llaves_; //!< Numero de llaves diferentes generadas en la planta.
  vector< Guardia*> guardias_; //!< Lista de los guardias de la planta.

  void IniciarParedes();
  void GenerarAtajos();
  bool HayAtajo(const Posicion &p,const int &id) const;
  bool ParedValida(const Posicion &p,const int &id) const;
  bool GeneraAtajo(const Posicion &p, const int &id) ;
  void ColocarLlaves(queue <Llave*> &llaves);
  void PrepararLlaves(const int &n_llaves, ColaGen<Llave*> *configuracion, queue<Llave*> &llaves);
  bool RutaRecursivo(const int &posicion, bool visitados[kMaxVert],list<Posicion> &ruta, int ultimo_movimiento) const;
  void ObtenerMasVisitadas(int frecuencia[kMaxVert]) const;
  void VisitadosRecursivo(const int &posicion, bool visitados[kMaxVert], stack < int > ruta, int frecuencia[kMaxVert]) const;
  void MostrarRutaEscape();
  void CalcularRuta(list<Posicion> &ruta) const;
};

#endif //de PLANTA_H
