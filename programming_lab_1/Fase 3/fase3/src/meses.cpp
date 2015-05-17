/**
@file meses.cpp                                                                     x
@brief source de la clase Meses                                                     x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
	Este archivo contiene la implementacion de todos los modulos contenidos en la clase meses y de su modulo de  prueba,
	definidos en meses.h.
@par Utilización:
	Para utilizar cualquiera de estos modulos hay que llamar a las cabeceras a traves de la clase, exceptuando el caso del
	modulo de prueba que se llama como a un modulo normal al no estar incluido en la clase.
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#include "meses.h"


Meses::Meses()
{
  l=NULL;
}



void Meses::Clonar(const Meses &dat)
{
  TipoDato dato;

  for(int i=1;i<13;i++){
	dat.Buscar( i,dato);
	InsertarFinal( dato);
  }

}

void Meses::InsertarPrincipio(const TipoDato &dat)
{
  PtrNodo Nuevo;
  Nuevo= new TNodo;
  Nuevo->dato=dat;
  Nuevo->suce=l;
  l=Nuevo;
}


void Meses::InsertarFinal(const TipoDato &dat)
{
  PtrNodo Nuevo;
  PtrNodo Aux;

  Nuevo= new TNodo;
  Nuevo->dato=dat;
  Nuevo->suce=NULL;
  if(l==NULL)
	l=Nuevo;
  else{
	Aux=l;
	while(Aux->suce!=NULL)
		Aux=Aux->suce;
	Aux->suce=Nuevo;}
}


void Meses::InsertarOrden(const TipoDato &dat)
{
  PtrNodo Nuevo,Indicador,Anterior;
  bool Encontrado=false;

  Nuevo= new TNodo;
  Nuevo->dato=dat;
  Anterior=NULL;
  Indicador=l;

  while(Indicador!=NULL && !Encontrado)
	if(Indicador->dato.Numero>dat.Numero)
		Encontrado=true;
	else{
		Anterior=Indicador;
		Indicador=Indicador->suce;
	}
	Nuevo->suce=Indicador;
	if(Anterior==NULL)
		l=Nuevo;
	else
		Anterior->suce=Nuevo;
}


bool Meses::Borrar(const int &i)
{
  PtrNodo Aux,Aux2;
  Aux=l;
  bool borrado=false;

  if(l->dato.Numero==i){
	l=l->suce;
	delete Aux;
  }

  while(Aux->suce!=NULL)
	if(Aux->suce->dato.Numero==i){
		Aux2=Aux->suce;
		Aux->suce=Aux2->suce;
		delete Aux2;
		borrado=true;
		if(Aux->suce==NULL) return true;
		Aux=Aux->suce;
	}
	else
		Aux=Aux->suce;
  return borrado;
}


void Meses::Mostrar() const{
  PtrNodo Aux;
  Aux=l;
  int i=1;
  while(Aux!=NULL){
	cout<<"Elemento "<<i<<"\t Numero: "<<Aux->dato.Numero<<" - "<<Aux->dato.Idioma[0]<<" / "<<Aux->dato.Idioma[1]<<endl;
	i++;
	Aux=Aux->suce;
  }
}


bool Meses::Buscar(const int i, TipoDato &dat) const
{
  PtrNodo Aux=l;
  while(Aux!=NULL){
	if(i==Aux->dato.Numero){
		dat.Numero=i;
		strcpy(dat.Idioma[0],Aux->dato.Idioma[0]);
		strcpy(dat.Idioma[1],Aux->dato.Idioma[1]);
		return true;
	}
	else
		Aux=Aux->suce;
  }
  return false;
}


void Meses::Cargar()
{
  ifstream entrada;
  char linea[MAXCAD];
  TipoDato Aux;

  entrada.open("meses.txt");
  if(!entrada) cout <<"Error al abrir el flujo\n";
  else{
	while(!entrada.eof()){
	  entrada.getline(linea,MAXCAD,'#');
	  if(!entrada.eof()){
		Aux.Numero=atoi(linea);

		entrada.getline(linea,MAXCAD,'#');
		strcpy(Aux.Idioma[0],linea);

		entrada.getline(linea,MAXCAD,'\n');
		strcpy(Aux.Idioma[1],linea);

		InsertarOrden( Aux);
	  }
	}
  entrada.close();
  }
}


void Meses::Eliminar()
{
  PtrNodo Aux=l;
  while(l!=NULL){
	l=l->suce;
	delete Aux;
	Aux=l;
  }
}


Meses::~Meses()
{
  PtrNodo Aux=l;
  while(l!=NULL){
	l=l->suce;
	delete Aux;
	Aux=l;
  }
}




void PruebaMeses()
{

  TipoDato dat;
  dat.Numero=12;
  strcpy(dat.Idioma[0],"Diciembre");
  strcpy(dat.Idioma[1], "December");

  Meses M,M2;
  M2.Cargar();
  M.Clonar(M2);
  M.Borrar( 12);
  M.Mostrar();//Mostramos prar probar Cargar y Borrar
  M.InsertarFinal(dat );
  cin.get();
  system("clear");//Limpiamos la pantalla

  M.Borrar(1);
  dat.Numero=1;
  strcpy(dat.Idioma[0],"Enero");
  strcpy(dat.Idioma[1], "January");

  M.InsertarFinal(dat );
  M.Mostrar();//Mostramos para mostrar Insertar al Final e insertar al Principio

  M.Buscar( 1,dat);
  if(strcmp(dat.Idioma[0],"Enero")==0&&strcmp(dat.Idioma[1], "January")==0&&dat.Numero==1) cout<<"\nEl modulo  Buscar funciona.\n";//Probamos Buscar

}
