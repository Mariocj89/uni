/**
* \file grafo.cpp
* \brief Implementacion de los metodos de la clase grafo
* \author
*   \b Nombre: Mario \n
*   \b Apellidos: Corchero Jimenez \n
*   \b Asignatura Laboratorio de Programacion II \n
*   \b Curso 08/09
*/

#include "grafo.h"

/**
* Metodo constructor por defecto de la clase grafo
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
Grafo::Grafo()  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::Grafo"<<endl);
  int x,y;
  num_nodos_=0;

  for (x=0;x<kMaxVert;x++)
    nodos_[x]= kNoValor;

  for (x=0;x<kMaxVert;x++)
    for (y=0;y<kMaxVert;y++){
      arcos_[x][y]=kInfinito;
      warshall_path_[x][y]=false;
      floyd_cost_[x][y]=kInfinito;
      floyd_path_[x][y]=kNoValor;
      }
  // Diagonales
  for (x=0;x<kMaxVert;x++){
    arcos_[x][x]=0;
    warshall_path_[x][x]=true;
    floyd_cost_[x][x]=0;
    //floyd_path_[x][x]=kNoValor;
    }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::Grafo"<<endl);
}

/**
* Metodo que comprueba si el grafo esta vacio
* \param "" No recibe parametros
* \return Retorna un valor booleano que indica si el grafo esta o no vacio
*/
bool Grafo::EsVacio(void) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::EsVacio()"<<endl);
  return bool (num_nodos_==0);
  DEPURAR_GRAFO_MSG ("Sale de Grafo::EsVacio()"<<endl);
}

/**
* Metodo que inserta un nuevo arco en el grafo
* \param origen es el nodo de origen del arco nuevo
* \param destino es el nodo de destino del arco nuevo
* \param valor es el peso del arco nuevo 
* \return true si se pudo insertar
*/
bool Grafo::set_arco(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino, const int &valor)  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::set_arco(TipoNodoGrafo origen, TipoNodoGrafo destino, int valor)"<<endl);
  bool resultado= false;
  if (((int)(origen) >= 0) && ((int)(origen) < num_nodos_) && 
     ((int)(destino) >= 0) && ((int)(destino) < num_nodos_))
    {
      arcos_[(int)(destino)][(int)(origen)]=valor;
      arcos_[(int)(origen)][(int)(destino)]=valor; // Cambiado
      resultado=true;
    }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::set_arco(TipoNodoGrafo origen, TipoNodoGrafo destino, int valor): "<<resultado<<endl);
  return resultado;
}

/**
* Metodo que borra un arco del grafo
* \param origen es el nodo de origen del arco nuevo
* \param destino es el nodo de destino del arco nuevo
* \return true si se pudo borrar
*/
bool Grafo::del_arco(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino)  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::del_arco(TipoNodoGrafo origen, TipoNodoGrafo destino)"<<endl);
  bool resultado= false;
  if ((get_pos_nodo(origen) >= 0) && (get_pos_nodo(origen) < num_nodos_) && 
     (get_pos_nodo(destino) >= 0) && (get_pos_nodo(destino) < num_nodos_)) // Cambiado
    {
        
       arcos_[get_pos_nodo(origen)][get_pos_nodo(destino)]=kInfinito;
       arcos_[get_pos_nodo(destino)][get_pos_nodo(origen)]=kInfinito;	// Cambiado
       resultado=true;
    }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::del_arco(TipoNodoGrafo origen, TipoNodoGrafo destino): "<<resultado<<endl);
  return resultado;
}

/**
* Metodo que comprueba si dos nodos son adyacentes
* \param origen es el primer nodo
* \param destino es el segundo nodo
* \return Retorna un valor booleano que indica si los dos nodos son adyacentes
*/
bool Grafo::Adyacente(const TipoNodoGrafo &origen, const TipoNodoGrafo &destino) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::Adyacente (TipoNodoGrafo origen, TipoNodoGrafo destino)"<<endl);
  bool resultado= false;

  if (((int)(origen) >= 0) && ((int)(origen) < num_nodos_) && 
     ((int)(destino) >= 0) && ((int)(destino) < num_nodos_)) // Cambiado
        resultado = (arcos_[(int)(origen)][(int)(destino)]!=kInfinito); // Cambiado

  DEPURAR_GRAFO_MSG ("Sale de Grafo::Adyacente (TipoNodoGrafo origen, TipoNodoGrafo destino): "<<resultado<<endl);
  return resultado;
}

