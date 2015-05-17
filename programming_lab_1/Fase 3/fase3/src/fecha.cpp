/**
@file fecha.cpp                                                                     x
@brief source de la clase fecha                                                     x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
	Este archivo contiene la implementacion de todos los modulos contenidos en la clase fecha y de su modulo de  prueba,
	definidos en fecha.h.
@par Utilización:
	Para utilizar cualquiera de estos modulos hay que llamar a las cabeceras a traves de la clase, exceptuando el caso del
	modulo de prueba que se llama como a un modulo normal al no estar incluido en la clase.
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#include "fecha.h"
using namespace std;
#include <iostream>


fecha::fecha()
{
	dia=0;
	mes=0;
	anio=0;
}

fecha::fecha(int d,int m)
{
	dia=d;
	mes=m;
	anio=2008;
}

fecha::fecha(int d,int m, int a)
{
	dia=d;
	mes=m;
	anio=a;
}
fecha::fecha(const fecha&F)
{
	dia=F.obtener_dia();
	mes=F.obtener_mes();
	anio=F.obtener_anio();
}

void fecha::Clonar(const fecha&F)
{
	dia=F.obtener_dia();
	mes=F.obtener_mes();
	anio=F.obtener_anio();
}

int fecha::dias_por_mes (int mes, int a)
{
	int dias_mes;
	switch (mes){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: 
			dias_mes=31; 
			break;
		
		case 2:
			if (bisiesto (a) )
				dias_mes=29;
			else
				dias_mes=28;
			break;
			
		case 4:
		case 6:
		case 9:
		case 11:
			
			dias_mes=30;
			break;
			
	}
return dias_mes;
}

bool fecha::bisiesto(int a)
{
  bool b;
   	if ((a%400)==0)
		b=true;
	else{
               if ((a%100)==0)
			b=false;
                else 
                    if ((a%4)==0)
                        b=true;
                    else
                       b=false;
		
             }
        return b;
}


bool fecha::fecha_correcta(int d,int m,int a)
{
bool correcto=false;
if ((m >=1) &&( m <=12))
      if ((d >=1)&& (d <=dias_por_mes (m,a)))
		correcto =true;
	else
		correcto=false;

return correcto;
}

void fecha::asignar_fecha(int d,int m,int a)
{
	if (fecha_correcta(d,m,a))
	{
		dia=d;
		mes=m;
		anio=a;
	}
}

void fecha::incrementar_fecha()
{
 // en dias intermedios del mes sólo es preciso incrementar el dia
  if (fecha_correcta (dia+1,mes,anio))
       dia=dia+1;
  else{
	// si estamos en el último dia del mes
	// es necesario pasar al dia 1 del mes siguiente
	if( fecha_correcta(1,mes+1,anio))
	{
		dia=1;
		mes=mes+1;
	}
	else    // estamos en el 31 de diciembre y es preciso
		// pasar al 1 de enero del año siguiente
		{
			dia=1;
			mes=1;
			anio=anio+1;
		}
	}
}
void fecha::decrementar_fecha()
{
// en dias intermedios del mes sólo es preciso decrementar el dia
if (fecha_correcta (dia-1,mes,anio))
	dia=dia-1;
else
	{  // si estamos en le primer dia del mes, es necesario
	   // pasar al último dia del mes anterior
	 int dias_mes;
	dias_mes=dias_por_mes(mes-1,anio);
	if (fecha_correcta(dias_mes,mes-1,anio))
		{
		dia=dias_mes,
		mes=mes-1;
		}
	else // estamos en 1 de enero y es preciso pasar al 31 de diciembre del ano anterior
		{
			dia=31;
			mes=12;
			anio=anio-1;
		}
	}
	
}
	
int fecha::obtener_dia() const
{
	return dia;
}
int fecha::obtener_mes() const
{
	return mes;
}
int fecha::obtener_anio() const
{
	return anio;
}

void fecha::Mostrar_Fecha() const
{
	cout << dia << "/" << mes << "/" << anio;
}



void Prueba_Fecha(){
  bool Ok=true;

/* Para probar estos modulos hay ke declararlos publicos mientras se ejecuten las pruebas:
  if(!H.bisiesto( 2008)) Ok=false;
  if(H.bisiesto(2009)) Ok =false;
  if(H.dias_por_mes(2,2008)!=29) Ok =false;
  if(H.dias_por_mes( 4,2008)!=30) Ok =false;
  if(H.dias_por_mes( 5,2008)!=31) Ok =false;
  if(H.fecha_correcta( 29,2,2009)) Ok =false;
  if(!H.fecha_correcta( 28,2,2008)) Ok =false;
*/

  int d,m,a;
  fecha F(30,4),G(1,1,2008),H,I(G);
  H.asignar_fecha( 1,1,1);
  d=H.obtener_dia();
  m=H.obtener_mes();
  a=H.obtener_anio();
  if(d!=a||a!=m||a!=1) Ok=false;//Provamos los obtener
  H.Clonar( G);
  H.decrementar_fecha();
  a=H.obtener_anio();
  d=H.obtener_dia();
  m=H.obtener_mes();
  if(d!=31||m!=12||a!=2007) Ok =false;//Provamos clonar y decrementar
  F.incrementar_fecha();
  d=F.obtener_dia();
  m=F.obtener_mes();
  if(d!=1||m!=5) Ok =false;//Provamos incrementar

  if(Ok) cout<<"Pasado el juego de pruebas de la clase fecha a la perfeccion.\n";
  else   cout<<"Se han detectado errores, use el depurador. \n";


}

