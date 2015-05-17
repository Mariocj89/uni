import java.util.Random;
public class GeneradorErrores {
	static public String IntroducirError(String datos){
		return '@' + datos.substring(1, datos.length());
	}
	static public String IntroducirErrorAleatorio(String datos){
		Random ram = new Random();
		int posicion = ram.nextInt(datos.length());
		return datos.substring(0, posicion) + '@' + datos.substring(posicion+1, datos.length());
	}
}
