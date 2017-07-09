/**
 * @brief   Fichero con la implementacion del receptor de mensajes TCP
 * @Author  Mario Corchero
 * @Date    25/05/2011
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Collections;

namespace QuercusEventChain
{

    /// <summary>
    /// Clase que genera eventos de tipo QESEvent tras la recepcion de un mensaje TCP
    /// </summary>
    /// <typeparam name="T">Tipo de eventos que emite</typeparam>
    abstract public class QESRecepMensTcp<T> : QESHead<T>
    {

        /// <summary>
        /// Paquete de datos recibido
        /// </summary>
        class SocketPacket
        {

            /// <summary>
            /// Socket que gestiona la recepcion de este paquete
            /// </summary>
            public Socket currentsocket;


            /// <summary>
            /// array donde se almacenan los datos recibidos
            /// </summary>
            public byte[] buffer = new byte[2048];


            /// <summary>
            /// Identificador del cliente que envia los datos
            /// </summary>
            public int clientnumber;

            /// <summary>
            /// Obtiene o Modifica el emisor del paquete
            /// </summary>
            /// <value>
            /// Emisor del paquete
            /// </value>
            public EndPoint Emisor { get; set; }

            /// <summary>
            /// Initializes a new instance of the <see cref="QESRecepMensTcp&lt;T&gt;.SocketPacket"/> class.
            /// </summary>
            /// <param name="_currentsocket">Socket que gestiona la recepcion de este paquete.</param>
            /// <param name="_clientnumber">Identificador del cliente que envia los datos.</param>
            public SocketPacket(Socket _currentsocket, int _clientnumber)
            {
                currentsocket = _currentsocket;
                clientnumber = _clientnumber;
            }
        }

        /// <summary>
        /// Callback para la recepcion asincrona de los datos
        /// </summary>
        private AsyncCallback _workercallback;

        /// <summary>
        /// socket que atiende las llamadas entrantes
        /// </summary>
        private Socket _mainsocket;


        /// <summary>
        /// Array de sockets para comunicacion con clientes
        /// </summary>
        private ArrayList _workersockets = new ArrayList();


        /// <summary>
        /// Numero de sockets activos
        /// </summary>
        private int _clientcount = 0;

        /// <summary>
        /// Si no esta a null, entidad encargada de recibir entradas para generar un log
        /// </summary>
        private ILogeable _log;

        /// <summary>
        /// puerto por el que se recibe
        /// </summary>
        private int _port;
        /// <summary>
        /// Obtiene el puerto
        /// </summary>
        public int Port { get { return _port; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESRecepMensTcp&lt;T&gt;"/> class.
        /// </summary>
        /// <param name="puerto">puerto de escucha.</param>
        /// <param name="clientsOnW8">Numero maximo de clientes en cola.</param>
        public QESRecepMensTcp(int puerto, int clientsOnW8 = 10, ILogeable log = null)
        {
            _log = log;
            _port = puerto;
            _clientcount = 0;
            try
            {
                _mainsocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPEndPoint local = new IPEndPoint(IPAddress.Any, puerto);
                _mainsocket.Bind(local);
                _mainsocket.Listen(clientsOnW8);
                _mainsocket.BeginAccept(new AsyncCallback(OnClientConnect), null);
            }
            catch (SocketException ex)
            {
                Console.WriteLine("Error al bindear el puerto "+ puerto + " con el servicio de recepcion de Mensajes Tcp");
                throw ex;
            }
        }

        /// <summary>
        /// Called when [client connect].
        /// </summary>
        /// <param name="asyn">Resultado asincrono.</param>
        private void OnClientConnect(IAsyncResult asyn)
        {
            Socket workersocket = _mainsocket.EndAccept(asyn);
            _clientcount++;
            _workersockets.Add(workersocket);
            WaitForData(workersocket, _clientcount);
            _mainsocket.BeginAccept(new AsyncCallback(OnClientConnect), null);
        }

        /// <summary>
        /// Espera la llegada de datos
        /// </summary>
        /// <param name="soc">Socket de recepcion de datos.</param>
        /// <param name="clientnumber">Identificador de cliente.</param>
        private void WaitForData(Socket soc, int clientnumber)
        {
            if (_workercallback == null)
                _workercallback = new AsyncCallback(OnDataReceived);
            SocketPacket data = new SocketPacket(soc, clientnumber);
            data.Emisor = soc.RemoteEndPoint;
            data.currentsocket = soc;
            soc.BeginReceive(data.buffer, 0, data.buffer.Length, SocketFlags.None, _workercallback, data);
        }

        /// <summary>
        /// Called when [data received].
        /// </summary>
        /// <param name="asyn">Resultado asincrono.</param>
        private void OnDataReceived(IAsyncResult asyn)
        {
            SocketPacket socketdata = (SocketPacket)asyn.AsyncState;
            int length = 0;
            length = socketdata.currentsocket.EndReceive(asyn);
            if (length > 0)
            {
                char[] chars = new char[length + 1];
                System.Text.Decoder d = System.Text.Encoding.UTF8.GetDecoder();
                int charlen = d.GetChars(socketdata.buffer, 0, length, chars, 0);
                string sdata = new System.String(chars);
                sdata = sdata.Substring(0, sdata.Length - 1);
                socketdata.currentsocket.Close();
                emitir(socketdata.Emisor,sdata);
                producirLog(socketdata.Emisor, sdata);
            }
        }

        /// <summary>
        /// Añade una entrada al log
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="data">The data.</param>
        protected void producirLog(EndPoint endPoint, String data)
        {
            var ip = endPoint as IPEndPoint;
            _log.AddEntry("Mensaje Tcp recibido de [" + ip.Address + "]:" + data);
        }

        /// <summary>
        /// Metodo a sobreescribir, se llamara cada vez que se reciba una cadena
        /// </summary>
        /// <param name="endPoint">emisor del mensaje.</param>
        /// <param name="data">mensaje recibido via tcp.</param>
        abstract protected void emitir(EndPoint endPoint, String data);
    }



    /// <summary>
    /// Clase que genera eventos de tipo QESEvent(subtipo QESTcpEvent) tras la recepcion de un mensaje TCP
    /// </summary>
    public class QESRecepMensTcp : QESRecepMensTcp<QESEvent>
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QESRecepMensTcp"/> class.
        /// </summary>
        /// <param name="puerto">puerto puerto de escucha.</param>
        /// <param name="clientsOnW8"> Numero maximo de clientes en cola. Opcional</param>
        public QESRecepMensTcp(int puerto, int clientsOnW8 = 10, ILogeable log = null)
            : base(puerto, clientsOnW8,log)
        { }

        /// <summary>
        /// se llamara cada vez que se reciba una cadena, lanza un evento
        /// </summary>
        /// <param name="endPoint">Emisor del mensaje.</param>
        /// <param name="data">data mensaje recibido via tcp.</param>
        override protected void emitir(EndPoint endPoint, String data)
        { 
            QESEvent ev = new QESTcpEvent(data, endPoint);
                #pragma warning disable
            ev = ev.AsDispositivoEvent() ?? (ev as QESTcpEvent).AsAxisCameraEvent() ?? ev;
                #pragma warning restore
            lanzar(ev);
        }
    }
}
