public class TramaControl implements Constantes, ITrama{
	public TramaControl(char CTRL, char destino, char origen, char nVerficiacion){
		_CTRL = CTRL;
		_destino = destino;
		_origen = origen;
		_nVerificacion = nVerficiacion;
	}
	
	public TramaControl(char CTRL, char destino, char origen){
		_CTRL = CTRL;
		_destino = destino;
		_origen = origen;
		_nVerificacion = '0';
	}
	
	public TramaControl(String cadena){
		_CTRL = cadena.charAt(1);
		_destino = cadena.charAt(2);
		_origen = cadena.charAt(3);
		_nVerificacion = cadena.charAt(4);
	}
	
	public String toString(){
		return String.valueOf(SYN)+String.valueOf(_CTRL)+String.valueOf(_destino)+String.valueOf(_origen)+String.valueOf(_nVerificacion);
	}
	
	public String dibujaTrama(){
		StringBuffer buff = new StringBuffer("| "+"SYN"+" | ");
		switch(_CTRL){
		case ACK: buff.append("ACK");break;
		case NAK: buff.append("NAK");break;
		case EOT: buff.append("EOT");break;
		case DC1: buff.append("DC1");break;
		case ENQ: buff.append("ENQ");break;
		default: buff.append(_CTRL);break;			
		}
		buff.append(" | "+_destino+" | "+_origen+" | "+ _nVerificacion+" |");
		return buff.toString();
	}

	public char getCTRL(){
		return _CTRL;
	}
	
	public char getDestino(){
		return _destino;
	}
	
	public char getOrigen(){
		return _origen;
	}
	
	public char getNVerificacion(){
		return _nVerificacion;
	}
	
	public void setVerificacion(char newVerif){
		_nVerificacion=newVerif;
	}
	
	private char _CTRL;
	private char _destino;
	private char _origen;
	private char _nVerificacion = 0;
}
