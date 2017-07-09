using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Alchemy.Classes;
using Alchemy;
using System.Collections.ObjectModel;


namespace QuercusEventChain
{
    public class QESWebSocket : IDisposable, QESTail<QESEvent>, IToggleable, IParametrizale
    {
        /// <summary>
        /// Lista de usuarios conectados
        /// </summary>
        public List<UserContext> Usuarios { get; set; }

        /// <summary>
        /// Servidor de webSocket
        /// </summary>
        private WebSocketServer wsServer;

        /// <summary>
        /// Referencia para añadir entradas al log
        /// </summary>
        private ILogeable _log;

        /// <summary>
        /// Gets the port.
        /// </summary>
        public int Port { get {return  wsServer.Port; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESWebSocket"/> class.
        /// </summary>
        /// <param name="puerto">puerto utilizado por el socket.</param>
        /// <param name="log">The log.</param>
        public QESWebSocket(int puerto = 8181, ILogeable log = null)
        {
            Usuarios = new List<UserContext>();
            Enabled = true;
            _log = log;

            wsServer = new WebSocketServer(81, System.Net.IPAddress.Any)
            {
                OnConnected = OnConnect,
                OnDisconnect = OnDisconnect,
                TimeOut = new TimeSpan(24, 0, 0)
            };

            wsServer.Start();
        }

        /// <summary>
        /// Event fired when a client connects to the Alchemy Websockets server instance.
        /// Adds the client to the online users list.
        /// </summary>
        /// <param name="context">The user's connection context</param>
        public void OnConnect(UserContext context)
        {
            Usuarios.Add(context);
        }

        /// <summary>
        /// Event fired when a client disconnects from the Alchemy Websockets server instance.
        /// Removes the user from the online users list and broadcasts the disconnection message
        /// to all connected users.
        /// </summary>
        /// <param name="context">The user's connection context</param>
        public void OnDisconnect(UserContext context)
        {
            Usuarios.Remove(context);
        }

        /// <summary>
        /// Broadcasts the specified mensaje.
        /// </summary>
        /// <param name="mensaje">The mensaje.</param>
        public void Broadcast(String mensaje)
        {
            if (_log != null) _log.AddEntry("Mensaje enviado a traves de WebSocket: " + mensaje);

            foreach (var uc in Usuarios)
                uc.Send(mensaje);
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            wsServer.Stop();
            wsServer.Dispose();
        }

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
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public Boolean Enabled { get; set; }

        /// <summary>
        /// Gets the data to store.
        /// </summary>
        /// <returns></returns>
        public virtual String[][] GetDataToStore() { return new String[][] { new String[] { "Enabled", Enabled.ToString() } }; }

        /// <summary>
        /// Maneja el evento recibido
        /// </summary>
        /// <param name="ev">evento.</param>
        public virtual void Manejar(QESEvent e)
        {
            if (!Enabled) return;

            QESAxisCameraEvent ev = e as QESAxisCameraEvent;
            if (ev != null)
                this.Broadcast(ev.Dispositivo.Nombre);
        }
    }
}
