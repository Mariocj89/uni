
#include "gestor.h"


gestor::gestor () {
	strcpy(contadorN,"N001");
	strcpy(contadorC,"S0");
}

gestor::~gestor() {
}

void gestor::Obtener_ContadorN(Tcadena1 cad1){
	strcpy(cad1,contadorN);
}

void gestor::Obtener_ContadorC(Tcadena1 cad1){
	strcpy(cad1,contadorC);
}

bool gestor::Reducir_contadorC(){
	if(contadorC[1]=='0')
		return false;
	contadorC[1]--;
	return true;
}

void gestor::Aumentar_contadorN(){
	if(contadorN[3]=='9'){
		contadorN[3]='0';
		if(contadorN[2]=='9'){
			contadorN[1]++;
			contadorN[2]='0';}
		else contadorN[2]++;}
	else contadorN[3]++;

}

bool gestor::Aumentar_contadorC(){
  contadorC[1]='1';
  categoria c;
  list.poner_inicio();
  char v[MaxCadRef];

  if(list.vacia()) {return true;}

  do{
	list.consultar(c);
	c.Obtener_Referencia(v);
	if(contadorC[1]=='5')
		return false;
	else contadorC[1]++;
	if(strcmp(contadorC,v)!=1) {
		contadorC[1]--;
		return true;}


	list.avanzar();
  }while(!list.fin());
	return true;

}

bool gestor::Insertar_Categoria(){
	categoria l;
	char v[MaxCadRef];
	list.poner_inicio();
	if(!list.vacia()){
	do{
		list.consultar(l);
		l.Obtener_Referencia(v);
		list.avanzar();
	}while(strcmp(v,contadorC)==1&&!list.fin());}

	if(Aumentar_contadorC()==false) {cout<<"Maximo de categorias alcanzado.\n"; return false;}
	char nam[MaxCadSec];
	l.Vaciar();
	l.Poner_Referencia( contadorC);
	cout<<"Introduce el nombre de la nueva categoria: ";
	cin.getline(nam,MaxCadSec);
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	l.Poner_Nombre( nam);
	cout<<"\n Creada categoria "<<contadorC<<" : "<<nam<<endl;
	list.insertar( l);
	return true;
}

bool gestor::Insertar_Categoria(const TcadRef ref){
	categoria l;
	char v[MaxCadRef];
	list.poner_inicio();
	if(!list.vacia()){
	do{
		list.consultar(l);
		l.Obtener_Referencia(v);
		list.avanzar();
	}while(strcmp(v,ref)==1&&!list.fin());}

	if(list.llena()) {cout<<"Maximo de categorias alcanzado.\n"; return false;}
	char nam[MaxCadSec];
	l.Vaciar();
	l.Poner_Referencia( ref);
	cout<<"Introduce el nombre de la nueva categoria: ";
	cin.getline(nam,MaxCadSec);
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	l.Poner_Nombre( nam);
	cout<<"\n Creada categoria "<<ref<<" : "<<nam<<endl;
	list.insertar( l);
	return true;
}

bool gestor::Insertar_Noticia_Con_Categoria(const TipoDato &Not, const TcadRef Ref){

	categoria l;
	bool find=false;
	char aux[MaxCadRef];
	Tcadena1 cont;
	Not.Obtener_Identificador(cont);

	list.poner_inicio();
	while(!list.fin()&&!find){
		list.consultar( l);
		l.Obtener_Referencia(aux);
		if(strcmp(Ref,aux)==0)
			find=true;
		else
			list.avanzar();
	}

	if(find){
		if(list.insertar_Noticia(Not)){
			if(strcmp(contadorN,cont)==-1)
				strcpy(contadorN,cont);
			return true;}
	}
	else{
		if(Insertar_Categoria(Ref))
		{Insertar_Noticia_Con_Categoria(Not,Ref);
		return true;}
	}
	return false;


}

