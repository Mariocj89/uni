/**
* \file testarbol.cpp
* \brief Implementacion de los juegos de prueba de la clase arbol (binario de busqueda)
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
#include "arbol.h"

//Creamos varias instancias con las que trabajar
class ArbolTest:public testing::Test  {
 protected:
  Arbol <int> E1, E2;
  Arbol <int*> D1, *D2;
  int* vector[20];
  virtual void SetUp()  {
    D2=new Arbol<int*>;
    for (int i=0;i<20;i++)
      vector[i]=new int(i);
  }

  virtual void TearDown()  {
    for (int i=0;i<20;i++)
      delete vector[i];
      delete D2;
  }
};

TEST_F (ArbolTest,ModificadoresyConsultores) {
  //comprobamos si ha construido bien el arbol:
  ASSERT_TRUE(E1.vacio());
  ASSERT_TRUE(NULL==E1.hijoIzq());
  ASSERT_TRUE(NULL==E2.hijoDer());

  //probamos el insertar
  ASSERT_TRUE(E1.insertar(5));
  EXPECT_FALSE(E1.vacio());
  EXPECT_TRUE(NULL==E1.hijoIzq());
  EXPECT_TRUE(NULL==E2.hijoDer());

  //probamos el consultor raiz
  ASSERT_EQ(5,E1.raiz());

  //insertamos varios datos:
  E1.insertar(4);
  E1.insertar(1);
  E1.insertar(6);
  E1.insertar(3);
  E1.insertar(9);
  E1.insertar(2);

  //probamos el pertenece y el insertar cuando existe el elemento
  EXPECT_TRUE(E1.pertenece(3));
  EXPECT_FALSE(E1.pertenece(8));
  ASSERT_FALSE(E1.insertar(1));

  //probamos borrar y profundidad
  EXPECT_EQ(5,E1.Profundidad());
  E1.borrar(5);
  E1.borrar(1);
  EXPECT_FALSE(E1.pertenece(5));
  EXPECT_FALSE(E1.pertenece(1));
  EXPECT_NE(5,E1.Profundidad());

  //inicializamos E2 y probamos eshoja()
  E2.insertar(4);
  EXPECT_TRUE(E2.EsHoja());
  E2.insertar(1);
  EXPECT_FALSE(E2.EsHoja());
  E2.insertar(6);
  E2.insertar(3);
  E2.insertar(9);
  E2.insertar(2);
  EXPECT_FALSE(E2.EsHoja());

  //probamos eshoja(const T& dato)
  EXPECT_TRUE(E2.EsHoja(2));
  EXPECT_TRUE(E2.EsHoja(9));
  EXPECT_FALSE(E2.EsHoja(6));
  EXPECT_FALSE(E2.EsHoja(4));
  EXPECT_FALSE(E2.EsHoja(5));

}

TEST_F (ArbolTest,OtrosMetodos) {
  //pasemos a trabajar con D1 y D2 (puesto que  la platilla dinamica tiene algunas diferencias
  for (int i=0;i<10;i++){
    ASSERT_TRUE(D1.insertar(vector[i]));
    ASSERT_TRUE(D2->insertar(vector[i]));
  }

  //probamos la sobrecarga del operador == y !=
  EXPECT_TRUE(D1==*D2);
  EXPECT_FALSE(*D2!=D1);
  D1.borrar(vector[9]);
  EXPECT_TRUE(D1!=*D2);
  EXPECT_FALSE(D1==*D2);

  //probamos nodosnivel,y  numnodos
  EXPECT_EQ(1,D2->NodosNivel(2));
  ASSERT_TRUE(D2->insertar(vector[15]));
  ASSERT_TRUE(D2->insertar(vector[13]));
  ASSERT_TRUE(D2->insertar(vector[17]));
  EXPECT_EQ(2,D2->NodosNivel(12));
  int hojas=0,nudos=0;
  D2->NumNodos(hojas,nudos);
  EXPECT_EQ(2,hojas);
  D2->borrar(vector[17]);
  D2->borrar(vector[13]);
  EXPECT_EQ(nudos,D2->NumNodos());
  EXPECT_EQ(1,D2->NumNodos(1));
  EXPECT_EQ(5,D2->NumNodos(5));

  //probamos equilibrar y equilibrado
  EXPECT_FALSE(D2->Equilibrado());
  D2=D2->Equilibrar();
  EXPECT_TRUE(D2->Equilibrado());
}
