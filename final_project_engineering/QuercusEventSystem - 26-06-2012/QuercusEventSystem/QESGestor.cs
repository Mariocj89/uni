/**
 * @file QESGestor.cs
 * @author Mario Corchero Jimenez
 * @brief Implementacion de la clase Gestor
 **/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuercusEventChain;
using System.Windows;
using System.Net;
using System.ServiceModel.Web;
using System.ServiceModel;
using System.Security.Cryptography.X509Certificates;
using System.Security.Permissions;
using System.ServiceModel.Description;


namespace QES
{

    /// <summary>
    /// Gestor encargado de coordinar la aplicación, es una instancia Singleton
    /// que puede ser accedida desde cualquier parte del proyecto
    /// </summary>
    sealed class QESGestor
    {
        public const string configXmlFileName = "config.xml";

        public const string WebServiceHost = "https://localhost/WS/";

        /// <summary>
        /// Prevents a default instance of the <see cref="QESGestor"/> class from being created.
        /// </summary>
        private QESGestor()
        {

            //Debido a que no tenemos ninguna ventana WPF abierta, nos creamos 1 auxiliar para el messagebox
            Window WpfBugWindow = new Window()
            {
                AllowsTransparency = true,
                Background = System.Windows.Media.Brushes.Transparent,
                WindowStyle = WindowStyle.None,
                Top = 0,
                Left = 0,
                Width = 1,
                Height = 1,
                ShowInTaskbar = false
            };
            WpfBugWindow.Show();

            //inicio de la configuracion del gestor
            _dispositivos = new Dictionary<string, QESDispositivo>();
            _recintos = new Dictionary<string, QESRecinto>();
            _servicios = new Dictionary<string, QESServicio>();
            _users = new Dictionary<string, QESUser>();
            _log = new QESLog();
            _log.AddEntry("Inicio de la aplicacion.");
            _instancia = this;

            ClienteBD = XmlFileManager.LoadDB(configXmlFileName);
            QESWebService.TimeToDiscard = XmlFileManager.LoadTimeout(configXmlFileName);

            if (ClienteBD != null)
            {
                _log.AddEntry("Configuracion de la base de datos cargada desde " + configXmlFileName + ".");
            }

            try
            {
                /** CODIGO GENERADO **/
                if (ClienteBD == null)
                {//si no se ha cargado el cliente, se coge el generado por codigo
                    ClienteBD =
                        new ODBCClient("QES"); 
                    _users.Add("Root", new QESUser("Root", "domouex", QESRole.Admin));
                    _users.Add("Guest", new QESUser("Guest", "1234"));
                    _users.Add("Julio", new QESUser("Julio", "pass", QESRole.Viewer));
                    QESWebService.TimeToDiscard = 0;
                }
                
                _dispositivos.Add("Quercus 0", new CamaraAxis("Quercus 0", "158.49.245.162", "root", "domouex", port: 900, audio: true));
                _dispositivos.Add("Repetida 0", new CamaraAxis("Repetida 0", "158.49.245.162", "root", "domouex", port: 900, audio: true));
                _dispositivos.Add("Quercus 1", new CamaraAxis("Quercus 1", "158.49.245.157", "root", "domouex", port: 901, audio: true));
                _dispositivos.Add("Quercus 2", new CamaraAxis("Quercus 2", "158.49.245.123", "root", "domouex", audio: true));
                _dispositivos.Add("Bicis", new CamaraAxis("Bicis", "83.64.164.6", "", "", audio: true));
                _dispositivos.Add("Perros", new CamaraAxis("Perros", "208.42.203.54", "", "", audio: false, port: 8588));
                _dispositivos.Add("Maquina", new CamaraAxis("Maquina", "129.22.128.85", "", "", audio: false));
                _dispositivos.Add("Casa", new CamaraAxis("Casa", "84.246.0.104", "", "", audio: false, port: 82));
                _dispositivos.Add("Fotocopias", new CamaraAxis("Fotocopias", "74.142.100.144", "", "", audio: false));
                _dispositivos.Add("Jardin", new CamaraAxis("Jardin", "193.252.215.70", "", "", audio: false,port:16666));
                _dispositivos.Add("SensorMovimiento", new QESDispositivo("SensorMovimiento"));

                String execPath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
                //Tras agregar todos los dispositivos, agregamos un rol para cada uno
                foreach (String d in _dispositivos.Keys)
                { var r = new QESRole(d); QESRole.MainRoles.Add(r); QESRole.Viewer.AddSuperRole(r); _dispositivos[d].Rol = r; }

                _recintos.Add("Lab Quercus", new QESRecinto("Lab Quercus", execPath + @"\img\pinvestigacion.png",
                    new QESRecinto.DispEntry(_dispositivos["Quercus 0"], 295, 161, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Quercus 1"], 147, 96, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Quercus 2"], 315, 96, execPath + @"\img\camera.png")
                    ));
                _recintos.Add("Despacho", new QESRecinto("Despacho", execPath + @"\img\aselcom.png",
                    new QESRecinto.DispEntry(_dispositivos["SensorMovimiento"], 44, 225, execPath + @"\img\sensor.png"),
                    new QESRecinto.DispEntry(_dispositivos["Repetida 0"], 315, 96, execPath + @"\img\camera.png")));

            
                _recintos.Add("Europa", new QESRecinto("Europa", execPath + @"\img\europe.jpg",
                    new QESRecinto.DispEntry(_dispositivos["Perros"], 31, 43, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Maquina"], 76, 137, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Casa"], 255, 85, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Fotocopias"], 158, 217, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Jardin"], 82, 250, execPath + @"\img\camera.png"),
                    new QESRecinto.DispEntry(_dispositivos["Bicis"], 50, 265, execPath + @"\img\camera.png")));

