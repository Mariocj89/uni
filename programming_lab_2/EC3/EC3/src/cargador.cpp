/**
 * \file cargador.cpp
 * \brief Práctica 2007-2008. Implementación de la Clase Cargador 
 * \author
 *   \b Profesores LPII \n
 *   \b Asignatura Laboratorio de Programación II \n
 *   \b Curso 07/08 -- Revisado en Curso 08/09
 */

#include "cargador.h"
#include "errorplanta.h"
//Inicialización del mapeo
Cargador::DatoMapeo Cargador::mapeo[NUMELTOSCONF] ={
            //{Nombre, Número de Campos}
            {"PLANTA",8},
            {"PRESO",5},
            {"GUARDIA",5}
        };

/**
* Constructor de Cargador
* \param p Objeto sistema que se va a cargar
*/
Cargador::Cargador(Prision* p)
{
    DEPURAR_MSG("Entra en Cargador::Constructor parametrizado");
    prision=p;
    DEPURAR_MSG("Sale de Cargador::Constructor parametrizado");
}

/**
* Devuelve la posición que ocupa el elemento en el vector de mapeo
* \param elto nombre del elemento
* \return posición que ocupa el elemento en el vector de mapeo
*/
int Cargador::queElemento(string elto)
{
    int res=-1;
    bool enc=false;

    DEPURAR_MSG("Entra en Cargador::queElemento ("<<elto<<")");

    for (int i=0; i<NUMELTOSCONF && !enc; i++)
        if (strcmp(mapeo[i].nombre,elto.c_str())==0)
        {
            res=i;
            enc=true;
        }

    DEPURAR_MSG("Sale de Cargador::queElemento ("<<elto<<"): "<<res);
    return res;
}

/**
* Método que realiza comprobaciones de datos básicos (existe elemento, número campos correcto, existe localidad...)
* \param elto nombre del elemento a crear
* \param numCampos número de campos ocupados del vector vCampos
* \param vCampos[] valores de configuración del elemento a crear
* \return No devuelve nada
*/
void Cargador::crear(string elto, int numCampos, string vCampos[kMaxCampos])
{
    DEPURAR_MSG("Entra en Cargador::crear ("<<elto<<","<<numCampos<<")");
    //Si existe elemento y el número de campos es correcto, procesarlo... si no, error
    int numElto = queElemento(elto);

    //Comprobación de datos básicos correctos
    if (numElto!=-1 && mapeo[numElto].numCampos==numCampos)
    {
        //procesar
        switch(queElemento(elto))
        {
        case 0:	   
            crearPlanta(numCampos,vCampos);
            break;
        case 1:
             crearPreso(numCampos,vCampos);
            break;
        case 2:
            crearGuarda(numCampos,vCampos);
            break;
     	}
    }
    else
        cout<<"ERROR Cargador::crear: Datos de configuración incorrectos... "<<elto<<","<<numCampos<<endl;
    DEPURAR_MSG("Sale de Cargador::crear");
}

