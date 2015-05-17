/* Misioneros v1.0
 * 
 * Una tribu de Caníbales come Misioneros que se cocinan en una Olla. En esta olla caben un
 * número limitado de Misioneros y cuando los Salvajes han terminado con ellos se lo hacen
 * saber a un Cocinero que rellena la Olla. Mientras el Cocinero está rellenando la olla
 * ningún Salvaje puede comer.
 * 
 */

import java.util.concurrent.*;

public class Principal {

	final static int NUM_SALVAJES = 15;
	
	public static void main(String[] args) {

		Olla olla = new Olla();
		
		Semaphore mutex = new Semaphore(1);
		Semaphore vacia = new Semaphore(1); // Inicialmente vacia
		Semaphore llena = new Semaphore(0); 
		
		Cocinero c = new Cocinero(olla, mutex, vacia, llena);
		Thread t = new Thread(c);
		t.start();
		
		for (int i = 0; i < NUM_SALVAJES; i++) {
			new Thread(new Salvaje(i, olla, mutex, vacia, llena)).start();
		}
	}
}
