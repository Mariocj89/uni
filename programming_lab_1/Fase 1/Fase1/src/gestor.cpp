
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
return insertado; //el que devuelva true, solo significa ke ha insertado el ultimo elemento.
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







