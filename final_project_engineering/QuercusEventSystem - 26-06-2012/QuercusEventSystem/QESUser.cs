/**
 * @brief   Fichero con la implementacion de QESUser y QESRole
 * @Author  Mario Corchero
 * @Date    24/10/2011
 */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QES
{
    /// <summary>
    /// Rol del sistema, se puede relacionar con dispositivos/servicios para indicar que
    /// tiene privilegios para visualizarlos, No puede haber dos roles/usuarios con el mismo nombre.
    /// </summary> 
    public class QESRole
    {
        static QESRole()
        {
            Admin.AddSuperRole(Viewer);
        }

        /// <summary>
        /// Lista con los roles por defecto. Al iniciar el programa se agregara uno para cada dispositivo
        /// </summary>
        public static List<QESRole> MainRoles = new List<QESRole> { new QESRole("Admin"), new QESRole("Viewer") };

        /// <summary>
        /// Gets the admin role.
        /// </summary>
        public static QESRole Admin { get { return (from r in QESRole.MainRoles where r.Name == "Admin" select r).First(); } }

        /// <summary>
        /// Gets the admin role.
        /// </summary>
        public static QESRole Viewer { get { return (from r in QESRole.MainRoles where r.Name == "Viewer" select r).First(); } }

        /// <summary>
        /// Initializes a new instance of the <see cref="QESRole"/> class.
        /// </summary>
        /// <param name="name">Nombre del rol.</param>
        /// <param name="rolList">Varargs de superroles.</param>
        public QESRole(String name, params QESRole[] rolList)
        {
            _name = name;
            foreach(QESRole rol in rolList)
            {
                AddSuperRole(rol);
            }
        }

        /// <summary>
        /// Añade un superRol(rol de que hereda todos sus privilegios)
        /// </summary>
        /// <param name="rol">Rol a añadir.</param>
        /// <returns>
        /// true si se ha añadido, false si ya existia
        /// </returns>
        public bool AddSuperRole(QESRole rol)
        {
            if (_superRoles.Contains(rol) || rol == null) return false;

            return _superRoles.Add(rol);
        }

        /// <summary>
        /// Elimina un rol de la lista de superoles
        /// </summary>
        /// <param name="rol">Rol a eliminar.</param>
        /// <returns>true si se elimino correctamente, false si no existe</returns>
        public bool RemoveSuperRole(QESRole rol)
        {
            return _superRoles.Remove(rol);
        }

        /// <summary>
        /// Comprueba si contiene alguno de los roles indicados
        /// </summary>
        /// <param name="rolList">Lista de roles a comprobar.</param>
        /// <returns>
        ///   <c>true</c> si contiene alguno de ellos; otherwise, <c>false</c>.
        /// </returns>
        public bool HasRole(params QESRole[] rolList)
        {
            return hasRole(rolList,new HashSet<QESRole>());
        }

        /// <summary>
        /// Funcion sumergida que realiza el checkeo de roles
        /// </summary>
        /// <param name="rolList">Lista de roles a comprobar.</param>
        /// <param name="checkeds">Roles comprobados.</param>
        /// <returns>
        ///   <c>true</c> if the specified rol list has role; otherwise, <c>false</c>.
        /// </returns>
        private bool hasRole(QESRole[] rolList, ISet<QESRole> checkeds)
        {
            //Comprueba si este rol esta en la lista de roles validos
            if (rolList.Contains<QESRole>(this)) return true;
            checkeds.Add(this);

            //busca en los superRoles
            foreach (QESRole role in _superRoles)
            {
                if (role.hasRole(rolList, checkeds)) return true;
            }

            //no se ha encontrado ninguna coincidencia
            return false;
        }

        /// <summary>
        /// Conjunto de roles de los que hereda privilegios
        /// </summary>
        private ISet<QESRole> _superRoles = new HashSet<QESRole>();

        /// <summary>
        /// nombre del rol
        /// </summary>
        private String _name;

        /// <summary>
        /// Propiedad para acceder al nombre
        /// </summary>
        public String Name { get { return _name; } }

        /// <summary>
        /// Gets the data to store.
        /// </summary>
        /// <returns>array de cadenas, en la posicion 0 nombre, en la 1 superroles separados por ;</returns>
        virtual public String[] GetDataToStore()
        {
            StringBuilder roles = new StringBuilder();
            foreach (QESRole r in _superRoles) roles.Append(r._name+";");
            return new String[] { _name, roles.ToString() };
        }
    }

    /// <summary>
    /// Usuario del sistema, es un rol con el que se puede acceder al sistema,
    /// es decir, ademas de nombre tiene contraseña y datos personales.
    /// </summary>
    public class QESUser : QESRole
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="QESUser"/> class.
        /// </summary>
        /// <param name="name">Nombre de usuario.</param>
        /// <param name="pass">contraseña.</param>
        /// <param name="rolList">Varargs de superRoles.</param>
        public QESUser(String user, String pass, params QESRole[] rolList) : base(user, rolList)
        {
            _pass = pass;
        }

        /// <summary>
        /// Comprueba si la contraseña coincide
        /// </summary>
        /// <param name="pass">Contraseña a probar.</param>
        /// <returns></returns>
        public bool CheckPassword(String pass)
        {
            return _pass.Equals(pass);
        }

        /// <summary>
        /// Establece la contraseña
        /// </summary>
        /// <value>
        /// Contraseña
        /// </value>
        public String Password { set { _pass = value; } }

        /// <summary>
        /// Contraseña del usuario
        /// </summary>
        private String _pass;

        override public String[] GetDataToStore()
        {
            return new String[] { base.GetDataToStore()[0], base.GetDataToStore()[1], _pass };
        }
    }
}