/**
* Metodo que retorna el peso de un arco
* \param origen es el primer nodo del arco
* \param destino es el segundo nodo del arco
* \return Retorna un valor entero que contiene el peso del arco
*/
int Grafo::get_arco(const TipoNodoGrafo &origen,const  TipoNodoGrafo &destino) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::get_arco (TipoNodoGrafo origen, TipoNodoGrafo destino)"<<endl);

  int arco=kNoValor;

  if (((int)(origen) >= 0) && ((int)(origen) < num_nodos_) && 
     ((int)(destino) >= 0) && ((int)(destino) < num_nodos_)) 	// Cambiado
     arco=arcos_[(int)(origen)][(int)(destino)];				// Cambiado

  DEPURAR_GRAFO_MSG ("Sale de Grafo::get_arco (TipoNodoGrafo origen, TipoNodoGrafo destino): "<<arco<<endl);

  return arco;
}

/**
* Metodo que inserta un nuevo nodo en el grafo
* \param n es el nodo que se desea insertar
* \return true si se pudo insertar
*/
bool Grafo::set_nodo(const TipoNodoGrafo &n)  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::set_nodo(TipoNodoGrafo n)"<<endl);
  bool resultado=false;

  if (num_nodos_<kMaxVert){
    nodos_[num_nodos_]=n;
    num_nodos_++;
    resultado=true;
  }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::set_nodo(TipoNodoGrafo n): "<<resultado<<endl);

  return resultado;
}

/**
* Metodo que elimina un nodo del grafo
* \param nodo Nodo que se desea eliminar
* \return true si se pudo borrar
*/
bool Grafo::del_nodo(const TipoNodoGrafo &nodo)  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::del_nodo(TipoNodoGrafo pos)"<<endl);
  bool resultado=false;
	
  int pos = (int)(nodo); // Añadido para borrar el nodo correcto

  if ((num_nodos_>0) && (pos <= num_nodos_)){
    int x,y;

    // Borrar el nodo
    for (x=pos; x<num_nodos_-1; x++){		// Añadido el -1 porque si no se salía de límites array
      nodos_[x]=nodos_[x+1];
      cout << nodos_[x+1];
		}

      // Borrar en la Matriz de Adyacencia

      // Borra la fila
      for (x=pos; x<num_nodos_-1; x++)		// Añadido el -1 porque si no se salía de límites array
        for (y=0;y<num_nodos_; y++)
          arcos_[x][y]=arcos_[x+1][y];

      // Borra la columna
      for (x=0; x<num_nodos_; x++)
        for (y=pos;y<num_nodos_-1; y++)	// Añadido el -1 porque si no se salía de límites array
          arcos_[x][y]=arcos_[x][y+1];

      // Decrementa el numero de nodos
      num_nodos_--;
      resultado=true;
  }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::del_nodo(TipoNodoGrafo pos): "<<resultado<<endl);
  return resultado;
}


