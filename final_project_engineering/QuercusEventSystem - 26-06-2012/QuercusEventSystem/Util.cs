using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuercusEventChain;
using System.Xml;

namespace QES
{
    /// <summary>
    /// Clase con extension method para aislar todo el codigo SQL
    /// </summary>
    static class UtilBD
    {

        /// <summary>
        /// Save the log to DB.
        /// </summary>
        /// <param name="log">The log.</param>
        /// <param name="cliente">The cliente.</param>
        public static void SaveToDB(this QESLog log, DBClient cliente)
        {
            //borramos y creamos la tabla
            try { cliente.Command("DROP TABLE log"); }
            catch { }
            cliente.Command("CREATE TABLE log(id serial,fecha date, hora time, content varchar(200), PRIMARY KEY(id));");
            

            //Creamos la sentencia
            StringBuilder sb = new StringBuilder();
            sb.Append("INSERT INTO log(fecha,hora,content) VALUES ");
            {
                DateTime date = log.Entradas.First().Key;
                String time = log.Entradas.First().Value.First().Time;
                sb.Append(String.Format("('{0}','{1}','{2}')", date, time, log.Entradas.First().Value.First().Content));
            }
            bool firstFlag = true;
            foreach (DateTime date in log.Entradas.Keys)
            {
                foreach (QESLog.ParLog par in log.Entradas[date])
                    if (firstFlag) firstFlag = false;
                    else { sb.Append(String.Format(", ('{0}','{1}','{2}')", date.Date, par.Time, par.Content)); }
            }

            sb.Append(";");

            //Realizamos la sentencia
            cliente.Command(sb.ToString());
        }

        /// <summary>
        /// Carga el log desde la BD.
        /// </summary>
        /// <param name="log">The log.</param>
        /// <param name="clienteBD">The cliente BD.</param>
        public static void LoadFromDB(this QESLog log, DBClient clienteBD)
        {
            try
            {//Es posible que la conexion sea correcta, pero no haya datos almacenados
                var reader = clienteBD.Select("SELECT * FROM log ORDER BY hora DESC");
                while (reader.Read())
                {
                    DateTime fecha = (DateTime)reader["fecha"];
                    if (!log.Entradas.ContainsKey(fecha))
                    {
                        log.Entradas.Add(fecha, new System.Collections.ObjectModel.ObservableCollection<QES.QESLog.ParLog>());
                    }
                    log.Entradas[fecha].Add(new QESLog.ParLog((TimeSpan)reader["hora"],reader["content"] as string));
                    
                }
            }
            catch (Exception ex) { Console.WriteLine(ex.ToString()); }
        }

        /// <summary>
        /// Almacena los parametros de todos los componentes
        /// </summary>
        public static void SaveComponentData(this QESGestor gestor)
        {
            var toSave = from c in gestor.Servicios.Values where c.Servicio is IParametrizale select c;
            Queue<String[]> paramsToSave = new Queue<String[]>();
            foreach (QESServicio s in toSave)
            {
                String[][] aux = (s.Servicio as IParametrizale).GetDataToStore();
                foreach (String[] pair in aux) paramsToSave.Enqueue(new String[] { s.Nombre, pair[0], pair[1] });
            }

            if (paramsToSave.Count <= 0) return;//si no hay parametros para salvar, salimos

            //borramos y creamos la tabla
            try { gestor.ClienteBD.Command("DROP TABLE params"); }
            catch { }
            gestor.ClienteBD.Command("CREATE TABLE params(id serial, componente varchar(20), parametro varchar(20), valor varchar(100), PRIMARY KEY(id));");

            //Creamos la sentencia
            StringBuilder sb = new StringBuilder();
            sb.Append("INSERT INTO params(componente,parametro,valor) VALUES ");

            {
                String[] param = paramsToSave.Dequeue();
                sb.Append(String.Format("('{0}','{1}','{2}')", param[0], param[1], param[2]));
            }

            foreach (String[] param in paramsToSave)
                sb.Append(String.Format(", ('{0}','{1}','{2}')", param[0], param[1], param[2]));

            sb.Append(";");

            //Realizamos la sentencia
            gestor.ClienteBD.Command(sb.ToString());

        }


        /// <summary>
        /// Carga todos los parametros de los servicios
        /// </summary>
        public static void RestoreComponentData(this QESGestor gestor)
        {
            try
            {//Es posible que la conexion sea correcta, pero no haya datos almacenados
                var reader = gestor.ClienteBD.Select("SELECT * FROM params");
                while (reader.Read())
                {
                    try
                    {
                        (gestor.Servicios[reader["componente"] as String].Servicio as IParametrizale).RestoreFromData(new String[] { 
                        reader["parametro"] as String, reader["valor"] as String});
                    }
                    catch (Exception ex) { Console.WriteLine(ex.ToString()); }
                }
            }
            catch (Exception ex) { Console.WriteLine(ex.ToString()); }
        }

