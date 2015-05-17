import java.util.concurrent.Semaphore;

import javax.swing.JFrame;


public class Swap {
	static boolean recibir = false;
	static String _puerto;
	static String _bps;
	static String _bDatos;
	static String _paridad;
	static String _bParada;
	static char _origen;
	static char _destino;
	static boolean _salir = false;
	static JFrame _vInicializacion;
	static JFrame _vElDestino;
	static JFrame _vllamada;
	static Entorno _entorno;
	static Semaphore semaforo = new Semaphore(0);
	static Semaphore semConectar = new Semaphore(0);
	static Semaphore semRecibir = new Semaphore(1);
	static boolean aceptar = false;
	static int retardo = 15;//tiempo(en seg) de retardo para el temporizador
	static int numIntentos = 3;//numero de intentos al cumplir el temporizador antes de parar
}
