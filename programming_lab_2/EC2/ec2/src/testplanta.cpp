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
}
