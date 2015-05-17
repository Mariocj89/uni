/**
* \file main.cpp
* \brief Implementacion de los juegos de prueba de la clase puerta
* \date 13-03-09
* \author
*   \b Nombre Mario \n
*   \b Apellidos Corchero Jiménez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Grupo 9 \n
*   \b Entrega 1
*   \b Curso 2º
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>
#include "puerta.h"
#include <queue>

using namespace std;

void prueba1()
{
  Puerta *P=new Puerta(7);  //ANTENCION, SI LO DECLARAS COMO PUERTA ESTATICA NO FUNCIONA, ¿POR QUE?
  ColaGen <Llave*> *C=new ColaGen <Llave*>;
  Llave *L1=new Llave(1),*L2=new Llave(2),*L3=new Llave(3),*L4=new Llave(4),*L5=new Llave(5);
  C->insertar_dato(L1);
  C->insertar_dato(L2);
  C->insertar_dato(L3);
  C->insertar_dato(L4);
  P->Configurar(C);
  P->Cerrar();
  P->ProbarLlave(L1);
  P->ProbarLlave(L1);
  P->ProbarLlave(L5);
  P->ProbarLlave(*L5);
  P->ProbarLlave(*L3);
  P->ProbarLlave(*L2); 
  P->Abrir();
  
  delete L1;
  delete L2;
  delete L3;
  delete L4;
  delete L5;
}

void prueba2()
{
  Puerta P(3);
  ColaGen <Llave*> *C=new ColaGen <Llave*>;


  Llave* vector [30];
  //Creamos 30 llaves, (0-29)
  for (int i=0;i<30;i++)
    vector[i]= new Llave(i);
  //Insertamos las impares en la cola.
  for (int i=1;i<30;i+=2)
    C->insertar_dato(vector[i]);


  //Iniciamos la puerta:
  cout<<P;
  P.Configurar(C);
  cout<<P;
  P.Cerrar();

  //Probamos llaves que sabemos que abriran la puerta
  cout<<P<<"\nVamos a intentar abrir la puerta con las llaves correctas\n";
  P.ProbarLlave(vector[1]);
  P.ProbarLlave(vector[5]);
  P.ProbarLlave(vector[13]);
  P.ProbarLlave(vector[21]);
  P.Abrir();
  cout<<"Comprobamos si se ha habierto correctamente:\n";
  cout<<P;
  P.Cerrar();

  //Empezamos a probar llaves
  int i=0;
  cout<<"\n\nProbamos todas las llaves: \n";
  while(i<30){
    P.ProbarLlave(vector[i]);
    P.Abrir();
    cout<<"Probamos la llave con identificador: "<<vector[i]->get_id()<<"  ---  ";
    cout<<P;
    i++;
  }


  //Probamos de nuevo con algunas llaves.
  cout<<"\n\nProbamos de nuevo algunas llaves: \n";
  P.ProbarLlave(vector[1]);
  P.ProbarLlave(vector[5]);
  P.ProbarLlave(vector[13]);
  P.ProbarLlave(vector[21]);


  //Borramos los datos
  for (int i=0;i<30;i++)
    delete vector[i];
  delete C;
}

void EC1()
{
  queue <Llave*> Recogidas;
  ColaGen <Llave*>* CSecreta=new ColaGen <Llave*>;

  Llave* vector [30];
  //Creamos 30 llaves, (0-29)
  for (int i=0;i<30;i++)
    vector[i]= new Llave(i);

  //Insertamos las llaves en CSecreta y Recogidas
  for (int i=0;i<30;i++){
    Recogidas.push(vector[i]);
    if(vector[i]->get_id()%2==1){
      CSecreta->insertar_dato(vector[i]);
      Recogidas.push(vector[i]);}
  }

  //Preparamos la puerta.
  Puerta* P=new Puerta(7);
  cout<<"La puerta recien creada: ---"<<*P;
  P->Configurar(CSecreta);
  cout<<"La puerta recien configurada: ---"<<*P;
  P->Cerrar();
  cout<<"La puerta recien cerrada: ---"<<*P;

  //Empezamos a probar llaves
  Llave* L;
  cout<<"\n\nProbamos todas las llaves: \n";
  for(int i=0;i<45;i++){
    L=Recogidas.front();
    Recogidas.pop();
    Recogidas.push(L);
    P->ProbarLlave(L);
    cout<<"Probamos la llave con identificador: "<<L->get_id()<<"  --  ";
    P->Abrir();
    cout<<*P;
  }

  delete CSecreta;
  delete P;
  for (int i=0;i<30;i++)
    delete vector[i];

}

int main(int argc, char *argv[])
{
  cout << "Hello, world!" << endl;
//   prueba1();
//   prueba2();
  EC1();


  return EXIT_SUCCESS;
}
