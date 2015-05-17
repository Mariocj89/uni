/**
* \file ec3.cpp
* \brief Main de la fase 3 del proyecto de programacion
* \date 08-06-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 3
*   \b Curso 2º
*/


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include <gtest/gtest.h>
#include "prision.h"
#include "cargador.h"

using namespace std;

int main(int argc, char *argv[])
{

  cout<<endl;
  cout<<"PRISON BREAK REDUX!\n";
  if(argc>2 && (strcmp("test",argv[2])==0||strcmp("Test",argv[2])==0||strcmp("TEST",argv[2])==0)) {
    cout<<"Realizando Pruebas"<<endl;
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
  }
  Prision *p = Prision::get_instancia();
  try{
    FicheroCarga f(argv[1]);
    f.ProcesarFichero();
    cout<<endl;
    p->MostrarPrision();
    p->IniciarSimulacion();
    cout<<"Game over!"<<endl<<endl;
  }
  catch(ios::failure &exc){
    cout<<exc.what()<<endl;
  }
  catch(string &exc){
    cout<<exc<<endl;
  }
  catch(...){
    cout<<"Atencion!\n\t Ha sido lanzada una excepcion no controlada!\n";
  }
  delete p;
  return EXIT_SUCCESS;
}
