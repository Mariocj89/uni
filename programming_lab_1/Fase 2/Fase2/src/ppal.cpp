/**
@file ppal.cpp                                                                      x
@brief Quguel Blog Site fase I                                                      x
@author  Mario Corchero Jiménez                                                     x
@date   12/04/08                                                                    x
@par Descripción:                                                                   x
        Programa que permite a un usuario gestionar noticias personales a modo de blog personal.
@par Utilización:
        La funcion principal del programa es: main
        Dentro hay que definir una variable tipo "gestor" e iniciar la aplicacion con la funcion "opcion_principal".
@par Plataforma
        Linux
*/



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <cstdlib>

#include "gestor.h"

using namespace std;



/**Modulo que devuelve true si el digito introducido se encuentra entre 1 y MaxOpciones*/
bool NoCaracter(const char &x, const char MAX){
	if(x<=MAX&&x>='1')	return true;
	else return false;
}

/**Modulo para escribir el menu principal en pantalla*/
void Menu_Principal (int &c) {
  char x[2];
  cout << endl << endl;
  cout << "MENU __________________________" 	    << endl;
  cout << '\t' <<"1.- Menu Noticia"                 << endl;
  cout << '\t' <<"2.- Menu Categoria"               << endl;
  cout << '\t' <<"3.- Mostrar Blog."                << endl;
  cout << '\t' <<"4.- Guardar Blog."		    << endl;
  cout << '\t' <<"5.- Cargar Blog."		    << endl;
  cout << '\t' <<"6.- Buscar cadena en Blog."	    << endl;
  cout << '\t' <<"7.- Generar codigo HTML"          << endl;
  cout << '\t' <<"8.- Salir"            	    << endl;
  cout << "  Seleccione Opción (1-8) --> ";
  
  do {
		cin.get(x[0]);
		while(NoCaracter(x[0], '8')==false){
			cout<<"\nCaracter invalido, elija una opcion correcta (1-8)";
			cin.get(x[0]);
		}
	x[1]='\0';
	c=atoi(x);
		cout<<endl<<endl;
      cin.ignore (10,'\n');
  } while ((c < 1) && (c > 8));
}

/**Modulo para escribir el menu de noticias en pantalla*/
void Menu_Noticia (int &c) {
  char x[2];
  cout << endl << endl;
  cout << "MENU NOTICIA_____________________" << endl;
  cout << '\t' <<"1.- Introducir Notica"          << endl;
  cout << '\t' <<"2.- Anular Noticia"              << endl;
  cout << '\t' <<"3.- Buscar Noticia"              << endl;
  cout << '\t' <<"4.- Mostrar Noticias"                << endl;
  cout << '\t' <<"5.- Volver al Menu Principal"                         << endl;
  cout << "  Seleccione Opción (1-5) --> ";
  
  do {
		cin.get(x[0]);
		while(NoCaracter(x[0],'5')==false){
			cout<<"\nCaracter invalido, elija una opcion correcta (1-5)";
			cin.get(x[0]);
		}
	x[1]='\0';
	c=atoi(x);
		cout<<endl<<endl;
      cin.ignore (10,'\n');
  } while ((c < 1) && (c > 5));
}

/**Modulo para escribir el menu de categorias en pantalla*/
void Menu_Categoria (int &c){
  char x[2];
  cout << endl << endl;
  cout << "MENU CATEGORIA_________________" << endl;
  cout << '\t' <<"1.- Introducir Categoria"          << endl;
  cout << '\t' <<"2.- Anular Categoria"              << endl;
  cout << '\t' <<"3.- Mostrar Categorias"              << endl;
  cout << '\t' <<"4.- Mostrar Noticias en categoria"   << endl;
  cout << '\t' <<"5.- Volver al Menu Principal"                         << endl;
  cout << "  Seleccione Opción (1-5) --> ";
  
  do {
		cin.get(x[0]);
		while(NoCaracter(x[0],'5')==false){
			cout<<"\nCaracter invalido, elija una opcion correcta (1-5)";
			cin.get(x[0]);
		}
	x[1]='\0';
	c=atoi(x);
		cout<<endl<<endl;
      cin.ignore (10,'\n');
  } while ((c < 1) && (c > 5));
}

/**Modulo para gestionar las noticias*/
void Opcion_Noticia (gestor &Lista){

  TipoDato dat;
  char nombre[20];
  Tcadena1 cad1;
  int    c;
  bool   fin = false;

  do {
    Menu_Noticia (c);
    switch (c) {
      case 1:	Lista.Pedir_Noticia(dat); 
		if(Lista.Insertar(dat)==true) 
			cout<<"\n Noticia insertada correctamente.\n"; 
			else cout <<"\n No se ha podido insertar la noticia.\n"; break;

      case 2:	cout<<"Introduce el identificador: ";
		cin.getline(cad1,10);
		if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
		if(Lista.Eliminar(cad1)==true) 
			cout<<endl<<"La noticia a sido borrada correctamente."<<endl<<endl;
		else 
		cout<<"Error, no existe ninguna noticia con ese identificador."<<endl<<endl;   break;


      case 3:	cout<<"Introduce el identificador: ";
		cin.getline(cad1,10);
 		if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
		if(Lista.Buscar(cad1)==false) 
			cout<<"No se ha encontrado la noticia."<<endl<<endl;   break;

      case 4: Lista.Mostrar();  break;

      case 5: fin = true;    break;
    }
  } while (!fin);
}

