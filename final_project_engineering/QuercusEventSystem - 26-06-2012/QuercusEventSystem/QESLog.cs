/**
 * @file QESLog.cs
 * @author Mario Corchero Jimenez
 * @date 05/11/2011
 * @brief Implementacion de la clase QESLog
 **/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace QES
{
    /// <summary>
    /// Clase para la gestion del log
    /// </summary>
    public class QESLog : QuercusEventChain.ILogeable
    {
        /// <summary>
        /// Interfaz que muestra el log
        /// </summary>
        public UILog Interfaz;

        /// <summary>
        /// Par de valores con la fecha y la info
        /// </summary>
        public class ParLog :IComparable
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="ParLog"/> class.
            /// </summary>
            /// <param name="date">tiempo.</param>
            /// <param name="content">contenido.</param>
            public ParLog(TimeSpan time, String content)
            {
                _Time = new TimeSpan(time.Hours, time.Minutes, time.Seconds);
                Content = content;
            }

            /// <summary>
            /// Obtiene o modifica la hora
            /// </summary>
            /// <value>
            /// hora de entrada de la entrada de log.
            /// </value>
            private TimeSpan _Time { get; set; }

            /// <summary>
            /// Obtiene el tiempo de la fecha. formato largo
            /// </summary>
            public String Time { get { return _Time.ToString(); } }

            /// <summary>
            /// Obtiene o modifica el contenido
            /// </summary>
            /// <value>
            /// Cotenido de la entrada
            /// </value>
            public String Content { get; set; }


            /// <summary>
            /// Compara el objeto con otro
            /// </summary>
            /// <param name="o">Objeto a comparar.</param>
            /// <returns></returns>
            public int CompareTo(Object o)
            {
                if (o == null || !(o is ParLog)) return 1;
                var y = o as ParLog;
                return _Time.CompareTo(y._Time);
            }

            public class CompareByDate : IComparer<ParLog>
            {
                public int Compare(ParLog x, ParLog y)
                {
                    return x._Time.CompareTo(y._Time);
                }
            }



            /// <summary>
            /// Returns a <see cref="System.String"/> that represents this instance.
            /// </summary>
            /// <returns>
            /// A <see cref="System.String"/> that represents this instance.
            /// </returns>
            override public String ToString()
            {
                return Time.ToString() + " -> " + Content;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESLog"/> class.
        /// </summary>
        public QESLog()
        {

        }


        /// <summary>
        /// Diccionario con dia/conjunto de entradas
        /// </summary>
        private SortedDictionary<DateTime, ObservableCollection<ParLog>> _entradas = new SortedDictionary<DateTime, ObservableCollection<ParLog>>();
        /// <summary>
        /// Gets the entradas.
        /// </summary>
        public SortedDictionary<DateTime, ObservableCollection<ParLog>> Entradas { get { return _entradas; } }

        /// <summary>
        /// Añade una entrada al log con fecha ahora
        /// </summary>
        /// <param name="content">contenido de la entrada a añadir.</param>
        public void AddEntry(String content)
        {
            lock (_entradas)//Exclusion mutua
            {
                if (!_entradas.ContainsKey(DateTime.Today))
                {
                    _entradas[DateTime.Today] = new ObservableCollection<ParLog>();
                    if (Interfaz != null) App.Current.Dispatcher.Invoke((Action)(() => Interfaz.AddDay(DateTime.Today)));
                }
            }
            //indicamos al dispatcher que debe realizar la sigueinte accion
            Action act = () =>
            {
                _entradas[DateTime.Today].Insert(0,new ParLog(DateTime.Now.TimeOfDay, content));
            };
            App.Current.Dispatcher.Invoke(act);
        }
    }
}