/**
* Metodo que muestra el vector de nodos del grafo
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
void Grafo::MostrarNodos(void) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::MostrarNodos()"<<endl);
  int x;

  cout << "NODOS:" << endl;
  for (x=0;x<num_nodos_;x++)
    cout << nodos_[x] << " ";
    cout << endl;
    DEPURAR_GRAFO_MSG ("Sale de Grafo::MostrarNodos()"<<endl);
}

/**
* Metodo que muestra los arcos del grafo (la matriz de adyacencia)
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
void Grafo::MostrarArcos(void) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::MostrarArcos()"<<endl);
  int x,y;

  cout << "ARCOS:" << endl;
  for (x=0;x<num_nodos_;x++){
    for (y=0;y<num_nodos_;y++){
      cout.width(3);
      if (arcos_[x][y]!=kInfinito)
        cout << arcos_[x][y] << " ";
      else
        cout << "#" <<" ";
    }
    cout << endl;
  }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::MostrarArcos()"<<endl);
}

/**
* Metodo que muestra la matriz de Warshall
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
void Grafo::MostrarPW(void) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::MostrarPW()"<<endl);
  int x,y;

  cout << "warshallC:" << endl;
  for (x=0;x<num_nodos_;x++){
    for (y=0;y<num_nodos_;y++)
      cout << warshall_path_[x][y] << " ";
      cout << endl;
  }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::MostrarPW()"<<endl);
}

/**
* Metodo que muestra las matrices de coste y camino de Floyd
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
void Grafo::MostrarFloydC(void) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::MostrarFloydC()"<<endl);
  int x,y;

  cout << "floydC:" << endl;

  for (y=0;y<num_nodos_;y++) {
    for (x=0;x<num_nodos_;x++){
      cout.width(3);
      cout << floyd_cost_[x][y] << " ";
      }
      cout << endl;
  }

  cout << "floydP:" << endl;
  for (x=0;x<num_nodos_;x++){
    for (y=0;y<num_nodos_;y++){
      cout.width(2);
      cout << floyd_path_[x][y] << " " ;
    }
    cout << endl;
  }
  DEPURAR_GRAFO_MSG ("Sale de Grafo::MostrarFloydC()"<<endl);
}

/**
* Metodo que realiza el algoritmo de Warshall sobre el grafo
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
void Grafo::Warshall(void)  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::Warshall()"<<endl);
	
  //Copìamos la matrid de adyacencia a warshal
  for (int i=0;i<kMaxVert;i++)
    for (int j=0;j<kMaxVert;j++)
      warshall_path_[i][j] = (arcos_[i][j]!=0);


  int aux;
  for (int k=0;k<kMaxVert;k++)
    for (int i=0;i<kMaxVert;i++)
      for (int j=0;j<kMaxVert;j++)
      if (!warshall_path_[i][j]) warshall_path_[i][j] = warshall_path_[i][k]&&warshall_path_[k][j];

  DEPURAR_GRAFO_MSG ("Sale de Grafo::Warshall()"<<endl);
}


/**
* Metodo que realiza el algoritmo de Floyd sobre el grafo
* \param "" No recibe parametros
* \return No retorna ningun valor
*/
void Grafo::Floyd(void)  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::Floyd()"<<endl);

  //Copìamos la matrid de adyacencia a floydC
  for (int i=0;i<kMaxVert;i++)
    for (int j=0;j<kMaxVert;j++)
      floyd_cost_[i][j] = arcos_[i][j];


  int aux;
  for (int k=0;k<kMaxVert;k++)
    for (int i=0;i<kMaxVert;i++)
      for (int j=0;j<kMaxVert;j++){
	aux = floyd_cost_[i][k]+floyd_cost_[k][j];
        if (aux<floyd_cost_[i][j]) {
          floyd_cost_[i][j] = aux;
          floyd_path_[i][j] = k;
        }
      }

  DEPURAR_GRAFO_MSG ("Sale de Grafo::Floyd()"<<endl);
}

/**
* Metodo que devuelve el siguiente nodo en la ruta entre un origen y un destino
* \param origen es el primer nodo
* \param destino es el segundo nodo
* \param origen es el primer nodo
* \param sig parametro de entrada salida que devuelve el siguiente nodo en la ruta entre origen y destino
* \return No retorna ningun valor
*/
void Grafo::Siguiente(const TipoNodoGrafo &origen, const TipoNodoGrafo destino, TipoNodoGrafo &sig) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::siguiente(TipoNodoGrafo origen, TipoNodoGrafo destino, TipoNodoGrafo &sig)"<<endl);

  sig = floyd_path_[origen][destino];
  if (sig==-1) sig=destino;
  else this->Siguiente(origen,sig,sig);

  DEPURAR_GRAFO_MSG ("Sale de Grafo::siguiente(TipoNodoGrafo origen, TipoNodoGrafo destino, TipoNodoGrafo &sig)"<<endl);
}



