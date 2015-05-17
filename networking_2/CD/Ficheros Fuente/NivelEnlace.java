import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;
import javax.swing.Timer;

public class NivelEnlace implements IEnlace, Constantes {

	public NivelEnlace(char origen) throws Exception{
		_fisico.Conectar();
		_origen = origen;
	}
	public ITrama construirTrama(String datos){
		_tramaEnvio = new Trama(_origen,_destino,datos,_contador,_verificacion);
		return _tramaEnvio;
	}
	@Override
	public void Enviar() {
		intentos = 0;
		if(Swap._entorno.errores.isSelected() && _tramaEnvio instanceof Trama){//Si es una trama de datos y esta seleccionado enviar con errores, introducimos errores
			String datos = new String(((Trama)_tramaEnvio).getDatos());
			ITrama aux = new  Trama(_origen,_destino,datos,_contador,_verificacion,1);
			_fisico.Enviar(aux.toString());
		}
		else{
			_fisico.Enviar(_tramaEnvio.toString());
		}
		if (_tramaEnvio instanceof Trama) {
			_confirmada = false;
			temporizador.start();//Activamos el temporizador por si algun metodo lo necesita
		}
		Swap._entorno.permitirEnviar(false);
	}
	@Override
	public String Recibir() {
		String cadena = _fisico.Recibir();
		if(cadena.isEmpty()) return new String();
		temporizador.stop();
		if(cadena.charAt(1) == STX){//si es trama de datos
			String aux = RecibirDatos(cadena);
			Swap._entorno.bConectar.setEnabled(false);
			return aux;
		}
		//si es de control
		return RecibirControl(cadena);
	}
	
	private String RecibirControl(String cadena){
		//TODO
		//System.out.println("Recibimos: "+cadena);	
		TramaControl recibida = new TramaControl(cadena);
		if(recibida.getDestino() != _origen) {Swap._entorno.EsperarRespuesta();return new String("Recibida una trama que no nos pertenece. (€ a "+recibida.getDestino()+" )");}
		switch (recibida.getCTRL()) {
		case ENQ:	if(Swap._entorno.bConectar.getText() == "Conectar")	{
						AceptarConexion(recibida.getOrigen());
						return ("Recibida trama de establecimiento.");
					}
					else{
						Swap._entorno.EsperarRespuesta();
						return ("Se ha recibido una trama de establecimiento que no procede.");
					}
		case EOT:	if(Swap._entorno.bConectar.getText() == "Conectar")	{
						Swap._entorno.EsperarRespuesta();
						return ("Se ha recibido una trama de desconexion que no procede.");
					}
					else{
						AceptarFinalizar();
						return ("Recibida trama de fin de comunicacion");
					}
		case ACK:	{Swap._entorno.EsperarRespuesta();return ("Recibida trama de aceptacion no esperada");}
		case NAK:	{Swap._entorno.EsperarRespuesta();return ("Recibida trama de rechazo no esperada");}
		case DC1:	if(_confirmada) return "Confirmacion no esperada";
					if(recibida.getNVerificacion() == incChar(_contador)){//Confirma la trama enviada
						_contador=incChar(_contador);
						_confirmada=true;
						Swap._entorno.permitirEnviar(true);
						return ("Trama enviada confirmada.");
					}
					else{
						if(recibida.getNVerificacion() == _contador){//Confirma que no ha recibido bien la trama enviada
							Swap._entorno.PedirConfirmacion(_tramaEnvio);
							Swap._entorno.permitirEnviar(false);
							return ("La trama enviada llegó mal.");
						}
						else{
							return "Error: numero de confirmacion no esperado.";
						}
					}
		default:
			break;
		}
		return cadena;
	}
	