bool gestor::Insertar_Noticia_Con_Categoria2(const TipoDato &Not, const TcadSec Sec){


	categoria l;
	bool find;
	char aux[MaxCadSec];
	Tcadena1 cont;
	Not.Obtener_Identificador(cont);

	list.poner_inicio();
	while(!list.fin()&&!find){
		list.consultar( l);
		l.Obtener_Nombre(aux);
		if(strcmp(Sec,aux)==0)
			find=true;
		else
			list.avanzar();
	}

	if(find)
		if(list.insertar_Noticia(Not))
			if(strcmp(contadorN,cont)==-1)
				strcpy(contadorN,cont);
			return true;
	return false;



}

bool gestor::Insertar (const Noticia &n) { 

  cin.ignore();

  categoria l;
  char v[MaxCadRef]="S0",b[MaxCadRef];

  cout<<"\nCategorias existentes: \n";
  Mostrar_Categorias();
  if(!list.vacia()){
  	cout<<"\n Introduzca el identificador de la categoria a la que desea añadir la noticia. \n Inserte S0 para añadirlo a una nueva categoria:";
  	cin.getline(v,MaxCadRef,'\n');
  	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  }

  while(v[1]>'5'||v[1]<'0'){
	cout<<"\nCaracter invalido, elija una opcion correcta (S0-S5):";
	cin.getline(v,MaxCadRef);
	 if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
  }

  if(v[1]=='0'){
	if(Aumentar_contadorC()==false) {cout<<"Maximo de categorias alcanzado.\n"; return false;}
	char nam[MaxCadSec];
	l.Poner_Referencia( contadorC);
	cout<<"Introduce el nombre de la nueva categoria: ";
	cin.getline(nam,MaxCadSec);
	 if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	l.Poner_Nombre( nam);
	cout<<"\n Creada categoria "<<contadorC<<" : "<<nam<<endl;
	l.Insertar( n); 
	list.insertar(l);
	Aumentar_contadorN();

	return true;}

  bool salir=false;
  list.poner_inicio();
  while(!salir){
	list.consultar(l);
	l.Obtener_Referencia(b);
	if(strcmp(v,b)==0) salir=true;
	else list.avanzar();
	if(list.fin()) return false;
}


  if(l.Llena()){
	TipoDato dat1;
	Tcadena1 id1;
	l.Poner_Inicio();
	l.Consultar(dat1);
	cout<<"\n \n Para insertar una noticia se va a borrar la siguiente noticia: \n \n";
	dat1.Mostrar_Noticia();
	dat1.Obtener_Identificador(id1);
	Eliminar(id1);}

  list.insertar_Noticia(n);
  Aumentar_contadorN();
  return true;

}

void gestor::Mostrar_Categorias(){
  if(list.vacia()) cout<<"El blog esta vacio. \n";
  categoria l;
  int contador=0;
  char cad1[MaxCadRef];
  char cad2[MaxCadSec];
  list.poner_fin();
  while(!list.inicio()){
	list.retroceder();
	list.consultar(l);
	l.Poner_Inicio();
	contador=0;
	while(!l.Fin()){
		contador++;
		l.Avanzar();
	}
	l.Obtener_Nombre( cad2);
	l.Obtener_Referencia( cad1);
	cout<<"Categoria " << cad1 << " : "<<cad2<< "\n Tiene: \t"<<contador<<" noticias.\n";
  }
}

void gestor::Mostrar_Categoria(const char ref[MaxCadRef]) {
  char cadd[MaxCadRef];
  strcpy(cadd,ref);
  categoria l;
  list.poner_fin();
  while(cadd[1]>'5'||cadd[1]<'0'){
	cout<<"\nCaracter invalido, elija una opcion correcta (S1-S5):";
	cin>>cadd;
  }
  char cad1[MaxCadSec];
  char cad2[MaxCadRef];
  if(list.vacia()==true) cout<<" La seccion esta vacia. \n";
  while(!list.inicio()){
     list.retroceder();
     list.consultar( l);
     l.Obtener_Referencia( cad2);
     if(strcmp(cad2,ref)==0){
	list.inicio();
  	l.Obtener_Nombre( cad1);
  	TipoDato dat;
  	l.Poner_Fin();
  	cout<<"\n [    Noticias pertenecientes a la seccion " << cad2 << " : " << cad1 << "    ] \n\n";
  	while(l.Inicio()==false){
		l.Retroceder();
		l.Consultar(dat);
		dat.Mostrar_Noticia();
  	}
     }

  }
}

