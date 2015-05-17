/**
* \file prision.h
* \brief Implementación de la clase Prision
* \date 28/04/09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Curso 08/09
*/

#ifndef PRISION_H
#define PRISION_H

#include "planta.h"
/**
* \class Prision
* \brief Clase con un modelo singleton que controla la prision
*/
class Prision{
 public:
  ~Prision();
  static Prision* get_instancia();
  void set_planta(Planta* p);
  int get_numero_plantas() const;
  Planta* get_planta(const int &posicion) const;
  void MostrarPrision() const;
  void Destruir();
 private:
  static Prision* instancia_;
  Prision();

  vector<Planta*> *plantas_; //!< Vector que contiene todas las plantas de la prision
};

#endif //PRISION_H
