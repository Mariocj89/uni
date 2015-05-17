/**
* \file testllave.cpp
* \brief Implementacion de los juegos de prueba de la clase llave
* \date 06-04-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 2
*   \b Curso 2º
*/

#include <gtest/gtest.h>
#include "llave.h"

//Creamos varias instancias con las que trabajar
class LlaveTest:public testing::Test  {
 protected:
  Llave *a, *b, *c;
  virtual void SetUp()  {
    a= new Llave(1);
    b= new Llave(2);
    c= new Llave(3);
  }

  virtual void TearDown()  {
    delete a;
    delete b;
    delete c;
  }
};

TEST_F(LlaveTest,ModificadoresyConsultores){
  EXPECT_EQ(1,a->get_id());
  EXPECT_EQ(3,c->get_id());
  a->set_id(7);
  EXPECT_EQ(7,a->get_id());
  a->set_id(1);
  EXPECT_EQ(1,a->get_id());
}

TEST_F(LlaveTest,SobrecargaOperadores){
  EXPECT_TRUE(*a<*b);
  EXPECT_FALSE(*c<*a);
  EXPECT_TRUE(*b>*a);
  EXPECT_TRUE(*b!=*a);
  EXPECT_TRUE(*c==*c);
}



