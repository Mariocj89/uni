/**
 * @file QESEssendexSMS.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase QESEsendexSMS
 **/
using System.Collections.Generic;
using System.Timers;
using System.Diagnostics;
using System.Collections;
using System.Data;
using System;
using QES.EsendexSendService;

namespace QuercusEventChain
{

    /// <summary>
    /// Estructura para el control temporal de un SMS
    /// </summary>
    public struct SMSTimer
    {

        /// <summary>
        /// Supervisa la temporizacion del SMS
        /// </summary>
        public Stopwatch watch;

        /// <summary>
        /// Texto del SMS
        /// </summary>
        public string sms;
    }

    /// <summary>
    /// Gestiona el envio de SMS a traves de una cuenta Essendex
    /// </summary>
    /// <typeparam name="T">Evento que trata</typeparam>
    abstract public class QESEsendexSMS<T> : QESTail<T>, IParametrizale, IToggleable
    {

        /// <summary>
        /// lista de destinatarios
        /// </summary>
        private ArrayList _recipients = new ArrayList();

        /// <summary>
        /// Propiedad para el acceso a los destinatarios
        /// </summary>
        public ArrayList Recipients
        {
            get { return _recipients; }
        }

        /// <summary>
        /// Obtiene el usuario de la cuenta essendex
        /// </summary>
        public String Account
        {
            get
            {
                return _smsaccount;
            }
        }

        /// <summary>
        /// Obtiene el intervalo en minutos entre el envio de sms
        /// </summary>
        public int Step
        {
            set
            {
                MIN_SMS_MINUTES = value;
            }
            get
            {
                return MIN_SMS_MINUTES;
            }
        }

        /// <summary>
        /// Tiempo minimo que debe transcurrir entre un SMS y otro
        /// </summary>
        private int MIN_SMS_MINUTES;

        /// <summary>
        /// Nombre de la cuenta de envio de SMS
        /// </summary>
        private string _smsaccount;

        /// <summary>
        /// Login de la cuenta de envio de SMS
        /// </summary>
        private string _smslogin;

        /// <summary>
        /// Password de la cuenta de envio de SMS
        /// </summary>
        private string _smspassword;

        /// <summary>
        /// Lista de temporizadores activos
        /// </summary>
        List<SMSTimer> timers = new List<SMSTimer>();

        /// <summary>
        /// Reloj de evento de actualizacion de temporizadores
        /// </summary>
        System.Timers.Timer _clock = new System.Timers.Timer();

        /// <summary>
        /// Servicio para el envio de SMS
        /// </summary>
        SendServiceSoapClient _sendsms;

        /// <summary>
        /// Si no esta a null, entidad encargada de recibir entradas para generar un log
        /// </summary>
        private ILogeable _log;

