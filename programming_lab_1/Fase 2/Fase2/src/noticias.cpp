#include "noticias.h"
using namespace std;
#include <iostream>

Noticia::Noticia()
{
	strcpy (Ident_N,"");
}

	
Noticia::Noticia (const Tcadena1 Id)
{
	strcpy (Ident_N,Id);
	
}

Noticia::Noticia (const Noticia &N)
{
	Tcadena1 c1;
        Tcadena2 c2;
	Tcadena3 c3;
	fecha F;


	N.Obtener_Identificador(c1);
	strcpy (Ident_N,c1);

	N.Obtener_Titulo(c2);
	strcpy (Titulo, c2);



	N.Obtener_SubTitulo(c2);
	strcpy (SubTitulo, c2);

	N.Obtener_Contenido(c3);
	strcpy (Contenido, c3);

	N.Obtener_Imagen(c2);
	strcpy (Imagen, c2);

	N.Obtener_Fecha(F);
	Fecha_N.Clonar(F);

	

}

void Noticia::Clonar (const Noticia &N)
{
	Tcadena1 c1;
	Tcadena2 c2;
	Tcadena3 c3;
	fecha F;



	N.Obtener_Identificador(c1);
	strcpy (Ident_N,c1);

	N.Obtener_Titulo(c2);
	strcpy (Titulo, c2);

	

	N.Obtener_SubTitulo(c2);
	strcpy (SubTitulo, c2);

	N.Obtener_Contenido(c3);
	strcpy (Contenido, c3);

   N.Obtener_Imagen(c2);
	strcpy (Imagen, c2);
	
  N.Obtener_Fecha(F);
	Fecha_N.Clonar(F);

}


void Noticia::Poner_Identificador(Tcadena1 I)
{
	strcpy (Ident_N,I);
}

void Noticia::Poner_Titulo(Tcadena2 T)
{
	strcpy (Titulo,T);
}
void Noticia::Poner_SubTitulo(Tcadena2 ST)
{
	strcpy (SubTitulo,ST);
}
void Noticia::Poner_Contenido(Tcadena3 C)
{
	strcpy (Contenido,C);
}

void Noticia::Poner_Imagen( Tcadena2 Im )
{
	strcpy(Imagen, Im);
}
void Noticia::Poner_Fecha (const fecha &F)
{
	Fecha_N.Clonar(F);
}

void Noticia::Obtener_Identificador (Tcadena1 &I)const
{
	strcpy (I,Ident_N);
}
void Noticia::Obtener_Titulo (Tcadena2 &T)const
{
	strcpy (T,Titulo);
}

void Noticia::Obtener_SubTitulo (Tcadena2 &ST)const
{
	strcpy (ST,SubTitulo);
}

void Noticia::Obtener_Contenido (Tcadena3 &C)const
{
	strcpy (C,Contenido);
}
void Noticia::Obtener_Imagen( Tcadena2 & Im ) const
{
	strcpy (Im, Imagen);
}
void Noticia::Obtener_Fecha(fecha &F)const 
{
	F.Clonar(Fecha_N);
}




int Noticia::Comparar(Tcadena1 c) const {
  return strcmp(Ident_N, c);
}

void Noticia::Mostrar_Noticia() const
{
cout <<"================================================================"<<endl;
	cout << "Noticia " << Ident_N << endl;
	//Mostrar seccion
	cout << "Fecha: "; Fecha_N.Mostrar_Fecha(); cout << endl;
	cout << "Título: "  << Titulo << endl;
	cout << "Subtítulo: " << SubTitulo << endl;
	cout << "Imagen   : "<< Imagen<< endl;
	cout << "Contenido: " << Contenido << endl;
cout <<"================================================================"<<endl;	
}

void Noticia::Guardar_Noticia(ofstream &salida)
{
		salida<<Titulo<<'#'<<SubTitulo<<'#'<<Contenido<<'#'<<Imagen<<'#'<<Fecha_N.obtener_dia()<<'/'<<Fecha_N.obtener_mes()<<'/'<<Fecha_N.obtener_anio()<<'\n';
	}