/**
* Metodo que devuelve el conjunto de nodos adyacentes al nodo actual
* \param origen es el nodo actual
* \param ady parametro de entrada salida que devuelve el conjunto de nodos adyacentes (en una cola)
* \return No retorna ningun valor
*/
void Grafo::Adyacentes(const TipoNodoGrafo &origen, TipoCjtoNodos &ady) const  {
  DEPURAR_GRAFO_MSG ("Entra en Grafo::adyacentes(TipoNodoGrafo origen, TipoCjtoNodos &ady)"<<endl); 

  //encontramos la posicion del nodo:
  int aux=-1;
  aux=get_pos_nodo(origen);

  if(aux != -1)
    for(int i=0;i<kMaxVert;i++) if(arcos_[aux][i] != kInfinito && i != aux) ady.push(nodos_[i]);

  DEPURAR_GRAFO_MSG ("Sale de Grafo::adyacentes(TipoNodoGrafo origen, TipoCjtoNodos &ady)"<<endl);  
}

/**
 * Funcion auxiliar que halla el máximo de dos enteros
 * @param a primer entero
 * @param b segundo entero
 * @return maximo de los 2, el segundo si son iguales
 */
int Maximo(const int &a, const int &b)  {
  DEPURAR_GRAFO_MSG ("Entra en Maximo"<<endl);
  if (a>b) return a;
  else return b;
  DEPURAR_GRAFO_MSG ("Sale de Maximo"<<endl);
}

/**
 * Funcion auxiliar que halla el mínimo de dos enteros
 * @param a primer entero
 * @param b segundo entero
 * @return minimo de los 2, el segundo si son iguales
 */
int Minimo(const int &a, const int &b)  {
  DEPURAR_GRAFO_MSG ("Entra en Minimo"<<endl);
  if (a<b) return a;
  else return b;
  DEPURAR_GRAFO_MSG ("Sale de Minimo"<<endl);
}

/**
 * Sobrecarga del operador <<, muestra la matrid de adyacencia
 * @param flujo flujo en el que se almacena toda la informacion
 * @param G grafo a mostrar
 * @return flujo con toda la informacion
 */
ostream& operator <<(ostream &flujo, const Grafo &G){
  DEPURAR_GRAFO_MSG ("Entra en sobrecarga de <<"<<endl);
  int x,y;

  flujo << "ARCOS:" << endl;
  for (x=0;x<G.num_nodos_;x++){
    for (y=0;y<G.num_nodos_;y++){
      flujo.width(3);
      if (G.arcos_[x][y]!=kInfinito)
        flujo << G.arcos_[x][y] << " ";
      else
        flujo << "#" <<" ";
    }
    flujo << endl;
  }
  DEPURAR_GRAFO_MSG ("Sale de sobrecarga de <<"<<endl);
}

/**
 * @PRE debe existir algun nodo
 * Funcion que devuelve el elemento con mayor grado de entrada y salida(es no dirigido)
 * @param grado grado del elemento con mayor grado
 * @return elemento con mayor grado
 */
TipoNodoGrafo Grafo::MayorGrado(int &grado) const 
{
  DEPURAR_GRAFO_MSG ("Entra en MayorGradoSalida(int &grado)"<<endl);
  grado=0;
  int grado2; //Variable donde guardar el grado de el ultimo nodo
  int mayor=-1; //Guardamos la posicion del nodo con mayor grado de los visitados
  for (int i=0;i<num_nodos_;i++)  {
    grado2=0;
    for (int j=0;j<num_nodos_;j++) 
      if (arcos_[i][j] != kInfinito && i != j) grado2++; //hallamos el grado del actual
    if (grado<=grado2) { //si el ultimo nodo tiene mayor grado que el mayor de los anteriores, sustituimos
      grado=grado2;
      mayor=i;
    }
  }
  return nodos_[mayor];
  DEPURAR_GRAFO_MSG ("Sale de MayorGradoSalida(int &grado)"<<endl);
}


/**
 * Funcion que halla los 2 elementos mas distantes entre si en cuanto a caminos minimos,
 * los devuelve por parametro
 * @param a uno de los 2 elementos mas distantes entre si
 * @param b uno de los 2 elementos mas distantes entre si
 * @return entero con la distancia entre los 2 nodos
 */
