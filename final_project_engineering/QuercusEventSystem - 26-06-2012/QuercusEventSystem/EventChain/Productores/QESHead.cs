/**
 * @brief   Fichero con la implementacion de la clase QESHead, parte de la libreria de Eventos de Quercus
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
    /// Clase que genera un evento interno del systema, ya sea transformando uno del exterior o generandolo
    /// por cualquier situacion. Ej: Receptor de mensajes por TCP
    /// Para lanzar el evento de forma asincrona se debe llamar a "lanzar"
    /// Es una clase generica, el tipo indicado corresponde al tipo de evento que generará en el sistema.
    /// </summary>
    /// <typeparam name="T">tipo del evento lanzado</typeparam>
    abstract public class QESHead<T> : QESBase
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QESHead&lt;T&gt;"/> class.
        /// </summary>
        public QESHead() { Enabled = true; }

        /// <summary>
        /// definicion del tipo de delegado QESDelegado, usado para crear el evento mas adelante. Especifica que argumentos
        /// deben tener los metodos que se asocien al evento, en este caso, un solo argumento del tipo generico indicado.
        /// </summary>
        /// <param name="info">informacion del evento.</param>
        public delegate void QESDelegado(T info);

        /// <summary>
        /// Evento al que se asociaran metodos para que sean ejecutados al lanzanrse.
        /// </summary>
        event QESDelegado QESEvent;

        /// <summary>
        /// Conecta una clase a esta, suscribiendo su metodo Manejar a el evento de esta.
        /// </summary>
        /// <param name="cola">clase a suscribir al evento.</param>
        public void Conectar(QESTail<T> cola)
        {
            QESEvent += cola.Manejar;
        }

        /// <summary>
        /// Desconecta una clase de esta, desasociando su metodo Manejar a el evento de esta.
        /// </summary>
        /// <param name="cola">clase a desasociar del evento.</param>
        public void Desconectar(QESTail<T> cola)
        {
            QESEvent -= cola.Manejar;
        }

        /// <summary>
        /// lanza de forma asincrona todos los metodos asociados al evento, enviando el argumento indicado.
        /// antes de lanzar el evento comprueba que se cumple el metodo condicion. Es posible sobreescribirlo
        /// aunque no se recomienda.
        /// </summary>
        /// <param name="args">Argumento del tipo generico que se enviara a los metodos asociados al evento.</param>
        virtual protected void lanzar(T args)
        {
            //QESEvent(args); //llamada sincrona
            if (Enabled && condicion(args))
            {
                foreach (QESDelegado qd in QESEvent.GetInvocationList())
                {
                    //System.Windows.Threading.Dispatcher.CurrentDispatcher.BeginInvoke(QESEvent, System.Windows.Threading.DispatcherPriority.Send,args);
                    qd.BeginInvoke(args, null, null);
                }
            }
            
        }

        /// <summary>
        /// metodo encargado de "decidir" si es correcto que se lance un evento determinado, puede sobreescribirse para 
        /// decidir como se comporta lanzar frente a un parametro determinado
        /// </summary>
        /// <param name="args">Argumento segun el cual realizar la decision. Si no se sobreescribe lanzar sera el que se envie con el evento..</param>
        /// <returns>true si y solo si la condicion de lanzado es correcta</returns>
        virtual protected bool condicion(Object args)
        {
            return true;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public Boolean Enabled { get; set; }
    }
}
