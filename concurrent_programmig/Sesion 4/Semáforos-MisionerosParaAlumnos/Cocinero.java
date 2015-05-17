import java.util.concurrent.*;

public class Cocinero implements Runnable {

	Olla olla;
	Semaphore mutex;
	Semaphore vacia;
	Semaphore llena;
	
	public Cocinero (Olla olla, Semaphore mutex, Semaphore vacia, Semaphore llena) {
		this.olla = olla;
		this.mutex = mutex;
		this.vacia = vacia;
		this.llena = llena;
	}
	
	public void run () {
		while (true) {

		}
	}
}
