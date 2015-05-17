#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>


int main(int argc, char **argv){
	if(argc != 2){
		printf("Error: Numero incorrecto de parametros.\n");
		return -1;
	}
	
	if(argv[1][0] != '/'){
		printf("Error: Debe introducir una ruta absoluta.\n");
		return -2;
	}
	//Comprobar si se tiene acceso
	if(access(argv[1],F_OK)!=0){
		printf("Error: No se tiene acceso al directorio.\n");
		return -1;
	}

	//Comprobamos que es un directorio
	struct stat buff;
	stat(argv[1],&buff);
	if(!S_ISDIR(buff.st_mode)){
		printf("Error: Se ha pasado un archivo en lugar de un directorio.\n");
		return -1;
	}

	return funcion(argv[1]);

}

int funcion(char* ruta){

	DIR *aux;
	aux = opendir(ruta);
	struct dirent *entrada;
	char cadena[100];
	struct stat buff;
	while(entrada = readdir(aux)){
		if(strcmp(entrada->d_name,".") && strcmp(entrada->d_name,"..")){

			strcpy(cadena, ruta);
			strcat(cadena,"/");
			strcat(cadena,entrada->d_name);
			stat(cadena,&buff);
			if(S_ISDIR(buff.st_mode)){// es un directorio
				printf("Directorio: %s\n",cadena);
				funcion(cadena);
				printf("Fin de: %s\n",cadena);
			}
			else{
				printf("Fichero: %s\n",cadena);
			}

		}
	}	
	return 0;
}
