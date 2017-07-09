using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace QES
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        QESGestor gestor;
        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindow"/> class.
        /// </summary>
        public MainWindow()
        {
            try { gestor = QESGestor.Instancia; }
            catch (Exception e) { System.Windows.MessageBox.Show("Atencion, se ha producido un error al iniciar la aplicación, asegurese de que .Net Framework 4 esta instalado y todos los pasos se han seguido correctamente. Los detalles de la excepcion "+e.GetType()+" son: "+e.Message,"Error al iniciar",MessageBoxButton.OK,MessageBoxImage.Error); }
            InitializeComponent();
            App.Current.MainWindow = this;
            this.Visibility = System.Windows.Visibility.Hidden;
            new QES.Login.LoginWindow(
                () => Dispatcher.BeginInvoke((Action)( () => Visibility = System.Windows.Visibility.Visible )),

                (user, password) => gestor.Usuarios.ContainsKey(user) &&
                    gestor.Usuarios[user].CheckPassword(password) &&
                    gestor.Usuarios[user].HasRole(QESRole.Admin)

                ).Show();
        }

        /// <summary>
        /// Handles the Closing event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (!this.IsVisible) return;//si esta en la ventana de login
                

            var res = MessageBox.Show("¿Seguro que desea cerrar la aplicacion?, todos los servicios se detendran.", "Salir", MessageBoxButton.YesNo, MessageBoxImage.Question, MessageBoxResult.No);
            if (res == MessageBoxResult.Yes)
            {
                gestor.Log.AddEntry("Cierre de la aplicacion");
                gestor.Dispose();
                App.Current.Shutdown();
            }
            else
                e.Cancel = true;
        }

    }
}