                var s1 = new QESRecepMensTcp(11111, log: _log);
                var s1b = new QESAxisRecordingTimer();
                var s2a = new QESEsendexSMS("CuentaEsendex", "login", "pass", log: _log);
                var s2b = new QESMailSender("quercuseventsystem@gmail.com", "quercuseventsystem@gmail.com", "quercuseventsystem", step: 5, log: _log);
                var s2c = new QESConditionBus<QESEvent>();
                var s3a = new AxisController("158.49.245.162", "root", "domouex", 15, port: "900", name: "Quercus 0", modo: AxisController.Mode.Recording, log: _log);
                //var s2d = new GenericAxisController(15, AxisController.Mode.Picture, true, _log);
                var s2e = new AxisConditionalController(15, AxisController.Mode.Picture, true, _log);
                //var s3a = new VAPIX2VideoRecorder<QESEvent>("root", "domouex", "158.49.245.162", 900, "Quercus 0");
                var s2y = new Pusher(log: Log);
                var s2z = new QESWebSocket(log: Log) ;

                /*s2a.Recipients.Add("661211518");
                s2a.Recipients.Add("610573234");
                s2b.Destinatarios.Add("mariocj89@gmail.com");
                s2b.Destinatarios.Add("otracuenta@correo.es");
                s2c.Conectar(x => x is QESTcpEvent &&
                     ((IPEndPoint)((QESTcpEvent)x).Emisor).Address.ToString() == "158.49.245.157"
                , s3a);
                //Lo de arriba es una funcion lambda que comprueba si el parametro pasado es un mensaje tcp y en caso
                //positivo comprueba si el emisor coincide con el indicado.

                s1.Conectar(s2b);
                s1.Conectar(s2c);
                s1b.Conectar(s2e);*/

                s1.Conectar(s2b);
                //s1.Conectar(s2y);
                s1b.Conectar(s2e);
                s1.Conectar(s2z);

                _servicios.Add("Pusher", new QESServicio("Pusher", s2y, typeof(UIPusher)));
                _servicios.Add("WebSocket", new QESServicio("WebSocket", s2z, typeof(UIWebSocket)));
                _servicios.Add("Timer", new QESServicio("Timer", s1b, typeof(UITimer)));
                _servicios.Add("Mail", new QESServicio("Mail", s2b, typeof(UIMail)));
                _servicios.Add("EssendexSMS", new QESServicio("EssendexSMS", s2a, typeof(UISMSEsendex)));
                _servicios.Add("Receptor TCP", new QESServicio("Receptor TCP", s1, typeof(UIRecepTcp)));
                _servicios.Add("Quercus 0 Recorder", new QESServicio("Quercus 0 Recorder", s3a, typeof(UIAxisController)));
                //_servicios.Add("Grabador Generico", new QESServicio("Grabador Generico", s2d, typeof(UIGenericAxisController)));
                _servicios.Add("Grabador Generico", new QESServicio("Grabador Generico", s2e, typeof(UIAxisConditionalController)));

                //Cargamos configuracion desde la base de datos
                this.RestoreComponentData();
                Log.LoadFromDB(ClienteBD);
                this.RestoreUsersData();