        /// <summary>
        /// Establece lo parametros para la cabecera de envio de SMS
        /// </summary>
        /// <returns>Cabecera del mensaje</returns>
        private MessengerHeader PopulateServiceHeader()
        {
            MessengerHeader header = new MessengerHeader();
            header.Account = _smsaccount;
            header.Username = _smslogin;
            header.Password = _smspassword;

            return header;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESEsendexSMS&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="account">ID de la cuenta de acceso a esendex.</param>
        /// <param name="login">nombre de la cuenta de acceso a esendex.</param>
        /// <param name="password">contraseña de la cuenta.</param>
        /// <param name="step">tiempo en minutos entre envio de sms.</param>
        public QESEsendexSMS(string account, string login, string password, int step = 1,ILogeable log = null)
        {
            // Inicializacion de intervalos de temporizacion.
            _clock.Interval = 100000;
            _clock.Start();
            _clock.Elapsed += new ElapsedEventHandler(clockElapsed);
            _clock.Enabled = true;
            _sendsms = new SendServiceSoapClient();

            _smsaccount = account;
            _smslogin = login;
            _smspassword = password;
            MIN_SMS_MINUTES = step;
            Enabled = true;

            _log = log;
        }

        /// <summary>
        /// Evento de contador de reloj finalizado
        /// </summary>
        /// <param name="sender">sender Objeto que produce el evento.</param>
        /// <param name="e">The <see cref="System.Timers.ElapsedEventArgs"/> instance containing the event data.</param>
        private void clockElapsed(object sender, ElapsedEventArgs e)
        {
            List<SMSTimer> _timers = new List<SMSTimer>();
            _clock.Enabled = false;
            for (int i = 0; i < timers.Count; i++)
            {
                if (timers[i].watch.ElapsedMilliseconds < (MIN_SMS_MINUTES * 60000))
                    _timers.Add(timers[i]);
                else
                    timers[i].watch.Stop();
            }
            timers = _timers;
            _clock.Enabled = true;
        }

        /// <summary>
        /// Envia un mensaje de texto a cada uno de los telefonos con acceso a la camara
        /// </summary>
        /// <param name="sms">Mensaje que se desea enviar.</param>
        public void sendSMS(string sms)
        {
            int i = 0;
            bool found = false;

            // Control de temporizacion
            while ((i < timers.Count) && (!found))
            {
                if (timers[i].sms == sms)
                    found = true;
                else
                    i++;
            }
            if (found)
            {
                timers[i].watch.Stop();
                long ms = timers[i].watch.ElapsedMilliseconds;
                if (ms >= (MIN_SMS_MINUTES * 60000))
                {
                    timers.RemoveAt(i);
                    found = false;
                }
                else
                    timers[i].watch.Start();
            }

            // Si se cumplen las reestricciones de tiempo
            if (!found)
            {
                // Si hay destinatarios
                if (_recipients.Count > 0)
                {
                    // Envio del mensaje
                    lock (_sendsms)
                    {
                        if (_recipients.Count == 1)
                            _sendsms.SendMessage(PopulateServiceHeader(),_recipients[0].ToString(), sms.ToString(), MessageType.Text);
                        else
                            _sendsms.SendMessageMultipleRecipients(PopulateServiceHeader(),(string[])_recipients.ToArray(typeof(string)), sms.ToString(), MessageType.Text);
                    }
                }

                // Agregamos el temporizador a la lista
                SMSTimer t = new SMSTimer();
                t.sms = sms;
                t.watch = new Stopwatch();
                t.watch.Start();
                timers.Add(t);
                producirLog(this.Recipients.ToString(), sms);
            }
        }

        /// <summary>
        /// Añade una entrada al log
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="data">The data.</param>
        protected void producirLog(string number, string mensaje)
        {
            _log.AddEntry("Se ha enviado un SMS a [" + number + "]: " + mensaje);
        }

        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        public virtual String[][] GetDataToStore()
        {
            String[][] paramToStore = new String[Recipients.Count+2][];
            paramToStore[0] = new String[]{"Enabled",Enabled.ToString()};
            paramToStore[1] = new String[] { "Steps", Step.ToString() };
            int i = 2;
            foreach (object o in Recipients)
            { paramToStore[i] = new String[] { "Recipient", o.ToString() }; i++; }
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
                case "Recipient": Recipients.Add(parametro[1]); break;
                case "Enabled": Enabled = Boolean.Parse(parametro[1]); break;
                case "Steps": MIN_SMS_MINUTES = Int32.Parse(parametro[1]); break;
            }

        }

        /// <summary>
        /// Metodo a sobrescribir para manejar el evento recibido
        /// </summary>
        /// <param name="args">The args.</param>
        abstract public void Manejar(T args);

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        abstract public Boolean Enabled { get; set; }
    }

    /// <summary>
    /// Gestiona el envio de SMS
    /// </summary>
    public class QESEsendexSMS : QESEsendexSMS<QESEvent>, IToggleable
    {

        /// <summary>
        /// Initializes a new instance of the <see cref="QESEsendexSMS"/> class.
        /// </summary>
        /// <param name="account">ID de la cuenta de acceso a esendex.</param>
        /// <param name="login">nombre de la cuenta de acceso a esendex.</param>
        /// <param name="password">contraseña de la cuenta.</param>
        /// <param name="step">tiempo en minutos entre envio de sms.</param>
        public QESEsendexSMS(string account, string login, string password, int step = 1, ILogeable log = null)
            : base(account, login, password, step,log)
        { }

        /// <summary>
        /// implementacion del comportamiento de la clase al recibir un evento
        /// </summary>
        /// <param name="args">parametros del evento.</param>
        override public void Manejar(QESEvent args)
        {
            if (!Enabled) return;
            try
            {
                sendSMS(args.Info);
            }
            catch (Exception) { }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        override public Boolean Enabled { get; set; }
    }
}