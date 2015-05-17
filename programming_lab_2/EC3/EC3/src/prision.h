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

/**
* \var kNumCeldaCastigo
* \brief Constante con el numero de la celda de castigo
*/
const int kNumCeldaCastigo = 1101;
#include <iterator>
#include "planta.h"
#include "persona.h"
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
  void set_persona(const int &planta, const int &pos, Persona *p);
  int ocupacion_celda(const int &planta, const int &celda) const;
  Persona* sacar_persona(const int &planta, const int celda);
  Persona* get_persona(const int &planta, const int &celda) const;
  int get_ancho_planta(const int &planta) const;
  int get_alto_planta(const int &planta) const;
  int get_entrada_panta(const int &planta) const;
  int get_salida_planta(const int &planta) const;
  void meter_celda_castigo(Persona *p);
  void meter_en_fugados(Persona *p);
  void IniciarSimulacion();

  inline void inc_numero_presos() {n_presos_++;} /**Metodo que incrementa en 1 el contador con el numero de presos que hay en la prision*/
  inline int get_turno() {return turno_;}  /** Metodo que obtiene el turno actual de la simulacion \n * @return turno de la simulacion*/

 private:
  static Prision* instancia_;
  void MostrarTodos();
  Prision();

  list <Persona*> celda_castigo_; //!< Lista de las personas almacenadas en la celda de castigo
  list <Persona*> fugados_; //!< Lista de personas que se han fugado
  int turno_; //!< Entero que almacena el turno actual de la simulacion
  vector<Planta*> *plantas_; //!< Vector que contiene todas las plantas de la prision
  int n_presos_; //!< Numero de presos que hay en la prision
};

#endif //PRISION_H
