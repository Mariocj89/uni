

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
public class Llamada extends javax.swing.JApplet implements Runnable{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JLabel titulo;
	private JButton _aceptar;
	private JButton _rechazar;
	private String cadTitulo;

	/**
	* Auto-generated main method to display this 
	* JApplet inside a new JFrame.
	*/
			public void run() {
				JFrame frame = new JFrame();
				Swap._vllamada = frame;
				Llamada inst = this;
				frame.getContentPane().add(inst);
				((JComponent)frame.getContentPane()).setPreferredSize(inst.getSize());
				frame.pack();
				frame.setVisible(true);
			}

	
	
	public Llamada(String tit) {
		super();
		cadTitulo = tit;
		initGUI();
	}
	
	public void DesactivarRechazo(){
		_rechazar.setEnabled(false);
	}
	
	private void initGUI() {
		try {
			GridBagLayout thisLayout = new GridBagLayout();
			setSize(new Dimension(300,100));
			thisLayout.rowWeights = new double[] {0.1, 0.1};
			thisLayout.rowHeights = new int[] {7, 7};
			thisLayout.columnWeights = new double[] {0.1, 0.1};
			thisLayout.columnWidths = new int[] {7, 7};
			getContentPane().setLayout(thisLayout);
			{
				_aceptar = new JButton("Aceptar");
				getContentPane().add(_aceptar, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				_rechazar = new JButton("Rechazar");
				getContentPane().add(_rechazar, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				titulo = new JLabel(cadTitulo);
				getContentPane().add(titulo, new GridBagConstraints(0, 0, 2, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
			}
			
			_aceptar.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					Swap.aceptar = true;
					Swap.semConectar.release();
				}
			});
			_rechazar.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					Swap.aceptar = false;
					Swap.semConectar.release();
				}
			});

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