int Grafo::MasDistantes(TipoNodoGrafo & a, TipoNodoGrafo & b) const 
{
  int max=0; //variable auxiliar que mantendra el valor del mayor camino encontrado
  DEPURAR_GRAFO_MSG ("Entra en MasDistantes(TipoNodoGrafo & a, TipoNodoGrafo & b)"<<endl);
  for (int i=0;i<num_nodos_;i++)
    for (int j=i+1;j<num_nodos_;j++) //Comprueba solo la triangular superior (grafo no dirigido)
      if(floyd_cost_[i][j]>max) {
        max=floyd_cost_[i][j];
	a=nodos_[i];
	b=nodos_[j];
      }
  return max;
  DEPURAR_GRAFO_MSG ("Sale de MasDistantes(TipoNodoGrafo & a, TipoNodoGrafo & b)"<<endl);
}

/**
 * Funcion que halla los 2 elementos menos distantes entre si, los devuelve por parametro
 * @param a uno de los 2 elementos menoss distantes entre si
 * @param b uno de los 2 elementos menoss distantes entre si
 * @return entero con la distancia entre los 2 nodos
 */
int Grafo::MasCorto( TipoNodoGrafo & a, TipoNodoGrafo & b) const 
{
  int min=kInfinito; //variable auxiliar que mantendra el valor del mayor camino encontrado
  DEPURAR_GRAFO_MSG ("Entra en MasCorto(TipoNodoGrafo & a, TipoNodoGrafo & b)"<<endl);
  for (int i=0;i<num_nodos_;i++)
    for (int j=i+1;j<num_nodos_;j++) //Comprueba solo la triangular superior (grafo no dirigido)
      if(floyd_cost_[i][j]<min) {
        min=arcos_[i][j];//Podemos usar la matrid de ayacencia, pues el menor coste siempre se conseguira en los adyacentes
	a=nodos_[i];
	b=nodos_[j];
      }
  return min;
  DEPURAR_GRAFO_MSG ("Sale de MasCorto(TipoNodoGrafo & a, TipoNodoGrafo & b)"<<endl);
}

/**
 * Devuelve por parametro la matriz de caminos calculada por el algoritmo de warshall
 * @param WP matriz booleana de caminos
 */
void Grafo::get_warshall_path(TipoMatrizBooleana & WP) const 
{
  for (int i=0;i<kMaxVert;i++)
    for(int j=i;j<kMaxVert;j++)
      WP[i][j]=WP[j][i]=warshall_path_[i][j];
}

/**
 * Devuelve por parametro la matriz de caminos calculada por el algoritmo de floyd
 * @param FP matriz de caminos
 */
void Grafo::get_floyd_path(TipoMatrizAdyacencia & FP) const 
{
  for (int i=0;i<kMaxVert;i++)
    for(int j=i;j<kMaxVert;j++)
      FP[i][j]=FP[j][i]=floyd_path_[i][j];
}

/**
 * Devuelve por parametro la matriz de costes hallada por el algoritmo de floyd
 * @param FC matriz de costes
 */
void Grafo::get_floyd_cost(TipoMatrizAdyacencia & FC) const 
{
  for (int i=0;i<kMaxVert;i++)
    for(int j=i;j<kMaxVert;j++)
      FC[i][j]=FC[j][i]=floyd_cost_[i][j];
}

/**
 * Metodo que muestra el recorrido en profundidad del grafo
 */
void Grafo::MostrarEnProfundidad(void ) const 
{
  bool visitados[kMaxVert]; //aqui almacenaremos si un elemento a sido visitado
  TipoCjtoNodos nodos_a_tratar;
  for (int i=0;i<this->num_nodos_;i++) visitados[i]=false;//inicializamos el vector de visitados
  for (int i=0;i<this->num_nodos_;i++) 
    if(!visitados[i])
      this->ObtenerEnProf(i,visitados, nodos_a_tratar);
  while(!nodos_a_tratar.empty()) {
    cout<<nodos_a_tratar.front();
    nodos_a_tratar.pop();
  }
}

/**
 * Devuelve por parametro todos los nodos en el orden obtenido por el recorrido en profundidad, para despues tratarlos en otro metodo
 * @param posicion posicion en el vector "nodos" del cual se va a partir
 * @param visitados[] nodos visitados previamente
 * @param prof conjunto con todos los elementos en el orden indicado por el recorrido en profundidad
 */
