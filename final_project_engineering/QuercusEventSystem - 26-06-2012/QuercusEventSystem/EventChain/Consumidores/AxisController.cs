/**
 * \file AxisController.cs
 * \author Mario Corchero Jimenez
 * \brief Implementacion de las clases para el control de eventos a traves de camaras Axis.
 **/
using System;
using System.Windows.Forms;
using AxAXISMEDIACONTROLLib;
using System.Net;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

namespace QuercusEventChain
{
    /// <summary>
    /// Clase para la grabacion/captura de imagenes de una camara axis
    /// </summary>
    public partial class AxisController : Form, QESTail<QESEvent>, IParametrizale, IToggleable
    {
        /// <summary>
        /// Enum para indicar que hara el controlador al recibir un evento
        /// </summary>
        public enum Mode { None, Recording, Picture, Both };

        /// <summary>
        /// Si no esta a null, entidad encargada de recibir entradas para generar un log
        /// </summary>
        private ILogeable _log;

        /// <summary>
        /// Url para captura de imagenes
        /// </summary>
        private String _imageUrl;

        /// <summary>
        /// Obtiene o establece la ruta de los ficheros de grabacion
        /// </summary>
        /// <value>
        /// The file path.
        /// </value>
        public String FilePath { get; set; }

        /// <summary>
        /// Añade una entrada al log de una grabacion
        /// </summary>
        /// <param name="endPoint">The end point.</param>
        /// <param name="data">The data.</param>
        protected void producirLog()
        {
            switch (Modo)
            {
                case Mode.Both: _log.AddEntry("Captura de video/imagen en la camara ["+_name+"]"); break;
                case Mode.Picture: _log.AddEntry("Captura de imagen en la camara [" + _name + "]"); break;
                case Mode.Recording: _log.AddEntry("Grabacion realizada en la camara [" + _name + "]"); break;
                default: break;
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        new public Boolean Enabled { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="SpecificAxisRecorder"/> class.
        /// </summary>
        /// <param name="ip">IP de la camara.</param>
        /// <param name="login">Usuario de la camara.</param>
        /// <param name="pass">Password de la camara.</param>
        /// <param name="time">Tiempo de grabacion en segundos.</param>
        /// <param name="modo">Modo de reaccion al evento.</param>
        /// <param name="port">Puerto de la camara. Opcional</param>
        /// <param name="name">Nombre de la camara. Opcional</param>
        /// <param name="showGrabacion">if set to <c>true</c> Muestra la grabacion mientras se realiza.</param>
        public AxisController(string ip, string login, string pass, int time = 15, Mode modo = Mode.Recording, string port = "80", string name = null, bool showGrabacion = true,ILogeable log = null,string path = "")
        {
            InitializeComponent();
            FilePath = path;
            this.Icon = QES.Properties.Resources.ResourceManager.GetObject("Icon.ico") as System.Drawing.Icon;
            Modo = modo;
            _show = showGrabacion;
            _amc.MediaUsername = login;
            _amc.MediaPassword = pass;
            string url = "http://" + ip + ":" + port + "/axis-cgi/mjpg/video.cgi";
            _imageUrl  = "http://" + ip + ":" + port + "/jpg/image.jpg";
            _amc.MediaURL = url;
            Time = time;
            if (name != null)
            { _name = name; this.Text = name; }
            else
            { _name = ip + "_" + port; }
            _log = log;
            Enabled = true;
        }

        /// <summary>
        /// Maneja el evento recibido realizando una grabacion /capturando una imagen
        /// de la camara asociada en el constructor
        /// </summary>
        /// <param name="args">argumentos del evento a tratar.</param>
        public virtual void Manejar(QESEvent args)
        {
            if (!Enabled) return;
            switch (Modo)
            {
                case Mode.Both: capturaImagen(); grabacionTemporizada(); break;
                case Mode.Picture: capturaImagen(); break;
                case Mode.Recording: grabacionTemporizada(); break;
                default: break;
            }
            producirLog();
        }

        /// <summary>
        /// Captura una imagen de la camara
        /// Mas a menudo de lo que deberia no funciona, se recomienda utilizar VAPIX 
        /// </summary>
        private void capturaImagen()
        {
            /*string date = DateTime.Now.ToString().Replace('/', '_').Replace(' ', '_').Replace(':', '_').Trim();
            string filename;
            filename = _name + "_" + date + ".jpeg";
            _amc.SaveCurrentImage(0,filename);// 0 = JPEG, 1 = BMP*/
            HttpWebRequest _request = (HttpWebRequest)WebRequest.Create(_imageUrl);

            _request.PreAuthenticate = true;
            _request.Credentials = new NetworkCredential(_amc.MediaUsername, _amc.MediaPassword);

            HttpWebResponse response = (HttpWebResponse)_request.GetResponse();
            System.IO.Stream stream = response.GetResponseStream();
            byte[] inBuf = new byte[100000];
            int bytesToRead = (int)inBuf.Length;
            int bytesRead = 0;
            while (bytesToRead > 0)
            {
                int n = stream.Read(inBuf, bytesRead, bytesToRead);
                if (n == 0)
                    break;
                bytesRead += n;
                bytesToRead -= n;
            }

            //Escribimos el fichero
            string date = DateTime.Now.ToString().Replace('/', '_').Replace(' ', '_').Replace(':', '_').Trim();
            string filename = FilePath == "" ? "" : (FilePath.Last() != '/') ? FilePath + '/' : FilePath;
            filename += _name + "_" + date + ".jpeg";

            System.IO.FileStream fout = new System.IO.FileStream(filename, System.IO.FileMode.OpenOrCreate,
                                                 System.IO.FileAccess.Write);
            fout.Write(inBuf, 0, bytesRead);
            stream.Close();
            fout.Close();
        }

        /// <summary>
        /// Realiza una grabacion temporizada con todos los datos indicados anteriormente
        /// </summary>
        private void grabacionTemporizada()
        {
            string date = DateTime.Now.ToString().Replace('/', '_').Replace(' ', '_').Replace(':', '_').Trim();
            if (_show)//si se indicó, se muetra la grabacion a la vez que se graba
            {
                var asyncRes = this.BeginInvoke((MethodInvoker)delegate
                {
                    this.Show();
                });
            }
            _amc.Play();
            string filename = FilePath == "" ? "" : (FilePath.Last() != '/') ? FilePath + '/' : FilePath;
            filename += _name + "_" + date + ".asf";
            _amc.StartRecordMedia(filename, 8, "ASF");
            System.Timers.Timer timer = new System.Timers.Timer();
            timer.Elapsed += delegate { this.BeginInvoke((MethodInvoker)delegate { 
                _amc.StopRecord(); if (_show)this.Hide(); 
            }); };
            timer.Interval = Time * 1000;
            timer.Enabled = true;
            timer.AutoReset = false;
            timer.Start();
        }

        /// <summary>
        /// ActiveX para controlar la camra
        /// </summary>
        private AxAxisMediaControl _amc = new AxAxisMediaControl();

        /// <summary>
        /// tiempo de grabacion
        /// </summary>
        public int Time { get; set; }

        /// <summary>
        /// nombre de la camara
        /// </summary>
        private String _name;
        /// <summary>
        /// Gets the name of the control.
        /// </summary>
        /// <returns>The name of the control. The default is an empty string ("").</returns>
        public String Nombre { get { return _name; } }

        /// <summary>
        /// Muestra la grabacion mientras se realiza
        /// </summary>
        private bool _show;

        /// <summary>
        /// Gets or sets el modo de reaccion de la camara
        /// </summary>
        /// <value>
        /// Modo de reaccion del controlador. (captura de video, imagen, ambos y ninguno)
        /// </value>
        public Mode Modo { get; set; }

        /// <summary>
        /// Seleccion de resolucion
        /// </summary>
        /// <param name="sender">Objeto que emite el evento.</param>
        /// <param name="e">Parametros del evento.</param>
        private void amcView_OnDoubleClick(object sender, AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnDoubleClickEvent e)
        {
            cmsOptions.Show(_amc, e.fX, e.fY);
        }

        /// <summary>
        /// Seleccion de resolucion
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void x480ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = _amc.MediaURL;
            if (url.Contains("resolution="))
                url = url.Remove(url.IndexOf("resolution"));
            url += "resolution=640x480";
            _amc.MediaURL = url; 
        }

        /// <summary>
        /// Seleccion de resolucion
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void x360ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = _amc.MediaURL;
            if (url.Contains("resolution="))
                url = url.Remove(url.IndexOf("resolution"));
            url += "resolution=480x360";
            _amc.MediaURL = url; 
        }

        /// <summary>
        /// Seleccion de resolucion
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void x240ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = _amc.MediaURL;
            if (url.Contains("resolution="))
                url = url.Remove(url.IndexOf("resolution"));
            url += "resolution=320x240";
            _amc.MediaURL = url; 
        }


