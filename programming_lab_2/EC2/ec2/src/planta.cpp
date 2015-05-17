/**
* \file planta.cpp
* \brief Implementacion de los metodos de la clase puerta
* \date 20-04-09
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/



#include "planta.h"

/**
 * Crea y prepara las llaves para tratarlas
 * @param n_llaves numero de llaves a crear
 * @param configuracion configuracion de la puerta
 * @param llaves llaves a insertar en la planta
 */
void Planta::PrepararLlaves(const int & n_llaves, ColaGen< Llave * > *configuracion, queue< Llave * > &llaves)
{
  Llave* llave;
  int max_llaves=((ancho_*alto_)-2)*kMaxLlavesPorCelda;
  for(int i=0;i<n_llaves;i++){
    llave=new Llave(i);
    llaves.push(llave);
    if(i%2==1){
      llaves.push(new Llave(i));
      configuracion->insertar_dato(llave);
    }
  }
  if(llaves.size()>max_llaves) throw ErrorNumeroLlaves(id_);
}


/**
 * Constructor parametrizado de la clase Planta
 * @param identificador identificador de la planta
 * @param ancho ancho de la planta
 * @param alto alto de la planta
 * @param entrada posicion de entrada
 * @param salida posicion de salida
 * @param n_llaves numero de llaves a generar
 * @param altura_control altura de control del arbol de la puerta
 */
Planta::Planta(const int &identificador, const int &ancho, const int &alto, const int &entrada, const int &salida, const int &n_llaves, const int &altura_control)
{
  if(kDepurarPlanta) cin.get();
  //Inicializamos las variables de la planta
  this->id_ = identificador;
  if(ancho<2||alto<2) throw ErrorTamanio(identificador);
  else{
    this-> ancho_ = ancho;
    this-> alto_= alto;
  }
  if(entrada<0||entrada>=ancho*alto||entrada==salida) throw ErrorPuerta(id_);
  else entrada_=entrada;
  if(salida<0||salida>=ancho*alto) throw ErrorPuerta(id_);
  else salida_=salida;
  puerta_ = new Puerta(altura_control);
  for (int i=0;i<ancho_*alto_;i++){
    celdas_.push_back(new Celda(i));
    grafo_.set_nodo(i);
  }
  //Inicializamos la planta (kruskal y atajos)
  this->IniciarParedes();
  cout<<endl<<*this<<endl;
  Registro::get_instancia()->Flujo()<<*this<<"(planta con ciclos)";

  this->GenerarAtajos();
  Registro::get_instancia()->Flujo()<<endl<<*this;
  cout<<endl<<*this<<endl;
  cout<<endl;


  //Introducir las llaves
  ColaGen <Llave*> *configuracion = new ColaGen<Llave*>;
  queue <Llave*> llaves;
  try{
    PrepararLlaves(n_llaves,configuracion,llaves);
  }
  catch(ErrorNumeroLlaves &exc){
    int num;
    cout<<exc.what(num)<<endl;
    while(!llaves.empty()){
      delete llaves.front();
      llaves.pop();
    }
    delete configuracion;
    configuracion = new ColaGen<Llave*>;
    PrepararLlaves(num,configuracion,llaves);
  }
  puerta_->Configurar(configuracion);
  puerta_->Cerrar();
  this->ColocarLlaves(llaves);
  MostrarRutaEscape();
  delete configuracion;
  Registro::get_instancia()->Flujo()<<endl;
}

/**
 * Metodo privado para iniciar las paredes de una planta
 */
