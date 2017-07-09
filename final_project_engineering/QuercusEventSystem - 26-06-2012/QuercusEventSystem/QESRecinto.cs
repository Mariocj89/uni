/**
 * @file QESRecinto.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase Recinto
 **/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace QES
{
    /// <summary>
    /// Recinto que contiene dispositivos y al que se le asignan roles
    /// </summary>
    class QESRecinto
    {
        /// <summary>
        /// Entrada para guardar el dispositivo y los datos para le plano
        /// </summary>
        public class DispEntry
        {
            /// <summary>
            /// Dispositivo
            /// </summary>
            /// <value>
            /// The dispositivo.
            /// </value>
            public QESDispositivo Dispositivo { get; set; }

            /// <summary>
            /// Distancia en pixeles de la izquierda
            /// </summary>
            /// <value>
            /// corrdenada x
            /// </value>
            public int X { set; get; }

            /// <summary>
            /// Distancia en pixeles de arriba
            /// </summary>
            /// <value>
            /// coordenada y
            /// </value>
            public int Y { set; get; }

            /// <summary>
            /// Gets or sets the image.
            /// </summary>
            /// <value>
            /// icono.
            /// </value>
            public String Image { set; get; }

            /// <summary>
            /// Initializes a new instance of the <see cref="DispEntry"/> class.
            /// </summary>
            public DispEntry(QESDispositivo disp, int x, int y, string image)
            {
                Dispositivo = disp;
                X = x;
                Y = y;
                Image = image;
            }

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESRecinto"/> class.
        /// </summary>
        /// <param name="camaras">Camaras a incluir.</param>
        public QESRecinto(String name, String plano, params DispEntry[] camaras)
        {
            Nombre = name;
            Plano = plano;
            foreach (DispEntry cam in camaras)
                _dispositivos.Add(cam.Dispositivo.Nombre, cam);
        }

        /// <summary>
        /// Coleccion privada contenedora de los dispositvos, la clave es el nombre(String) 
        /// y el valor el dispositivo en si
        /// </summary>
        private Dictionary<String, DispEntry> _dispositivos = new Dictionary<String, DispEntry>();

        /// <summary>
        /// Propiedad para el acceso solo de lectura a la coleccion de dispositivos contenidas
        /// en el recinto.
        /// </summary>
        public Dictionary<String, DispEntry> Dispositivos { get { return _dispositivos; } }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>
        /// Nombre del recinto.
        /// </value>
        public String Nombre { get; set; }

        /// <summary>
        /// Gets or sets the plano.
        /// </summary>
        /// <value>
        /// plano del recinto.
        /// </value>
        public String Plano { get; set; }
    }
}
