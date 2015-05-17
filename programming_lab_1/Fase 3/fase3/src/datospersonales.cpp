/**
@file datospersonales.cpp                                                           x
@brief source de la clase DatosPersonales                                           x
@author  Mario Corchero Jiménez                                                     x
@date   15/05/08                                                                    x
@par Descripción:                                                                   x
	Este archivo contiene la implementacion de todos los modulos contenidos en la clase DatosPersonales y de su modulo de
	prueba, definidos en datospersonales.h.
@par Utilización:
	Para utilizar cualquiera de estos modulos hay que llamar a las cabeceras a traves de la clase, exceptuando el caso del
	modulo de prueba que se llama como a un modulo normal al no estar incluido en la clase.
@par Plataforma
        Linux.
@par Creado en KDevelop.
*/


#include "datospersonales.h"

		/** Modulos Auxiliares	*/



int DatosPersonales::CalcularEdad() const
{

  int d1, m1, a1;//Estas variables se usaran para guardar la fecha actual.
  int d2, m2, a2;//Estas variables se usaran para guardar la fecha de nacimiento.
  int edad;//Variable que guardara la edad hasta que se devuelva

  /**Obtenemos la fecha actual*/ //Se copiara a d1,m1,a1
  time_t rawtime;
  tm *ptm;
  time(&rawtime);
  ptm=gmtime(&rawtime);
  a1=ptm->tm_year+1900;
  m1=ptm->tm_mon+1;//Hemos de sumarle uno porque devuelve los meses empezando desde 0(enero)
  d1=ptm->tm_mday;


  ObtenerFecha(d2,m2,a2);

  edad=a1-a2;

  if(m2>m1) edad--;
  if(m2==m1&&d2>d1) edad--;

  return edad;

}



		/** Constructores	*/

DatosPersonales::DatosPersonales()
{
  strcpy(Nombre,"");
  strcpy(Apellido1,"");
  strcpy(Apellido2,"");
  strcpy(Telefono,"");
}


DatosPersonales::DatosPersonales(const DatosPersonales &dat)
{
  TCadena2 Name,Surname1,Surname2;
  TCadena1 Number;
  fecha Date;

  dat.ObtenerTodo( Name,Surname1,Surname2,Date,Number);
  PonerTodo( Name,Surname1,Surname2,Date,Number);
}


DatosPersonales::DatosPersonales(const TCadena2 Name, const TCadena2 Surname1, const TCadena2 Surname2, const fecha &Date, const TCadena1 Number)
{
  strcpy(Nombre,Name);
  strcpy(Apellido1,Surname1);
  strcpy(Apellido2,Surname2);
  strcpy(Telefono,Number);
  FechaNacimiento.Clonar(Date);
}


		/** Modulos Poner	*/

void DatosPersonales::PonerNombre(const TCadena2 Name)
{
  strcpy(Nombre,Name);
}


void DatosPersonales::PonerApellido1(const TCadena2 Surname1)
{
  strcpy(Apellido1,Surname1);
}


void DatosPersonales::PonerApellido2(const TCadena2 Surname2)
{
  strcpy(Apellido2,Surname2);
}


void DatosPersonales::PonerFecha(const fecha &Date)
{
  FechaNacimiento.Clonar(Date);
}


void DatosPersonales::PonerFecha(const int &d, const int &m, const int &a)
{
  FechaNacimiento.asignar_fecha( d,m,a);
}


void DatosPersonales::PonerTelefono(const TCadena1 Number)
{
  strcpy(Telefono,Number);
}


void DatosPersonales::PonerTodo(const TCadena2 Name, const TCadena2 Surname1, const TCadena2 Surname2, const fecha &Date, const TCadena1 Number)
{
  strcpy(Nombre,Name);
  strcpy(Apellido1,Surname1);
  strcpy(Apellido2,Surname2);
  strcpy(Telefono,Number);
  FechaNacimiento.Clonar(Date);
}


		/** Modulos Obtener	*/


void DatosPersonales::ObtenerNombre(TCadena2 &Name) const
{
  strcpy(Name,Nombre);
}


void DatosPersonales::ObtenerApellido1(TCadena2 &Surname1) const
{
  strcpy(Surname1,Apellido1);
}


void DatosPersonales::ObtenerApellido2(TCadena2 &Surname2) const
{
  strcpy(Surname2,Apellido2);
}


void DatosPersonales::ObtenerFecha(fecha &Date) const
{
  Date.Clonar( FechaNacimiento);
}


