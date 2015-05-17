import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.concurrent.Semaphore;


public class NivelFisico implements IFisico, Constantes {

	Semaphore semaforo = new Semaphore(1);
	CommPortIdentifier portIdentifier;
	CommPort commPort;
	@Override
	public void Enviar(String cadena) {
		try{_out.write(cadena.getBytes());}catch(IOException exc){System.out.println("Excepcion al enviar datos en el nivel fisico." + exc);}
	}

	@Override
	public String Recibir() {
		try{semaforo.acquire();}catch(Exception exc){;}//Exclusion mutua
        byte[] buffer = new byte[1024];
        int len = -1;
        StringBuffer sb = new StringBuffer();
        try
        {
            while ( ( len = this._in.read(buffer)) > 0)
            {
                sb.append(new String(buffer,0,len));
            }
            return sb.toString();
        }
        catch ( IOException e )
        {
        	System.out.println("Excepcion al recibir datos en el nivel fisico." + e);
            return new String();
        }
        finally{
        	semaforo.release();//Exclusion mutua
        }
	}
	
    public NivelFisico()
    {
        super();
		//System.load("D:\\interconexion\\rxtxSerial.dll");
    }
    
	@Override
	protected void finalize() throws Throwable{
		commPort.close();
	}
    
    public boolean Conectar () throws Exception
    {
  	
        portIdentifier = CommPortIdentifier.getPortIdentifier(Swap._puerto);
        if ( portIdentifier.isCurrentlyOwned() )
        {
            System.out.println("Error: El puerto esta en uso");
            return false;
        }
        else
        {
            commPort = portIdentifier.open(this.getClass().getName(),2000);
            
            if ( commPort instanceof SerialPort )
            {
                SerialPort serialPort = (SerialPort) commPort;
                int paridad = 0; //Obtenemos el bit de paridad(en entero, puesto que lo tenemos en caracter)
                if(Swap._paridad.equals("Ninguno")) paridad = SerialPort.PARITY_NONE;
                else if(Swap._paridad.equals("Espacio")) paridad = SerialPort.PARITY_SPACE;
                else if(Swap._paridad.equals("Marca")) paridad = SerialPort.PARITY_MARK; 
                else if(Swap._paridad.equals("Impar")) paridad = SerialPort.PARITY_ODD; 
                else paridad = SerialPort.PARITY_EVEN; 
                serialPort.setSerialPortParams(Integer.parseInt(Swap._bps),Integer.parseInt(Swap._bDatos),Integer.parseInt(Swap._bParada),paridad);
                //serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,SerialPort.STOPBITS_2,SerialPort.PARITY_NONE);
                
                //Salvamos los streams de salida y entrada del puerto
                _in = serialPort.getInputStream();
                _out = serialPort.getOutputStream();
                while(!Recibir().isEmpty());
                return true;

            }
            else
            {
                System.out.println("Error: Solo se controlan puertos de serie.");
                return false;
            }
        }     
    }
    //Programa principal que muestra todo lo que recibe por el puerto
	public static void main(String[] args) {
		NivelFisico n = new NivelFisico();
		Swap._puerto = "COM1";
		try{n.Conectar();}catch(Exception exc){;}
		String mostrar = new String();
		while(mostrar != "Salir"){
			while(mostrar.isEmpty()){
				mostrar=n.Recibir();
			}
			System.out.println(mostrar);
			mostrar = new String();
		}
	}
    
    private InputStream _in;
    private OutputStream _out;

}