	private String RecibirDatos(String cadena){
		String resultado = "";
		Trama recibida = new Trama(cadena);
		if(recibida.getDestino() != _origen) {Swap._entorno.EsperarRespuesta();return new String("Recibida una trama que no nos pertenece. (€ a "+recibida.getDestino()+" )");}
		

		if(recibida.getNumTrama() != _verificacion)
			{Swap._entorno.EsperarRespuesta();return new String("Numero de trama no esperado. Recibido: " + recibida.getNumTrama() + " esperado: "+ _verificacion);}
		
		//Parte de confirmar la trama enviada anteriormente
		if(!_confirmada){ //Esta confirmando
			if(recibida.getVerificacion() == _contador){//Ha llegado mal
				//Volvemos a enviar la trama
				resultado = "La trama anterior llego mal.\nRecibido:";
				Swap._entorno.PedirConfirmacion(_tramaEnvio);
			}
			else{
				if(recibida.getVerificacion() == incChar(_contador)){//Ha llegado bien
					_contador=incChar(_contador);
					_confirmada = true;
					Swap._entorno.permitirEnviar(true);
					resultado = "Trama anterior confirmada.\nRecibido: ";
				}
				else //numero no esperado de confirmacion
					resultado = "Error: numero de confirmacion no esperado.\nRecibido: ";
			}
		}
		else{//no esta confirmando
			Swap._entorno.permitirEnviar(true);
		}

		if(recibida.comprobarError()) {//Los datos Nos ha llegado con errores
			if(_confirmada){//Si tenemos una trama de datos pendiente por enviar, no podemos enviar una trama de control
				_tramaEnvio=new TramaControl(DC1, _destino, _origen, recibida.getNumTrama());
				Swap._entorno.PedirConfirmacion(_tramaEnvio);
				Swap._entorno.permitirEnviar(true);//Permitimos que envie una trama diferente(sino siempre manda la trama mal.)
				return resultado + (new String("Trama recibida con errores: "+recibida.dibujaTrama()));
			}
		}
		else{//Los datos nos han llegado bien			
			buffer.append(recibida.getDatos() + '\n');//añadimos los datos al buffer(resultado final)
			_verificacion=recibida.getNumTrama();
			_verificacion=incChar(_verificacion);
			if(_confirmada){//Si tenemos una trama de datos pendiente por enviar, no podemos enviar una trama de control
				_tramaEnvio=new TramaControl(DC1, _destino, _origen, _verificacion );
				Swap._entorno.PedirConfirmacion(_tramaEnvio);
			}
			else{//si tenemos que reenviar la trama de datos actual, actualizamos el campo de verificacion
				_tramaEnvio.setVerificacion(_verificacion);
				Swap._entorno.PedirConfirmacion(_tramaEnvio);
				Swap._entorno.permitirEnviar(true);//Permitimos que envie una trama diferente(sino siempre manda la trama mal.)
			}
		}
		return resultado + recibida.dibujaTrama();
	}

	
	@Override
	public boolean Conectar(char destino) {
		intentos = 0;
		temporizador.start();
		try{Swap.semRecibir.acquire();}catch(Exception exc){;}
		_destino = destino;
		_tramaEnvio=new TramaControl(ENQ, _destino, _origen);
		Swap._entorno.PedirConfirmacion(_tramaEnvio);
		String cadena=_fisico.Recibir();
		while(cadena.isEmpty()){ 
			if(intentos>Swap.numIntentos) return false;
			cadena=_fisico.Recibir();
		}

		temporizador.stop();
		Swap.semRecibir.release();
		TramaControl trama = new TramaControl(cadena);
		switch(trama.getCTRL()){
		case ACK: buffer = new StringBuffer(); return true;
		case NAK: return false;
		default: Swap._entorno.informacion("Error, recibida trama no esperada: "+trama.dibujaTrama()); return false;
		}	
	}
	
	private void AceptarConexion(char equipo){
		_destino = equipo;
		(new Thread(new Llamada("Llamada entrante de: "+_destino))).start();
		try{Swap.semConectar.acquire();}catch(InterruptedException exc){;}
		Swap._vllamada.dispose();
		if(Swap.aceptar){
			_tramaEnvio = new TramaControl(ACK, _destino, _origen); 
			Swap._entorno.informacion("Conectados con el equipo "+_destino);
			Swap._entorno.bConectar.setText("Finalizar");
			Swap._entorno.bConectar.setEnabled(false);
			buffer = new StringBuffer(); 
		}
		else{
			Swap._entorno.EsperarRespuesta();
			_tramaEnvio = new TramaControl(NAK, _destino, _origen); 
			Swap._entorno.informacion("Rechaza la conexion con el equipo "+_destino);
		}
		Swap._entorno.PedirConfirmacion(_tramaEnvio);	
	}
	