void DatosPersonales::ObtenerFecha(int &d,int &m,int &a) const
{
  d=FechaNacimiento.obtener_dia();
  m=FechaNacimiento.obtener_mes();
  a=FechaNacimiento.obtener_anio();
}


void DatosPersonales::ObtenerTelefono(TCadena1 &Number) const
{
  strcpy(Number,Telefono);
}


void DatosPersonales::ObtenerTodo(TCadena2 &Name, TCadena2 &Surname1, TCadena2 &Surname2, fecha &Date, TCadena1 &Number) const
{
  strcpy(Name,Nombre);
  strcpy(Surname1,Apellido1);
  strcpy(Surname2,Apellido2);
  Date.Clonar( FechaNacimiento);
  strcpy(Number,Telefono);
}


		/** Resto de Modulos	*/


void DatosPersonales::Clonar(const DatosPersonales &dat)
{
  TCadena2 Name,Surname1,Surname2;
  TCadena1 Number;
  fecha Date;

  dat.ObtenerTodo( Name,Surname1,Surname2,Date,Number);
  PonerTodo( Name,Surname1,Surname2,Date,Number);

}

int DatosPersonales::CompararA(const DatosPersonales &dat) const
{
  TCadena1 Number;
  dat.ObtenerTelefono( Number);
  return strcmp(Telefono, Number);
}

void DatosPersonales::MostrarES(const Meses &M) const
{
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  fecha Date;
  int d,m,a;
  TipoDato dat;


  ObtenerTodo(Name,Surname1, Surname2,Date, Number);
  d=Date.obtener_dia();
  m=Date.obtener_mes();
  a=Date.obtener_anio();

  M.Buscar( m,dat);

  cout<<"||----------------------------------------------------||\n";
  cout<<"|| Nombre:  "<<Name<<" "<<Surname1<<" "<<Surname2<<endl;
  cout<<"|| Cumpleaños:  "<<d<<" del "<<dat.Idioma[0]<<endl;
  cout<<"|| Edad  :"<<CalcularEdad()<<endl;
  cout<<"|| Telefono:  "<<Number<<endl;
  cout<<"||----------------------------------------------------||\n";
}

void DatosPersonales::MostrarEN(const Meses &M) const
{
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  fecha Date;
  int d,m,a;
  TipoDato dat;

  ObtenerTodo(Name,Surname1, Surname2,Date, Number);
  d=Date.obtener_dia();
  m=Date.obtener_mes();
  a=Date.obtener_anio();

  M.Buscar( m,dat);

  cout<<"||----------------------------------------------------||\n";
  cout<<"|| Name:  "<<Name<<" "<<Surname1<<" "<<Surname2<<endl;
  cout<<"|| Birthday:  "<<d<<" of "<<dat.Idioma[1]<<endl;
  cout<<"|| Age  :"<<CalcularEdad()<<endl;
  cout<<"|| Tlf:  "<<Number<<endl;
  cout<<"||----------------------------------------------------||\n";
}


void DatosPersonales::PedirES()
{
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  int d,m,a;
  fecha date;

  cout<<"Introduzca el Nombre: ";
  cin.getline(Name,MAXCAD2);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  cout<<"Introduzca el primer apellido: ";
  cin.getline(Surname1,MAXCAD2);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  cout<<"Introduzca el segundo apellido: ";
  cin.getline(Surname2,MAXCAD2);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  cout<<"Introduzca su fecha de nacimiento: \n";
  cout<<"\t -Dia: "; cin>>d;
  cout<<"\t -Mes: "; cin>>m;
  cout<<"\t -Año: "; cin>>a;
  date.asignar_fecha( d,m,a);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  cin.ignore();

  cout<<"Introduzca su numero de telefono: ";
  cin.getline(Number,MAXCAD1);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  PonerTodo(Name,Surname1,Surname2,date,Number);
}


void DatosPersonales::PedirEN()
{
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  int d,m,a;
  fecha date;

  cout<<"Insert the name: ";
  cin.getline(Name,MAXCAD2);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  cout<<"Insert the first surname: ";
  cin.getline(Surname1,MAXCAD2);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  cout<<"Insert the second surname: ";
  cin.getline(Surname2,MAXCAD2);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  cout<<"Insert the birthday: \n";
  cout<<"\t -Day: "; cin>>d;
  cout<<"\t -Month: "; cin>>m;
  cout<<"\t -Year: "; cin>>a;
  date.asignar_fecha( d,m,a);
  cin.ignore();

  cout<<"Insert the telephone number: ";
  cin.getline(Number,MAXCAD1);
  if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}

  PonerTodo(Name,Surname1,Surname2,date,Number);
}