/**Modulo para gestionar las categorias*/
void Opcion_Categoria (gestor &Lista){
  int    c;
  bool   fin = false;
  char   ref[MaxCadRef];

 do {
	Menu_Categoria(c);
 	switch (c) {
	  case 1: Lista.Insertar_Categoria();break;

	  case 2: cout<<"Estas son las categorias existentes: \n"; Lista.Mostrar_Categorias();
		  cout<<"Introduzca el identificador de la que desea eliminar: ";
		  cin.getline(ref,MaxCadRef);
		  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
		  if(Lista.Eliminar_Categoria( ref)) cout<<"Categoria eliminada correctamente. \n";
		  else cout<<"Error al eliminar la Categoria. \n";
		  ;break;

	  case 3: Lista.Mostrar_Categorias();break;

	  case 4: cout<<"Introduzca el identificador: ";
		  cin.getline(ref,MaxCadRef);
		  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
		  Lista.Mostrar_Categoria( ref);break;

	  case 5: fin=true; break;
    }
  } while (!fin);
}

//Modulo para gestionar el menu principal
void Opcion_Principal (gestor &Lista){

  TipoDato dat;
  char nombre[20];
  Tcadena3 cad1;
  int    c;
  bool   fin = false;

  do {
    Menu_Principal (c);
    switch (c) {
      case 1: Opcion_Noticia(Lista); break;

      case 2: Opcion_Categoria(Lista); break;

      case 3: Lista.Mostrar();  break;

      case 4: cout<<"Introduce el nombre del archivo: ";cin.getline(nombre,20); if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}Lista.Guardar(nombre);break;


      case 5: cout<<"Introduce el nombre del archivo: ";cin.getline(nombre,20); if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}Lista.Cargar(nombre);break;

      case 6: cout<<"Introduzca la cadena que desea buscar: "; cin.getline(cad1,MaxCad3); if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');} Lista.Buscar_Cadena(cad1);break;

      case 7: if(Lista.Crear_Html()) cout<<"Se ha generado correctamente el codigo HTML.\nSe encuentra en debug/src, dentro de la carpeta del proyecto. \nPulse una tecla para continuar."; else cout<<"No se ha creado correctamente los ficheros HTML.\nPulse una tecla para continuar."; cin.get(); break;

      case 8: if(Lista.Guardar_Binario()) {cout<<"Blog Guardado Correctamente \n"; cin.get();}
	      else cout<<"Ocurrio un error al guardar el Blog, no podra recuperarlo. \n";
	      fin = true;    break;
    }
  } while (!fin);
}

void Inicializar(gestor &Lista){

	char g;
	char nombre[20];

	cout<<"Indique como desea inicializar el blog: \n\t1.Vacio.\n\t2.Reanudar el ultimo Blog.\n\t3.A partir de 2 ficheros de texto.\n\t4.A Partir de un fichero de texto.\n";

	cin.get(g);
	cin.clear();
	cin.ignore(10,'\n');
	while(NoCaracter(g,'4')==false){
		cout<<"\nCaracter invalido, elija una opcion correcta (1-4)";
		cin>>g;
	}

	switch(g) {

	  case '2':	if(Lista.Iniciar_Binario()) cout<<"\nSe ha cargado correctamente la ultima sesion.\n";
			else cout<<"Ha ocurrido un error al abrir el archivo\n"; break;

	  case '4':	cout<<"Introduce el nombre del archivo: ";cin.getline(nombre,20);
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			if(Lista.Cargar(nombre)) break;

	  case '1':	cout<<"Se procede a iniciar el Blog vacio, pulse una tecla.";cin.get();break;

	  case '3':	Lista.Iniciar_Texto(); break;
	}


	Opcion_Principal(Lista);

}

int main () {


  gestor Lista;
  Inicializar(Lista);

  /*
		///Juego de pruebas

	//!Fase 1
  Prueba_Fecha();
  Prueba_Noticias();

  if(Prueba_Categoria()) cout<<"Juego de prueba de la clase categoria pasado correctamtente \n";
  else   cout<<"categoria: tiene errores, use el depurador. \n";
  if(Prueba_Lista()) cout<<"Juego de prueba de la clase Lista pasado correctamtente \n";
  else   cout<<"lista: tiene errores, use el depurador. \n";
  //Para provar la clase gestor se usa directamente la aplicacion.
  
	//!Fase 2
  cout<<"Si los modulos creados funcionan correctamente deben mostrarse 2 blogs iguales.\n"; cin.get();
  gestor L,G;
  L.Iniciar_Texto();
  L.Mostrar();
  L.Guardar_Binario();
  G.Iniciar_Binario();
  G.Mostrar();
  */


  return EXIT_SUCCESS;
}









