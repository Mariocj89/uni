/**
 * @file QESDispositivo.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase Dispositivo
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
    public class QESDispositivo
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QESDispositivo"/> class.
        /// </summary>
        /// <param name="nombre">Nombre del dispositivo.</param>
        public QESDispositivo(string nombre)
        {
            Nombre = nombre;
        }

        /// <summary>
        /// Metodo para visualizar el dispositivo
        /// </summary>
        virtual public void Visualizar()
        {
            var gui = new System.Windows.Window();
            gui.Height = 300;
            gui.Width = 400;
            gui.Content = new UIDispositivo(this);
            gui.Title = this.Nombre;
            gui.Show();  
        }

        /// <summary>
        /// Gets or sets the nombre.
        /// </summary>
        /// <value>
        /// nombre del dispositivo
        /// </value>
        public String Nombre { get; set; }

        /// <summary>
        /// Interfaz para motrar al usuario
        /// </summary>
        virtual public Object Interfaz {
            get
            {
                return new UIDispositivo(this);
            }
        }

        /// <summary>
        /// Gets or sets the rol.
        /// </summary>
        /// <value>
        /// Rol asociado al dispositivo.
        /// </value>
        public QESRole Rol { get; set; }
    }
}
