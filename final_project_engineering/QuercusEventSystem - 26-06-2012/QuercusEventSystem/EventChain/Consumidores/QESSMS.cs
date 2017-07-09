/**
 * @file QESSMS.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase QESSMS
 **/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QES.SendSMSWorld;


namespace QuercusEventChain
{

    /// <summary>
    /// Gestiona el envio de SMS
    /// Atencion:La ultima vez que se testeo, el servicio web, no funcionaba correctamente
    /// </summary>
    /// <typeparam name="T">tipo de eventos que recibe</typeparam>
    abstract class QESSMS<T> : QESTail<T>, IToggleable
    {
        /// <summary>
        /// cliente sms
        /// </summary>
        private SendSMSWorldSoap client;

        /// <summary>
        /// Si no esta a null, entidad encargada de recibir entradas para generar un log
        /// </summary>
        private ILogeable _log;


        /// <summary>
        /// Initializes a new instance of the <see cref="QESSMS&lt;T&gt;"/> class.
        /// </summary>
        public QESSMS(ILogeable log = null)
        {
            _log = log;
            client = new SendSMSWorldSoapClient();
        }

        /// <summary>
        /// Envia un sms con los datos proporcionados como parametros
        /// </summary>
        /// <param name="from">quien envia el mensaje(email).</param>
        /// <param name="code">codigo telefonico del pais.</param>
        /// <param name="number">numero de telefono.</param>
        /// <param name="message">cuerpo del mensaje.</param>
        public void SendSMS(string from, string code, string number, string message)
        {
            client.sendSMS(from, code, number, message);
            producirLog(number, message);
        }

        /// <summary>
        /// Añade una entrada al log
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="data">The data.</param>
        protected void producirLog(string number, string mensaje)
        {
            _log.AddEntry("Se ha enviado un SMS a ["+number+"]: "+mensaje);
        }

        abstract public void Manejar(T args);

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public abstract Boolean Enabled { get; set; }
    }
}
