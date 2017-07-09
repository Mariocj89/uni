/**
 * @file QESGestor.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de las clases para el control de dispositivos que cumplen el estandar VAPIX 2.0
 *        url del API: http://www.axis.com/techsup/cam_servers/dev/cam_http_api_2.php
 **/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace QuercusEventChain
{
    /// <summary>
    /// Clase para realizar grabaciones de camaras que cumplan el estandar VAPIX 2.0
    /// en respuesta a un evento. No funciona correctamente
    /// </summary>
    /// <typeparam name="T">Tipo de evetos que recibe</typeparam>
    [Obsolete("Use AxisController en lugar de esta clase, puede no funcionar correctamente.")]
    public class VAPIX2VideoRecorder<T> : QESTail<T>
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VAPIX2VideoRecorder&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="user">Usuario de la camara.</param>
        /// <param name="password">Password de la camara.</param>
        /// <param name="ip">Ip de la camara.</param>
        /// <param name="port">Puerto de la camara.</param>
        /// <param name="name">Nombre de la camara. Opcional</param>
        public VAPIX2VideoRecorder(String user, String password, String ip, int port = 80, String name = null)
        {
            _url = "http://" + ip + ":" + port + "/mpeg4/media.sdp";
            _credentials = new NetworkCredential(user, password);
            _name = name;
        }

        /// <summary>
        /// Captura una imagen de la camara y la guarda en un fichero con el nombre
        /// de la camara y la fecha actual
        /// </summary>
        public void Captura()
        {
            _request = (HttpWebRequest)WebRequest.Create(_url);

            _request.PreAuthenticate = true;
            _request.Credentials = _credentials;

            HttpWebResponse response = (HttpWebResponse)_request.GetResponse();
            System.IO.Stream stream = response.GetResponseStream();
            byte[] inBuf = new byte[100000];
            int bytesToRead = (int)inBuf.Length;
            int bytesRead = 0;
            while (bytesToRead > 0)
            {
                int n = stream.Read(inBuf, bytesRead, bytesToRead);
                if (n == 0)
                    break;
                bytesRead += n;
                bytesToRead -= n;
            }

            //Escribimos el fichero
            string date = DateTime.Now.ToString().Replace('/', '_').Replace(' ', '_').Replace(':', '_').Trim();
            string filename;
            filename = _name + "_" + date + ".mjpg";

            System.IO.FileStream fout = new System.IO.FileStream(filename, System.IO.FileMode.OpenOrCreate,
                                                 System.IO.FileAccess.Write);
            fout.Write(inBuf, 0, bytesRead);
            stream.Close();
            fout.Close();
        }

        /// <summary>
        /// Responde al evento capturando video
        /// </summary>
        /// <param name="ev">Evento.</param>
        public virtual void Manejar(T ev)
        {
            if(Enabled)
                Captura();
        }

        /// <summary>
        /// Webrequest con la url de la camara
        /// </summary>
        private HttpWebRequest _request;

        /// <summary>
        /// Nombre de la camara
        /// </summary>
        private String _name;

        /// <summary>
        /// Url para acceder a la imagen de la camara
        /// </summary>
        private String _url;

        /// <summary>
        /// Credenciales para acceder a la camara
        /// </summary>
        private NetworkCredential _credentials;

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public Boolean Enabled { get; set; }
    }


    /// <summary>
    /// Clase para realizar capturas de imagenes de camaras que cumplan el estandar VAPIX 2.0
    /// en respuesta a un evento.
    /// </summary>
    /// <typeparam name="T">Tipo de eventos que recibe</typeparam>
    [Obsolete("Use AxisController en lugar de esta clase, puedo no funcionar correctamente.")]
    public class VAPIX2ImageCapturer<T> : QESTail<T>, IToggleable
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VAPIX2ImageCapturer&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="user">Usuario de la camara.</param>
        /// <param name="password">Password de la camara.</param>
        /// <param name="ip">Ip de la camara.</param>
        /// <param name="port">Puerto de la camara.</param>
        /// <param name="name">Nombre de la camara. Opcional</param>
        public VAPIX2ImageCapturer(String user, String password, String ip, int port = 80, String name = null)
        {
            _url = "http://" + ip + ":" + port + "/jpg/image.jpg";
            _credentials = new NetworkCredential(user, password);
            _name = name;
        }

        /// <summary>
        /// Captura una imagen de la camara y la guarda en un fichero con el nombre
        /// de la camara y la fecha actual
        /// </summary>
        public void Captura()
        {
            _request = (HttpWebRequest)WebRequest.Create(_url);

            _request.PreAuthenticate = true;
            _request.Credentials = _credentials;

            HttpWebResponse response = (HttpWebResponse)_request.GetResponse();
            System.IO.Stream stream = response.GetResponseStream();
            byte[] inBuf = new byte[100000];
            int bytesToRead = (int)inBuf.Length;
            int bytesRead = 0;
            while (bytesToRead > 0)
            {
                int n = stream.Read(inBuf, bytesRead, bytesToRead);
                if (n == 0)
                    break;
                bytesRead += n;
                bytesToRead -= n;
            }

            //Escribimos el fichero
            string date = DateTime.Now.ToString().Replace('/', '_').Replace(' ', '_').Replace(':', '_').Trim();
            string filename;
            filename = _name + "_" + date + ".jpeg";

            System.IO.FileStream fout = new System.IO.FileStream(filename, System.IO.FileMode.OpenOrCreate,
                                                 System.IO.FileAccess.Write);
            fout.Write(inBuf, 0, bytesRead);
            stream.Close();
            fout.Close();
        }

        /// <summary>
        /// Maneja el evento realizando una captura
        /// </summary>
        /// <param name="ev">Evento recibido.</param>
        public virtual void Manejar(T ev)
        {
            if (Enabled)
                Captura();
        }


        /// <summary>
        /// Webrequest con la url de la camara
        /// </summary>
        private HttpWebRequest _request;

        /// <summary>
        /// Nombre de la camara
        /// </summary>
        private String _name;

        /// <summary>
        /// Url para acceder a la imagen de la camara
        /// </summary>
        private String _url;

        /// <summary>
        /// Credenciales para acceder a la camara
        /// </summary>
        private NetworkCredential _credentials;

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public Boolean Enabled { get; set; }
    }
}