        /// <summary>
        /// Seleccion de resolucion
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void x180ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = _amc.MediaURL;
            if (url.Contains("resolution="))
                url = url.Remove(url.IndexOf("resolution"));
            url += "resolution=240x180";
            _amc.MediaURL = url; 
        }

        /// <summary>
        /// Seleccion de resolucion
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void x120ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string url = _amc.MediaURL;
            if (url.Contains("resolution="))
                url = url.Remove(url.IndexOf("resolution"));
            url += "resolution=160x120";
            _amc.MediaURL = url; 
        }

        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        public virtual String[][] GetDataToStore()
        {
            return new String[][] { new String[] { "Modo", Modo.ToString() }, new String[] { "Enabled", Enabled.ToString() }, new String[] { "Path", FilePath } };
        }

        /// <summary>
        /// Pone el valor a un atributo por parametro.
        /// </summary>
        /// <param name="parametros">El parametro.</param>
        public virtual void RestoreFromData(String[] parametro)
        {
            switch (parametro[0])
            {
                case "Modo": Modo = (AxisController.Mode)Enum.Parse(typeof(AxisController.Mode), parametro[1]); break;
                case "Enabled": Enabled = Boolean.Parse(parametro[1]); break;
                case "Path": FilePath = parametro[0]; break;
            }

        }
    }

    /// <summary>
    /// Clase para la grabacion/captura de imagenes de camaras axis. 
    /// Cuando recibe un evento, en el evento debe incluirse los datos de la camara de la que grabar
    /// </summary>
    public class GenericAxisController : QESTail<QESEvent>, IParametrizale, IToggleable
    {
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="QESBase"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public Boolean Enabled { get; set; }

        /// <summary>
        /// Gets or sets the time.
        /// </summary>
        /// <value>
        /// Tiempo entre grabaciones
        /// </value>
        public int Time { get; set; }

        /// <summary>
        /// Gets or sets the modo.
        /// </summary>
        /// <value>
        /// Modo de operar con las camaras
        /// </value>
        public AxisController.Mode Modo { get; set; }

        /// <summary>
        /// true si debe mostrarse una ventana visualizando la grabacion
        /// </summary>
        private bool _showGrabacion;

        /// <summary>
        /// Gets or sets the grabadores.
        /// </summary>
        /// <value>
        /// Controladores para realizar grabaciones
        /// </value>
        public Dictionary<String, AxisController> Grabadores { get; set; }

        /// <summary>
        /// Instancia para emitir logs
        /// </summary>
        private ILogeable _log;

        public GenericAxisController(int time, AxisController.Mode modo, bool showGrabacion = false, ILogeable log = null, string path = "")
        {
            Enabled = true;
            Modo = modo;
            Time = time;
            _showGrabacion = showGrabacion;
            _log = log;
            Grabadores = new Dictionary<string, AxisController>();
            foreach (QES.QESDispositivo c in QES.QESGestor.Instancia.Dispositivos.Values)
            {
                var camera = c as QES.CamaraAxis;
                if(camera == null) continue;
                Grabadores.Add(camera.Nombre,new AxisController(camera.IPString,camera.User,camera.Pass, port : camera.Puerto.ToString(), name : camera.Nombre,showGrabacion:showGrabacion,log:QES.QESGestor.Instancia.Log,path: path));
            }
        }

        /// <summary>
        /// Ruta del archivo de grabacion
        /// </summary>
        /// <value>
        /// The path.
        /// </value>
        public string FilePath { get { return Grabadores.Values.Count > 0 ? Grabadores.Values.First().FilePath : ""; } set { foreach (var g in Grabadores.Values) { g.FilePath = value; } } }

        /// <summary>
        /// Cuando recive un evento, si es del tipo <see cref="QESAxisCameraEvent"/> realiza una captura/grabacion
        /// en la camara que indique el evento
        /// </summary>
        /// <param name="e">The e.</param>
        public virtual void Manejar(QESEvent e)
        {
            if (!Enabled) return;
            if (e != null && e is QESAxisCameraEvent)
            {
                var ev = e as QESAxisCameraEvent;
                int newTime;//Si la informacion del evento trae especificado el intervalo lo extraemos
                if (!Int32.TryParse(ev.Info, out newTime)) { newTime = Time; }
                var t = new System.Threading.Thread(delegate() {
                    if (Grabadores.ContainsKey(ev.Dispositivo.Nombre))
                    {
                        Grabadores[ev.Dispositivo.Nombre].Time = newTime;
                        Grabadores[ev.Dispositivo.Nombre].Manejar(ev);
                    }
                });
                t.SetApartmentState(System.Threading.ApartmentState.STA);
                t.Start();
            }
            
        }

        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        public virtual String[][] GetDataToStore()
        {
            return new String[][] { new String[] {"Modo",Modo.ToString() }, new String[] {"Enabled", Enabled.ToString()}, new String[]{"Path",FilePath} };
        }

        /// <summary>
        /// Pone el valor a un atributo por parametro.
        /// </summary>
        /// <param name="parametros">El parametro.</param>
        public virtual void RestoreFromData(String[] parametro)
        {
            switch (parametro[0])
            {
                case "Modo": Modo = (AxisController.Mode)Enum.Parse(typeof(AxisController.Mode), parametro[1]); break;
                case "Enabled": Enabled = Boolean.Parse(parametro[1]); break;
                case "Path": FilePath = parametro[0]; break;
            }

        }
    }

    /// <summary>
    /// Clase para realizar grabaciones en las camaras en funcion de las que hay definidas en el sistema
    /// </summary>
    public class AxisConditionalController : GenericAxisController
    {

        /// <summary>
        /// Lista de camaras que el sistema grabará
        /// </summary>
        /// <value>
        /// Lista de camaras que el sistema grabará
        /// </value>
        public HashSet<String> Camaras { get; set; }


        /// <summary>
        /// Initializes a new instance of the <see cref="AxisConditionalController"/> class.
        /// </summary>
        /// <param name="time">tiempo de grabacion.</param>
        /// <param name="modo">modo de reaccion(imagen, video).</param>
        /// <param name="showGrabacion">indica si mostrar la grabacion mientras se graba.</param>
        /// <param name="log">The log.</param>
        public AxisConditionalController(int time, AxisController.Mode modo, bool showGrabacion = false, ILogeable log = null,String path ="")
            : base(time, modo, showGrabacion, log,path)
        {
            Camaras = new HashSet<string>();
            foreach(QES.QESDispositivo d in QES.QESGestor.Instancia.Dispositivos.Values)
            {
                if (d is QES.CamaraAxis) Camaras.Add(d.Nombre);
            }
        }

        /// <summary>
        /// Cuando recive un evento, si es del tipo <see cref="QESAxisCameraEvent"/> realiza una captura/grabacion
        /// en la camara que indique el evento, filtrando ademas por camara
        /// </summary>
        /// <param name="e">The event.</param>
        public override void Manejar(QESEvent e)
        {
            QESAxisCameraEvent ev = e as QESAxisCameraEvent;
            if (ev != null)
            {
                if(Camaras.Contains(ev.Dispositivo.Nombre)) base.Manejar(ev);
            }
        }

        /// <summary>
        /// Devuelve todos los datos que deben ser almacenados
        /// </summary>
        /// <returns>Conjunto de pares. Cada par contiene Clave + valor</returns>
        public override String[][] GetDataToStore()
        {
            List<String[]> l = new List<String[]>();
            foreach (String[] s in base.GetDataToStore()) l.Add(s);
            foreach(String c in this.Camaras) l.Add(new String[]{"CamaraON",c});

            return l.ToArray();
        }


        /// <summary>
        /// Pone el valor a un atributo por parametro.
        /// </summary>
        /// <param name="parametros">El parametro.</param>
        public override void RestoreFromData(String[] parametro)
        {
            if (Camaras.Count == (from d in QES.QESGestor.Instancia.Dispositivos where d.Value is QES.CamaraAxis select d).Count())
                Camaras.Clear();//Al leer el primer parametro se vacian las camaras
            switch (parametro[0])
            {
                case "CamaraON": Camaras.Add(parametro[1]); break;
                default: base.RestoreFromData(parametro); break;
            }

        }
    }
}