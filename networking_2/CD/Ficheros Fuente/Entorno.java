import java.awt.Dimension;

import java.awt.GridBagConstraints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.JCheckBox;

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
public class Entorno extends javax.swing.JApplet implements Runnable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	* Auto-generated main method to display this 
	* JApplet inside a new JFrame.
	*/
	JCheckBox errores;
		
    /** El botón */
    private JButton bEnviar;
    JButton bConectar;
    private JButton bConfigurar;
    private JButton bOk;
   
    /** Campos de texto */
    private JTextField areaEnvio;
    private JTextField areaRecepcion;
    private JTextField areaInformacion;
    /** Etiquetas */
    private JLabel lEnvio;
    private JLabel lRecepcion;
    private JLabel lInformacion;
    private JLabel lCreditos;

    private IEnlace _enlace;
    
    static private Entorno _instancia = null;

	public static void main(String[] args) {
		Entorno miEntorno = new Entorno();
		Thread hilo1 = new Thread(miEntorno);
		hilo1.start();
	}
	
	protected void finalize() throws Throwable{
		super.finalize();
		Swap.recibir = false;
	}
	
	void permitirEnviar(boolean var){
		bEnviar.setEnabled(var);
		bConectar.setEnabled(var);
	}

	private boolean Recibir(){
		String recibido;
		recibido = _enlace.Recibir();
		if(!recibido.isEmpty())
			areaRecepcion.setText(recibido);
		return !recibido.isEmpty();
	}
	
	public void EsperarRespuesta(){
		(new Thread(new Runnable() {
			@Override
			public void run() {
				boolean aux = Recibir();
				while(!aux) 
				{
					try{Swap.semRecibir.acquire();}catch(Exception exc){;}
					aux= Recibir();
					Swap.semRecibir.release();
					Thread.yield();
				}
			}
		})).start();
	}

	
	
	void EsperarENQ(){
		(new Thread(new Runnable() {
			@Override
			public void run() {
		   		Swap.recibir = true;
				boolean aux = Recibir();
				while(Swap.recibir&&!aux) 
				{
					try{Swap.semRecibir.acquire();}catch(Exception exc){;}
					aux= Recibir();
					Swap.semRecibir.release();
					Thread.yield();
				}
			}
		})).start();
	}
	
	public void run() {
				JFrame frame = new JFrame();
				Entorno inst = getEntorno();
				Swap._entorno = inst;
				//inst.setEnlace(new NivelEnlace('A','B'));
				frame.getContentPane().add(inst);
				((JComponent)frame.getContentPane()).setPreferredSize(inst.getSize());
				frame.pack();
				frame.setVisible(true);
	}
	
	static public Entorno getEntorno(){
		if(_instancia == null) _instancia=new Entorno();
		return _instancia;
	}
	void setEnlace(IEnlace enlace){
		_enlace = enlace;
	}
	public void informacion(String cadena){
		areaInformacion.setText(cadena);
	}
	public void recepcion(String cadena){
		areaRecepcion.setText(cadena);
	}
	
	private Entorno() {
		super();
		initGUI();
	}
	
	void PedirConfirmacion(ITrama trama){
		informacion("¿Enviar: "+ trama.dibujaTrama()+" ?");
		bOk.setEnabled(true);
	}
	
	private void initGUI() {
		GridBagLayout thisLayout = new GridBagLayout();
			thisLayout.rowWeights = new double[] {0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1};
			thisLayout.rowHeights = new int[] {14, 30, 14, 30, 14, 30, 20};
			thisLayout.columnWeights = new double[] {0.0, 0.0};
			thisLayout.columnWidths = new int[] {582, 140};
			getContentPane().setLayout(thisLayout);
			setSize(new Dimension(750, 160));
			{
				errores = new JCheckBox("¿Errores?");
				getContentPane().add(errores, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				lRecepcion = new JLabel("Area de Recepción");
				getContentPane().add(lRecepcion, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.VERTICAL, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				lEnvio = new JLabel("Area de Envio");
				getContentPane().add(lEnvio, new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.VERTICAL, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				lInformacion = new JLabel("Area de Información");
				getContentPane().add(lInformacion, new GridBagConstraints(0, 4, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.VERTICAL, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				lCreditos = new JLabel("Por: Manuel Cantonero y Mario Corchero");
				getContentPane().add(lCreditos, new GridBagConstraints(0, 6, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.VERTICAL, new Insets(0, 0, 0, 0), 0, 0));
			}
			{
				areaRecepcion = new JTextField();
				getContentPane().add(areaRecepcion, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
				areaRecepcion.setEnabled(false);
			}
			{
				areaInformacion = new JTextField();
				getContentPane().add(areaInformacion, new GridBagConstraints(0, 5, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
				areaInformacion.setEnabled(false);
			}
			{
				areaEnvio = new JTextField(); 
				getContentPane().add(areaEnvio, new GridBagConstraints(0, 3, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
	        // Se crea el botón y se mete en la ventana
	        bConfigurar = new JButton("Fisico");
	        getContentPane().add(bConfigurar, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(0, 0, 0, 0), 0, 0));
	        bEnviar = new JButton("Enviar");
	        getContentPane().add(bEnviar, new GridBagConstraints(1, 3, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
	        bEnviar.setEnabled(false);
	        bConectar = new JButton("Conectar");
	        bConectar.setEnabled(false);
	        getContentPane().add(bConectar, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
	        bOk = new JButton("Ok");
	        getContentPane().add(bOk, new GridBagConstraints(1, 5, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
	        bOk.setEnabled(false);

	        //Clase auxiliar
	        class AccionFisico implements Runnable, ActionListener{

				@Override
				public void run() {
					try{
						bConfigurar.setEnabled(false);  
						Swap.semaforo.acquire();
						Swap._vInicializacion.dispose();//Cerramos la ventana de inicializacion
						setEnlace(new NivelEnlace(Swap._origen));

						informacion("Conectados al fisico con exito");
						bConectar.setEnabled(true);
					}catch(Exception exc){
						informacion("Error al conectarse al fisico");
						bConfigurar.setEnabled(true);
					}
            		EsperarENQ();
            		while(true) Thread.yield();
				}

				@Override
				public void actionPerformed(ActionEvent e) {
            			Thread myHilo = new Thread(new Inicializacion());
            			myHilo.start();        
            			Thread myHilo2 = new Thread(this);
            			myHilo2.start();	
				}
	        	
	        };
	        
	        
	        class AccionConectar implements Runnable, ActionListener{

				@Override
				public void run() { 
					
				  if(bConectar.getText().compareToIgnoreCase("Conectar")==0){
					Swap.recibir = false;
					bConectar.setEnabled(false);
        			try{Swap.semaforo.acquire();}catch(InterruptedException exc){;}//Esperamos a que nos indiquen los parametros del fisico.
        			Swap._vElDestino.dispose();//Cerramos la ventana de inicializacion
            		if(_enlace.Conectar(Swap._destino)){
            			bConectar.setText("Finalizar");
            			informacion("Conectados con el equipo destino");
            			bEnviar.setEnabled(true);
    					bConectar.setEnabled(true);
            		}else{
	            		EsperarENQ();
            			informacion("No se ha podido conectar con el equipo destino.");
    					bConectar.setEnabled(true);
            		}
				  }else{
						bConectar.setEnabled(false);
						if(_enlace.Finalizar()){
		            		EsperarENQ();
							informacion("La comunicacion ha finalizado correctamete.");
							bConectar.setText("Conectar");
							bEnviar.setEnabled(false);
						}else{
							informacion("No se a podido cortar la comunicacion con el otro equipo.");
						}
						bConectar.setEnabled(true);
				  }
				}

				@Override
				public void actionPerformed(ActionEvent e) {
					  if(bConectar.getText().compareToIgnoreCase("Conectar")==0){
            			Thread myHilo = new Thread(new ElDestino());
            			myHilo.start();   
					  }
            			Thread myHilo2 = new Thread(this);
            			myHilo2.start();
				}
	        	
	        };
	        // Se le dice al botón qué tiene que hacer cuando lo pulsemos.
	        bConfigurar.addActionListener(new AccionFisico());
	        
	        bConectar.addActionListener(new AccionConectar());
	        
	        // Se le dice al botón qué tiene que hacer cuando lo pulsemos.
	        bEnviar.addActionListener(new ActionListener()
	        {
	            public void actionPerformed(ActionEvent e)
	            {
	            	if(areaEnvio.getText().isEmpty()){
	            		informacion("Debe introducir el texto a enviar.");
	            		return;
	            	}
	            	String datos = areaEnvio.getText();
	            	ITrama trama;
	                trama = _enlace.construirTrama(datos);
	                areaEnvio.setText(null);
	                PedirConfirmacion(trama);
	            }
	        });
	        bOk.addActionListener(new ActionListener()
	        {
	            public void actionPerformed(ActionEvent e)
	            {
	            	bOk.setEnabled(false);
	            	_enlace.Enviar();
	            	informacion("Trama Enviada.");
	            	EsperarRespuesta();
	            }
	        });
	        
	}
}