void gestor::Mostrar() { 
  categoria l;
  list.poner_fin();
  char cad1[MaxCadSec];
  char cad2[MaxCadRef];
  while(!list.inicio()){
	list.retroceder();
  	list.consultar( l);

  	l.Obtener_Nombre( cad1);
  	l.Obtener_Referencia( cad2);
  	if(list.vacia()==true) cout<<" El Blog esta vacio. \n";
  	TipoDato dat;
  	l.Poner_Fin();
  	cout<<"\n [    Noticias pertenecientes a la seccion " << cad2 << " : " << cad1 << "    ] \n\n";
  	while(l.Inicio()==false){
		l.Retroceder();
		l.Consultar(dat);
		dat.Mostrar_Noticia();
  	}
  	if(l.Vacia()==true) cout<<" La categoria "<<cad2<<" : "<<cad1<<" esta vacia."<<endl;

  }
}

bool gestor::Eliminar(Tcadena ident) { 
list.borrar_Noticia(ident);
}

bool gestor::Eliminar_Categoria(char ref[MaxCadRef]){

  if(list.vacia()) return false;
  char id[MaxCadRef];
  char aux;
  TipoDato d;
  char refe[MaxCadRef];
  categoria dat,dat2;
  bool salir=false;
  list.poner_inicio();
  while(list.fin()==false){
	list.consultar(dat);
	dat.Obtener_Referencia( id);
	if(strcmp(id,ref)==0){
		list.borrar();
		if(!dat.Vacia()){
			cout<<"¿Desea pasar las noticias de esta categoria a otra?\nS(si) o N(No): ";
			cin.get(aux);
			cin.ignore();
			if(aux=='S'||aux=='s'){
				cout<<"Introduzca el identificador de la categoria: ";
				cin.getline(refe,MaxCadRef,'\n');
				if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
				dat.Poner_Inicio();
				list.poner_inicio();
				while(!salir&&!list.fin()){
					list.consultar(dat2);
					dat2.Obtener_Referencia(id);
					if(strcmp(id,refe)!=0) list.avanzar();
					else salir=true;
					}
				while(!dat.Fin()){
					dat.Consultar(d);
					list.insertar_Noticia(d);
					dat.Avanzar();
				}
			}
		}
		Reducir_contadorC();
		return true;}
	list.avanzar();
  }
  return false;
}

bool gestor::Buscar_Cadena( Tcadena cad1){
  char x='N';
  cout<<"¿Desea que la busqueda distinga mayusculas y minusculas? \n Si(S) o No(N): ";
  cin.get(x);
  cin.ignore();
  categoria l;
  bool encontrado=false;
  list.poner_fin();
  char cad[MaxCadSec];
  char cad2[MaxCadRef];
  Tcadena3 cont, cad4, buscada;
  Tcadena2 tit, sub;
  if(x=='S'||x=='s')
	strcpy(buscada, cad1);
  else
  	Pasar_Minusculas( cad1, buscada);

  while(!list.inicio()){
	list.retroceder();
  	list.consultar( l);

  	l.Obtener_Nombre( cad);
  	l.Obtener_Referencia( cad2);

  	TipoDato dat;
  	l.Poner_Inicio();
  	while(l.Fin()==false){
		l.Consultar(dat);
		dat.Obtener_Titulo( tit);//Busca en el titulo
		if(x=='S'||x=='s')
			strcpy(cad4,tit);
		else
			Pasar_Minusculas( tit,cad4);
		if(strstr(cad4,buscada)!=NULL){
			cout<<"Seccion [ "<<cad2<<" : "<<cad<<" ] \n";
			dat.Mostrar_Noticia();
			encontrado=true;}
		else{
			dat.Obtener_SubTitulo( sub);//Busca en el subtitulo
			if(x=='S'||x=='s')
				strcpy(cad4,sub);
			else
				Pasar_Minusculas( sub,cad4);
			if(strstr(cad4,buscada)!=NULL){
				cout<<"Seccion [ "<<cad2<<" : "<<cad<<" ] \n";
				dat.Mostrar_Noticia();
				encontrado=true;}
			else{
				dat.Obtener_Contenido( cont);//Busca en el contenido
				if(x=='S'||x=='s')
					strcpy(cad4,cont);
				else
					Pasar_Minusculas( cont,cad4);
				if(strstr(cad4,buscada)!=NULL){
					cout<<"Seccion [ "<<cad2<<" : "<<cad<<" ] \n";
					dat.Mostrar_Noticia();
					encontrado=true;}
			}
		}
		l.Avanzar();
  	}
  }
  if(!encontrado) cout<<"No hay coincidencias para: "<<cad1<<endl;
  return encontrado;
}


