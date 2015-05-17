
#include "lpi.h"


lista::lista () {
  ocupacion = 0;
  pi        = 0;
}

int lista::ocupadas() const{
  return ocupacion;
}

bool lista::vacia () {
  return (ocupacion==0);
}


bool lista::llena () {
  return (ocupacion==Max_Categorias);
}


void lista::poner_inicio () {
  pi=0;
}

void lista::poner_fin () {
  pi=ocupacion;
}


void lista::avanzar () {
  pi++;
}


void lista::retroceder () {
  pi--;
}


bool lista::fin () {
  return (pi==ocupacion);
}

bool lista::inicio () {
  return (pi==0);
}


bool lista::insertar (categoria &e) {
  if(llena()) return false;
  for(int i=ocupacion; i>pi;i--)
	elemento[i].Clonar(elemento[i-1]);
  elemento[pi].Clonar(e);
  ocupacion++;
  return true;
}

bool lista::consultar (categoria &e) {
  if(pi>ocupacion-1) return false;
  e.Clonar(elemento[pi]);
  return true;
}

bool lista::borrar () {
  if(vacia()) return false;
  for(int i=pi; i<ocupacion-1;i++)
	elemento[i].Clonar(elemento[i+1]);
  ocupacion--;
}

bool lista::insertar_Noticia (const TipoDato &e) {
	Tcadena1 r;
	TipoDato dat;
	e.Obtener_Identificador( r);
	elemento[pi].Poner_Inicio();
	while(!elemento[pi].Fin()){
		elemento[pi].Consultar(dat);
		if(dat.Comparar(r)==1){
			elemento[pi].Insertar(e);
			return true;}
		elemento[pi].Avanzar();}
	if(elemento[pi].Fin()) elemento[pi].Insertar(e);
	return false;
}

bool lista::borrar_Noticia (Tcadena1 cad){
  char cad2[MaxCadRef];
  poner_fin();
  while(!inicio()){
	 retroceder();
 	 if(elemento[pi].Vacia()) return false;
 	 TipoDato dat;
 	 elemento[pi].Poner_Inicio();
  	while(elemento[pi].Fin()==false){
		elemento[pi].Consultar(dat);
		if(dat.Comparar(cad)==0){;
			elemento[pi].Borrar();
			return true;}
		elemento[pi].Avanzar();
 	 }
  }
  return false;
}


bool Prueba_Lista(){
  bool Ok=true;
  lista l;
  TipoDato n;

  categoria c;


  if(!l.vacia())  Ok=false;
  if(l.llena())  Ok=false;
  if(!l.inicio()) Ok=false;
  for(int i=0;i<5;i++)
	l.insertar(c);
  if(!l.llena()) Ok=false;
  if(l.vacia())  Ok=false;

  l.poner_inicio();
  if(!l.inicio())  Ok=false;
  l.poner_fin();
  if(!l.fin())  Ok=false;
  for (int i=1; i<=5;i++)
	l.retroceder();
  if(!l.inicio())  Ok=false;
  for (int i=1; i<=5;i++)
	l.avanzar();
  if(!l.fin())  Ok=false;

  char cad1[MaxCadRef];
  char cad2[MaxCadSec];



  return Ok;
}

