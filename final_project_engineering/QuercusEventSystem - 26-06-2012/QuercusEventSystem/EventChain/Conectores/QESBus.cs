/**
 * @brief   Fichero con la implementacion de varios tipos de bus, uno diferenciador por tipo
 *          otro por una condicion especifica
 * @Author  Mario Corchero
 * @Date    20/05/2011
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

namespace QuercusEventChain
{

    /// <summary>
    /// Clase que coge un evento y segun el tipo que sea lo envia por una salida(evento) u otra
    /// al añadir conectar un evento de salida debe indicarse el tipo de este.
    /// </summary>
    /// <typeparam name="Q">tipo de evento del bus</typeparam>
    public class QESTypeBus<Q>:QESTail<Q>
    {

        /**
         * @class   QESAutohead<R>
         * @brief   Clase interna head, de la que se compondra el bus
         */
        class QESAutoHead<R>:QESHead<R>
        {
            new public void lanzar(R args)
            {
                base.lanzar(args);
            }
        }

        /// <summary>
        /// diccionario con las "heads" productoras de eventos asociadas a los tipos
        /// </summary>
        private Dictionary<Type, Object> _heads = new Dictionary<Type, Object>();

        /// <summary>
        /// agrega un tipo de evento a los que se permitirá producir a este bus si no existe
        /// </summary>
        /// <typeparam name="T">tipo de evento que se agrega</typeparam>
        private void agregarEvento<T>()
        {
            if (!_heads.ContainsKey(typeof(T))) _heads.Add(typeof(T), new QESAutoHead<T>());
        }

        /// <summary>
        /// conecta un evento con su tipo asociado en el bus
        /// </summary>
        /// <typeparam name="T">tipo de evento que se conecta</typeparam>
        /// <param name="cola">cola instacia a conectar</param>
        public void Conectar<T>(QESTail<T> cola)
        {
            if (!_heads.ContainsKey(typeof(T))) agregarEvento<T>();
            ((QESAutoHead<T>)_heads[typeof(T)]).Conectar(cola);
        }

        /// <summary>
        /// lanza un evento del tipo al que corresponda args
        /// </summary>
        /// <typeparam name="T">tipo del parametro del evento que se lanza</typeparam>
        /// <param name="args">argumento del evento lanzado.</param>
        virtual public void lanzar<T>(T args)
        {
            if (condicion(args)&&_heads.ContainsKey(args.GetType())) ((QESAutoHead<T>)_heads[args.GetType()]).lanzar(args);
        }

        /// <summary>
        /// condicion de lanzado
        /// </summary>
        /// <param name="args">parametro de la condicion.</param>
        /// <returns></returns>
        virtual protected bool condicion(Object args)
        {
            return true;
        }

        /// <summary>
        /// reaccion al lanzamiento de un evento
        /// </summary>
        /// <param name="e">Evento a Manejar.</param>
        public virtual void Manejar(Q e)
        {
            foreach(Type t in _heads.Keys)
                if (t == e.GetType()) 
                {
                    //lanzar(e); break; 
                    MethodInfo castMethod = this.GetType().GetMethod("lanzar").MakeGenericMethod(t);
                    object castedObject = castMethod.Invoke(this, new object[] { e });
                    break;
                }
        }

    }

    /// <summary>
    /// Clase, a la que llega un evento y salen tantos como condiciones indicadas se cumplan
    /// Una especie de "difusor" con condicion
    /// </summary>
    /// <typeparam name="T">tipo de evento de entrada y salida(debe coincidir con las conexiones)</typeparam>
    public class QESConditionBus<T>: QESTail<T>
    {
        /// <summary>
        /// Tipo de delegado que devuelve un boolean dado un evento
        /// Es el tipo de metodo que se le pasara a la clase para checkear una salida
        /// </summary>
        /// <param name="ev">evento a evaluar.</param>
        /// <returns>true si se cumple, false en caso contrario</returns>
        public delegate bool DelegadoCondicion(T ev);

        private Dictionary<DelegadoCondicion, QESTail<T>> _salidas = new Dictionary<DelegadoCondicion, QESTail<T>>();

        /// <summary>
        /// Añade una salida con una condicion asociada
        /// </summary>
        /// <param name="cond">Condicion para que el evento pase a la salida.</param>
        /// <param name="salida">Salida que recibira el evento en caso de que se cumpla la condicion.</param>
        public void Conectar(DelegadoCondicion cond, QESTail<T> salida)
        {
            _salidas.Add(cond, salida);
        }

        /// <summary>
        /// Maneja el evento recibido. Lanzando el evento en todas las salidas que cumplan
        /// su condicion asociada.
        /// </summary>
        /// <param name="ev">evento recibido.</param>
        public virtual void Manejar(T ev)
        {
            foreach (var cond in _salidas.Keys)
            {
                if (cond(ev)) { _salidas[cond].Manejar(ev); }
            }
        }

    }
}
