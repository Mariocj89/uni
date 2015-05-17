/**
* \file llave.h
* \brief Implementacion del header de la clase Llave
* \date 13-03-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 1
*   \b Curso 2º
*/

#ifndef LLAVE_H
#define LLAVE_H

using namespace std;

#include <iostream>

/**
* \class Llave
* \brief Esta clase representa los atributos y metodos de llaves
*
* La clase llave contendra un entero con el identificador de cada llave,
* usado mas adelante en las puertas.
*/
class Llave{
 public:
  Llave();
  Llave(const int &i);
  Llave(const Llave &L);

  int get_id() const;
  void set_id(const int& a); 
  
  ~Llave();
  Llave operator=(const Llave &L);
  bool operator<(const Llave &L) const;
  bool operator>(const Llave &L) const;
  bool operator==(const Llave &L) const;
  bool operator!=(const Llave &L) const;

  friend ostream& operator<<(ostream &flujo, const Llave &L);

 private:
  int id_; //!<Entero que contiene el identificador de la llave, (-1 representa inicializado pero sin valor asignado)
};

/**
 * \class CompLlavesMayor
 * \brief Objeto funcion para comparar si un puntero a una llave es mayor que otra.
 */
class CompLlavesMayor{
 public:
  inline bool operator() (Llave* x, Llave* y) const {return x->get_id()>y->get_id();}
};



#endif //de LLAVE_H
