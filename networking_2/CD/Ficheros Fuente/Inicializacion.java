
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import info.clearthought.layout.TableLayout;
import java.awt.GridBagConstraints; 

import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JTextField;


/**
* This code was edited or generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR
* THIS MACHINE, SO JIGLOO OR THIS CODE CANNOT BE USED
* LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
*/
public class Inicializacion extends javax.swing.JApplet implements Runnable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	/**
	* Auto-generated main method to display this 
	* JApplet inside a new JFrame.
	*/
	
	private JTextField _temisor;
	private JComboBox _puerto;
    private JLabel _lPuerto;
    private JLabel _lvelocidad;
    private JLabel jLabel2;
    private JLabel jLabel3;
    private JLabel jLabel4;
    private JTextField jTextField1;
    private JTextField jTextField2;
    private JLabel jLabel1;
    private JComboBox _parada;
    private JLabel _lparada;
    private JComboBox _paridad;
    private JLabel _lparidad;
    private JComboBox _datos;
    private JLabel _ldatos;
    private JComboBox _velocidad;
    private JButton _enviar;
    
    private JFrame _frame; // ventana donde se ejecuta

    
	public void run() {
				_frame = new JFrame();
				Swap._vInicializacion = _frame;
				Inicializacion inst = new Inicializacion();
				_frame.getContentPane().add(inst);
				((JComponent)_frame.getContentPane()).setPreferredSize(inst.getSize());
				_frame.pack();
				_frame.setVisible(true);
	}
	
	public Inicializacion() {
		super();
		initGUI();
	}
	
	private void initGUI() {
		TableLayout thisLayout = new TableLayout(new double[][] {{TableLayout.FILL, TableLayout.FILL, TableLayout.FILL, TableLayout.FILL, TableLayout.FILL}, {TableLayout.FILL, TableLayout.FILL, TableLayout.FILL, TableLayout.FILL, 37.0}});
		thisLayout.setHGap(5);
		thisLayout.setVGap(5);
		getContentPane().setLayout(thisLayout);
		this.setSize(654, 214);
		{
			_enviar = new JButton("Aceptar");
			getContentPane().add(_enviar, "4, 4");
		}
		_enviar.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent e)
            {
            	if(_temisor.getText().length()!=1){//Comprobamos que el receptor y el emisor son correctos
            		jLabel3.setText("El nombre del equipo no es correcto.");
            		return;
            	}            		
            	Swap._puerto = _puerto.getSelectedItem().toString();
            	Swap._bps = _velocidad.getSelectedItem().toString();
            	Swap._bDatos = _datos.getSelectedItem().toString();
            	Swap._paridad = _paridad.getSelectedItem().toString();
            	Swap._bParada = _parada.getSelectedItem().toString();
            	//cogemos como identificadores el primer caracter de la cadena que inserten
              	Swap._origen = _temisor.getText().toString().charAt(0);
				if(!jTextField2.getText().isEmpty())
					Swap.numIntentos = Integer.parseInt(jTextField2.getText());
				if(!jTextField1.getText().isEmpty())
					Swap.retardo = Integer.parseInt(jTextField1.getText());
            	Swap.semaforo.release();
            }
        });
		{
			_temisor = new JTextField();
			getContentPane().add(_temisor, "1, 4");
		}
		{
			 _puerto = new JComboBox();
			 getContentPane().add(_puerto, "0, 2");
			 _puerto.addItem("COM1");
			 _puerto.addItem("COM2");
			 _puerto.addItem("COM3");
			 _puerto.addItem("COM4");
			
		}
		
		{
			_lPuerto = new JLabel("Puerto:");
			getContentPane().add(_lPuerto, "0, 1, c, f");
		}
		{
			_lvelocidad = new JLabel("BPS:");
			getContentPane().add(_lvelocidad, "1,1,c,f");
		}
		{
			 _velocidad = new JComboBox();
			 getContentPane().add(_velocidad, "1, 2");
			 _velocidad.addItem("1200");
			 _velocidad.addItem("2400");
			 _velocidad.addItem("4800");
			 _velocidad.addItem("9600");
		}
		{
			_ldatos = new JLabel("Bit de datos:");
			getContentPane().add(_ldatos, "2,1,c,f");
		}
		{
			 _datos = new JComboBox();
			 getContentPane().add(_datos, "2, 2");
			 _datos.addItem("7");
			 _datos.addItem("8");
		}
		{
			_lparidad = new JLabel("Paridad:");
			getContentPane().add(_lparidad, "3,1,c,f");
		}
		{
			 _paridad = new JComboBox();
			 getContentPane().add(_paridad, "3, 2");
			 _paridad.addItem("Ninguno");
			 _paridad.addItem("Espacio");
			 _paridad.addItem("Marca");
			 _paridad.addItem("Impar");
			 _paridad.addItem("Par");
		}
		{
			_lparada = new JLabel("Bit de Parada:");
			getContentPane().add(_lparada, "4,1,c,f");
		}
		{
			 _parada = new JComboBox();
			 getContentPane().add(_parada, "4, 2");
			 _parada.addItem("1");
			 _parada.addItem("2");
		}
		{
			jLabel2 = new JLabel("Nombre del Equipo:");
			getContentPane().add(jLabel2, "0, 4, c, f");
		}
		{
			jLabel3 = new JLabel("Escoja la configuracion deseada:");
			getContentPane().add(jLabel3, "1,0,3,0,c,f");
		}
		{
			jLabel1 = new JLabel();
			getContentPane().add(jLabel1, "3, 3");
			jLabel1.setText("Tiempo espera");
		}
		{
			jLabel4 = new JLabel();
			getContentPane().add(jLabel4, "2, 3");
			jLabel4.setText("Intentos");
		}
		{
			jTextField2 = new JTextField();
			getContentPane().add(jTextField2, "2, 4");
		}
		{
			jTextField1 = new JTextField();
			getContentPane().add(jTextField1, "3, 4");
		}
	}

}
