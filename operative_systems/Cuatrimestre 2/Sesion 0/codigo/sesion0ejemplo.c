int main (int argc, char argv[])
{
	int f1;
	//f1 = creat("texto2.txt",0644); //para crearlo
	f1=open("texto2.txt",2); //0 - Lectura, 1 - Escritura, 2 - Lectura/Escritura

	char c;
	read (f1, &c, 1); //Leer de archivo: numbytes_leidos=read(archivo, direc mem, numbytes);
	write(1, &c, 1); //El fichero: (1) es la pantalla, (0) es teclado, (2) es error(por pantalla).
	close(f1);//Cerramos el fichero

	return (0);
}