void Planta::IniciarParedes()
{
  cout<<"Creando distribucion de la planta: "<<id_<<endl;
  list <TipoArco> paredes;
  list <TipoArco>::iterator it;
  TipoArco aux;
  int buscada;
  int n_aleatorio;
  TipoMatrizBooleana path;
  for (int i=0;i<ancho_*alto_;i++){ //insertamos las paredes que se pueden eliminar
    aux.x=i;
    if(ParedValida(NORTE,i)) {//insertamos la pared norte
      aux.y = i-ancho_;
      paredes.push_back(aux);
      if(kDepurarPlanta)  cout<<"( "<<aux.x<<" , "<<aux.y<<" )"<<" N -- ";
    } 
    if(ParedValida(ESTE,i) ) { //insertamos la pared este
      aux.y = i+1;
      paredes.push_back(aux);
      if(kDepurarPlanta)  cout<<"( "<<aux.x<<" , "<<aux.y<<" )"<<" E -- ";
    }
    if(ParedValida(SUR, i)) { //insertamos la pared sur
      aux.y = i+ancho_;
      paredes.push_back(aux);
      if(kDepurarPlanta)      cout<<"( "<<aux.x<<" , "<<aux.y<<" )"<<" S -- ";
    }
    if(ParedValida(OESTE,i) ) { //insertamos la pared oeste
      aux.y = i-1;
      paredes.push_back(aux);
      if(kDepurarPlanta)      cout<<"( "<<aux.x<<" , "<<aux.y<<" )"<<" O -- ";
    }
  }

  //eliminamos paredes:
  while(!paredes.empty()){
    it = paredes.begin();
    cout<<endl<<*this<<endl; 
    n_aleatorio=GenAleatorios::generarNumero(paredes.size());
    if(kDepurarPlanta)  cout<<"\n Numero aleatorio generado: "<<n_aleatorio<<'\n';
    for (int i=1; i<n_aleatorio+1; i++) it++; //localizamos el elemento
    aux = *it; //obtenemos el arco situado en una posicion aleatoria
    cout<<"pared elegida: "<<aux.x<<" - "<<aux.y<<endl;
    if(celdas_[aux.x]->get_marca()!=celdas_[aux.y]->get_marca()) {
      grafo_.set_arco(aux.x,aux.y,1);
      cout<<"Se tira la pared. Marca: "<<celdas_[aux.x]->get_marca()<<endl;
      buscada=celdas_[aux.y]->get_marca();
      for(int i=0;i<celdas_.size();i++){ 
       if(celdas_[i]->get_marca()==buscada) {
         celdas_[i]->set_marca(celdas_[aux.x]->get_marca());
       }
      }
    }
    if(kDepurarPlanta)    cout<<"\nEliminamos de la lista: ( "<<it->x<<" , "<<it->y<<" )"<<" \n ";


    paredes.erase(it); //eliminamos el arco tras procesarlo
  }
}

/**
 * Algoritmo que genera los atajos de la prision
 */
void Planta::GenerarAtajos( )
{

  bool tirado;
  Posicion punto_cardinal;
  int n_aleatorio=0, contador=0, atirar=(ancho_*alto_*5)/100;
  cout<<endl<<"Creacion de atajos - Numero de paredes a tirar: "<<atirar<<endl;
  while(contador<atirar) {
    n_aleatorio=GenAleatorios::generarNumero( ancho_*alto_);
    tirado=false;
    tirado = GeneraAtajo(NORTE,n_aleatorio);
    if(!tirado) tirado = GeneraAtajo(SUR,n_aleatorio);
    if(!tirado) tirado = GeneraAtajo(OESTE,n_aleatorio);
    if(!tirado) tirado = GeneraAtajo(ESTE,n_aleatorio);
    if(tirado) contador++;
  }
}

/**
 * Comprueba si hay una casilla en la direccion indicada
 * @param p direccion a mirar
 * @param id celda desde la que mirar
 * @return true si hay casilla en la direccion indicada
 */
bool Planta::ParedValida(const Posicion & p, const int & id) const
{
  switch(p){
    case NORTE: if(id>(ancho_-1)) return true; break;
    case SUR:   if(id<(ancho_*(alto_-1))) return true; break;
    case ESTE:  if(id%ancho_ < ancho_-1) return true; break;
    case OESTE: if(id%ancho_ != 0) return true; break;
  }
  return false;
}

/**
 * Comprueba si se puede generar un atajo en la direccion indicada
 * @param p direccion en la que se quiere tirar la pared
 * @param id casilla de la que se parte
 * @return true si se puede tirar la pared
 */
