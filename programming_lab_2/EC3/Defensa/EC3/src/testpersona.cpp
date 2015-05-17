/**
* \file testpersona.cpp
* \brief Implementacion de los juegos de prueba de las clases heredadas de persona
* \date 08-06-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 3
*   \b Curso 2º
*/

#include <gtest/gtest.h>
#include "prision.h"
#include "preso.h"

//Creamos varias instancias con las que trabajar
class PersonaTest:public testing::Test  {
 protected:
  Persona *a, *b, *c;
  Planta *plant;
  Posicion orientacion[4];
  Prision *p;
  virtual void SetUp()  {
    plant=new Planta(0,3,3,0,3,5,2);
    orientacion[0] = NORTE;
    orientacion[1] = SUR;
    orientacion[2] = ESTE;
    orientacion[3] = OESTE;
    p = Prision::get_instancia();
    p->set_planta(plant);
    a= new Guardia("@",'@',2,0,0);
    b= new Guardia("#",'#',1,0,0);
    c= new Preso("p",'p',0,orientacion ,0,0);
  }

  virtual void TearDown()  {
    delete p;
    delete a;
  }
};


TEST_F(PersonaTest,Guardias_y_Personas){
//   Prision *p;

  EXPECT_EQ('@',a->get_marca());
  EXPECT_EQ('#',b->get_marca());
  EXPECT_EQ('p',c->get_marca());

  EXPECT_EQ("@",a->get_nombre());
  EXPECT_EQ("#",b->get_nombre());
  EXPECT_EQ("p",c->get_nombre());


  p->set_persona(0,8,a);
  p->set_persona(0,8,b);
  p->set_persona(0,0,c);

  EXPECT_EQ(c,p->get_persona(0,0));
  EXPECT_EQ(a,p->sacar_persona(0,8));
  EXPECT_EQ(b,p->get_persona(0,8));

  p->IniciarSimulacion();


}