	@Override
	public boolean Finalizar() {
		if(!_confirmada){
			Swap._entorno.informacion("Hay datos pendientes de confirmar");
			return false;
		}
		intentos = 0;
		temporizador.start();
		try{Swap.semRecibir.acquire();}catch(Exception exc){;}
		_tramaEnvio = new TramaControl(EOT, _destino, _origen); 
		Swap._entorno.PedirConfirmacion(_tramaEnvio);
		
		String cadena=_fisico.Recibir();
		while(cadena.isEmpty()){
			if(intentos>Swap.numIntentos) return false;
			cadena=_fisico.Recibir();
		}
		temporizador.stop();
		Swap.semRecibir.release();
		TramaControl trama = new TramaControl(cadena);
		switch(trama.getCTRL()){
		case ACK: Reset(); JOptionPane.showMessageDialog(Swap._entorno, buffer.toString(),"Total Recibido:",JOptionPane.INFORMATION_MESSAGE); return true;
		case NAK: return false;
		default: Swap._entorno.informacion("Error, recibida trama no esperada: "+trama.dibujaTrama()); return false;
		}
	}	
	
	public void AceptarFinalizar(){
		Llamada my_llamada = new Llamada("El equipo: "+_destino+" quiere colgar.");
		my_llamada.DesactivarRechazo();
		(new Thread(my_llamada)).start();
		try{Swap.semConectar.acquire();}catch(InterruptedException exc){;}
		Swap._vllamada.dispose();
		if(Swap.aceptar){
			_tramaEnvio = new TramaControl(ACK, _destino, _origen); 
			Swap._entorno.informacion("Llamada finalizada");
			Swap._entorno.permitirEnviar(false);
			Swap._entorno.bConectar.setText("Conectar");
			Reset();
			JOptionPane.showMessageDialog(Swap._entorno, buffer.toString(),"Total Recibido:",JOptionPane.INFORMATION_MESSAGE);
		}
		else{
			Swap._entorno.EsperarRespuesta();
			_tramaEnvio = new TramaControl(NAK, _destino, _origen); 
			Swap._entorno.informacion("Rechazado fin de comunicacion de "+_destino);
		}
		Swap._entorno.PedirConfirmacion(_tramaEnvio);	
	}
	
	char _contador = '1'; //Contador prox trama a enviar
	char _verificacion = '1'; //trama que debemos confirmar(o volver a pedir)
	boolean _confirmada = true; //booleano para saber si se ha confirmado la ultima trama que enviamos.
	private char _origen; //ETD actual
	private char _destino; //ETD destino
	private ITrama _tramaEnvio; //Proxima/actual trama a enviar
	private IFisico _fisico = new NivelFisico(); //NivelFisico
	private StringBuffer buffer;
	private int intentos= 0;//intentos consumidos
	
	private Timer temporizador = new Timer(Swap.retardo*1000,new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent arg0) {
				if(intentos< Swap.numIntentos){
					intentos++;
					temporizador.stop();
					Swap._entorno.recepcion("Ha vencido el temporizador. Intentos restantes: " + (Swap.numIntentos-intentos));
					Swap._entorno.PedirConfirmacion(_tramaEnvio);
				}
				else{
					intentos++;
					Swap.semRecibir.release();
					//deja de esperar recibir
				}
		}
	});
	
	
	
	private char incChar(char numero){
		char copia = numero;
		copia++;
		if(copia == ':') copia = '1';
		return copia;
	}
	
	private void Reset(){
		_contador = '1';
		_verificacion = '1';
		_confirmada = true;
	}
}