bool Planta::HayAtajo(const Posicion & p, const int & id) const
{
  if(!ParedValida(p,id))  {
    return false;
  }
  else  {
    if(grafo_.Adyacente(get_vecina(p,id),id)) return false; //si no hay pared no podemos eliminar
    switch(p){
      case NORTE: return ((!grafo_.Adyacente(id,get_vecina(OESTE,id)))|| //comrpueba CE - OESTE
                         (!grafo_.Adyacente(get_vecina(OESTE,id),get_vecina(NORTE,(get_vecina(OESTE,id)))))|| //comprueba OESTE- NOROESTE
                         (!grafo_.Adyacente(get_vecina(NORTE,(get_vecina(OESTE,id))),get_vecina(NORTE,id))))&& //comprueba NORTE - NOROESTE
                         ((!grafo_.Adyacente(id,get_vecina(ESTE,id)))|| //comrpueba CE - ESTE
                         (!grafo_.Adyacente(get_vecina(ESTE,id),get_vecina(NORTE,(get_vecina(ESTE,id)))))|| //comprueba ESTE- NORESTE
                         (!grafo_.Adyacente(get_vecina(NORTE,(get_vecina(ESTE,id))),get_vecina(NORTE,id)))); //comprueba NORTE - NORESTE
                         break;

      case SUR: return   ((!grafo_.Adyacente(id,get_vecina(OESTE,id)))|| //comrpueba CE - OESTE
                         (!grafo_.Adyacente(get_vecina(OESTE,id),get_vecina(SUR,(get_vecina(OESTE,id)))))|| //comprueba OESTE- SUROESTE
                         (!grafo_.Adyacente(get_vecina(SUR,(get_vecina(OESTE,id))),get_vecina(SUR,id))))&& //comprueba SUR - SUROESTE
                         ((!grafo_.Adyacente(id,get_vecina(ESTE,id)))|| //comrpueba CE - ESTE
                         (!grafo_.Adyacente(get_vecina(ESTE,id),get_vecina(SUR,(get_vecina(ESTE,id)))))|| //comprueba ESTE- SURESTE
                         (!grafo_.Adyacente(get_vecina(SUR,(get_vecina(ESTE,id))),get_vecina(SUR,id)))); //comprueba SUR - SURESTE
                         break;

      case OESTE: return ((!grafo_.Adyacente(id,get_vecina(NORTE,id)))|| //comrpueba CE - NORTE
                         (!grafo_.Adyacente(get_vecina(OESTE,id),get_vecina(NORTE,(get_vecina(OESTE,id)))))|| //comprueba OESTE- NOROESTE
                         (!grafo_.Adyacente(get_vecina(NORTE,(get_vecina(OESTE,id))),get_vecina(NORTE,id))))&& //comprueba NORTE - NOROESTE
                         ((!grafo_.Adyacente(id,get_vecina(SUR,id)))|| //comrpueba CE - SUR
                         (!grafo_.Adyacente(get_vecina(OESTE,id),get_vecina(SUR,(get_vecina(OESTE,id)))))|| //comprueba OESTE- SUROESTE
                         (!grafo_.Adyacente(get_vecina(SUR,(get_vecina(OESTE,id))),get_vecina(SUR,id)))); //comprueba SUR - SUROESTE
                         break;

      case ESTE: return  ((!grafo_.Adyacente(id,get_vecina(NORTE,id)))|| //comrpueba CE - NORTE
                         (!grafo_.Adyacente(get_vecina(ESTE,id),get_vecina(NORTE,(get_vecina(ESTE,id)))))|| //comprueba ESTE- NORESTE
                         (!grafo_.Adyacente(get_vecina(NORTE,(get_vecina(ESTE,id))),get_vecina(NORTE,id))))&& //comprueba NORTE - NORESTE
                         ((!grafo_.Adyacente(id,get_vecina(SUR,id)))|| //comrpueba CE - SUR
                         (!grafo_.Adyacente(get_vecina(ESTE,id),get_vecina(SUR,(get_vecina(ESTE,id)))))|| //comprueba ESTE- SURESTE
                         (!grafo_.Adyacente(get_vecina(SUR,(get_vecina(ESTE,id))),get_vecina(SUR,id)))); //comprueba SUR - SURESTE
                         break;
    }
  }
}

/**
 * Obtiene el identificador de la celda en la direccion indicada
 * @param p direccion en la que buscamos la pared
 * @param id celda actual
 * @return identificador de la celda (-1 = no valida)
 */
int Planta::get_vecina(const Posicion & p, const int & id) const
{
  if(!ParedValida(p,id)) return -1;
  else{
    switch(p){
      case NORTE: return celdas_[id-ancho_]->get_id(); break;
      case SUR:   return celdas_[id+ancho_]->get_id(); break;
      case ESTE:  return celdas_[id+1]->get_id(); break;
      case OESTE: return celdas_[id-1]->get_id(); break;
    }
  }
}

/**
 * Intenta generar un atajo en la direccion indicada
 * @param p direccion indicada	
 * @param id celda desde la que partimos
 * @return true si se elimina correctamente
 */
bool Planta::GeneraAtajo(const Posicion & p, const int & id)
{
  if(HayAtajo(p,id))  {
    grafo_.set_arco(id,get_vecina(p,id),1);
    cout<<"Pared tirada: "<<id<<" - "<<get_vecina(p,id)<<endl;
    return true;
  }
  else  {
   return false;
  }
}

