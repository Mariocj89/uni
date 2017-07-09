/**
 * @brief   Fichero con la implementacion de las clases que producen eventos a partir de timers
 * @Author  Mario Corchero
 * @Date    11/02/2012
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;

namespace QuercusEventChain
{
    /// <summary>
    /// Clase a heredar para implementar como se lanzaran los eventos ante la activacion de temoprizadores
    /// </summary>
    /// <typeparam name="T">tipo de eventos que emite</typeparam>
    public class QESTimer<T> : QESHead<T>
    {
        /// <summary>
        /// Firma de metodo que se ejecutará al finalizar el temporizador
        /// </summary>
        /// <returns>Evento a lanzar, null si no se debe lanzar</returns>
        public delegate T TimerAction();

        /// <summary>
        /// Tipo para definir cada cuanto se debe repetir el temporizador
        /// </summary>
        public enum REPEAT { UNASIGNED, NO, DIARIO, SEMANAL, MENSUAL };

        /// <summary>
        /// Temporizadores que contiene la clase
        /// </summary>
        protected List<Timer> _timers = new List<Timer>();

        /// <summary>
        /// Variable para añadir entradas al log
        /// </summary>
        private ILogeable _log;

        /// <summary>
        /// Initializes a new instance of the <see cref="QESTimer&lt;T&gt;"/> class.
        /// </summary>
        public QESTimer(ILogeable log = null)
        {
            _log = log;
        }

        /// <summary>
        /// Add an acction asociated to a specific date
        /// </summary>
        /// <param name="datetime">The date.</param>
        /// <param name="accion">The accion.</param>
        /// <param name="repetir">The repetir.</param>
        public void AddEvent(DateTime datetime, TimerAction accion, REPEAT repetir = REPEAT.NO)
        {
            var timer = new Timer();
            //Intervalo igual a la fecha deseada menos la actual
            timer.Interval = datetime.Subtract(DateTime.Now).TotalMilliseconds;

            if(repetir == REPEAT.UNASIGNED) throw new ArgumentException();
            //Para que se ejecute de nuevo
            if (repetir != REPEAT.NO)
            {
                ElapsedEventHandler restartEvent = delegate
                {
                    switch (repetir)
                    {
                        case REPEAT.DIARIO: timer.Interval = 86400000; break;
                        case REPEAT.SEMANAL: timer.Interval = 604800000; break;
                        case REPEAT.MENSUAL: timer.Interval = DateTime.Now.Subtract(DateTime.Now.AddMonths(1)).TotalMilliseconds; break;
                    }
                    timer.Start();
                };
                timer.Elapsed += restartEvent;
            }

            timer.Elapsed += delegate
            {
                var evento = accion.Invoke();
                if (evento != null)
                    base.lanzar(evento);
                if(_log != null) _log.AddEntry("Disparado evento de temporizador");
            };

            _timers.Add(timer);
            timer.AutoReset = false;
            timer.Start();

        }

    }


    /// <summary>
    /// Al cumplirse una fecha, se envía un evento de grabación, cámara + duración en campo info.
    /// </summary>
    public class QESAxisRecordingTimer : QESTimer<QESEvent>, IParametrizale
    {

        /// <summary>
        /// Clase que representa una entrada para un evento
        /// </summary>
        public class EventEntry
        {
            /// <summary>
            /// Gets or sets the camera.
            /// </summary>
            /// <value>
            /// Camara d ela que grabar
            /// </value>
            public String Camera { get; set; }

            /// <summary>
            /// Gets or sets from.
            /// </summary>
            /// <value>
            /// Inicio de la grabacion
            /// </value>
            public DateTime From { get; set; }

            /// <summary>
            /// Gets or sets to.
            /// </summary>
            /// <value>
            /// Fin de la grabacion
            /// </value>
            public DateTime To { get; set; }

            /// <summary>
            /// Gets or sets the repetir.
            /// </summary>
            /// <value>
            /// Indica si hay que repetir el evento
            /// </value>
            public REPEAT Repetir { get; set; }

            /// <summary>
            /// Gets or sets the temporizador.
            /// </summary>
            /// <value>
            /// Timer del evento
            /// </value>
            public Timer Temporizador { get; set; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESAxisRecordingTimer"/> class.
        /// </summary>
        /// <param name="log">The log.</param>
        public QESAxisRecordingTimer(ILogeable log = null) : base(log) { }

        /// <summary>
        /// Obtiene la lista de eventos
        /// </summary>
        /// <value>
        /// Lista de los eventos salvados
        /// </value>
        public List<EventEntry> Eventos { get { return _eventos; } }

        /// <summary>
        /// Lista de los eventos salvados
        /// </summary>
        private List<EventEntry> _eventos = new List<EventEntry>();


        /// <summary>
        /// Añade un temporizador para una grabacion
        /// </summary>
        /// <param name="Camera">The camera.</param>
        /// <param name="from">fecha y hora de inicio.</param>
        /// <param name="to">fecha y hora de fin.</param>
        /// <param name="repetir">Modo de repeticion. Por defecto NO</param>
        /// <param name="onStartup">true = esta iniciando la aplicacion</param>
        public void AddEvent(String Camera, DateTime from, DateTime to, REPEAT repetir = REPEAT.NO, bool onStartup = false)
        {
            if (to < from) throw new ArgumentException();
            if (from < DateTime.Now) throw new ArgumentException();
            QESTimer<QESEvent>.TimerAction accion = delegate()
            {
                var query = from d in QES.QESGestor.Instancia.Dispositivos where d.Value is QES.CamaraAxis && d.Key == Camera
                            select d.Value as QES.CamaraAxis;
                if(query.Count() < 1) return null;
                return new QESAxisCameraEvent(to.Subtract(from.Subtract(new TimeSpan(0,0,1))).TotalSeconds.ToString(),query.First());
            };
            lock (base._timers)
            {
                base.AddEvent(from, accion, repetir);
                if(!onStartup) Eventos.Add(new EventEntry {Camera = Camera, From = from, To = to, Repetir = repetir, Temporizador = _timers.Last() });
            }
        }

        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        public virtual String[][] GetDataToStore()
        {
            String[][] paramToStore = new String[Eventos.Count*4][];
            int i = 0;//indice de la camara
            int j = 0;
            foreach (EventEntry e in Eventos)
            {
                paramToStore[j++] = new String[] { "Camera-"+ i, e.Camera };
                paramToStore[j++] = new String[] { "From-" + i, e.From.ToString() };
                paramToStore[j++] = new String[] { "To-" + i, e.To.ToString() };
                paramToStore[j++] = new String[] { "Repetir-" + i, e.Repetir.ToString() };
                i++; 
            }
            return paramToStore;
        }

        /// <summary>
        /// Pone el valor a un atributo por parametro.
        /// </summary>
        /// <param name="parametros">El parametro.</param>
        public virtual void RestoreFromData(String[] parametro)
        {
            int separadorPosition = parametro[0].LastIndexOf('-');

            string name = parametro[0].Substring(0, separadorPosition);
            int number = Int32.Parse(parametro[0].Substring(separadorPosition+1, parametro[0].Length - separadorPosition-1));
            while (Eventos.Count <= number) Eventos.Add(new EventEntry());
            switch (name)
            {
                case "Camera": Eventos[number].Camera = parametro[1]; break;
                case "From": Eventos[number].From = DateTime.Parse(parametro[1]); break;
                case "To": Eventos[number].To = DateTime.Parse(parametro[1]); break;
                case "Repetir": Eventos[number].Repetir = (REPEAT)Enum.Parse(typeof(REPEAT), parametro[1]);break;
            }

            if (Eventos[number].Camera != null && Eventos[number].From != null && Eventos[number].Repetir != REPEAT.UNASIGNED && Eventos[number].To != null)
            {
                switch (Eventos[number].Repetir)
                {
                    case REPEAT.DIARIO: 
                        while (Eventos[number].From < DateTime.Now) Eventos[number].From = Eventos[number].From.AddDays(1); 
                        while (Eventos[number].To < DateTime.Now) Eventos[number].To = Eventos[number].To.AddDays(1);
                        break;
                    case REPEAT.SEMANAL:
                        while (Eventos[number].From < DateTime.Now) Eventos[number].From = Eventos[number].From.AddDays(7);
                        while (Eventos[number].To < DateTime.Now) Eventos[number].To = Eventos[number].To.AddDays(7);
                        break;
                    case REPEAT.MENSUAL:
                        while (Eventos[number].From < DateTime.Now) Eventos[number].From = Eventos[number].From.AddMonths(1);
                        while (Eventos[number].To < DateTime.Now) Eventos[number].To = Eventos[number].To.AddMonths(1);
                        break;
                    case REPEAT.NO:
                    default: break;
                }
                
                this.AddEvent(Eventos[number].Camera, Eventos[number].From, Eventos[number].To, Eventos[number].Repetir, true);
            }

        }

    }
}
