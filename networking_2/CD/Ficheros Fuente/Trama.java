
public class Trama implements Constantes, ITrama {
	public Trama(char origen, char destino, String datos, char numTrama, char verif){
		_datos = datos;
		_origen = origen;
		_destino = destino;
		_verif = verif;
		_numTrama = numTrama;
		_long = (char)datos.length();
		while (_datos.length() < 7)
			_datos = _datos + '#';
		_bce = calcularBCE();
	}
	public Trama(char origen, char destino, String datos, char numTrama, char verif, int numErrores){
		_datos = datos;
		_origen = origen;
		_destino = destino;
		_verif = verif;
		_numTrama = numTrama;
		_long = (char)datos.length();
		_bce = calcularBCE();
		for(int i=0;i<numErrores;i++)
			_datos=GeneradorErrores.IntroducirErrorAleatorio(_datos);
		while (_datos.length() < 7)
			_datos = _datos + '#';
	}
	
	public Trama(String trama){
		_destino = trama.charAt(2);
		_origen = trama.charAt(3);
		_numTrama = trama.charAt(4);
		_verif = trama.charAt(5);
		_long = trama.charAt(6);
		_datos = trama.substring(7, 7+Integer.valueOf(_long));
		_bce = trama.charAt(trama.length()-1);
	}
	
	private char calcularBCE(){
		char res = 0;
		for(int i = 0; i < _long; i++){
			res^=_datos.charAt(i);
		}
		if(res == 0x00) res = 0x01;
		return res;
	}
	
	public String toString(){
		return String.valueOf(SYN)+String.valueOf(STX)+String.valueOf(_destino)+String.valueOf(_origen)+String.valueOf(_numTrama)+String.valueOf(_verif)+String.valueOf(_long)+_datos+String.valueOf(_bce);
	}
	public String dibujaTrama(){
		return "| "+"SYN"+" | "+"STX"+" | "+_destino+" | "+_origen+" | "+
			_numTrama+" | "+_verif+" | "+_long+"("+(int)_long+")"+" | "+_datos+" | "+_bce+" |";	
	}
	
	public String getDatos(){
		return _datos.substring(0,_long);
	}
	
	public char getDestino(){
		return _destino;
	}
	
	public char getNumTrama(){
		return _numTrama;
	}
	
	public char getVerificacion(){
		return _verif;
	}
	
	public void setVerificacion(char newVerif){
		_verif=newVerif;
	}
	
	public boolean comprobarError(){
		//System.out.println("BCE: "+ calcularBCE()+ " | BCE trama: "+ _bce);
		if(calcularBCE() == _bce) return false;
		return true;
	}
	
	private char _long;
	private char _verif;
	private String _datos;
	private char _origen;
	private char _destino;
	private char _numTrama;
	private char _bce;
}
