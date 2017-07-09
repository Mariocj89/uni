/**
 * @brief   Fichero con la implementacion de QESMailSender
 * @Author  Mario Corchero
 * @Date    25/05/2011
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Net.Mail;
using System.Timers;
using System.Net;

namespace QuercusEventChain
{


    /// <summary>
    /// Estructura para el control temporal de un MAIL
    /// </summary>
    public struct MAILTimer
    {
        /// <summary>
        /// Supervisa la temporizacion del mail
        /// </summary>
        public Stopwatch watch;

        /// <summary>
        /// Texto del mail
        /// </summary>
        public string txt;
    }


    /// <summary>
    /// Clase que envia emails a distintos destinatarios.(Esta clase deberia llamarse de forma asincrona)
    /// </summary>
    /// <typeparam name="T">tipo de evento que recibe</typeparam>
    abstract public class QESMailSender<T> : QESTail<T>, IParametrizale, IToggleable
    {

        /// <summary>
        /// Gets or sets the origen.
        /// </summary>
        /// <value>
        /// Texto origen del mail, debe ser una direccion de correo
        /// </value>
        public String Origen { get { return mensaje.From.ToString(); } set { mensaje.From = new MailAddress(value);} }


        /// <summary>
        /// usuario de correo
        /// </summary>
        private String _user;
        /// <summary>
        /// Gets or sets the usuario.
        /// </summary>
        /// <value>
        /// Usuario de la cuenta de correo
        /// </value>
        public String Usuario { get { return _user; } set { _user = value; cliente.Credentials = new NetworkCredential(value, _pass); } }


        /// <summary>
        /// contraseña del correo
        /// </summary>
        private String _pass;
        /// <summary>
        /// Gets or sets the password.
        /// </summary>
        /// <value>
        /// contraseña del correo
        /// </value>
        public String Password { get { return _pass; } set { _pass = value; cliente.Credentials = new NetworkCredential(_user, value); } }


        /// <summary>
        /// Gets or sets the host.
        /// </summary>
        /// <value>
        /// Direccion del Servidor de correo
        /// </value>
        public String Host { get { return cliente.Host; } set { cliente.Host = value; } }


        /// <summary>
        /// Gets or sets the puerto.
        /// </summary>
        /// <value>
        /// Puerto del servidor de correo
        /// </value>
        public int Puerto { get { return cliente.Port; } set { cliente.Port = value; } }


        /// <summary>
        /// Gets or sets the step.
        /// </summary>
        /// <value>
        /// Tiempo entre mails
        /// </value>
        public int Step { get { return MIN_MINUTES; } set { MIN_MINUTES = value; } }


        /// <summary>
        /// cliente de mensajeria encargado del envio de mensajes
        /// </summary>
        private SmtpClient cliente = new SmtpClient();//Deberia de permitir mas servidores? O crear 1 cuenta especifica para esto.


        /// <summary>
        /// mensaje a enviar, contiene el destinatario, asunto, cuerpo...
        /// </summary>
        private MailMessage mensaje = new MailMessage();


        /// <summary>
        /// minutos que deben pasar hasta que se envie el proximo mail(con el mismo contenido).
        /// </summary>
        private int MIN_MINUTES = 1;

        /// <summary>
        /// Lista de temporizadores activos
        /// </summary>
        List<MAILTimer> timers = new List<MAILTimer>();

        /// <summary>
        /// Reloj de evento de actualizacion de temporizadores
        /// </summary>
        System.Timers.Timer clock = new System.Timers.Timer();

        /// <summary>
        /// Si no esta a null, entidad encargada de recibir entradas para generar un log
        /// </summary>
        private ILogeable _log;


        /// <summary>
        /// Propiedad para el acceso a los destinatarios
        /// </summary>
        public MailAddressCollection Destinatarios
        {
            get
            {
                return mensaje.To;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESMailSender&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="origen">Al receptor le aparecera esta cadena como origen del mensaje..</param>
        /// <param name="usuario">usuario del servidor de correo.</param>
        /// <param name="pass">pass del servidor de correo.</param>
        /// <param name="host">direccion del servidor de correo.</param>
        /// <param name="puerto">puerto del servidor de correo.</param>
        /// <param name="step">tiempo entre envio de mails.</param>
        public QESMailSender(String origen, String usuario, String pass, String host = "smtp.gmail.com", int puerto = 587, int step = 0,ILogeable log = null)
        {
            // Inicializacion de intervalos de temporizacion.
            clock.Interval = 100000;
            clock.Start();
            clock.Elapsed += new ElapsedEventHandler(clockElapsed);
            clock.Enabled = true;

            cliente.Host = host;
            cliente.Port = puerto;
            mensaje.From = new MailAddress(origen);

            MIN_MINUTES = step;

            cliente.Credentials = new NetworkCredential(_user = usuario, _pass = pass);
            cliente.EnableSsl = true;

            _log = log;
            Enabled = true;
        }

        /// <summary>
        /// rellena el mensaje y lo envia
        /// </summary>
        /// <param name="asunto">asunto del mensaje.</param>
        /// <param name="cuerpo">cuerpo del mensaje.</param>
        /// <param name="archivo">ruta del fichero a enviar. En caso de ser null no se incluye fichero.</param>
        public void SendMail(String asunto, String cuerpo, String archivo = null)
        {
            int i = 0;
            bool found = false;

            // Control de temporizacion
            while ((i < timers.Count) && (!found))
            {
                if (timers[i].txt == cuerpo)
                    found = true;
                else
                    i++;
            }
            if (found)
            {
                timers[i].watch.Stop();
                long ms = timers[i].watch.ElapsedMilliseconds;
                if (ms >= (MIN_MINUTES * 60000))
                {
                    timers.RemoveAt(i);
                    found = false;
                }
                else
                    timers[i].watch.Start();
            }

            //si habia un temporizador corriendo, salimos y no eviamos mail
            if (found) return;

            // Agregamos el temporizador a la lista
            MAILTimer t = new MAILTimer();
            t.txt = cuerpo;
            t.watch = new Stopwatch();
            t.watch.Start();
            timers.Add(t);
            //fin codigo relativo a temporizacion

            mensaje.Subject = asunto;
            mensaje.Body = cuerpo;
            if (archivo != null) mensaje.Attachments.Add(new Attachment(archivo));
            if (Destinatarios.Count == 0) return;
            lock (cliente) //Nos aseguramos de que no se envia desde el mismo servidor dos correos al mismo tiempo.
            {
                cliente.Send(mensaje);
            }
            producirLog(Destinatarios.ToString(), asunto);
        }

        /// <summary>
        /// Evento de contador de reloj finalizado
        /// </summary>
        /// <param name="sender">Objeto que produce el evento.</param>
        /// <param name="e">The <see cref="System.Timers.ElapsedEventArgs"/> instance containing the event data.</param>
        private void clockElapsed(object sender, ElapsedEventArgs e)
        {
            List<MAILTimer> _timers = new List<MAILTimer>();
            clock.Enabled = false;
            for (int i = 0; i < timers.Count; i++)
            {
                if (timers[i].watch.ElapsedMilliseconds < (MIN_MINUTES * 60000))
                    _timers.Add(timers[i]);
                else
                    timers[i].watch.Stop();
            }
            timers = _timers;
            clock.Enabled = true;
        }

        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        public virtual String[][] GetDataToStore()
        {
            String[][] paramToStore = new String[Destinatarios.Count + 2][];
            paramToStore[0] = new String[] { "Enabled", Enabled.ToString() };
            paramToStore[1] = new String[] { "Steps", Step.ToString() };
            int i = 2;
            foreach (object o in Destinatarios)
            { paramToStore[i] = new String[] { "Destinatario", o.ToString() }; i++; }
            return paramToStore;
        }

        /// <summary>
        /// Pone el valor a un atributo por parametro.
        /// </summary>
        /// <param name="parametros">El parametro.</param>
        public virtual void RestoreFromData(String[] parametro)
        {
            switch (parametro[0])
            {
                case "Destinatario": Destinatarios.Add(parametro[1]); break;
                case "Enabled": Enabled = Boolean.Parse(parametro[1]); break;
                case "Steps": Step = Int32.Parse(parametro[1]); break;
            }

        }

        /// <summary>
        /// Metodo a sobrescribir para Manejar el evento recibido y mandar un mail
        /// </summary>
        /// <param name="args">evento.</param>
        abstract public void Manejar(T args);

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        abstract public Boolean Enabled { get; set; }

        /// <summary>
        /// Añade una entrada al log
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="data">The data.</param>
        protected void producirLog(String destinatario, String asunto)
        {
            _log.AddEntry("Enviado un mail a [" + destinatario + "] con asunto: " + asunto);
        }
    }


    /// <summary>
    /// Clase que envia emails a distintos destinatarios.(Esta clase deberia llamarse de forma asincrona)
    /// </summary>
    public class QESMailSender : QESMailSender<QESEvent>, IToggleable
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QESMailSender"/> class.
        /// </summary>
        /// <param name="origen">Al receptor le aparecera esta cadena como origen del mensaje..</param>
        /// <param name="usuario">usuario del servidor de correo.</param>
        /// <param name="pass">pass del servidor de correo.</param>
        /// <param name="host">direccion del servidor de correo.</param>
        /// <param name="puerto">puerto del servidor de correo.</param>
        /// <param name="step">tiempo entre envio de mails.</param>
        public QESMailSender(String origen, String usuario, String pass, String host = "smtp.gmail.com", int puerto = 587, int step = 0,ILogeable log =null)
            : base(origen, usuario, pass,host,puerto,step,log)
        { }

        /// <summary>
        /// metodo para el trato de un evento, envia un correo
        /// </summary>
        /// <param name="args">argumentos del evento manejado.</param>
        override public void Manejar(QESEvent args)
        {
            if(!Enabled) return;

                if (args is QESAxisCameraEvent.QESCrossLineEvent)
                {
                    args = new QESMailEvent("Cruze de linea en " + (args as QESAxisCameraEvent).Dispositivo.Nombre + "\r\nFecha: "+DateTime.Now.ToLongDateString(), "Cross line Event", null);
                }
                else if (args is QESAxisCameraEvent.QESMotionDetectedEvent)
                {
                    args = new QESMailEvent("Deteccion de movimiento en " + (args as QESAxisCameraEvent).Dispositivo.Nombre + "\r\nFecha: " + DateTime.Now.ToLongDateString(), "Deteccion de Movimiento", null);
                }
                else if (args is QESCameraEvent)
                {
                    args = new QESMailEvent("Evento producido en la camara " + (args as QESAxisCameraEvent).Dispositivo.Nombre + "\r\nFecha: " + DateTime.Now.ToLongDateString(), "Evento en Camara", null);
                }
                else if (args is QESDispositivoEvent)
                {
                    args = new QESMailEvent("Evento producido en el dispositivo " + (args as QESAxisCameraEvent).Dispositivo.Nombre + "\r\nFecha: " + DateTime.Now.ToLongDateString(), "Evento en Dispositivo", null);
                }
                else if (args is QESTcpEvent)
                {
                    args = new QESMailEvent("Evento tcp recibido desde " + (args as QESTcpEvent).Emisor.ToString() + "\r\nFecha: " + DateTime.Now.ToLongDateString(), "Evento TCP", null);
                }
            

            if (args is QESMailEvent)
            {
                QESMailEvent args2 = args as QESMailEvent;
                base.SendMail(args2.Asunto, args2.Info, args2.Adjunto);
            }
            else
            {
                base.SendMail("Quercus Event System", args.Info);
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public override Boolean Enabled { get; set; }

    }


}
