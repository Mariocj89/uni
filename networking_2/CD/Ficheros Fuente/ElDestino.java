


import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
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
public class ElDestino extends javax.swing.JApplet implements Runnable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JButton _aceptar;
	private JTextField _destino;
	private JLabel _titulo;

	/**
	* Auto-generated main method to display this 
	* JApplet inside a new JFrame.
	*/
			public void run() {
				Swap._vElDestino = new JFrame();
				ElDestino inst = new ElDestino();
				Swap._vElDestino.getContentPane().add(inst);
				((JComponent)Swap._vElDestino.getContentPane()).setPreferredSize(inst.getSize());
				Swap._vElDestino.pack();
				Swap._vElDestino.setVisible(true);
			}
	
	public ElDestino(){
		super();
		initGUI();
	}
	
	private void initGUI() {
		try {
			GridBagLayout thisLayout = new GridBagLayout();
			setSize(new Dimension(300, 100));
			thisLayout.rowWeights = new double[] {0.1, 0.0, 0.1};
			thisLayout.rowHeights = new int[] {7, 36, 7};
			thisLayout.columnWeights = new double[] {0.1, 0.1, 0.1};
			thisLayout.columnWidths = new int[] {7, 20, 20};
			getContentPane().setLayout(thisLayout);
			{
				_aceptar = new JButton("Aceptar");
				getContentPane().add(_aceptar, new GridBagConstraints(0, 2, 3, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
				_aceptar.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
		            	if(_destino.getText().length()!=1){//Comprobamos que el receptor y el emisor son correctos
		            		_titulo.setText("Nombre incorrecto.");
		            		return;
		            	}   
						Swap._destino = _destino.getText().charAt(0);
						Swap.semaforo.release();
					}
				});
				
				_titulo = new JLabel("Equipo Destino:");
				getContentPane().add(_titulo, new GridBagConstraints(0, 0, 3, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.VERTICAL, new Insets(0, 0, 0, 0), 0, 0));
				_destino = new JTextField();
				getContentPane().add(_destino, new GridBagConstraints(0, 1, 3, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