void Grafo::ObtenerEnProf(const int &posicion, bool visitados[kMaxVert], TipoCjtoNodos &prof) const 
{
  TipoCjtoNodos ady;
  TipoNodoGrafo w;
  int aux=-1; //lo usaremos para trabajar con la posicion del nodo en el vector "nodos_" en lugar de con el nodo en si
  this->Adyacentes(this->nodos_[posicion],ady);

//   cout<<endl<<"Adyacentes de :"<<posicion<<endl;
//   while(!ady.empty()){
//     cout<<ady.front()<<" - ";
//     ady.pop();
//   }

  visitados[posicion]=true;
  prof.push(this->nodos_[posicion]);
  while(!ady.empty()){
    w=ady.front();
    ady.pop();
    aux=get_pos_nodo(w);
    if(!visitados[aux]) {
      this->ObtenerEnProf(aux,visitados,prof);
      //Procesamiento del arco.
    }
  }
}

/**
 * Metodo que muestra el recorrido en anchura del grafo
 */
void Grafo::MostrarEnAnchura(void ) const 
{
  bool visitados[kMaxVert]; //aqui almacenaremos si un elemento a sido visitado
  TipoCjtoNodos nodos_a_tratar;
  for (int i=0;i<this->num_nodos_;i++) visitados[i]=false;//inicializamos el vector de visitados
  for (int i=0;i<this->num_nodos_;i++) 
    if(!visitados[i])
      this->ObtenerEnAnch(i,visitados, nodos_a_tratar);
  while(!nodos_a_tratar.empty()) {
    cout<<nodos_a_tratar.front();
    nodos_a_tratar.pop();
  }
}

/**
 * Devuelve por parametro todos los nodos en el orden obtenido por el recorrido en anchura, para despues tratarlos en otro metodo
 * @param posicion posicion en el vector "nodos" del cual se va a partir
 * @param visitados[] nodos visitados previamente
 * @param anch conjunto con todos los elementos en el orden inidicado por el recorrido en anchura
 */
void Grafo::ObtenerEnAnch(const int & posicion, bool visitados[kMaxVert], TipoCjtoNodos & anch) const 
{
  TipoNodoGrafo v;
  TipoCjtoNodos ady;
  TipoNodoGrafo w;
  int pos;
  queue <TipoNodoGrafo> C;
  visitados[posicion] = true;
  C.push(nodos_[posicion]);
  while(!C.empty()) {
    v = C.front();
    C.pop();
    anch.push(v);
    this->Adyacentes(v,ady);
    while(!ady.empty()) {
      w = ady.front();
      ady.pop();
      pos=this->get_pos_nodo(w);
      if(!visitados[pos]) {
        visitados[pos]=true;
        C.push(w);
      }
    }
  }
}
 
/**
 * Obtiene   todos   los   nodos   que   se encuentran a n saltos de un nodo dado.
 * @param nodo Nodo desde el que empezar
 * @param nodos nodos encontrados
 * @param distancia distancia dada
 */
void Grafo::ANSaltos(const TipoNodoGrafo &nodo, TipoCjtoNodos & nodos, const int & distancia) const 
{
  TipoCjtoNodos ady;
  bool escogido[kMaxVert];
  for(int i=0;i<kMaxVert;i++) escogido[i]=false;
  nodos.push(nodo);
  int aux=distancia;
  while(aux>0) {
    while(!nodos.empty()){
      ady.push(nodos.front());
      nodos.pop();
    }
    for(int i=0;i<kMaxVert;i++) escogido[i]=false;
    while(!ady.empty()) {
        for(int i=0;i<kMaxVert;i++) 
          if(arcos_[this->get_pos_nodo(ady.front())][i] != kInfinito && i != this->get_pos_nodo(ady.front()) && !escogido[i]){
            nodos.push(nodos_[i]);
            escogido[i]=true;
          }
        ady.pop();
    }
    aux--;
  }
}

/**
 * Metodo que nos devuelve la posicion de un nodo
 * @param N nodo que buscamos
 * @return la posicion del nodo, -1 quiere decir que no se encuentra
 */
