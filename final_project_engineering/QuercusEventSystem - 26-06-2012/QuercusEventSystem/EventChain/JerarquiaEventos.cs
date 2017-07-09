/**
 * @brief   Fichero con la implementacion de la jerarquia de eventos de QES
 * @Author  Mario Corchero
 * @Date    20/05/2011
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QES;
using System.Net;

namespace QuercusEventChain
{

    /// <summary>
    /// Evento basico del sistema, solo contiene un campo de informacion
    /// </summary>
    public class QESEvent
    {

        /// <summary>
        /// Initializes a new instance of the <see cref="QESEvent"/> class.
        /// </summary>
        /// <param name="info">info informacion del evento</param>
        public QESEvent(String info) { Info = info; }


        /// <summary>
        /// Initializes a new instance of the <see cref="QESEvent"/> class.
        /// </summary>
        public QESEvent() { }


        /// <summary>
        /// Gets or sets the information of the event.
        /// </summary>
        /// <value>
        /// informacion básica del evento
        /// </value>
        public String Info { get; set; }
    }

    /// <summary>
    /// Evento producido al llegar un mensaje TCP
    /// </summary>
    public class QESTcpEvent : QESEvent
    {
        /// <summary>
        /// Obtiene o modifica el emisor del mensaje
        /// </summary>
        /// <value>
        /// EndPoint que envio el mensaje
        /// </value>
        public System.Net.EndPoint Emisor { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESTcpEvent"/> class.
        /// </summary>
        /// <param name="info">Mensaje.</param>
        /// <param name="emisor">El emisor del mensaje.</param>
        public QESTcpEvent(String info, System.Net.EndPoint emisor) : base(info)
        { Emisor = emisor; }
    }


    /// <summary>
    /// evento para el envio de un mail.
    /// </summary>
    public class QESMailEvent : QESEvent
    {

        /// <summary>
        /// Gets or sets asunto.
        /// </summary>
        /// <value>
        /// propiedad que identifica el asunto del mensaje.
        /// </value>
        public String Asunto { get; set; }


        /// <summary>
        /// Gets or sets adjunto.
        /// </summary>
        /// <value>
        /// fichero adjunto al email
        /// </value>
        public String Adjunto { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESMailEvent"/> class.
        /// </summary>
        /// <param name="_asunto">asunto.</param>
        /// <param name="_adjunto">fichero adjunto.</param>
        public QESMailEvent(String cuerpo, String _asunto, String _adjunto) : base(cuerpo)
        {
            Asunto = _asunto;
            Adjunto = _adjunto;
        }
    }

    /// <summary>
    /// Evento lanzado por un dispositivo
    /// </summary>
    public class QESDispositivoEvent: QESEvent
    {
        /// <summary>
        /// Gets or sets the dispositivo.
        /// </summary>
        /// <value>
        /// Dispositivo relacionado con el evento
        /// </value>
        public QES.QESDispositivo Dispositivo { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESDispositivoEvent"/> class.
        /// </summary>
        /// <param name="info">The info.</param>
        /// <param name="dispositivo">The dispositivo.</param>
        public QESDispositivoEvent(String info, QES.QESDispositivo dispositivo) :base (info)
        {
            Dispositivo = dispositivo;
        }
    }

    /// <summary>
    /// Evento lanzado por una camara
    /// </summary>
    public class QESCameraEvent : QESDispositivoEvent
    {
        /// <summary>
        /// Gets or sets the dispositivo.
        /// </summary>
        /// <value>
        /// Camara relacionado con el evento
        /// </value>
        new public QESCamara Dispositivo { get { return base.Dispositivo as QESCamara; } set { base.Dispositivo = value; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESCameraEvent"/> class.
        /// </summary>
        /// <param name="info">The info.</param>
        /// <param name="camara">The camara.</param>
        public QESCameraEvent(String info, QESCamara camara) : base(info, camara) { }
    }

    /// <summary>
    /// Evento lanzado por una camara axis (tambien usado para solicitar una grabacion)
    /// </summary>
    public class QESAxisCameraEvent : QESCameraEvent
    {
        /// <summary>
        /// Gets or sets the dispositivo.
        /// </summary>
        /// <value>
        /// Camara axis relacionado con el evento
        /// </value>
        new public CamaraAxis Dispositivo { get { return base.Dispositivo as CamaraAxis; } set { base.Dispositivo = value; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESAxisCameraEvent"/> class.
        /// </summary>
        /// <param name="info">The info.</param>
        /// <param name="camara">The camara.</param>
        public QESAxisCameraEvent(String info, CamaraAxis camara) : base(info, camara) { }

        /// <summary>
        /// Evento de deteccion de movimiento en una camara axis
        /// </summary>
        public class QESMotionDetectedEvent: QESAxisCameraEvent
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="QESMotionDetectedEvent"/> class.
            /// </summary>
            /// <param name="info">The info.</param>
            /// <param name="camara">The camara.</param>
            public QESMotionDetectedEvent(String info, CamaraAxis camara) : base(info, camara) { }
        }

        /// <summary>
        /// Evento de cross line en una camara axis
        /// </summary>
        public class QESCrossLineEvent : QESAxisCameraEvent
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="QESCrossLineEvent"/> class.
            /// </summary>
            /// <param name="info">The info.</param>
            /// <param name="camara">The camara.</param>
            public QESCrossLineEvent(String info, CamaraAxis camara) : base(info, camara) { }
        }
    }

    /// <summary>
    /// Clase para añadir un metodo a QESTCPEvent 
    /// </summary>
    static class EventsExtensionMethods
    {
        /// <summary>
        /// Metodo para pasar un evento Tcp a un evento de camara axis
        /// </summary>
        /// <param name="ev">The ev.</param>
        /// <returns></returns>
        [Obsolete("No se recomienda clasificar un evento a partir de su origen, aunque es mas seguro puede producir errores.")]
        public static QESAxisCameraEvent AsAxisCameraEvent(this QESTcpEvent ev)
        {
            IPAddress ip = ((IPEndPoint)ev.Emisor).Address;
            int port = ((IPEndPoint)ev.Emisor).Port;
            //obtenemos las camaras que tienen ip y puerto = al que emitio el evento (solo deberia haber 1)
            var cams = from d in QESGestor.Instancia.Dispositivos.Values
                       where (d is CamaraAxis && ((CamaraAxis)d).IP.Equals(ip))
                       select d;
            if (cams.Count() == 0) return null;
            return new QESAxisCameraEvent(ev.Info, cams.First() as CamaraAxis);
        }

        /// <summary>
        /// With the information on the info field morphs the event to the proper device event
        /// </summary>
        /// <param name="ev">The event.</param>
        /// <returns>Proper device event</returns>
        public static QESDispositivoEvent AsDispositivoEvent(this QESEvent ev)
        {
            var info = ev.Info.Split(':');
            info = info.Where<String>(i => i != "").ToArray();//elimiar vacios
            if (info.Count() > 1)
            {
                var dispositivo = QESGestor.Instancia.Dispositivos[info[1]];
                var extraInfo = info.Count() > 2 ? info[2] : "";
                switch (info[0])
                {
                    case "MDI": return new QESAxisCameraEvent.QESMotionDetectedEvent(extraInfo, dispositivo as CamaraAxis);
                    case "CL": return new QESAxisCameraEvent.QESMotionDetectedEvent(extraInfo, dispositivo as CamaraAxis);
                    case "ESM": case "EST": case "EI": return new QESDispositivoEvent(extraInfo, dispositivo);
                    default: return null;
                }
            }
            else return null;
        }
    }
}
