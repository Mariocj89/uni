/**
 * @brief   Fichero con la implementacion de los clientes para base de datos
 * @Author  Mario Corchero
 * @Date    05/12/2011
 */
using System;
using System.Data.Odbc;
using Npgsql;

namespace QES
{

    /// <summary>
    /// Enum con los tipos de conexiones soportados
    /// </summary>
    public enum DBConectionTypes
    {
        Driver_PostgreSQL,
        Windows_ODBC
    };

    /// <summary>
    /// Interface para acceder a la BD
    /// </summary>
    public interface DBClient
    {
        /// <summary>
        /// Obtiene el resultado de una cosulta SQL
        /// </summary>
        /// <param name="select">The select.</param>
        /// <returns></returns>
        System.Data.Common.DbDataReader Select(String select);

        /// <summary>
        /// Operacion sql sin resultado
        /// </summary>
        /// <param name="command">The command.</param>
        /// <returns>codigo de resultado</returns>
        int Command(String command);

        /// <summary>
        /// Gets or sets the pairs to save.
        /// </summary>
        /// <value>
        /// Valores a guardar en el archivo
        /// </value>
        String[][] ConfigToSave { get; set; }
    }


    /// <summary>
    /// Cliente para conectar a la base de datos a traves de ODBC
    /// </summary>
    class ODBCClient : DBClient
    {
        /// <summary>
        /// Conexion con la base de datos
        /// </summary>
        private OdbcConnection connection = new OdbcConnection();

        /// <summary>
        /// Cadena de conexion a la base de datos
        /// </summary>
        String connectionString;

        /// <summary>
        /// Gets or sets the pairs to save.
        /// </summary>
        /// <value>
        /// Valores a guardar en el archivo
        /// </value>
        public String[][] ConfigToSave { get; set; }

        /// <summary>
        /// Temporizador para la conexion SQL
        /// </summary>
        System.Timers.Timer timeOut;

        public ODBCClient(String dsn)
        {
            connectionString = "DSN=" + dsn + ";";
            ConfigToSave = new String[][]{new String[]{"DSN",dsn}};
        }

        /// <summary>
        /// Open the connection.
        /// </summary>
        /// <param name="connectionString">The connection string.</param>
        /// <returns></returns>
        public void OpenConnection()
        {
            try
            {
                connection.ConnectionString = connectionString;
                connection.Open();

                //iniciamos un temporizador y cuando acabe
                timeOut = new System.Timers.Timer(30 * 1000);
                timeOut.Elapsed += delegate { lock (connection) { connection.Close(); } };
                timeOut.Start();
            }
            catch (Exception e)
            {
                // dispose of the connection to avoid connections leak
                if (connection != null)
                {
                    connection.Dispose();
                }
                throw e;
            }
        }

        /// <summary>
        /// Select from db
        /// </summary>
        /// <param name="select">The select command.</param>
        /// <returns></returns>
        public System.Data.Common.DbDataReader Select(String select)
        {
            lock (connection)
            {
                if (connection.State == System.Data.ConnectionState.Closed)
                {//Si la conexion esta cerrada la abrimos
                    OpenConnection();
                }
                else
                {//sino renovamos el temporizador
                    timeOut.Interval += 30 * 1000;
                }
                return new OdbcCommand(select, connection).ExecuteReader();
            }
        }

        /// <summary>
        /// Realiza una operacion sql
        /// </summary>
        /// <param name="command">The command.</param>
        /// <returns>codigo de resultado</returns>
        public int Command(String command)
        {
            lock (connection)
            {
                if (connection.State == System.Data.ConnectionState.Closed)
                {//Si la conexion esta cerrada la abrimos
                    OpenConnection();
                }
                else
                {//sino renovamos el temporizador
                    timeOut.Interval += 30 * 1000;
                }
                return new OdbcCommand(command, connection).ExecuteNonQuery();
            }
        }
    }

    /// <summary>
    /// Clase para conectarse a la base de datos a traves del driver de postgre NPGSQL
    /// </summary>
    class PostgreClient : DBClient
    {
        /// <summary>
        /// Conexion a la base de datos
        /// </summary>
        private NpgsqlConnection connection = new NpgsqlConnection();

        /// <summary>
        /// Cadena de conexion de la BD
        /// </summary>
        private String connectionString;

        /// <summary>
        /// Temporizador para la conexion SQL
        /// </summary>
        System.Timers.Timer timeOut;

        /// <summary>
        /// Gets or sets the pairs to save.
        /// </summary>
        /// <value>
        /// Valores a guardar en el archivo
        /// </value>
        public String[][] ConfigToSave { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="PostgreClient"/> class.
        /// </summary>
        /// <param name="server">The server.</param>
        /// <param name="port">The port.</param>
        /// <param name="database">The database.</param>
        /// <param name="user">The user.</param>
        /// <param name="pass">The pass.</param>
        public PostgreClient(String server, String port, String database, String user, String pass)
        {
            ConfigToSave = new String[][] { new String[] { "server", server }, new String[] { "port", port }, new String[] { "database", database }, new String[] { "user", user }, new String[] { "password", pass } };
            //connection.ConnectionString = "Data Source=" + server + "," + port + ";Initial Catalog=" + database + ";user=" + user + ";password=" + pass + ";";
            connectionString = "Server=" + server + ";Port=" + port + ";Database=" + database + ";User Id=" + user + ";Password=" + pass + ";";
        }


        /// <summary>
        /// Open the connection.
        /// </summary>
        /// <param name="connectionString">The connection string.</param>
        /// <returns></returns>
        public void OpenConnection()
        {
            try
            {
                connection.ConnectionString = connectionString;
                connection.Open();

                //iniciamos un temporizador y cuando acabe
                timeOut = new System.Timers.Timer(30*1000);
                timeOut.Elapsed += delegate { lock (connection) { connection.Close(); } };
                timeOut.Start();
            }
            catch (Exception e)
            {
                // dispose of the connection to avoid connections leak
                if (connection != null)
                {
                    connection.Dispose();
                }
                throw e;
            }
        }

        /// <summary>
        /// Select from db
        /// </summary>
        /// <param name="select">The select command.</param>
        /// <returns></returns>
        public System.Data.Common.DbDataReader Select(String select)
        {
            lock (connection)
            {
                if (connection.State == System.Data.ConnectionState.Closed)
                {//Si la conexion esta cerrada la abrimos
                    OpenConnection();
                }
                else
                {//sino renovamos el temporizador
                    timeOut.Interval += 30 * 1000;
                }
                return new NpgsqlCommand(select, connection).ExecuteReader();
            }
        }

        /// <summary>
        /// Realiza una operacion sql
        /// </summary>
        /// <param name="command">The command.</param>
        /// <returns>codigo de resultado</returns>
        public int Command(String command)
        {
            lock (connection)
            {
                if (connection.State == System.Data.ConnectionState.Closed)
                {//Si la conexion esta cerrada la abrimos
                    OpenConnection();
                }
                else
                {//sino renovamos el temporizador
                    timeOut.Interval += 30 * 1000;
                }
                return new NpgsqlCommand(command, connection).ExecuteNonQuery();
            }
        }

    }
}