        /// <summary>
        /// Almacena los datos de todos los usuarios
        /// </summary>
        public static void SaveUserData (this QESGestor gestor)
        {
            
            Queue<String[]> paramsToSave = new Queue<String[]>();
            foreach (QESUser u in gestor.Usuarios.Values)
            {
                paramsToSave.Enqueue(u.GetDataToStore());
            }

            if (paramsToSave.Count <= 0) return;//si no hay parametros para salvar, salimos

            //borramos y creamos la tabla
            try { gestor.ClienteBD.Command("DROP TABLE users"); }
            catch { }
            gestor.ClienteBD.Command("CREATE TABLE users(id serial, name varchar(20), superrole varchar(100), pass varchar(50), PRIMARY KEY(id));");

            //Creamos la sentencia
            StringBuilder sb = new StringBuilder();
            sb.Append("INSERT INTO users(name,superrole,pass) VALUES ");

            {
                String[] param = paramsToSave.Dequeue();
                sb.Append(String.Format("('{0}','{1}','{2}')", param[0], param[1], param[2]));
            }

            foreach (String[] param in paramsToSave)
                sb.Append(String.Format(", ('{0}','{1}','{2}')", param[0], param[1], param[2]));

            sb.Append(";");

            //Realizamos la sentencia
            gestor.ClienteBD.Command(sb.ToString());
            
        }

        /// <summary>
        /// Carga todos los usuarios
        /// </summary>
        public static void RestoreUsersData(this QESGestor gestor)
        {
            try
            {//Es posible que la conexion sea correcta, pero no haya datos almacenados
                var mw = App.Current.MainWindow as MainWindow;
                var reader = gestor.ClienteBD.Select("SELECT * FROM users");
                while (reader.Read())
                {
                    var user = new QESUser(reader["name"] as String, reader["pass"] as String);
                    gestor.Usuarios.Add(user.Name,user);  
                }

                reader = gestor.ClienteBD.Select("SELECT * FROM users");
                while (reader.Read())
                {
                    var user = (from u in gestor.Usuarios.Values.Union(QESRole.MainRoles) where u.Name == reader["name"] as String select u).First();
                    foreach (String role in reader["superrole"].ToString().Split(';'))
                        if(role != "")user.AddSuperRole((from u in gestor.Usuarios.Values.Union(QESRole.MainRoles) where u.Name == role as String select u).First());
                }
            }
            catch (Exception ex) { 
                Console.WriteLine(ex.ToString());
            }
        }

    }

