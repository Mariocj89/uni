/**
 * \file fichero.cpp
 * \brief Implementacion de la clase FicheroCarga
 * \date 09/04/09
 * \author
 *   \b Nombre: Mario \n
 *   \b Apellidos: Corchero Jimenez \n
 *   \b Asignatura Laboratorio de Programacion II \n
 */
#include "fichero.h"
#include "cargador.h"

/**
* Constructor de la clase FicheroCarga. Se encarga de abrir el fichero
* \param nombre Nombre del fichero que se va a abrir
* \return Objecto FicheroCarga que permite realizar operaciones sobre el fichero con nombre pasado por parametro
*/
FicheroCarga::FicheroCarga(string nombre){
  DEPURAR_FICHERO_MSG("Entra en FicheroCarga::FicheroCarga("<<nombre<<")");
  this->nombre_fichero_ = nombre;
  f_in_.open(nombre_fichero_.c_str());
  if (!f_in_.good()) {
     throw ios::failure("Error de Apertura");
  }
  DEPURAR_FICHERO_MSG("Sale de FicheroCarga::FicheroCarga("<<nombre<<")");
}


/**
* Procesa el fichero de configuracion para cargar el sistema
* No procesa las lineas que comienzan por --
*/
void FicheroCarga::ProcesarFichero()
{
  string vector_campos[kMaxCampos];
  char linea[300];
  int num_campos;
  DEPURAR_FICHERO_MSG("Entra en FicheroCarga::ProcesarFichero()");

  while (!f_in_.eof()) {
    if (f_in_.bad()) {
      throw ios::failure("Error de Acceso");
    }
    f_in_.getline(linea,300);
    if(!f_in_.eof()){
      if (f_in_.bad()) {
        throw ios::failure("Error de Acceso");
      }
      if (linea[0]!=' ' && linea[0]!='-' && linea[1]!='-') { //comprueba si la linea NO comienza por "--"(comentario)
        num_campos = this->TrocearLinea(linea,vector_campos);
        this->ProcesarDatos(num_campos, vector_campos);
      }
    }
  }
  f_in_.close();
  if (f_in_.bad()) {
    throw ios::failure("Error de Cierre");
  }
  DEPURAR_FICHERO_MSG("Sale de FicheroCarga::ProcesarFichero()");
}

/**
* Divide una cadena en los campos que la forman, token de separacion '#'
* \param linea cadena orgien a dividir
* \param vector_campos[] vector que contendra los valores de los campos
* \return Número de campos que contenia la cadena origen
*/
int FicheroCarga::TrocearLinea(string linea,string vector_campos[kMaxCampos])
{
  bool eol = false;
  int pos=0, posini=0, num_campos=0;

  DEPURAR_FICHERO_MSG("Entra en FicheroCarga::TrocearLinea ("<<linea<<")");

  while (!eol) {
    pos = linea.find("#",posini);
    if (pos == string::npos) {
      eol = true;
    }
    else {
      vector_campos[num_campos] = linea.substr(posini,pos);
      linea.erase(posini,pos+1);
      num_campos++;
    }
  }

  DEPURAR_FICHERO_MSG("Sale de FicheroCarga::TrocearLinea: "<<num_campos);

  return num_campos;
}

/**
* Metodo que muestra por pantalla todas los datos contenidos en un vector
 * @param num_campos numero de campos que tiene el vector que queremos mostrar
 * @param vector_campos[] vector que contiene toda la informacion de una linea
 */
void FicheroCarga::ProcesarDatos(int num_campos,string vector_campos[kMaxCampos]){
  DEPURAR_FICHERO_MSG("Entra en FicheroCarga::ProcesarDatos");
  Prision *prison=Prision::get_instancia();
  Cargador c(prison);
  c.crear(vector_campos[0],num_campos,vector_campos+1);
  DEPURAR_FICHERO_MSG("Sale de FicheroCarga::ProcesarDatos");
}


