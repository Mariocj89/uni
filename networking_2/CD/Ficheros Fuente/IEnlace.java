
public interface IEnlace {
	//Establece conexion con el otro terminal
	public boolean Conectar(char destino);
	//Finaliza la conexion
	public boolean Finalizar();
	//Reccibe una trama y la muestra por pantalla
	public String Recibir();
	//Construye la siguiente trama a enviar
	public ITrama construirTrama(String datos);
	//Envia la ultima trama almacenada
	public void Enviar();
}