bool gestor::Buscar(Tcadena ident){
  categoria l;
  list.poner_fin();
  char cad1[MaxCadSec];
  char cad2[MaxCadRef];
  while(!list.inicio()){
	list.retroceder();
  	list.consultar( l);

  	l.Obtener_Nombre( cad1);
  	l.Obtener_Referencia( cad2);

  	TipoDato dat;
  	l.Poner_Inicio();
  	while(l.Fin()==false){
		l.Consultar(dat);
		if(dat.Comparar(ident)==0){
			cout<<"Seccion [ "<<cad2<<" : "<<cad1<<" ] \n";
			dat.Mostrar_Noticia();
			return true;}
		l.Avanzar();
  	}
  }
  return false;
}

bool gestor::Guardar(char nombre[20]){
  categoria l;
  Noticia dat;
  char nam[MaxCadSec];
  cout << endl << "Guardando Blog. " << endl;
  ofstream salida;
  salida.open(nombre);
  if(!salida) cout<<"Error al abrir el fichero: "<<nombre<<endl;
  else{
	list.inicio();
	while(!list.fin()){
		list.consultar(l);
		l.Poner_Inicio();
		l.Obtener_Nombre(nam);
		while(l.Fin()==false){
			l.Consultar(dat);
			l.Avanzar();
			salida<<nam<<'#';
			dat.Guardar_Noticia(salida);
		}
		list.avanzar();
	}salida.close();
  }
  cout<<"Blog guardado correctamente como: "<<nombre<<endl;
}

bool  gestor::Cargar(char nombre[20]){
  categoria l,m;
  bool salir=false;
  bool insertado=false;
  char sec[MaxCadSec],aux[MaxCadSec];
  cout << endl << "Cargando Blog. " << endl;
  ifstream entrada;
  entrada.open(nombre);
  char linea[100];
  if(!entrada) cout<< "Error al abrir el fichero: "<<nombre<<endl;
  else{
	TipoDato dat;
	while(!entrada.eof()){
		l.Vaciar();
		insertado=false;
		salir=false;
		entrada.getline(sec,MaxCadSec,'#');
		if(!entrada.eof()){
			dat.Cargar_Noticia(entrada);
			dat.Poner_Identificador(contadorN);
			Aumentar_contadorN();
			/** Inicio de la parte consistente en la inserccion correcta de la noticia*/
			list.poner_inicio();
			if(list.vacia()) salir=true;
			while(!salir){
				list.consultar(m);
				m.Poner_Inicio();
				m.Obtener_Nombre(aux);
				if(strcmp(aux,sec)==0) salir=true;
				else list.avanzar();
				if(list.fin()) salir=true;
			}
			if(list.fin()){
				/** Inicio de la parte consistente en la inserccion correcta de una categoria*/
				if(Aumentar_contadorC()==false) {cout<<"Maximo de categorias alcanzado.\n No han podido añadirse todas las noticias. \n"; return false;}
				l.Poner_Referencia(contadorC);
				l.Poner_Nombre(sec);
				l.Insertar(dat);
				list.insertar(l);
				insertado=true;
				/**Fin de la parte consistente en la inserccion correcta de una categoria*/	
			}
			if(!insertado) {
				if(m.Llena()){
					TipoDato dat1;
					Tcadena1 id1;
					m.Poner_Inicio();
					m.Consultar(dat1);
					cout<<"\n \n Para insertar una noticia se va a borrar la siguiente noticia: \n \n";
					dat1.Mostrar_Noticia();
					dat1.Obtener_Identificador(id1);
					Eliminar(id1);}
				list.insertar_Noticia(dat);}
			/** Fin de la parte consistente en la inserccion correcta de la noticia*/
		}
	}entrada.close();
	cout<<" Blog cargado correctamente."<<endl;

}
return true; //El que devuelva true solo significa que ha llegado hasta el final.
}

