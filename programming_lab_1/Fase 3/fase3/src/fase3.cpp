



#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

# include "gestor.h"



void Opcion(Gestor &g,const int &i){

  switch (i){
	case 1:  g.Insertar();      break;
	case 2:  g.Eliminar();      break;
	case 3:  g.Mostrar();       break;
	case 4:  g.Buscar();        break;
	case 5:  g.CambiarIdioma(); break;
	case 6:  g.MostrarMes();    break;
	case 7:  g.MostrarEdad();   break;
	case 8:  g.Guardar();	    break;


  }
}

void Menu(Gestor &g){
  int i;//entero para seleccionar una opcion.
  TIdioma l=Castellano;//para alterna entre idiomas.
  bool salir=false;
  while(!salir){
    g.ObtenerIdioma( l);//Comprobamos el idioma actual
    if(l==Castellano){
	cout<<"Pulse una tecla para continuar.\n";
	cin.get();
	system("clear");
  	cout<<"-------Menu (Castellano)------- \n";
  	cout<<"1.Añadir Dato.\n";
  	cout<<"2.Borrar Dato.\n";
  	cout<<"3.Mostrar Agenda.\n";
  	cout<<"4.Buscar Dato.\n";
	cout<<"5.Cambiar Idioma.\n";
  	cout<<"6.Mostrar por mes.\n";
  	cout<<"7.Mostrar mayores de...\n";
  	cout<<"8.Salir.\n";

  	cout<<"Introduzca una opcion (1-8):";
  	cin>>i;
	cin.ignore();
    }

    if(l==Ingles){
	cout<<"Press a key to continue.\n";
	cin.get();
	system("clear");
  	cout<<"-------Menu (English)------- \n";
  	cout<<"1.Insert an element.\n";
  	cout<<"2.Delete an element.\n";
  	cout<<"3.Show all elements.\n";
  	cout<<"4.Search.\n";
	cout<<"5.Change language.\n";
  	cout<<"6.Show people borned in...\n";
  	cout<<"7.Show people older than...\n";
  	cout<<"8.Exit.\n";

  	cout<<"Insert an option (1-8):";
  	cin>>i;
	cin.ignore();
    }


	if(i==8) salir=true;

  	Opcion(g,i);
  }
}






int main()
{
// El gestor se prueba directamente desde la aplicacion
// PruebaListaEnlazada();
// PruebaDatosPersonales();
// PruebaMeses();
// Prueba_Fecha();



//Iniciamos la aplicacion y cargamos de archivo
  Gestor g;
  g.Cargar();

//Iniciamos el menu.
  Menu(g);

}


