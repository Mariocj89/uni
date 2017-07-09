/**
 * @brief   Fichero con la implementacion de Pusher
 * @Author  Mario Corchero
 * @Date    30/06/2012
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using System.Configuration;
using System.Net;
using PusherRESTDotNet;

namespace QuercusEventChain
{
    /// <summary>
    /// Clase para enviar eventos a clientes web
    /// </summary>
    public class Pusher : QESTail<QESEvent>, IToggleable, IParametrizale
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="Pusher"/> class.
        /// </summary>
        /// <param name="applicationKey">The application key.</param>
        /// <param name="applicaitonSecret">The applicaiton secret.</param>
        /// <param name="applicationId">The application id.</param>
        /// <param name="channelName">Name of the channel.</param>
        public Pusher(string applicationKey = "9a3fe2f64106d87e0291", string applicaitonSecret = "9814209c36d68d22417c", string applicationId = "21427", string channelName = "QESTest", ILogeable log = null)
        {
            Enabled = true;
            ApplicationKey = applicationKey;
            ApplicaitonSecret = applicaitonSecret;
            ApplicationId = applicationId;
            Channel = channelName;
            _log = log;
        }

        /// <summary>
        /// Referencia para añadir entradas al log
        /// </summary>
        private ILogeable _log;

        /// <summary>
        /// Obtiene o establece la key de pusher
        /// </summary>
        /// <value>
        /// The application key.
        /// </value>
        public string ApplicationKey { get; set; }
        /// <summary>
        /// Obtiene o establece la clave de pusher
        /// </summary>
        /// <value>
        /// The applicaiton secret.
        /// </value>
        public string ApplicaitonSecret { get; set; }
        /// <summary>
        /// Obtiene o establece la id de la aplicacion pusher
        /// </summary>
        /// <value>
        /// The application id.
        /// </value>
        public string ApplicationId { get; set; }
        /// <summary>
        /// Obtiene o establece el canal del pusher
        /// </summary>
        /// <value>
        /// The channel.
        /// </value>
        public string Channel { get; set; }

        /// <summary>
        /// Restores from data.
        /// </summary>
        /// <param name="parametro">The parametro.</param>
        public virtual void RestoreFromData(String[] parametro) 
        {
            switch (parametro[0])
            {
                case "Enabled": Enabled = Boolean.Parse(parametro[1]); break;
            }        
        }
        /// <summary>
        /// Gets the data to store.
        /// </summary>
        /// <returns></returns>
        public virtual String[][] GetDataToStore() { return new String[][] { new String[]{ "Enabled", Enabled.ToString() } }; }

        /// <summary>
        /// Utilizando pusher, envia un evento de notificacion de una camara
        /// </summary>
        /// <param name="camera">The camera.</param>
        /// <param name="message">The message.</param>
        /// <returns></returns>
        [HttpPost]
        public ActionResult EnviarCameraNotification(string camera, string message = null)
        {

            IPusherProvider provider =
              new PusherProvider(ApplicationId, ApplicationKey, ApplicaitonSecret);
            ObjectPusherRequest request =
              new ObjectPusherRequest(Channel,
                                      "alertaCamara",
                                      new
                                      {
                                          camara = camera,
                                          message = message
                                      });
            provider.Trigger(request);
            if (_log != null) _log.AddEntry("Alerta de camara enviada a Pusher para " + camera);

            return new HttpStatusCodeResult((int)HttpStatusCode.OK);
        }

        /// <summary>
        /// Realiza la gestion del evento
        /// </summary>
        /// <param name="args">evento.</param>
        public virtual void Manejar(QESEvent e)
        {
            if (!Enabled) return;
            QESAxisCameraEvent ev = e as QESAxisCameraEvent;
            if( ev != null)
                this.EnviarCameraNotification(ev.Dispositivo.Nombre, ev.Info);
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
