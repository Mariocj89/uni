/**
* \file ec2.cpp
* \brief fichero main del proyecto
* \date 20-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo: 9 \n
*   \b Entrega: 2 \n
*   \b Curso 08/09
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

/**
 * Metodo Principal
 * @param argc 
 * @param argv[] 
 * @return 
 */
int main(int argc, char *argv[])
{
  cout<<endl;
  cout<<"PRISON BREAK REDUX!\n";
  if(argc>2 && (strcmp("test",argv[2])==0||strcmp("Test",argv[2])==0||strcmp("TEST",argv[2])==0)) {
    cout<<"Realizando Pruebas"<<endl;
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
  }
  try{
    FicheroCarga f(argv[1]);
    f.ProcesarFichero();
    cout<<endl;
    (Prision::get_instancia())->MostrarPrision();
    Prision::get_instancia()->Destruir();
    Registro::get_instancia()->Destruir();
    cout<<"Game over!"<<endl<<endl;
  }
  catch(ios::failure &exc){
    cout<<exc.what()<<endl;
  }
  catch(...){
    cout<<"Atencion!\n\t Ha sido lanzada una excepcion no controlada!\n";
  }


  return EXIT_SUCCESS;
}
