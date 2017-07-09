/**
 * @brief   Fichero con la implementacion de la clase QESBody, parte de la libreria de Eventos de Quercus
 * @Author  Mario Corchero
 * @Date    07/05/2011
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuercusEventChain
{
    /// <summary>
    /// Clase que consume eventos del sistema y genera otro de tipo diferente, siendo una
    /// especie de "pieza" intermedia. Ej: Clase que al recibir dos eventos difrentes emita otro.  
    /// Es una clase generica, el primer tipo corresponde al que consume y el segundo al que genera.
    /// </summary>
    /// <typeparam name="Q"></typeparam>
    /// <typeparam name="T"></typeparam>
    public abstract class QESBody<Q,T> : QESHead<T>, QESTail<Q>
    {
        abstract public void Manejar(Q args);
    }

    /// <summary>
    /// Esta implementacion recibe y genera los eventos del mismo tipo.
    /// Ej: Clase que al recibir dos eventos difrentes emita otro.    
    /// Es una clase generica, el primer tipo corresponde al que consume y el segundo al que genera.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public abstract class QESBody<T> : QESHead<T>, QESTail<T>
    {
        /// <summary>
        /// metodo con el que se trata el evento lanzado por la case a la que esta suscrito, no hace mas
        /// que volver a lanzarlo.
        /// </summary>
        /// <param name="args">argumento del evento a pasar.</param>
        public virtual void Manejar(T args)
        {
            lanzar(args);
        }
    }
}