/**
* Método que crea una planta y la registra en la prisión
* \param numCampos número de campos ocupados del vector vCampos
* \param vCampos[] valores de configuración del elemento a crear
* \return No devuelve nada
*/
void Cargador::crearPlanta(int numCampos, string vCampos[kMaxCampos])
{
    DEPURAR_MSG("Entra en Cargador::crearPlanta("<<numCampos<<")");
    cout << "Creada planta: " << vCampos[0] << endl;
    try{
      prision->set_planta(new Planta(atoi(vCampos[0].c_str()),atoi(vCampos[1].c_str()),atoi(vCampos[2].c_str()),atoi(vCampos[3].c_str()),atoi(vCampos[4].c_str()), atoi(vCampos[5].c_str()), atoi(vCampos[6].c_str())));
    }
    catch(ErrorTamanio &exc){
      int anch, alt;
      cout<<exc.what(anch,alt)<<endl;
      prision->set_planta(new Planta(atoi(vCampos[0].c_str()),anch,alt,atoi(vCampos[3].c_str()),atoi(vCampos[4].c_str()), atoi(vCampos[5].c_str()), atoi(vCampos[6].c_str())));
    }
    catch(ErrorPuerta &exc){
      cout<<exc.what()<<endl;
      cout<<"Se procede a colocarlas de la siguiente manera:\n\tEntrada: Primera Celda.\n\tSalida: Ultima Celda.\n";
      prision->set_planta(new Planta(atoi(vCampos[0].c_str()),atoi(vCampos[1].c_str()),atoi(vCampos[2].c_str()),0,(atoi(vCampos[1].c_str())*atoi(vCampos[2].c_str())-1), atoi(vCampos[5].c_str()), atoi(vCampos[6].c_str())));
    }
    catch(ErrorPlanta &exc){
      int id;
      cout<<exc.what(id)<<endl;
      prision->set_planta(new Planta(id,atoi(vCampos[1].c_str()),atoi(vCampos[2].c_str()),atoi(vCampos[3].c_str()),atoi(vCampos[4].c_str()), atoi(vCampos[5].c_str()), atoi(vCampos[6].c_str())));
   }
    DEPURAR_MSG("Sale de Cargador::crearPlanta");
}

/**
* Método que crea un preso y lo registra en la prisión
* \param numCampos número de campos ocupados del vector vCampos
* \param vCampos[] valores de configuración del elemento a crear
* \return No devuelve nada
*/
void Cargador::crearPreso(int numCampos, string vCampos[kMaxCampos])
{
    DEPURAR_MSG("Entra en Cargador::crearPreso ("<<numCampos<<")");
    cout << "Creado Preso: " << vCampos[1] << endl;
    Posicion orientacion[4];
    for(int i = 0;i < 4;i++)
      switch(vCampos[2][i]){
        case 'N' : orientacion[i] = NORTE; break;
        case 'S' : orientacion[i] = SUR; break;
        case 'E' : orientacion[i] = ESTE; break;
        case 'O' : orientacion[i] = OESTE; break;
        default : throw string("Atencion, error en la ruta de un preso, revise el fichero inicio.txt");
      }
    Prision::get_instancia()->set_persona(Prision::get_instancia()->get_numero_plantas()-1,0,new Preso(vCampos[0],vCampos[1][0],atoi(vCampos[3].c_str()),orientacion,Prision::get_instancia()->get_numero_plantas()-1,0));
    Prision::get_instancia()->inc_numero_presos();
    DEPURAR_MSG("Sale de Cargador::crearPreso");
}

/**
* Método que crea un guarda y lo registra en la prisión
* \param numCampos número de campos ocupados del vector vCampos
* \param vCampos[] valores de configuración del elemento a crear
* \return No devuelve nada
*/
void Cargador::crearGuarda(int numCampos, string vCampos[kMaxCampos])
{
    DEPURAR_MSG("Entra en Cargador::crearGuarda ("<<numCampos<<")");
    cout << "Creado Guarda: " << vCampos[1] << endl;
    Prision *p= Prision::get_instancia(); 
    int n_planta = atoi(vCampos[2].c_str()), n_celda = p->get_alto_planta(n_planta)*p->get_ancho_planta(n_planta)-1;
    try{
      p->set_persona(n_planta,n_celda,new Guardia(vCampos[0],vCampos[1][0],atoi(vCampos[3].c_str()),n_planta,n_celda));
    }
    catch(ErrorPlanta &exc){
      cout<<exc.what(n_planta)<<endl;
      n_celda = p->get_alto_planta(n_planta)*p->get_ancho_planta(n_planta)-1;
      p->set_persona(n_planta,n_celda,new Guardia(vCampos[0],vCampos[1][0],atoi(vCampos[3].c_str()),n_planta,n_celda));
    }
    DEPURAR_MSG("Sale de Cargador::crearGuarda");
}