                //iniciamos los servicios web
                this.StartWebServices();
                
            }
            catch (System.Net.Sockets.SocketException)
            {
                System.Windows.MessageBox.Show("No ha sido posible iniciar la aplicacion, compruebe si existe otra instancia abierta.", "Error al iniciar la aplicacion.", MessageBoxButton.OK, MessageBoxImage.Error);
                App.Current.Shutdown();
            }
            catch (System.Runtime.InteropServices.COMException)
            {
                System.Windows.MessageBox.Show("No ha sido posible iniciar la aplicacion, es necesario que el ActiveX de Axis se encuentre instalado. Puede encontrarlo en http://www.axis.com/techsup/cam_servers/dev/activex.htm", "Error al iniciar la aplicacion.", MessageBoxButton.OK, MessageBoxImage.Error);
                App.Current.Shutdown();
            }
            catch (Exception e)
            {
                System.Windows.MessageBox.Show(e.GetType() + ":" + e.Message, "Error al iniciar", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// Starts the web services.
        /// </summary>
        public bool StartWebServices()
        {
            try
            {
                WebServiceHost serviceHost = new WebServiceHost(typeof(QESWebService), new Uri(WebServiceHost));
                /*ServiceEndpoint ep = serviceHost.AddServiceEndpoint(typeof(IQESWebService), new WebHttpBinding(), "");
                var a = new WebHttpBehavior();
                a.FaultExceptionEnabled = true;
                ep.Behaviors.Add(a);
                ServiceDebugBehavior debug = serviceHost.Description.Behaviors.Find<ServiceDebugBehavior>();
                if (debug == null)
                {
                    serviceHost.Description.Behaviors.Add(
                         new ServiceDebugBehavior() { IncludeExceptionDetailInFaults = true });
                }
                else
                {
                    // make sure setting is turned ON
                    if (!debug.IncludeExceptionDetailInFaults)
                    {
                        debug.IncludeExceptionDetailInFaults = true;
                    }
                }
                */
                serviceHost.Open();

                _activeServices.Enqueue(serviceHost);
                return true;
            }
            catch (System.ServiceModel.AddressAccessDeniedException)
            {
                System.Windows.MessageBox.Show("No ha sido posible iniciar los servicios web, se requieren privilegios de administrador para ello. Reinicie la aplicación en modo administrador para activarlos.", "Atencion: Los servicios web no se han podido activar.", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            catch (System.ServiceModel.AddressAlreadyInUseException)
            {
                System.Windows.MessageBox.Show("No ha sido posible iniciar los servicios web, alguna otra aplicacion esta utilizando el puerto 443. Reinicie el servidor tras haber cerrado la aplicacion conflictiva para activarlos.", "Atencion: Los servicios web no se han podido activar.", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
        }

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources
        /// </summary>
        public void Dispose()
        {
            try
            {
                this.SaveComponentData();
                _log.SaveToDB(ClienteBD);
                this.SaveUserData();
                XmlFileManager.SaveTimeout(configXmlFileName, QESWebService.TimeToDiscard, configXmlFileName);
                XmlFileManager.SaveDB(configXmlFileName, this.ClienteBD, configXmlFileName);
                //Cerramos todos los servicios web
                while (_activeServices.Count > 0) _activeServices.Dequeue().Close();
            }
            catch (Exception e)
            {
                MessageBox.Show("Error al salvar la configuracion del sistema. Detalles de "+e.GetType()+":"+e.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// variable que referencia a la unica instancia posible de la clase QESGestor
        /// </summary>
        static private QESGestor _instancia = null;

        /// <summary>
        /// propiedad para el acceso a la instancia de la clase
        /// </summary>
        static public QESGestor Instancia
        {
            get
            {
                if (_instancia == null) return new QESGestor();
                else return _instancia;
            }
        }

        /// <summary>
        /// Cola de servicios web
        /// </summary>
        private Queue<WebServiceHost> _activeServices = new Queue<WebServiceHost>();

        /// <summary>
        /// Log del sistema
        /// </summary>
        private QESLog _log;

        /// <summary>
        /// dispositivos contenidos en el sistema
        /// </summary>
        private Dictionary<String, QESDispositivo> _dispositivos;

        /// <summary>
        /// recinstos en los que se divide el sistema
        /// </summary>
        private Dictionary<String, QESRecinto> _recintos;

        /// <summary>
        /// servicios que ofrece el sistema en respuesta a eventos
        /// </summary>
        private Dictionary<String, QESServicio> _servicios;

        /// <summary>
        /// Usuarios que posee el systema
        /// </summary>
        private Dictionary<String, QESUser> _users;

        public Queue<WebServiceHost> WebServices { get { return _activeServices; } }

        /// <summary>
        /// Gets the log.
        /// </summary>
        public QESLog Log { get { return _log; } }

        /// <summary>
        /// Gets the dispositivos.
        /// </summary>
        public Dictionary<String, QESDispositivo> Dispositivos { get { return _dispositivos; } }

        /// <summary>
        /// Gets the recintos.
        /// </summary>
        public Dictionary<String, QESRecinto> Recintos { get { return _recintos; } }

        /// <summary>
        /// Gets the servicios.
        /// </summary>
        public Dictionary<String, QESServicio> Servicios { get { return _servicios; } }

        /// <summary>
        /// Gets the usuarios.
        /// </summary>
        public Dictionary<String, QESUser> Usuarios { get { return _users; } }

        /// <summary>
        /// Gets or sets the ciente BD.
        /// </summary>
        /// <value>
        /// The ciente BD.
        /// </value>
        public DBClient ClienteBD { get; set; }
        
        public QESRole[] Roles { get { return QESRole.MainRoles.Union(QESGestor.Instancia.Usuarios.Values).ToArray<QESRole>(); } }

        /// <summary>
        /// Obtiene un rol del sistema
        /// </summary>
        /// <param name="role">Nombre del rol a buscar.</param>
        /// <returns>Rol buscado</returns>
        public QESRole FindRole(String role) { foreach (var r in Roles) if (role == r.Name) return r; return null; }
    }
}
