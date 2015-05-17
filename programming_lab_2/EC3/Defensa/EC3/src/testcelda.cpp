/**
* \file testcelda.cpp
* \brief Implementacion de los juegos de prueba de la clase celda
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
#include "celda.h"

//Creamos varias instancias con las que trabajar
class CeldaTest:public testing::Test  {
 protected:
  Celda ce1;
  Celda *cd2;
  Llave *llave1, *llave2;
  virtual void SetUp()  {
    llave1 = new Llave(1);
    llave2 = new Llave(2);
    cd2 = new Celda(1);
  }

  virtual void TearDown()  {
    delete cd2;
    delete llave1;
    delete llave2;
  }
};

TEST_F(CeldaTest, Modificadores_y_consultores_basicos){
  ASSERT_EQ(1,cd2->get_id());
  ASSERT_EQ(1,cd2->get_marca());
  ASSERT_EQ(-1,ce1.get_id());
  ASSERT_EQ(-1,ce1.get_id());
  cd2->set_id(5);
  ce1.set_marca(3);
  EXPECT_EQ(5,cd2->get_id());
  EXPECT_EQ(3,ce1.get_marca());
}

TEST_F(CeldaTest, Operaciones_con_llaves){
  cd2->set_llave(llave1);
  cd2->set_llave(llave2);
  EXPECT_EQ(1,cd2->sacar_llave()->get_id());
  EXPECT_EQ(2,cd2->sacar_llave()->get_id());
  EXPECT_EQ(0,cd2->sacar_llave());
}


