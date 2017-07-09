/**
 * @brief   Fichero con la implementacion de la interfaz QESTail, parte de la libreria de Eventos de Quercus
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
    /// Interfaz que consume un evento interno del systema, ya sea para transformarlo en uno del exterior o cualquier proposito.
    /// Ej: Servicio de emails
    /// Es una interfaz generica, el tipo indicado corresponde al tipo de evento que consumirá del sistema.
    /// </summary>
    /// <typeparam name="T">tipo de evento que recibe</typeparam>
    public interface QESTail<T> : QESBase
    {
        /// <summary>
        /// metodo con el que se tratara un evento lanzado por la clase a la que este suscrito.
        /// </summary>
        /// <param name="e">argumento del evento a Manejar.</param>
        void Manejar(T e);

    }
}
