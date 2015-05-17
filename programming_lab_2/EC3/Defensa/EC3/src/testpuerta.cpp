/**
* \file testpuerta.cpp
* \brief Implementacion de los juegos de prueba de la clase Puerta
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
#include "puerta.h"

//Creamos varias instancias con las que trabajar
class PuertaTest:public testing::Test  {
 protected:
  Puerta PE, *PD;
  Llave* vector[30];
  virtual void SetUp()  {
    PD=new Puerta;
  }

  virtual void TearDown()  {
    delete PD;
  }
};

TEST_F(PuertaTest,Metodos_de_la_Puerta){

  ColaGen <Llave*> CSecreta;
  ColaGen <Llave*> Recogidas;
  Llave *l;

  //Insertamos las llaves en CSecreta y Recogidas
  for (int i=0;i<30;i++){
    Recogidas.insertar_dato(vector[i] = new Llave(i));
    if(i%2==1){
      CSecreta.insertar_dato(l = new Llave(i));
      Recogidas.insertar_dato(l);}
  }
  ASSERT_EQ(45,Recogidas.get_num_elementos());
  ASSERT_EQ(15,CSecreta.get_num_elementos());
  ASSERT_EQ(NOCONFIGURADA,PE.get_estado());
  PE.Configurar(&CSecreta);
  ASSERT_EQ(ABIERTA,PE.get_estado());
  EXPECT_TRUE(PE.Cerrar());
  ASSERT_EQ(CERRADA,PE.get_estado());
  EXPECT_FALSE(PE.Abrir());
  ASSERT_EQ(CERRADA,PE.get_estado());

  //abrimos la puerta
  EXPECT_TRUE(PE.ProbarLlave(vector[1]));
  EXPECT_TRUE(PE.ProbarLlave(vector[5]));
  EXPECT_TRUE(PE.ProbarLlave(vector[13]));
  EXPECT_TRUE(PE.ProbarLlave(vector[21]));
  ASSERT_TRUE(PE.Abrir());


  EXPECT_EQ(ABIERTA,PE.get_estado());
  PE.Cerrar();
  EXPECT_EQ(CERRADA,PE.get_estado());

  delete vector[0];
  for(int i=2;i<5;i++) delete vector[i];
  for(int i=6;i<13;i++) delete vector[i];
  for(int i=14;i<21;i++) delete vector[i];
  for(int i=22;i<30;i++) delete vector[i];
}