void  gestor::Pedir_Noticia(TipoDato &Dat){
	Dat.PedirNoticia(contadorN);
}

void Pasar_Minusculas(const Tcadena3 cad1, Tcadena3 cad2){
	int i=0;
	while(cad1[i]!='\0'){
		if(cad1[i]<='Z'&&cad1[i]>='A')
			cad2[i]=cad1[i]+32;
		else
			cad2[i]=cad1[i];
		i++;
	}
	cad2[i]='\0';
}


bool gestor::Guardar_Binario(){

	categoria l;
	ofstream salida;
	salida.open("blog.dat",ios::binary|ios::trunc);
	
	if(!salida) return false;
	else{
		list.poner_inicio();
		while(!list.fin()){
			list.consultar(l);
			salida.write((const char *) &l, sizeof (categoria));
			list.avanzar();
		}
	salida.close();
	}


}

bool gestor::Iniciar_Binario(){

	categoria l;
	ifstream entrada;
	entrada.open("blog.dat",ios::binary);

	list.poner_inicio();
	if(!entrada) return false;
	else{
		while(!entrada.eof()){
			entrada.read((char *) &l, sizeof(categoria));
			if(!entrada.eof()){
				list.insertar(l);
				Aumentar_contadorC();}
		}
	entrada.close();
	}
	return true;
}


