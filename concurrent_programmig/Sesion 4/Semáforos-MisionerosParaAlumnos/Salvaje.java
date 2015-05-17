import java.util.concurrent.Semaphore;

public class Salvaje implements Runnable {

	int id;
	Olla olla;
	Semaphore mutex;
	Semaphore vacia;
	Semaphore llena;
	
	public Salvaje (int _id, Olla _olla, Semaphore _mutex, Semaphore _vacia, Semaphore _llena) {
		id = _id;
		olla = _olla;
		mutex = _mutex;
		vacia = _vacia;
		llena = _llena;
	}
	
	public void run () {
		while (true) {

		}
	}
}