Noticia::~Noticia()
{
}


void Noticia::Cargar_Noticia(ifstream &entrada){

	char linea[MaxCad3];
	fecha f;
	int dia,mes,anio;





	entrada.getline(linea,MaxCad2,'#');
	Poner_Titulo(linea);

    if(!entrada.eof()){

	entrada.getline(linea,MaxCad2,'#');
	Poner_SubTitulo(linea);

	entrada.getline(linea, MaxCad3,'#');
	Poner_Contenido(linea);

	entrada.getline(linea,MaxCad1,'#');
	Poner_Imagen(linea);

	entrada.getline(linea, 10, '/');
	dia=atoi(linea);

	entrada.getline(linea, 10, '/');
	mes=atoi(linea);

	entrada.getline(linea, 10, '\n');
	anio=atoi(linea);

	f.asignar_fecha(dia,mes,anio);
	Poner_Fecha(f);}


}


void Noticia::PedirNoticia(Tcadena1  contador){


 fecha f;
 Tcadena2 Tit,Sub,imagen;
 Tcadena3 cont;
 int d,m,a;



     Poner_Identificador(contador);

     cout<<"Introduce título:";
     cin.getline(Tit,MaxCad2);
     if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
     Poner_Titulo(Tit);

    cout<<"Introduce el subtitulo:";
     if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
    cin.getline(Sub,MaxCad2);
    Poner_SubTitulo(Sub);

   cout<<"Introduce el contenido:";
   cin.getline(cont,MaxCad3);
    if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
   Poner_Contenido(cont);

  cout<<"Introduce la imagen:";
  cin.getline(imagen,MaxCad2);
   if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  Poner_Imagen(imagen);

 cout<<"Introduce el día:"<<endl;
 cin>>d;
 cout<<"Introduce el mes:"<<endl;
 cin>>m;
 cout<<"Introduce el año:"<<endl;
 cin>>a;
      
       f.asignar_fecha(d,m,a);
       Poner_Fecha(f);
}


void Prueba_Noticias(){
  bool Ok=true;
  int a,b,c;
  fecha f(1,1,1),g;
  Tcadena1 cad1;
  Tcadena2 cad2;
  Tcadena3 cad3;

  Noticia N,H;
  N.Poner_Contenido( "contenido");
  N.Poner_Fecha( f);
  N.Poner_Identificador( "N001");
  N.Poner_Imagen( "imagen");
  N.Poner_SubTitulo( "subtitulo");
  N.Poner_Titulo( "titulo");

  N.Obtener_Contenido( cad3);
  if(strcmp(cad3, "contenido")!=0) Ok=false; //Provamos obtener contenido
  N.Obtener_Fecha( g);
  a=g.obtener_dia();
  b=g.obtener_anio();
  c=g.obtener_mes();
  if(a!=1||b!=1||c!=1)  Ok=false;//Provamos obtener fecha
  N.Obtener_Identificador( cad1);
  if(strcmp(cad1,"N001")!=0)  Ok=false;//Provamos obtener identificador
  N.Obtener_Imagen( cad2);
  if(strcmp(cad2,"imagen")!=0)  Ok=false;//Provamos obtener imagen
  N.Obtener_SubTitulo( cad2);
  if(strcmp(cad2,"subtitulo")!=0)  Ok=false;//Provamos obtener Subtitulo
  N.Obtener_Titulo( cad2);
  if(strcmp(cad2,"titulo")!=0)  Ok=false;//Provamos obtener titulo
  H.Clonar(N);
  Noticia J(H);
  if(J.Comparar( "N001")!=0)  Ok=false;//Provamos comparar

  H.PedirNoticia( "N001");
  H.Mostrar_Noticia();//Provamos mostrar y pedir noticia

  if(Ok) cout<< "Juego de pruebas de la clase noticia superado satisfactoriamente.\n";
  else   cout<< "Se han encontrado errores, use el depurador. \n";



}



