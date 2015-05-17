/**
* \file testgrafo.cpp
* \brief Implementacion de los juegos de prueba de la clase grafo
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
#include "grafo.h"

//Creamos varias instancias con las que trabajar
class GrafoTest:public testing::Test  {
 protected:
  Grafo *G;
  TipoNodoGrafo Sig,a,b;

  virtual void SetUp()  {
    G=new Grafo;
    Sig=0;
  }

  virtual void TearDown()  {
    delete G;
  }
};

TEST_F(GrafoTest,MetodosBasicos){
  ASSERT_TRUE(G->EsVacio());
  EXPECT_FALSE(G->set_arco(0,1,5));
  for (int i=0;i<20;i++)
    ASSERT_TRUE(G->set_nodo(i));
  EXPECT_TRUE(G->set_arco(0,1,5));

  EXPECT_EQ(kInfinito, G->get_arco(5,6));
  EXPECT_EQ(5, G->get_arco(0,1));

  //Probamos adyacente
  EXPECT_TRUE(G->Adyacente(0,1));
  EXPECT_FALSE(G->Adyacente(2,1));

  //Probamos el borrar
  EXPECT_TRUE(G->del_arco(0,1));
  EXPECT_EQ(kInfinito,G->get_arco(0,1));
}

TEST_F(GrafoTest,Algoritmos){
  //Datos ejemplo para creacion grafo
  TipoNodoGrafo nodos[10];
  TipoArcoGrafo arcos[10][10] ={{0,97,kInfinito,kInfinito,119,kInfinito,kInfinito,kInfinito,kInfinito,kInfinito},
                                {97,0,10,kInfinito,kInfinito,57,kInfinito,kInfinito,kInfinito,kInfinito},
                                {kInfinito,10,0,17,kInfinito,kInfinito,67,kInfinito,kInfinito,kInfinito},
                                {kInfinito,kInfinito,17,0,kInfinito,kInfinito,kInfinito,kInfinito,kInfinito,122},
                                {119,kInfinito,kInfinito,kInfinito,0,kInfinito,kInfinito,37,kInfinito,kInfinito},
                                {kInfinito,57,kInfinito,kInfinito,kInfinito,0,63,kInfinito,50,kInfinito},
                                {kInfinito,kInfinito,67,kInfinito,kInfinito,63,0,kInfinito,61,kInfinito},
                                {kInfinito,kInfinito,kInfinito,kInfinito,37,kInfinito,kInfinito,0,72,kInfinito},
                                {kInfinito,kInfinito,kInfinito,kInfinito,kInfinito,50,61,72,0,153},
                                {kInfinito,kInfinito,kInfinito,122,kInfinito,kInfinito,kInfinito,kInfinito,153,0}};


  for(int i=0;i<10;i++){
    nodos[i]=i;
    ASSERT_TRUE(G->set_nodo(nodos[i]));
  }

  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      ASSERT_TRUE(G->set_arco(nodos[i],nodos[j],arcos[i][j]));


  //Probamos Warshall
  G->Warshall();
  TipoMatrizBooleana B;
  G->get_warshall_path(B);
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      EXPECT_TRUE(B[i][j]);

  //Probamos Floyd-path
  G->Floyd();
  TipoMatrizAdyacencia A;
  G->get_floyd_path(A);
  EXPECT_EQ(-1,A[0][0]);
  EXPECT_EQ(2,A[0][3]);
  EXPECT_EQ(3,A[0][9]);
  EXPECT_EQ(5,A[8][0]);
  EXPECT_EQ(3,A[9][1]);
  EXPECT_EQ(8,A[9][7]);

  //Probamos Floyd-cost
  G->get_floyd_cost(A);
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      EXPECT_NE(kInfinito,A[i][j]);
  EXPECT_EQ(0,A[0][0]);
  EXPECT_EQ(124,A[0][3]);
  EXPECT_EQ(246,A[0][9]);
  EXPECT_EQ(204,A[8][0]);
  EXPECT_EQ(149,A[9][1]);
  EXPECT_EQ(225,A[9][7]);

  //Probamos Siguiente
  G->Siguiente(nodos[0],nodos[9],Sig);
  EXPECT_EQ(nodos[1],Sig);
  G->Siguiente(nodos[5],nodos[2],Sig);
  EXPECT_EQ(nodos[1],Sig);
  G->Siguiente(nodos[5],nodos[6],Sig);
  EXPECT_EQ(nodos[6],Sig);
  G->Siguiente(nodos[5],nodos[5],Sig);
  EXPECT_EQ(nodos[5],Sig);

  //Probamos Adyacentes
  queue <TipoNodoGrafo> ady;
  G->Adyacentes(nodos[5],ady);
  EXPECT_EQ(nodos[1],ady.front());
  ady.pop();
  EXPECT_EQ(nodos[6],ady.front());
  ady.pop();
  EXPECT_EQ(nodos[8],ady.front());
  ady.pop();
  EXPECT_TRUE(ady.empty());

  //Probamos MayorGrado
  int grado=0;
  EXPECT_EQ(nodos[8],G->MayorGrado(grado));
  EXPECT_EQ(4,grado);

  //Probamos MasDistantes
  EXPECT_EQ(262,G->MasDistantes(a,b));
  EXPECT_EQ(nodos[4],a);
  EXPECT_EQ(nodos[9],b);

  //Probamos MasCorto
  EXPECT_EQ(10,G->MasCorto(a,b));
  EXPECT_EQ(nodos[1],a);
  EXPECT_EQ(nodos[2],b);

  //Probamos Excentricidad
  EXPECT_EQ(203,G->Excentricidad(nodos[5]));

  //Probamos Centro
  EXPECT_EQ(nodos[5],G->Centro());

  //Probamos ExisteCiclo
  EXPECT_TRUE(G->ExisteCiclo(nodos[4]));
  ASSERT_TRUE(G->del_arco(1,5));
  ASSERT_TRUE(G->del_arco(2,6));
  ASSERT_TRUE(G->del_arco(7,4));
  ASSERT_TRUE(G->del_arco(8,6));
  EXPECT_FALSE(G->ExisteCiclo(nodos[4]));
}

