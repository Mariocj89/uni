/**
@file listaenlazada.cpp                                                             x
@brief source de la clase ListaEnlazada                                             x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
	Este archivo contiene la implementacion de todos los modulos contenidos en la clase ListaEnlazada y de su modulo de
	prueba, definidos en listaenlazada.h.
@par Utilización:
	Para utilizar cualquiera de estos modulos hay que llamar a las cabeceras a traves de la clase, exceptuando el caso del
	modulo de prueba que se llama como a un modulo normal al no estar incluido en la clase.
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#include "listaenlazada.h"


ListaEnlazada::ListaEnlazada()
{
  l=NULL;
  M.Cargar();
}


void ListaEnlazada::Clonar(ListaEnlazada &dat)
{
  PNodo Aux=l;
  while(Aux!=NULL){
	dat.InsertarFinal( Aux->dato);
	Aux=Aux->suce;
  }
}


void ListaEnlazada::ObtenerMeses(Meses &mes) const
{
  mes.Clonar( M);
}


void ListaEnlazada::FiltrarPorMes(const int i)
{
  fecha f;
  int m;
  PNodo Aux=l;//Usaremos aux para recorrer
  TCadena1 tfn;//usaremos el telefono para borrar desde el modulo borrar
  while(Aux!=NULL){
	Aux->dato.ObtenerFecha(f);
	m=f.obtener_mes();
	if(m!=i){
		Aux->dato.ObtenerTelefono(tfn);
		Aux=Aux->suce;
		Borrar( tfn);
	}
	else Aux=Aux->suce;
  }
}


void ListaEnlazada::FiltrarPorEdad(const int i)
{
  PNodo Aux=l;//Usaremos aux para recorrer
  TCadena1 tfn;//usaremos el telefono para borrar desde el modulo borrar
  while(Aux!=NULL){
	if(Aux->dato.CalcularEdad()<=i){
		Aux->dato.ObtenerTelefono(tfn);
		Aux=Aux->suce;
		Borrar( tfn);
	}
	else Aux=Aux->suce;
  }
}


void ListaEnlazada::InsertarPrincipio(const DatosPersonales &dat)
{
  PNodo Nuevo;
  Nuevo= new TipoNodo;
  Nuevo->dato=dat;
  Nuevo->suce=l;
  l=Nuevo;
}


void ListaEnlazada::InsertarFinal(const DatosPersonales &dat)
{
  PNodo Nuevo;
  PNodo Aux;

  Nuevo= new TipoNodo;
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


void ListaEnlazada::InsertarOrden(const DatosPersonales &dat)
{
  PNodo Nuevo,Indicador,Anterior;
  bool Encontrado=false;

  Nuevo= new TipoNodo;
  Nuevo->dato=dat;
  Anterior=NULL;
  Indicador=l;
  TCadena2 Tlf1, Tlf2;//Usaremos estas variables para comprar a traves de los telefonos


  while(Indicador!=NULL && !Encontrado)
	if(Indicador->dato.CompararA(dat)==1)
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


int  ListaEnlazada::Ocupacion() const
{
  PNodo Aux=l;
  for(int i=0;i<i+1;i++){
	if(Aux==NULL) return i;
	else Aux=Aux->suce;
  }
}


bool ListaEnlazada::Borrar( const TCadena1 dat)
{
  PNodo Aux,Aux2;
  Aux=l;
  bool borrado=false;
  TCadena1 Tfn;
  l->dato.ObtenerTelefono(Tfn);

  if(strcmp(dat,Tfn)==0){
	l=l->suce;
	delete Aux;
	borrado=true;
  }

  while(Aux->suce!=NULL){
	Aux->suce->dato.ObtenerTelefono(Tfn);
	if(strcmp(dat,Tfn)==0){
		Aux2=Aux->suce;
		Aux->suce=Aux2->suce;
		delete Aux2;
		borrado=true;
		if(Aux->suce==NULL) return true;
		Aux=Aux->suce;
	}
	else
		Aux=Aux->suce;
  }
  return borrado;
}


void ListaEnlazada::MostrarES() const
{
  PNodo Aux;
  Aux=l;
  int i=1;
  if(Aux==NULL)  cout<<"No existe ningun elemento.\n";

  while(Aux!=NULL){
	cout<<"Elemento "<<i<<" :"<<endl;
	Aux->dato.MostrarES(M);
	i++;
	Aux=Aux->suce;
	cout<<"\n\n";
  }
}


void ListaEnlazada::MostrarEN() const
{
  PNodo Aux;
  Aux=l;
  int i=1;

  if(Aux==NULL)  cout<<"There is no elemets.\n";

  while(Aux!=NULL){
	cout<<"Element "<<i<<" :"<<endl;
	Aux->dato.MostrarEN(M);
	i++;
	Aux=Aux->suce;
	cout<<"\n\n";
  }
}


bool ListaEnlazada::Buscar( const TCadena1 i, DatosPersonales &dat) const
{
  TCadena1 Tfn; //Variable destinada a guardar el telefono de la actual clase DatosPersonales dentro del siguiente bucle
 
  PNodo Aux=l;
  while(Aux!=NULL){
	Aux->dato.ObtenerTelefono(Tfn);
	if(strcmp(i,Tfn)==0){
		dat.Clonar( Aux->dato);
		return true;
	}
	else
		Aux=Aux->suce;
  }
  return false;
}


bool ListaEnlazada::Cargar(const char nombre[20])
{
  DatosPersonales dat;
  ifstream entrada;
  entrada.open(nombre);
  if(!entrada) return false;
  else{
	while(!entrada.eof()){
	  dat.Cargar( entrada);
	  if(!entrada.eof()){
		InsertarOrden( dat);//Si no se desea que la lista que se carge sea ordenada hay que cambiar esta instruccion
	  }
	}
  entrada.close();
  }
  return true;
}


bool ListaEnlazada::Guardar(const char nombre[20]) const
{
  PNodo Aux=l;
  DatosPersonales dat;
  ofstream salida;
  salida.open(nombre);
  if(!salida) return false;
  else{
	while(Aux!=NULL){
		Aux->dato.Guardar(salida);
		Aux=Aux->suce;
	}
  salida.close();
  }
  return true;
}


void ListaEnlazada::Eliminar()
{
  PNodo Aux=l;
  while(l!=NULL){
	l=l->suce;
	delete Aux;
	Aux=l;
  }
}


ListaEnlazada::~ListaEnlazada()
{
  PNodo Aux=l;
  while(l!=NULL){
	l=l->suce;
	delete Aux;
	Aux=l;
  }
}

void PruebaListaEnlazada()
{
  ListaEnlazada lis,lis2;
  DatosPersonales dat1,dat2,dat3;

  ifstream entrada;
  entrada.open("datos_per.txt");
  if(!entrada) cout<<"Error al abrir el flujo en el modulo PruebaListaEnlazada()\n";
  else{

	//cargamos 3 elementos para insertar, es necesario que haya almenos 3 en el archivo
	dat1.Cargar(entrada);
	dat2.Cargar(entrada);
	dat3.Cargar(entrada);

	entrada.close();

	//Probamos los insertar en orden y MostrarES
	lis.InsertarOrden( dat1);
	lis.InsertarOrden( dat2);
	lis.InsertarOrden( dat3);
	lis.MostrarES();

	//Probamos los insertar al final y Mostrar EN
	lis.Eliminar();
	lis.InsertarFinal( dat1);
	lis.InsertarFinal( dat2);
	lis.InsertarFinal( dat3);
  	lis.MostrarEN();

	//Probamos los insertar al principio
	lis.Eliminar();
	lis.InsertarPrincipio( dat1);
	lis.InsertarPrincipio( dat2);
	lis.InsertarPrincipio( dat3);
  	lis.MostrarES();

	//Probamos Borrar y Ocupacion
	TCadena1 Tfn;
	dat2.ObtenerTelefono( Tfn);
	lis.Borrar( Tfn);
	if(lis.Ocupacion()!=2) cout<<"No funciona el modulo ocuapcion! \n";
  	lis.MostrarES();

	//Probamos Buscar
	DatosPersonales datper;
	dat3.ObtenerTelefono( Tfn);
	if(!lis.Buscar( Tfn,datper)) cout<<"Modulo Buscar no funciona correctamente\n";

	//Probamos Guardar y Cargar
	cout<<"Mostrando de nuevo la ultima lista:\n";
	lis.Guardar( "prueba");
	lis2.Cargar( "prueba");
	lis2.MostrarES();


  }
}


