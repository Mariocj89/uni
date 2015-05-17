
#include "area.h"

Area::Area(Posicion inicio, int largo, int alto,char titulo[]){
	Area(inicio.x,inicio.y,largo,alto,titulo);
}

Area::Area(int iniciox, int inicioy, int largo, int alto, char titulo[]){
	this->inicio.x = iniciox;
	this->inicio.y = inicioy;
	this->actual.y = this->inicio.y + 2;
	this->actual.x = this->inicio.x + 2;
	this->largo = largo;
	this->alto = alto;

	this->PintarArea();

	//	setfillstyle(0,0);
	EscribirMensaje(titulo);

}

void Area::PintarArea(){

	rectangle(inicio.x,inicio.y, inicio.x+largo+1, inicio.y + alto+1);
}

void Area::EscribirMensaje(char mensaje[]){
	bar(actual.x,actual.y,actual.x+largo-10,actual.y+8);//limpiamos antes d escribir
	outtextxy(actual.x,actual.y,mensaje);
	SaltoDeLinea();

}

void Area::EscribirChar(char caracter){
	if(caracter == '\n') SaltoDeLinea();
	else
		if(caracter == 8){ //pulsa backspace
			if(actual.x-inicio.x > 10) actual.x-=10;
			bar(actual.x, actual.y, actual.x+10,actual.y+8);

		}
		else{   //si no es ni salto de linea(\n) ni backspace
			if(actual.x - inicio.x >= largo) SaltoDeLinea();
			char cad[2];
			cad[0] = caracter;
			cad[1] = '\0';
			outtextxy(actual.x,actual.y,cad);
			actual.x+=10;
		}
}

void Area::SaltoDeLinea(){
	actual.y+=10;
	actual.x= inicio.x+2;
	if((actual.y-inicio.y) > alto){
		actual.y = inicio.y+2+10; //sumamos 10 para acceder a la segunda linea(1¦ es el titulo);
	}
	bar(actual.x,actual.y,inicio.x+largo-2,actual.y+8);

}