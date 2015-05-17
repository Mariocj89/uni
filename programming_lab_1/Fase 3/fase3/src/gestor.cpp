/**
@file gestor.cpp                                                                    x
@brief source de la clase Gestor                                                    x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
	Este archivo contiene la implementacion de todos los modulos contenidos en la clase Gestor, definidos en gestor.h.
@par Utilización:
	Para utilizar cualquiera de estos modulos hay que llamar a las cabeceras a traves de la clase.
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#include "gestor.h"



void Gestor::InsertarDato(const DatosPersonales &dat)
{
  lista.InsertarOrden( dat);
}


bool Gestor::EliminarDato( const TCadena1 dat)
{
  return lista.Borrar( dat);
}


void Gestor::MostrarES() const
{
  lista.MostrarES();
}


void Gestor::MostrarEN() const
{
  lista.MostrarEN();
}


bool Gestor::BuscarDato(const TCadena1 tfn,DatosPersonales &dat) const
{
  return lista.Buscar( tfn,dat);
}


Gestor::Gestor()
{
  Idioma=Castellano;
}


void Gestor::Mostrar() const
{
  if(Idioma==Castellano) MostrarES();
  if(Idioma==Ingles) MostrarEN();
}


void Gestor::MostrarMes()
{
  int i;
  if(Idioma==Castellano) cout<<"Introduzca el numero del mes. \n";
  if(Idioma==Ingles) cout<<"Insert the month's number.\n";
  cin>>i;
  cin.ignore();
  ListaEnlazada lis;//Aqui tendremos todos las personas nacidas en el mes i
  lista.Clonar(lis);
  lis.FiltrarPorMes(i);
  if(Idioma==Castellano) lis.MostrarES();
  if(Idioma==Ingles) lis.MostrarEN();

}


void Gestor::MostrarEdad()
{
  int i;
  if(Idioma==Castellano) cout<<"Introduzca la edad que deben pasar. \n";
  if(Idioma==Ingles) cout<<"Insert age to superate.\n";
  cin>>i;
  cin.ignore();
  ListaEnlazada lis;//Aqui tendremos todos las personas nacidas en el mes i
  lista.Clonar(lis);
  lis.FiltrarPorEdad(i);
  if(Idioma==Castellano) lis.MostrarES();
  if(Idioma==Ingles) lis.MostrarEN();

}


void Gestor::Insertar()
{
  DatosPersonales dat;

  //Dependiendo del idioma actual debemos pedir el dato en un idioma u otro.
  if(Idioma==Castellano) dat.PedirES();
  if(Idioma==Ingles) dat.PedirEN();

  InsertarDato( dat);
}


bool Gestor::Eliminar( )
{
  TCadena1 linea;

  //Dependiendo del idioma actual debemos pedir el numero en un idioma u otro.
  if(Idioma==Castellano){
	cout<<"Introduzca el numero del elemento a eliminar: ";
	cin.getline(linea, MAXCAD1);
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  }

  if(Idioma==Ingles){
	cout<<"Insert the number of the element to delete: ";
	cin.getline(linea, MAXCAD1);
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  }

  if (!EliminarDato( linea)){
	if(Idioma==Ingles)
		cout<<"No matches for that number.\n";
	if(Idioma==Castellano)
		cout<<"No se ha encontrado ningun dato con ese numero.\n";
	return false;
  }
  else{
	if(Idioma==Ingles)
		cout<<"Removed succesfuly.\n";
	if(Idioma==Castellano)
		cout<<"Eliminado correctamente.\n";
	return true;


  }
}	


bool Gestor::Cargar()
{
  if(!lista.Cargar("datos_per.txt")){
	cout<<"Atencion, no se ha hallado datos_per.txt, se procede a iniciar la agenda vacia.\n";
	return false;}
  else{
	cout<<"Se ha cargado correctamente desde datos_per.txt.\n";
	return true;}

}


bool Gestor::Guardar() const
{
  if(lista.Guardar( "datos_per.txt")){
	if(Idioma==Castellano) cout << "Se ha actualizado \"datos_per.txt\".\n";
	if(Idioma==Ingles) cout << "Refreshed \"datos_per.txt\".\n";
	return true;}
  else  return false;
}


bool Gestor::Buscar() const
{
  TCadena1 linea;
  DatosPersonales dat;
  Meses M;
  bool encontrado;

  //Dependiendo del idioma actual debemos pedir el numero en un idioma u otro.
  if(Idioma==Castellano){
	cout<<"Introduzca el numero del elemento a buscar: ";
	cin.getline(linea, MAXCAD1);
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  }

  if(Idioma==Ingles){
	cout<<"Insert the number of the element to search: ";
	cin.getline(linea, MAXCAD1);
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  }

  encontrado=BuscarDato( linea,dat);

  lista.ObtenerMeses( M);
  if(encontrado){
	if(Idioma==Castellano) dat.MostrarES( M );
	if(Idioma==Ingles) dat.MostrarEN( M );}
  else{
	if(Idioma==Ingles)
		cout<<"No matches for that number.\n";
	if(Idioma==Castellano)
		cout<<"No se ha encontrado ningun dato con ese numero.\n";
  }
  return encontrado;
}


void Gestor::CambiarIdioma()
{
	if(Idioma==Castellano) Idioma=Ingles;
	else if(Idioma==Ingles) Idioma=Castellano;
}

void Gestor::ObtenerIdioma(TIdioma &l)
{
	l=Idioma;
}


