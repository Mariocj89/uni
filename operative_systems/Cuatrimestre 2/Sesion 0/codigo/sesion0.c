#include  "auxiliar.c"

int main (int argc, char* argv[])
{
	if(argc != 3) {
		printf("Sintaxis: ");printf(argv[0]);printf(" <origen> <destino>\n");
		return(-1);
	}
	/*
	int fd1 = open(argv[1], 0);
	if(fd1 == -1){
		printf("Error: Fichero origen\n");
		return (-1);
	}
	int fd2 = creat(argv[2],0777);
	if(fd2==-1) {
		printf("Error: Fichero destino\n");
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

	return (0);*/
	return copy(argv[1],argv[2]);
}