//La estructura del archivo es:  NOMBRE#APELLIDO1#APELLIDO2#DIA#MES#ANIO#TELEFONO\n
void DatosPersonales::Cargar(ifstream &entrada) 
{
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  int d,m,a;
  char aux[6];//Lo usaremos para obtener las fechas
  fecha date;

  entrada.getline(Name,MAXCAD2,'#');//Obtenemos el nombre

  entrada.getline(Surname1,MAXCAD2,'#');//Obtenemos el 1er apellido

  entrada.getline(Surname2,MAXCAD2,'#');//Obtenemos el segundo apellido

  //Obtenemos la fecha
  entrada.getline(aux,6,'#');
  d=atoi(aux);
  entrada.getline(aux,6,'#');
  m=atoi(aux);
  entrada.getline(aux,6,'#');
  a=atoi(aux);
  date.asignar_fecha( d,m,a);

  entrada.getline(Number,MAXCAD2,'\n');//Obtenemos el numero de telefono

  PonerTodo( Name,Surname1,Surname2,date,Number);
}


//La estructura del archivo es:  NOMBRE#APELLIDO1#APELLIDO2#DIA#MES#ANIO#TELEFONO\N
void DatosPersonales::Guardar(ofstream &salida) const
{
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  int d,m,a;
  fecha date;

  ObtenerTodo(Name,Surname1,Surname2,date,Number);

  d=date.obtener_dia();
  m=date.obtener_mes();
  a=date.obtener_anio();

  salida<<Name<<'#'<<Surname1<<'#'<<Surname2<<'#'<<d<<'#'<<m<<'#'<<a<<'#'<<Number<<'\n';
}


DatosPersonales::~DatosPersonales()
{

}


void PruebaDatosPersonales()//Actualizar a la vez que se incluyen nuevos modulos
{

  Meses M;
  M.Cargar();

  fecha f(24,4,1989);
  DatosPersonales Dato("Mario","Corchero","Jimenez",f,"661211518"), Dato2, Dato3, Dato4(Dato),Dato5;




  /**Probamos los dos pedir y los dos mostrar(con los mostrar estamos probando tambien calcular edad)*/
  Dato2.PedirES();
  cout<<endl;
  Dato2.MostrarES(M);
  cout<<endl;
  Dato3.PedirEN();
  cout<<endl;
  Dato3.MostrarEN(M);
  cout<<endl;

  cout<<"Al comparar los 2 ultimos datos personales obtenemos: "<<Dato2.CompararA(Dato3)<<endl<<endl;

  Dato4.MostrarES(M);//Probamos el constructor parametrizado y el constructor por copia
  /**Probamos los obtener y los poner*/
  TCadena1 Number;
  TCadena2 Name, Surname1, Surname2;
  fecha Date;
  int d,m,a;
  //ObtenerTodo y PonerTodo han sido probados en otros modulos internamente.
  Dato4.ObtenerNombre( Name);
  Dato4.ObtenerApellido1( Surname1);
  Dato4.ObtenerApellido2( Surname2);
  Dato4.ObtenerFecha( Date);
  Dato4.ObtenerFecha( d,m,a);
  if(Date.obtener_anio()!=a||Date.obtener_dia()!=d||Date.obtener_mes()!=m) cout <<"Error en obtener fecha \n";
  Dato4.ObtenerTelefono( Number);

  Dato5.PonerNombre( Name);
  Dato5.PonerApellido1( Surname1);
  Dato5.PonerApellido2( Surname2);
  Dato5.PonerFecha( Date);
  Dato5.PonerTelefono( Number);

  Dato5.MostrarES(M);

  /**Probamos Cargar*/
  ifstream entrada;
  entrada.open("datos_per.txt");
  if(!entrada) cout<<"No se puede abrir el flujo \n";
  else Dato5.Cargar(entrada );
  entrada.close();
  Dato5.MostrarES(M);


  /**Probamos Guardar*/
  cout<<"Pulse una tecla para continuar.\n";
  cin.get();
  system("clear");//Limpiamos para no liarnos
  cout<<"Deben mostrarse 2 datos personales iguales a continuacion\n";
  Dato4.MostrarES(M);
  ofstream salida;
  //Guardamos la clase
  salida.open("pruebas");
  Dato4.Guardar(salida);
  salida.close();
  //La recuperamos y mostramos
  entrada.open("pruebas");
  Dato5.Cargar(entrada);
  Dato5.MostrarES(M);
  entrada.close();
}