bool gestor::Iniciar_Texto(){

  Noticia Not;
  ifstream entrada;
  categoria l;
  TcadRef Ref;
  Tcadena3 linea;
  fecha f;
  int d,m,a;

  /**Comienzo de la parte perteneciente a la inserccion de las secciones*/
  entrada.open("secciones.txt");
  if(!entrada) return false;
  else{
	//!Despreciamos las 2 primeras lineas.
	entrada.getline(linea,MaxCad3,'\n');
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	entrada.getline(linea,MaxCad3,'\n');
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	while(!entrada.eof()){
		entrada.getline(linea,MaxCad3,'#');
		if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
		if(!entrada.eof()){
			l.Poner_Referencia(linea);
			entrada.getline(linea,MaxCad3,'\n');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			l.Poner_Nombre(linea);
			list.insertar(l);
			list.avanzar();	
		}
	}
  entrada.close();
  }
  /**Terminada la parte perteneciente a la inserccion de las secciones*/
  /**Comienzo de la parte perteneciente a la inseccion de las noticias*/
  entrada.open("noticias.txt");
  if(!entrada) return false;
  else{
	//!Despreciamos las 2 primeras lineas.
	entrada.getline(linea,MaxCad3,'\n');
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	entrada.getline(linea,MaxCad3,'\n');
	if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
	while(!entrada.eof()){
		entrada.getline(linea,MaxCad3,'#');
		if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
		if(!entrada.eof()){
			Not.Poner_Identificador(linea);
			entrada.getline(Ref,MaxCadRef,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			entrada.getline(linea,MaxCad3,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			Not.Poner_Titulo(linea);
			entrada.getline(linea,MaxCad3,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			Not.Poner_SubTitulo(linea);
			entrada.getline(linea,MaxCad3,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			Not.Poner_Contenido(linea);
			entrada.getline(linea,MaxCad3,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			Not.Poner_Imagen(linea);
			entrada.getline(linea,MaxCad3,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			d=atoi(linea);
			entrada.getline(linea,MaxCad3,'#');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			m=atoi(linea);
			entrada.getline(linea,MaxCad3,'\n');
			if(cin.fail()) {cin.clear(); cin.ignore(10,'\n');}
			a=atoi(linea);
			f.asignar_fecha(d,m,a);
			Not.Poner_Fecha(f);
			Insertar_Noticia_Con_Categoria(Not,Ref);//Si no existe la seccion la crea.
		}
	}
  entrada.close();
  }
  /**Terminada la parte perteneciente a la inserccion de las noticias*/


}

bool gestor::Crear_Html(){

  categoria l;
  Noticia n;
  fecha f;
  Tcadena1 cad1;
  Tcadena2 cad2;
  Tcadena3 cad;
  int x;
  ofstream salida;


  list.poner_inicio();
  while(!list.fin()){
	list.consultar(l);
	l.Obtener_Nombre(cad);
	Quitar_Espacios(cad);
	strcat(cad,".html");
	salida.open(cad,ios::out|ios::trunc);
	if(!salida) {cout<<"No se ha conseguido escribir: "<<cad<<".\n"; return false;}
	else{
		salida<<"<html>\n<head>\n<title>"<<cad<<"</title>\n</head><body>\n";//Parte perteneciente al titulo
		l.Poner_Inicio();
		/**Linea de codigo por si la seccion esta vacia*/
		if(l.Vacia()) salida<<"<p style=\"color: #0000FF; font-size: 20pt \"> La categoria esta vacia.</p> ";
		while(!l.Fin()){
			l.Consultar(n);	
			/**Comienzo del codigo destinado a guardar una noticia en formato html, dividida para mejor comprension*/

			salida<<" <TABLE CELLPADDING=10 CELLSPACING=6 BORDER=6 BORDER>\n";//Creamos una tabla con un estilo determinado
			salida<<" <CAPTION ALIGN=top> <B> "; n.Obtener_Identificador(cad1); salida<<cad1<<"</B></CAPTION>";//identificador de la noticia
			salida<<"<TR align=\"center\"><TD><B> Titulo: </B></TD> <TD> "; n.Obtener_Titulo(cad2); salida<<cad2<<"</TD></TR>";//Titulo de la noticia
			salida<<"<TR align=\"center\"><TD><B> Subtitulo: </B></TD> <TD> "; n.Obtener_SubTitulo(cad2); salida<<cad2<<"</TD></TR>";//Subtitulo de la noticia
			salida<<"<TR align=\"center\"><TD><B> Contenido: </B></TD> <TD> "; n.Obtener_Contenido(cad); salida<<cad<<"</TD></TR>";//Contenido de la noticia
			salida<<"<TR align=\"center\"><TD><B> Imagen: </B></TD> <TD> "; n.Obtener_Imagen(cad2); salida<<"<IMG src=\""<<cad2<<"\" align=middle>"<<"</TD></TR>";//Imagen de la noticia
			salida<<"<TR align=\"center\"><TD><B> Fecha: </B></TD> <TD> "; n.Obtener_Fecha(f);salida<<f.obtener_dia()<<"/"<<f.obtener_mes()<<"/"<<f.obtener_anio(); salida<<"</TD></TR>";//Fecha de la noticia
			salida<<"</table>\n<BR>\n<BR>";//cerramos la tabla
			/**Fin del codigo destinado a guardar una noticia en formato html*/
			l.Avanzar();
		}
		salida<<" </body>\n</html>";//cerramos el documento html
	salida.close();
	}

	list.avanzar();
  }
  return true;
}


void Quitar_Espacios(Tcadena3 cad){

  Tcadena3 aux;
  int j=0;
  for (int i=0;i<=strlen(cad);i++)
	if(cad[i]!=' '){
		aux[j]=cad[i];
		j+=1;
	}
  strcpy(cad,aux);
}


