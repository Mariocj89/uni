/**
 * @file QESDispositivo.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase Camara
 **/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace QES
{
    /// <summary>
    /// Camara del sistema, con toda la informacion necesaria
    /// </summary>
    public class CamaraAxis : QESCamara
    {

        /// <summary>
        /// Initializes a new instance of the <see cref="CamaraAxis"/> class.
        /// </summary>
        /// <param name="nombre">Nombre de la camar.</param>
        /// <param name="ip">ip.</param>
        /// <param name="user">user.</param>
        /// <param name="pass"> pass.</param>
        /// <param name="audio">if set to <c>true</c> [audio].</param>
        /// <param name="audioOut">if set to <c>true</c> [audio out].</param>
        /// <param name="ptz">if set to <c>true</c> [PTZ].</param>
        /// <param name="port">The port.</param>
        public CamaraAxis(String nombre, String ip, String user, String pass, Boolean audio = false, Boolean audioOut = false, Boolean ptz = false, int port = 80)
            : base(nombre,ip,port)
        {
            _user = user;
            _pass = pass;
            _audioOut = audioOut;
            _audio = audio;
            _ptz = ptz;
        }

        /// <summary>
        /// Usuario para conectarse a la camara
        /// </summary>
        private String _user;

        /// <summary>
        /// Gets the user.
        /// </summary>
        public String User { get { return _user; } }

        /// <summary>
        /// Contraseña para conectarse a la camara
        /// </summary>
        private String _pass;

        /// <summary>
        /// Gets the pass.
        /// </summary>
        public String Pass { get { return _pass; } }

        /// <summary>
        /// Boleano que indica si la camara envia audio
        /// </summary>
        private Boolean _audio;

        /// <summary>
        /// Gets a value indicating whether this <see cref="CamaraAxis"/> is audio.
        /// </summary>
        /// <value>
        ///   <c>true</c> if audio; otherwise, <c>false</c>.
        /// </value>
        public Boolean Audio { get { return _audio; } }

        /// <summary>
        /// Boleano que indica si la camara recibe audio(y emite al exterior)
        /// </summary>
        private Boolean _audioOut;

        /// <summary>
        /// Gets a value indicating whether [audio out].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [audio out]; otherwise, <c>false</c>.
        /// </value>
        public Boolean AudioOut { get { return _audioOut; } }

        /// <summary>
        /// Boleano que indica si la camara es PTZ
        /// </summary>
        private Boolean _ptz;

        /// <summary>
        /// Gets a value indicating whether this <see cref="CamaraAxis"/> is PTZ.
        /// </summary>
        /// <value>
        ///   <c>true</c> if PTZ; otherwise, <c>false</c>.
        /// </value>
        public Boolean PTZ { get { return _ptz; } }

        /// <summary>
        /// Metodo para visualizar el dispositivo
        /// </summary>
        override public void Visualizar()
        {
            new QESAxisView(_audio, _audioOut, IP.ToString(), Puerto, _ptz, _user, _pass).Show();
        }

        /// <summary>
        /// Interfaz para motrar al usuario
        /// </summary>
        override public Object Interfaz
        {
            get
            {
                return new UICamaraAxis(this);
            }
        }
    }
}
