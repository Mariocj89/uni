#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>


char* my_fread(int fin, char* cadena, int numbytes, char delimitador)
{
	int i = 0;
	char leido = 'X';
	while(i < numbytes-1 && leido != delimitador && leido != '\0')
	{
		read(fin,&leido,1);
		cadena[i] = leido;
		i++;
	}
	cadena[i-1] = '\0';
	return cadena;
}

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		printf("Error: debe pasar al menos 1 parametro.\n");
		return -1;
	}	
	//abrimos los ficheros de salida y entrada
	int fout = open("salida.txt",2);
	if(fout == 0) fout = creat("salida.txt",0777);
	int fin = open(argv[1],0);
	//leemos el numero de lineas
	char c_numlineas;
	read(fin,&c_numlineas,1);
	int numlineas = c_numlineas - '0';
	read(fin,&c_numlineas,1);//leemos para pasar el \n
	
	int i;

	for(i=0;i<numlineas;i++){
	    int x = fork();
	    if(x==0){
		char cadena1[20];
		char cadena2[20];
		int numIguales=0;
		char *c_directorio = my_fread(fin,cadena1,20,'\n');
		
		char *extension = my_fread(fin,cadena2,20,'\n');
		DIR *directorio = opendir(c_directorio);
		if(directorio != NULL){
			struct dirent *entrada;
			entrada = readdir(directorio);
			int contador = 0;
			char cadaux[10];
			while(entrada!=NULL)
			{
				if(strcmp(entrada->d_name,".")&&strcmp(entrada->d_name,".."))
				{
					//metemos en una cadena la extension
					int v = 0;
					int j;
					for(j= strlen(entrada->d_name) -strlen(extension);j<=strlen(entrada->d_name);j++)
					{
						cadaux[v] = entrada->d_name[j];
						v++;
					}
					if(strcmp(cadaux,extension)==0)//el fichero tiene la misma extension
						numIguales++;
				}
				entrada = readdir(directorio);
			}
		}
		else{
			printf("No se ha conseguido abrir el directorio %s!\n",c_directorio);
		}
		exit(numIguales);
	    }
		
	}

	int total = 0,aux;
	for(i=0;i<numlineas;i++){
		wait(&aux);
		total +=(aux>>8);
	}
	printf("Encontrados %d ficheros con las extensiones indicadas en los directorios indicados. \n",total);

	return 0;

}

//Recibe por parametro la direccion de un fichero de entrada donde hay un numero al principio que indica el numero de pares de lineas
//Cada par de lineas se compone de: 1 linea indicando el directorio en el que trabajar. 2. extension a buscar
//El programa buscara en el directorio el numero de ficheros que coinciden con esa extension.