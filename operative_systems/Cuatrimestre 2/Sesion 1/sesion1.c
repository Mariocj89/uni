#include "auxiliar.c"

int main(int argc, char* argv[]){
	int pausa=0;
	if(argc==1){
		printf("Error, debe introducir el fichero fuente por parametro.\n");
		return -1;
	}
	if(argc>3)
		printf("Aviso: Solo se tendran en cuenta los 2 primero parametros.\n");
	if(argc==3){
		if(argv[2][0] == '-' && argv[2][1] == 'm'){
			printf("Activada la visualizacion pantalla a pantalla.\n");
			pausa=1;
		}
		else
			printf("Aviso: el segundo parametro carece de sentido(distinto de -m).\n");
	}
	int fd1=open(argv[1],0);
	if(fd1 == -1){
		printf("Error: Fichero origen\n");
		return (-1);
	}

	char cadena[81];
	char auxiliar = 0;
	int leidos = 1, ncaracteres, numlineas=0;
	while(leidos){
		ncaracteres=0;
		auxiliar = 0;
		leidos = 1;
		numlineas = 0;
		while(leidos !=0 && numlineas < 25){
			leidos = fread(fd1, &auxiliar, 1);
			write(1,&auxiliar,1);
			ncaracteres++;
			if(auxiliar == '\n'){
				numlineas++;
				ncaracteres=0;
			}
			if(ncaracteres == 80) numlineas++;
		}
		cadena[ncaracteres] = '\0';
		if(pausa){
			read(0, &auxiliar, 1);
			if(auxiliar == 'q'){
				close(fd1);
				return 0;
			}
		}
	}

	close(fd1);
	return 0;
}
