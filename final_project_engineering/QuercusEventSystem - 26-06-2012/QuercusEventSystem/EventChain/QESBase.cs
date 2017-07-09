/**
 * @brief   Fichero con la implementacion de la interfaz QESBase, parte de la libreria de Eventos de Quercus
 * @Author  Mario Corchero
 * @Date    07/05/2011
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuercusEventChain
{

    /// <summary>
    /// Implementacion de la clase QESBase, base de todas los servicios de la libreria
    /// </summary>
    public interface QESBase
    {
    }

    /// <summary>
    /// Interfaz para marcar un servicio como activable/desactivable
    /// </summary>
    public interface IToggleable
    {
        bool Enabled { get; set; }
    }

    /// <summary>
    /// Interfaz para implementar las clases con parametros que necesiten salvarse/recuperarse en/de la base de datos
    /// </summary>
    public interface IParametrizale
    {
        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        String[][] GetDataToStore();

        /// <summary>
        /// Dados un par de string (atributo, valor), establece la configuracion
        /// </summary>
        /// <param name="parametros">clave + valor.</param>
        void RestoreFromData(String[] parametro);
    }

    /// <summary>
    /// Interfaz para clases que actuen de log y permitan añadir entradas a este
    /// </summary>
    public interface ILogeable
    {
        /// <summary>
        /// Añade una entrada al log
        /// </summary>
        /// <param name="entry">The entry.</param>
        void AddEntry(String entry);
    }
}
