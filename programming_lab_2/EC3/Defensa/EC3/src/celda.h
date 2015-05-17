/**
* \file celda.h
* \brief Declaracion de la clase celda
* \date 20-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#ifndef CELDA_H
#define CELDA_H

using namespace std;

#include <iostream>
#include <queue>

#include "llave.h"
#include "persona.h"

/**
* \class Celda
* \brief Esta representa una celda de una planta
*/
class Celda
{
 public:
  Celda();
  Celda(const int &id);
  ~Celda();

  inline int get_id() const { return id_;} //!< Metodo que devuelve la id_ de la celda
  void set_id(const int &id);
  friend ostream& operator<<(ostream &flujo, const Celda &C);
  void set_llave(Llave *llave);
  Llave* sacar_llave();
  inline void set_marca(const int &marca) {marca_=marca;} //!< Cambia el valor de la marca por uno pasado por parametro
  inline int get_marca() const {return marca_;}  //!< obtiene el valor de la marca. @return marca de la celda
//   void Destruir();
  void set_persona(Persona* p);
  int ocupacion() const;
  Persona* get_persona() const;
  Persona* sacar_persona() const;
  bool Simular();

 private:
  int marca_; //!< atributo usado por el algoritmo de kruskall
  int id_;  //!< identificador de la celda (-1 si no esta inicializado)
  priority_queue<Llave*, vector<Llave*>, CompLlavesMayor>* llaves_; //!<llaves que contiene la celda
  queue<Persona*>* personas_; //!<personas que estan en la celda
};

#endif //de PLANTA_H
