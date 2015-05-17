#include "lpi.h"


categoria::categoria () {
  ocupacion = 0;
  pi        = 0;
}


bool  categoria::Clonar      (categoria &e){
	Vaciar();
	char i[MaxCadSec];
	e.Obtener_Nombre( i);
	Poner_Nombre( i);
	e.Obtener_Referencia( i);
	Poner_Referencia( i);

	TipoDato r;
	Poner_Inicio();
	e.Poner_Inicio();
	while(!e.Fin()){
		e.Consultar( r);
		Insertar( r);
		e.Avanzar();
		Avanzar();
	}
}

void  categoria::Obtener_Referencia(    char    ref[MaxCadRef]){
	strcpy(ref,id); 
}

void  categoria::Obtener_Nombre(    char    name[MaxCadSec]){
	strcpy(name,nombre);
}

void  categoria::Poner_Referencia(const    char    ref[MaxCadRef]){
	strcpy(id,ref);
}

void  categoria::Poner_Nombre(const    char    name[MaxCadSec]){
	strcpy(nombre,name);
}

bool categoria::Vacia () {
  return (ocupacion==0);
}


bool categoria::Llena () {
  return (ocupacion==MAX_ELEMENTOS);
}


void categoria::Poner_Inicio () {
  pi=0;
}

void categoria::Poner_Fin () {
  pi=ocupacion;
}


void categoria::Avanzar () {
  pi++;
}


void categoria::Retroceder () {
  pi--;
}


bool categoria::Fin () {
  return (pi==ocupacion);
}

bool categoria::Inicio () {
  return (pi==0);
}

bool categoria::Insertar (const TipoDato &e) {
  if(Llena()) return false;
  for(int i=ocupacion; i>pi;i--)
	elemento[i].Clonar(elemento[i-1]);
  elemento[pi].Clonar(e);
  ocupacion++;
  return true;
}

bool categoria::Consultar (TipoDato &e) {
  if(pi>ocupacion-1) return false;
  e.Clonar(elemento[pi]);
  return true;
}

bool categoria::Borrar () {
  if(Vacia()) return false;
  for(int i=pi; i<ocupacion-1;i++)
	elemento[i].Clonar(elemento[i+1]);
  ocupacion--;
}

void  categoria::Vaciar     (){
  ocupacion=0;
  pi=0;
}

bool Prueba_Categoria(){
  bool Ok=true;
  categoria l;
  TipoDato n;

  n.PedirNoticia("N001");


  if(!l.Vacia())  Ok=false;//Provamos Vacia cuando esta vacia
  if(l.Llena())  Ok=false;//Provamos Llena cuando esta vacia
  if(!l.Inicio()) Ok=false;//Provamos Inicio cuando esta vacia
  for(int i=1;i<=10;i++)
  	if(!l.Insertar(n))  Ok=false;//Provamos insertar sin insertar mas de el maximo
  if(!l.Llena()) Ok=false;//Provamos llena cuando esta llena
  if(l.Vacia())  Ok=false;//Provamos vacia cuando esta llena

  l.Poner_Inicio();
  if(!l.Inicio())  Ok=false;//Provamos Poner inicio y inicio
  l.Poner_Fin();
  if(!l.Fin())  Ok=false;//Provamos Poner fin y fin
  for (int i=1; i<=10;i++)
	l.Retroceder();
  if(!l.Inicio())  Ok=false;//Provamos retroceder
  for (int i=1; i<=10;i++)
	l.Avanzar();
  if(!l.Fin())  Ok=false;//Provamos avanzar

  char cad1[MaxCadRef];
  char cad2[MaxCadSec];

  l.Vaciar();
  if(l.Consultar(n))  Ok=false;//Provamos vaciar


  return Ok;
  


}