int Grafo::get_pos_nodo(const TipoNodoGrafo & N) const 
{
  for(int i=0;i<this->num_nodos_;i++) if(nodos_[i] == N) return i;
  return -1;
}

/**
 * @PRE debe haberse calculado la matriz de costes de floyd
 * Metodo que calcula la excentricidad de un nodo, (el maximo de las distancias minimas a todos los nodos)
 * @param nodo nodo del que se quiere calcular la excentricidad
 * @return entero con la excentricidad del nodo
 */
int Grafo::Excentricidad(const TipoNodoGrafo & nodo) const 
{
  int aux=-1;
  for(int i=0;i<this->num_nodos_;i++)
    aux=Maximo(aux, this->floyd_cost_[this->get_pos_nodo(nodo)][i]);
  return aux;
}

/**
 * Calcula el centro del grafo, es decir, el nodo que tiene menor excentricidad
 * @return nodo considerado centro del grafo
 */
TipoNodoGrafo Grafo::Centro() const 
{
  TipoNodoGrafo N;
  int aux=kInfinito;
  for(int i=0;i<this->num_nodos_;i++) 
    if(this->Excentricidad(nodos_[i])<aux) {
      N=nodos_[i];
      aux=Excentricidad(nodos_[i]);
    }
  return N;
}

/**
 * Nodo que comprueba si existe un ciclo a partir de un nodo dado
 * @param nodo nodo de partida
 * @return true si existe un cilo, false en caso contrario
 */
bool Grafo::ExisteCiclo(const TipoNodoGrafo & nodo) const 
{
  bool visitados[kMaxVert], resultado=false, salir=false;
  TipoNodoGrafo vengo_de[kMaxVert];//nodos desde los que llegamos(es decir, la posicion N contendra: el nodo desde el que llegamos a nodos_[N] por primera vez)
  for(int i=0;i<kMaxVert;i++) vengo_de[i]=-1;
  for(int i=0;i<kMaxVert;i++) visitados[i]=false;
  visitados[get_pos_nodo(nodo)]=true;
//   vengo_de[get_pos_nodo(nodo)]=get_pos_nodo(nodo);
  TipoCjtoNodos ady, nodos;
  nodos.push(nodo);

  TipoNodoGrafo N;

  //A continuacion, vamos ampliando el espacio de busqueda, y en cada espacio, comprobamos si podemos llegar a un nodo de dos maneras diferentes,
  // en el momento que se llege a un nodo de 2 formas, tenemos un ciclo, saliendo de todos los bucles y devolviendo true.
  // usamos la variable "nodos" como el siguiente espacio de busqueda y "ady" como el espacio de busqueda actual.
  while(!salir) {
    while(!nodos.empty()){//el siguiente espacio de busqueda pasa a ser el actual y el siguiente queda vacio.
      ady.push(nodos.front());
      nodos.pop();
    }
    while(!ady.empty()&&!resultado) { //tratamos el actual espacio de busqueda
      N=ady.front();
      for(int i=0;i<num_nodos_;i++)   { //comprobamos los adyacentes de el primero nodo del espacio de busqueda actual(ady)
        if(arcos_[this->get_pos_nodo(ady.front())][i] != kInfinito && i != this->get_pos_nodo(ady.front()) && vengo_de[ady.front()]!=i ){//Hemos encontrado un nodo adyacente(no valido del que venimos):
          if(visitados[i]) { //El nodo a sido visitado previamente:
            resultado = (vengo_de[i]!=get_pos_nodo(ady.front())); //si hemos llegado al nodo por una ruta diferente, HAY UN CICLO!
          }
          else { //El nodo no ha sido visitado previamente
            nodos.push(nodos_[i]);//lo almacenamos el el siguiente espacio de busqueda
            vengo_de[i]=get_pos_nodo(ady.front());//indicamos el nodo desde el cual hemos llegado a este
            visitados[i]=true;
          }
        }
      }
      ady.pop();//al terminar de tratar este nodo, lo sacamos del actual espacio de busqueda.
      salir = resultado||nodos.empty();//si no tenemos mas nodos que procesar, o hemos encontrado un ciclo, salimos
    }
  }
  return resultado;
}