/**
 * Sobrecarga del operador <<
 * @param salida flujo de salida
 * @param p planta a mostrar
 * @return flujo con la informacion
 */
ostream& operator<<(ostream &salida, const Planta &p) {
  int celda_actual=-1;
  for(int j=0;j<p.ancho_;j++) salida<<" _";
  salida<<" "<<endl;
  for(int i=0;i<p.alto_-1;i++){
    salida<<"|";
    for(int j=0;j<p.ancho_-1;j++) {
      celda_actual = p.celdas_[(i*p.ancho_)+j]->get_id();
      if(!p.grafo_.Adyacente(celda_actual,p.get_vecina(SUR,celda_actual))) salida<<"_";
      else salida<<" ";
      if(!p.grafo_.Adyacente(celda_actual,p.get_vecina(ESTE,celda_actual))) salida<<"|";
      else salida<<" ";
    }
    celda_actual = p.celdas_[(i*p.ancho_)+p.ancho_-1]->get_id();
    if(!p.grafo_.Adyacente(celda_actual,p.get_vecina(SUR,celda_actual))) salida<<"_";
    else salida<<" ";
    salida<<"|"<<endl;
  }

  salida<<"|";
  int este=0;
  for(int j=0;j<p.ancho_;j++) {
    salida<<"_";
    celda_actual = p.celdas_[(p.alto_-1)*p.ancho_+j]->get_id();
    este = p.get_vecina(ESTE,celda_actual);
    if(!p.grafo_.Adyacente(celda_actual,p.get_vecina(ESTE,celda_actual))) salida<<"|";
    else salida<<" ";
  }
  salida<<endl;
  return salida;
}

/**
 * Coloca las llaves en la planta
 * @param llaves cola de llaves a colocar
 */
void Planta::ColocarLlaves(queue<Llave*> & llaves)
{
  Llave *l;
  Celda* c;

  Registro::get_instancia()->Escribir("(distribucion llaves)\n");
  cout<<"Distribucion de llaves: \n";
  int frecuencia[100], maximo=-1, pos_maximo=-1,j;
  ObtenerMasVisitadas(frecuencia);
  while(!llaves.empty()){
    maximo=-1;
    for(int i=0;i<alto_*ancho_;i++)
      if(frecuencia[i]>maximo){
        maximo=frecuencia[i];
        pos_maximo=i;
      }
    frecuencia[pos_maximo]=-1;
    cout<<"(celda:"<<pos_maximo<<"("<<maximo<<"):";
    Registro::get_instancia()->Flujo()<<"(celda:"<<pos_maximo<<":";
    for(j=0;j<kMaxLlavesPorCelda && !llaves.empty();j++){
      c=celdas_[pos_maximo];
      l=llaves.front();
      c->set_llave(l);
      llaves.pop();
      cout<<" "<<*l;
      Registro::get_instancia()->Flujo()<<" "<<*l;
      if(kDepurarPlanta) cout<<"Se han insertado la llave: "<<*l<<" en la celda: "<<pos_maximo<<endl;
    }
    Registro::get_instancia()->Escribir(")\n");
    cout<<")"<<endl;
  }
  if(kDepurarPlanta) cin.get();
}

/**
 * Calcula la ruta de escape segun lo indicado en el guion
 * @return cola STL con la ruta de escape
 */
void Planta::CalcularRuta(list<Posicion> &ruta ) const
{
  bool visitados[kMaxVert]={false};
  RutaRecursivo(entrada_,visitados,ruta,3);
}

/**
 * Metodo recursivo para el calculo de la ruta de escape
 * @param posicion posicion de la que se parte
 * @param visitados[] vector de visitados
 * @param ruta ruta de escape
 * @param ultimo_movimiento entero que informa del la direccion del ultimo movimiento
 * @return true si ha encontrado el elemento
 */
