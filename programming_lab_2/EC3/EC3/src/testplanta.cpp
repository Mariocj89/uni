/**
* \file testplanta.cpp
* \brief Implementacion de los juegos de prueba de la clase planta
* \date 04-05-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 2
*   \b Curso 2º
*/

#include <gtest/gtest.h>
#include "planta.h"

TEST(TestPlanta,MetodosBasicos){
  Planta P(0,3,3,0,8,10,3);
  EXPECT_EQ(0,P.get_id());
  EXPECT_EQ(0,P.ocupacion(3));
  EXPECT_EQ(0,P.get_entrada());
  EXPECT_EQ(8,P.get_salida());
  EXPECT_EQ(3,P.get_alto());
  EXPECT_EQ(3,P.get_ancho());
  EXPECT_FALSE(P.Accesible(0,7));
  EXPECT_TRUE(P.Accesible(0,3));
  EXPECT_FALSE(P.AbrirPuerta());
  EXPECT_EQ(0,P.get_num_guardias());
//   P.Destruir();
}
