/**
 * @file QESGestor.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase Servicio
 **/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuercusEventChain;

namespace QES
{

    /// <summary>
    /// Clase que ofrece servicios en respuesta a un evento
    /// </summary>
    public class QESServicio
    {
        
        /// <summary>
        /// Initializes a new instance of the <see cref="QESServicio"/> class.
        /// </summary>
        /// <param name="nombre">Nombre del servicio.</param>
        /// <param name="servicio">Servicio que contiene.</param>
        /// <param name="tipoInterfaz">tipo de la interfaz para el servicio.</param>
        public QESServicio(String nombre, QESBase servicio, Type tipoInterfaz)
        {
            Nombre = nombre;
            _servicio = servicio;
            _tipoInterfaz = tipoInterfaz;
        }

        public Type TipoInterfaz { get { return _tipoInterfaz; } set { _tipoInterfaz = value; } }

        /// <summary>
        /// Tipo que define la interfaz del servicio
        /// </summary>
        private Type _tipoInterfaz;

        /// <summary>
        /// Gets or sets the nombre.
        /// </summary>
        /// <value>
        /// nombre del servicio
        /// </value>
        public String Nombre { get; set; }

        /// <summary>
        /// servicio configurable que trata eventos
        /// </summary>
        private QESBase _servicio;

        /// <summary>
        /// Gets the servicio.
        /// </summary>
        public QESBase Servicio { get { return _servicio; } }

        /// <summary>
        /// Interfaz para motrar al usuario
        /// </summary>
        public System.Windows.Controls.UserControl Interfaz
        {
            get
            {
                return _tipoInterfaz == null ? null : Activator.CreateInstance(_tipoInterfaz, this) as System.Windows.Controls.UserControl;
            }
        }
    }
}