    /// <summary>
    /// Clase para cargar configuracion de fichero xml
    /// </summary>
    static public class XmlFileManager
    {
        /// <summary>
        /// Devuelve un DBclient en funcion de la configuracion en el archivo indicado.
        /// null en caso de errores
        /// </summary>
        /// <param name="file">The file.</param>
        /// <returns></returns>
        static public DBClient LoadDB(string file)
        {
            //intentamos cargar el fichero de configuracion
            try
            {
                //Obtenemos la direccion de la base de datos de archivo
                XmlDocument xDoc = new XmlDocument();
                xDoc.Load(file);
                XmlNodeList xmlList = xDoc.GetElementsByTagName("Database");
                if (xmlList.Count != 1)
                    throw new FormatException("Hay " + " nodos etiquetados como Database, deberia de haber 1.");
                var xmlDBConfig = xmlList[0].Attributes;

                switch (xmlDBConfig["type"].Value)
                {
                    case "Windows_ODBC":
                        return new ODBCClient(xmlDBConfig["DSN"].Value);
                    case "Driver_PostgreSQL":
                        return new PostgreClient(xmlDBConfig["server"].Value, xmlDBConfig["port"].Value, xmlDBConfig["database"].Value, xmlDBConfig["user"].Value, xmlDBConfig["password"].Value);
                    default: throw new FormatException("Tipo de conector para la base de datos no valido. No se reconoce: " + xmlDBConfig["type"].Value);
                }

            }
            catch (XmlException)
            {
                System.Windows.MessageBox.Show("El fichero \"config.xml\" no esta correctamente formateado.", "Error en config.xml", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
            }
            catch (FormatException fEx)
            {
                System.Windows.MessageBox.Show("Error en el fichero config xml, servise su contenido si ha sido manupulado. \nDetalles: " + fEx.Message, "Error en config.xml", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
            }
            catch (System.IO.FileNotFoundException)
            {//si no se encuentra el archivo retornamos null
                return null;
            }
            catch (Exception)
            {
                System.Windows.MessageBox.Show("Error en el fichero config xml, servise su contenido si ha sido manupulado.", "Error en config.xml", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
            }
            return null;
        }

        static public void SaveDB(string file, DBClient client, string oldOne = null)
        {
            XmlDocument xDoc = new XmlDocument();
            if (oldOne != null)
            {
                XmlDocument oldXmlDoc = new XmlDocument();
                try
                {//si existe el ficher eliminamos la entrada Database
                    oldXmlDoc.Load(oldOne);
                    foreach (XmlNode node in oldXmlDoc.GetElementsByTagName("config")[0].ChildNodes)
                    {
                        if (node.Name == "Database") oldXmlDoc.GetElementsByTagName("config")[0].RemoveChild(node);
                    }
                    xDoc = oldXmlDoc;
                }
                catch (System.IO.FileNotFoundException) { }//si el fichero no existe, perfecto :P
            }
            //añadimos los valores de la base de datos
            var dbNode = xDoc.CreateElement("Database");

            if (client is PostgreClient)
                dbNode.SetAttribute("type", "Driver_PostgreSQL");
            else if (client is ODBCClient)
                dbNode.SetAttribute("type", "Windows_ODBC");

            if (xDoc.GetElementsByTagName("config").Count == 0) xDoc.AppendChild(xDoc.CreateElement("config"));

            foreach (String[] pair in client.ConfigToSave)
                dbNode.SetAttribute(pair[0], pair[1]);
            xDoc.GetElementsByTagName("config")[0].AppendChild(dbNode);
            xDoc.Save(file);
        }


        /// <summary>
        /// Devuelve el tiempo de desconecsion de los usuarios cargado del fichero xml.
        /// null en caso de errores
        /// </summary>
        /// <param name="file">The file.</param>
        /// <returns></returns>
        static public int LoadTimeout(string file)
        {
            //intentamos cargar el fichero de configuracion
            try
            {
                //Obtenemos la direccion de la base de datos de archivo
                XmlDocument xDoc = new XmlDocument();
                xDoc.Load(file);
                XmlNodeList xmlList = xDoc.GetElementsByTagName("Timeout");
                if (xmlList.Count != 1)
                    throw new FormatException("Hay " + " nodos etiquetados como Timeout, deberia de haber 1.");
                var xmlTimeoutConfig = xmlList[0].Attributes;
                return Int32.Parse(xmlTimeoutConfig["minutes"].Value.ToString());

            }
            catch (XmlException)
            {
                System.Windows.MessageBox.Show("El fichero \"config.xml\" no esta correctamente formateado.", "Error en config.xml", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
            }
            catch (FormatException fEx)
            {
                System.Windows.MessageBox.Show("Error en el fichero config xml, revise su contenido si ha sido manupulado. \nDetalles: " + fEx.Message, "Error en config.xml", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
            }
            catch (System.IO.FileNotFoundException)
            {//si no se encuentra el archivo retornamos null
                return -1;
            }
            catch (Exception)
            {
                System.Windows.MessageBox.Show("Error en el fichero config xml, revise su contenido si ha sido manupulado.", "Error en config.xml", System.Windows.MessageBoxButton.OK, System.Windows.MessageBoxImage.Error);
            }
            return -1;
        }

        static public void SaveTimeout(string file, int timeout, string oldOne = null)
        {
            XmlDocument xDoc = new XmlDocument();
            if (oldOne != null)
            {
                XmlDocument oldXmlDoc = new XmlDocument();
                try
                {//si existe el ficher eliminamos la entrada Database
                    oldXmlDoc.Load(oldOne);
                    foreach (XmlNode node in oldXmlDoc.GetElementsByTagName("config")[0].ChildNodes)
                    {
                        if (node.Name == "Timeout") oldXmlDoc.GetElementsByTagName("config")[0].RemoveChild(node);
                    }
                    xDoc = oldXmlDoc;
                }
                catch (System.IO.FileNotFoundException) { }//si el fichero no existe, perfecto :P
            }
            //añadimos los valores de la base de datos
            var toNode = xDoc.CreateElement("Timeout");

            toNode.SetAttribute("minutes", timeout.ToString());

            if(xDoc.GetElementsByTagName("config").Count == 0) xDoc.AppendChild(xDoc.CreateElement("config"));
            xDoc.GetElementsByTagName("config")[0].AppendChild(toNode);
            xDoc.Save(file);
        }



    }

}
