
/** Escribe una cadena en pantalla
 ** @PRE: La cadena debe de acabar en '\0'
**/
void printf(char *cadena){
	char *copCadena = cadena;
	while(copCadena[0] != '\0') write(1, copCadena++, 1);
}

/** Escribe una cadena en un fichero
 ** @PRE: La cadena debe de acabar en '\0'
**/
void fprintf(const int fd, char* cadena){
	char *copCadena = cadena;
	while(copCadena[0] != '\0') write(fd, copCadena++, 1);
}

/** Lee de fichero
 ** @PRE: el fichero debe estar abierto y debemos disponer de memoria suficiente reservada
**/
int fread(const int fd, char* cadena, const int numbytes){
	return read(fd,cadena, numbytes);
}

/** Escribe de fichero
 ** @PRE: el fichero debe estar abierto y cadena debe tener almenos numbytes
**/
int fwrite(const int fd, char* cadena, const int numbytes){
	return write(fd,cadena, numbytes);
}

/** Copia el fichero llamado origen a destino
 ** @PRE: el fichero origen debe existir.
 ** AVISO: Machaca el fichero destino
**/
int copy(char* origen, char* destino)
{
	int fd1 = open(origen, 0);
	if(fd1 == -1){
		printf("Funcion copy ==> Error: Fichero origen\n");
		return (-1);
	}
	int fd2 = creat(destino,0777);
	if(fd2==-1) {
		printf("Funcion copy ==> Error: Fichero destino\n");
		return (-1);
	}

	char cadena[20];
	int leidos = 1;
	while(leidos){
		leidos = fread(fd1, cadena, 20);
		fwrite(fd2,cadena,leidos);
	}

	close(fd1);
	close(fd2);	

	return (0);
}