bool Planta::RutaRecursivo(const int & posicion, bool visitados[kMaxVert], list< Posicion > & ruta, int ultimo_movimiento) const
{
  TipoCjtoNodos ady;
  TipoNodoGrafo w, vecina;
  Posicion orientacion;
  int movimiento;
  
  //insertamos los adyacentes en el orden conveniente
  for(int i=0;i<4;i++){
    switch((i+ultimo_movimiento+1)%4){
      case 0: orientacion = NORTE; break;
      case 1: orientacion = ESTE; break;
      case 2: orientacion = SUR; break;
      case 3: orientacion = OESTE; break;
    }
    vecina = get_vecina(orientacion,posicion);
    if(grafo_.Adyacente(posicion, vecina)) ady.push(vecina);
  }

  if(posicion == salida_) return true;
  visitados[posicion]=true;
  while(!ady.empty()){
    w=ady.front();
    ady.pop();
    if(!visitados[w]) {
      if(w-posicion == 1) {orientacion = ESTE; movimiento=1;}
      if(w-posicion == -1) {orientacion = OESTE; movimiento=3;}
      if(w-posicion == -ancho_) {orientacion = NORTE; movimiento=0;}
      if(w-posicion == ancho_) {orientacion = SUR; movimiento=2;}
      if(this->RutaRecursivo(w,visitados,ruta,movimiento)){
        ruta.push_front(orientacion);
        return true;
      }
    }
  }
  return false;
}

/**
 * Calcula el numero de veces que se pasa por cada celda y lo devuelve por parametro
 * @param frecuencia[] numero de veces que se pasa por cada celda
 */
void Planta::ObtenerMasVisitadas(int frecuencia[kMaxVert]) const
{
  for(int i=0;i<alto_*ancho_;i++) frecuencia[i]=0;
  bool visitados[kMaxVert] = {false};
  stack < int > ruta;
  VisitadosRecursivo(entrada_,visitados,ruta,frecuencia);
  frecuencia[entrada_]=-1;
  frecuencia[salida_]=-1;
}

/**
 * Metodo auxiliar que calcula recursivamente el numero de veces que se visita una celda pasando 1 vez por cada ruta de escape
 * @param posicion posicion actual
 * @param visitados[] nodos visitados en la ruta actual
 * @param ruta ruta actual
 * @param frecuencia[] numero de veces que aparece cada nodo
 */
void Planta::VisitadosRecursivo(const int & posicion, bool visitados[kMaxVert], stack< int > ruta, int frecuencia[kMaxVert]) const
{
  TipoCjtoNodos ady;
  int w;
  bool insertado=false;

  if(posicion == salida_){ //Hemos encontrado una ruta!
    stack<int> aux;
    while(!ruta.empty()){
      aux.push(ruta.top());
      w=ruta.top();
      frecuencia[ruta.top()]++;
      ruta.pop();
    }
    while(!aux.empty()){
      ruta.push(aux.top());
      aux.pop();
    }
  }
  else{
    grafo_.Adyacentes(posicion,ady);
    if(!visitados[posicion]) {ruta.push(posicion); insertado=true;}
    visitados[posicion]=true;


    while(!ady.empty()){
      w=ady.front();
      ady.pop();
      if(!visitados[w]){
        VisitadosRecursivo(w,visitados,ruta,frecuencia);

      }
    }
    visitados[posicion]=false;
    if(insertado) ruta.pop();
  }

}

void Planta::MostrarRutaEscape()
{
  list<Posicion> pos;
  CalcularRuta ( pos );
  Registro::get_instancia()->Escribir("(ruta:");
  cout<<"\nRuta de escape de la planta:\n";
  int x= pos.size();
  for ( int i=0;i<x;i++ )
  {
    switch ( pos.front() ){
      case 0: cout<<"Norte ";Registro::get_instancia()->Escribir(" N");break;
      case 1: cout<<"Sur ";Registro::get_instancia()->Escribir(" S");break;
      case 2: cout<<"Oeste ";Registro::get_instancia()->Escribir(" O");break;
      case 3: cout<<"Este ";Registro::get_instancia()->Escribir(" E");break;
    }
    pos.pop_front();
  }
  cout<<"\n";
  Registro::get_instancia()->Escribir(")");
  if(kDepurarPlanta) cin.get();
}

/**
 * Devuelve la id de la planta
 * @return id de la planta
 */
int Planta::get_id() const
{
  return id_;
}

/**
 * Libera toda la memoria de la planta
 */
void Planta::Destruir()
{
  for(int i=0;i<celdas_.size();i++){
    for(int j=0;j<celdas_[i]->get_llaves()->size();j++) delete (*(celdas_[i]->get_llaves()))[j];
    if(celdas_[i]!=NULL) delete celdas_[i];  //una vez liberada la memoria el vector se destruye solo
  }
}

/**
 * Destructor de la clase Planta
 */
Planta::~ Planta()
{
  Destruir();
  delete puerta_;
  GenAleatorios::destruir();
}
