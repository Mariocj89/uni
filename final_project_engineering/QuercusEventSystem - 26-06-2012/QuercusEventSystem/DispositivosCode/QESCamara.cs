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
    public class QESCamara : QESDispositivo
    {

        /// <summary>
        /// Initializes a new instance of the <see cref="QESCamara"/> class.
        /// </summary>
        /// <param name="nombre">Nombre de la camara.</param>
        /// <param name="ip">ip de la camara.</param>
        /// <param name="port">puerto de la camara. Opcional</param>
        public QESCamara(String nombre, String ip, int port = 80): base(nombre)
        {
            Puerto = port;
            try { IP = IPAddress.Parse(ip); }
            catch (FormatException) { Console.WriteLine("Error, formato de ip incorrecto."); IP = IPAddress.Parse("0.0.0.0"); }
        }


        /// <summary>
        /// Gets or sets the IP.
        /// </summary>
        /// <value>
        /// Direccion IP de la camara en IPAddress
        /// </value>
        public IPAddress IP { get; set; }

        /// <summary>
        /// Gets or sets the IP string.
        /// </summary>
        /// <value>
        /// Direccion IP de la camara en String
        /// </value>
        public String IPString { get { return IP.ToString(); } set { IP = IPAddress.Parse(value);} }

        /// <summary>
        /// Gets or sets the puerto.
        /// </summary>
        /// <value>
        /// Puerto que usa la camara
        /// </value>
        public int Puerto { get; set; }

        /// <summary>
        /// Metodo para visualizar el dispositivo
        /// </summary>
        override public void Visualizar()
        {
            var gui = new System.Windows.Window();
            gui.Height = 300;
            gui.Width = 400;
            gui.Content = new UICamara(this);
            gui.Title = this.Nombre;
            gui.Show();
        }

        /// <summary>
        /// Interfaz para motrar al usuario
        /// </summary>
        override public Object Interfaz
        {
            get
            {
                return new UICamara(this);
            }
        }
    }
}
