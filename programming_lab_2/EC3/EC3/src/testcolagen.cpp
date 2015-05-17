/**
* \file testcolagen.cpp
* \brief Implementacion de los juegos de prueba de la clase ColaGen
* \date 07-04-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 2
*   \b Curso 2º
*/

#include <gtest/gtest.h>
#include "colagen.h"

//Creamos varias instancias con las que trabajar
class ColaGenTest:public testing::Test  {
 protected:
  ColaGen <int> C1;
  ColaGen <int*> D1;
  int *vector[10];
  virtual void SetUp()  {
    for (int i=0;i<10;i++)
      vector[i]=new int(i);
  }

  virtual void TearDown()  {
    for (int i=0;i<10;i++)
      delete vector[i];
  }
};

TEST_F(ColaGenTest,ConsultoresyModificadores){
  ASSERT_TRUE(C1.vacia());
  C1.insertar_dato(1);
  ASSERT_FALSE(C1.vacia());
  ASSERT_EQ(1,C1.get());
  C1.insertar_dato(2);
  C1.insertar_dato(3);
  C1.insertar_dato(4);
  ASSERT_EQ(4,C1.get_num_elementos());
  EXPECT_TRUE(C1.borrar());
  EXPECT_EQ(2,C1.get());
  EXPECT_TRUE(C1.borrar());
  EXPECT_EQ(3,C1.get());
  EXPECT_TRUE(C1.borrar());
  EXPECT_EQ(4,C1.get());
  EXPECT_TRUE(C1.borrar());
  EXPECT_FALSE(C1.borrar());

  //con elementos dinamicos:

  ASSERT_TRUE(D1.vacia());
  D1.insertar_dato(vector[1]);
  ASSERT_FALSE(D1.vacia());
  ASSERT_EQ(vector[1],D1.get());
  D1.insertar_dato(vector[2]);
  D1.insertar_dato(vector[3]);
  D1.insertar_dato(vector[4]);
  ASSERT_EQ(4,D1.get_num_elementos());
  EXPECT_TRUE(D1.borrar());
  EXPECT_EQ(vector[2],D1.get());
  EXPECT_TRUE(D1.borrar());
  EXPECT_EQ(vector[3],D1.get());
  EXPECT_TRUE(D1.borrar());
  EXPECT_EQ(vector[4],D1.get());
  EXPECT_TRUE(D1.borrar());
  EXPECT_FALSE(D1.borrar());


}

TEST_F(ColaGenTest,Constructores){
  ASSERT_TRUE(C1.vacia()&&D1.vacia());

  C1.insertar_dato(2);
  C1.insertar_dato(3);
  C1.insertar_dato(4);
  ColaGen <int> CC(C1);

  ASSERT_EQ(C1.get_num_elementos(),CC.get_num_elementos());
  for(int i=0;i<C1.get_num_elementos();i++){
    ASSERT_EQ(C1.get(),CC.get());
    C1.borrar();
    CC.borrar();
  }

  //con elementos dinamicos

  for (int i=0;i<10;i++)
    D1.insertar_dato(vector[i]);
  ColaGen <int*> DD(D1);

  ASSERT_EQ(D1.get_num_elementos(),DD.get_num_elementos());
  for(int i=0;i<D1.get_num_elementos();i++){
    ASSERT_EQ(D1.get(),DD.get());
    D1.borrar();
    DD.borrar();
  }

}
