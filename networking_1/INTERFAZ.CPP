

#include "interfaz.h"

Interfaz::Interfaz():
envio(12,8,620,100,"                            Area de Envio:"),
recepcion(12,112,620,100,"                           Area de Recepcion:"),
informacion(12,216,620,150, "                           Area de Informacion:"),
puerto(12,372,200,100,"  Parametros del puerto:"),
control(222,372,200,100,"  Circuitos de Control:"),
opciones(432,372,200,100,"       Opciones:")
{
	//setfillstyle(0,0);
	PintarControl();
	informacion.EscribirMensaje("Inicio del programa.");
	fichero = NULL;
}

void Interfaz::Informacion(char mensaje[]){
	informacion.EscribirMensaje(mensaje);
}

void Interfaz::Envio(char caracter){
	envio.EscribirChar(caracter);
}

void Interfaz::Recepcion(char caracter){
	recepcion.EscribirChar(caracter);
}

void Interfaz::PintarControl(){
	opciones.EscribirMensaje("F5: Cambiar RTS");
	opciones.EscribirMensaje("F6: Cambiar DTR");
	opciones.EscribirMensaje("F4: Enviar Correo");
	opciones.EscribirMensaje("F9: Estadistica correo");
	opciones.EscribirMensaje("ESC: Fin de aplicacion");

}

void Interfaz::PintarPuertos(char nom_puerto[5], int &bps, int &bits, char paridad[9], int &parada){
	char cadena[50];

	sprintf(cadena, "Puerto: %s",nom_puerto);
	puerto.EscribirMensaje(cadena);

	sprintf(cadena, "bps: %d",bps);
	puerto.EscribirMensaje(cadena);

	sprintf(cadena, "Bits datos: %d",bits);
	puerto.EscribirMensaje(cadena);

	sprintf(cadena, "Paridad: %s",paridad);
	puerto.EscribirMensaje(cadena);

	sprintf(cadena, "Bits parada: %d",parada);
	puerto.EscribirMensaje(cadena);
}


void Interfaz::MostrarEstados(TCom &Puerto){

	control.EscribirMensaje(" ");
	char cadena[20];
	sprintf(cadena,"DTR: %i", Puerto.EstadoDTR());
	control.EscribirMensaje(cadena);
	sprintf(cadena,"RTS: %i", Puerto.EstadoRTS());
	control.EscribirMensaje(cadena);
	sprintf(cadena,"CTS: %i", Puerto.EstadoCTS());
	control.EscribirMensaje(cadena);
	sprintf(cadena,"DSR: %i", Puerto.EstadoDSR());
	control.EscribirMensaje(cadena);
	sprintf(cadena,"RI: %i", Puerto.EstadoRI());
	control.EscribirMensaje(cadena);
	sprintf(cadena,"DCD: %i", Puerto.EstadoDCD());
	control.EscribirMensaje(cadena);

	for(int i =0 ;i<2;i++)
		control.EscribirMensaje(" ");



}

void Interfaz::Iniciar(){
	int gdriver = DETECT, gmode;
	initgraph(&gdriver,&gmode,"C:\\ARCHIV~1\\BC3.1\\BGI");
	setfillstyle(0,0);
	//bar(0,0,200,200);
}

int Interfaz::EnviarFichero(TCom &Puerto,int &salir, int &contador,char filename[]){
	//  	informacion.EscribirMensaje("Introduzca el nombre del fichero: ");
	//	char filename[50] = "enviar.txt";
	char car;
	/*	int enviar = 0;
	int contador = 0;
	while(!enviar)
	{
	if(kbhit())
	{
	car = getch();
	if(car == 8)
	{
	informacion.EscribirChar(8);
	contador--;
	}
	if(car == 27)
	{
	informacion.EscribirChar('\n');
	Informacion("Cancelado el envio de archivo");
	return;
	}
	if(car >=32 && car<= 122)
	{
	informacion.EscribirChar(car);
	filename[contador] = car;
	contador++;
	}
	if(car == 13)
	{
	filename[contador] = '\0';
	informacion.EscribirChar('\n');
	enviar = 1;

	}


	}
	} */
	char dirfile[50] = ".\\Pendie~1\\";
	strcat(dirfile,filename);
	FILE *fp = fopen(dirfile,"rb");
	Informacion("Enviando fichero...");
	if(fp == NULL) {
		informacion.EscribirMensaje("No se ha podido abrir el fichero");
		return -1;
	}
	Puerto<<126;
	Puerto<<filename;
	Puerto<<125;
	char envio, salida, recepcion;
	while(!feof(fp))
	{
		if(kbhit() && getch() == 27){//Si pulsa escape mientras enviamos un archivo
				fclose(fp);
				Puerto<<126;
				Informacion("Se ha cancelado el envio de un fichero.");
				return 1;
		}
		envio = fgetc(fp);
		if(!feof(fp)){
			while(Puerto.OcupacionBufferSalida() != 0) ;
			Puerto<<envio;
			//Vemos si hay caracteres para leer
			if(Puerto.OcupacionBufferEntrada() !=0)
			{
				if(fichero != NULL){

					if(Puerto.OcupacionBufferEntrada() != 0)
					{
						Puerto>>recepcion;
						if(recepcion != 126) fputc(recepcion,fichero);
						else { fclose(fichero); fichero= NULL;}
					}
				}
				else{
					Puerto>>salida;
					if(salida == 127) MostrarEstados(Puerto);
					else if(salida == 126) RecibirFichero(Puerto,salir, contador);
					else Recepcion(salida);
				}
			}
		}
	}
	fclose(fp);
	Puerto<<126;
	Informacion("Se ha enviado el fichero satisfactoriamente.");
	return 0;

}

void Interfaz::RecibirFichero(TCom &Puerto, int &salir, int &contador){
	Informacion("Se esta recibiendo un fichero");
	char filename[50] = "recibido.txt";
	int contadorname = 0;
	char car=0;
	while(car != 125&&contadorname<20){
		if(Puerto.OcupacionBufferEntrada() != 0){
			Puerto>>car;
			filename[contadorname] = car;
			contadorname++;
		}
	}
	filename[contadorname-1] = '\0';
	fichero = fopen(filename,"wb");
	if(fichero==NULL) {
		Informacion("No se a podido escribir el archivo");
		return;
	}
	char salida, recepcion;
	int separadores = 0; //contador de separadores # encontrados
	char cdestino[50]; //Futura carpeta contenedora del archivo
	int c_cd = 0;
	while(recepcion!=126){
		if(Puerto.OcupacionBufferEntrada() != 0)
		{
			Puerto>>recepcion;
			if(separadores <= 5){
				if(recepcion != '#'){
					if(separadores == 0){} //lee POringen
					if(separadores == 1){} //lee PDestino
					if(separadores == 2){ //lee CDestino
						cdestino[c_cd++] = recepcion;
					}
					if(separadores == 3){cdestino[c_cd] = '\0';} //lee rings
					if(separadores == 4){} //lee Volumen
					if(separadores == 5){separadores++;} //lee modo
				}
				else {
					separadores++;
				}

			}
			if(recepcion != 126) fputc(recepcion,fichero);

		}
		if(kbhit()){
			salida = getch();
			//Puerto<<salida;
			 Enviar(Puerto,salir,salida,contador);
		}
	}
	if(fichero!=NULL) fclose(fichero);
	fichero = NULL;


	/*char cadena[50] = "dir ";
	strcat(cadena,cdestino);
	strcat(cadena," >> log.txt");
	sprintf(cadena2, "result: %d\0", system(cadena));
	Informacion(cadena2);

	//crea directorio
	strcpy(cadena,"mkdir ");
	strcat(cadena,cdestino);
	strcat(cadena," >> log.txt");
	system(cadena);   */

	//mover el archivo
	char cadena[50];
	strcpy(cadena,"copy ");
	strcat(cadena, filename);
	strcat(cadena, " ");
	strcat(cadena, cdestino);
	strcat(cadena, "\\");
	strcat(cadena, filename);
	strcat(cadena," >> log.txt");
	//informacion.EscribirMensaje(cadena);
	system(cadena);
	strcpy(cadena,"del ");
	strcat(cadena, filename);
	strcat(cadena, " >> log.txt");
	system(cadena);



	Informacion("Fichero recibido satifactoriamente.");


}

void Interfaz::Enviar(TCom &Puerto, int &salir, char car, int &contador){
	char cadena[100]; //Cadena en la que escribimos para mandar los datos juntos
	if(car == 27) salir = 1; //Pulsa esc
	if((car>='0' && car<='9')||(car>='a' && car<='z')  //Introduce una
		||(car>='A' && car<='Z') || car == ' ' ){    //letra o numero
			cadena[contador] = car;
			Envio(car);
			contador++;
	}
	if(car==8) //pulsa backspace
	{
		Envio(8);
		/*gotoxy(wherex()-1,wherey());
		printf(" ");
		gotoxy(wherex()-1,wherey());*/
		contador--;
	}
	if(car==13)   //Pulsa Enter
	{
		cadena[contador] = '\n';
		Envio('\n');
		cadena[contador+1]='\0';
		contador=0;
		Puerto<<cadena;
		Informacion("Se ha enviado un mensaje.");
	}
	if(car == 63) //Pulsa F5
	{
		if(Puerto.EstadoRTS()) Puerto.DesactivarRTS();
		else Puerto.ActivarRTS();
		MostrarEstados(Puerto);
		Informacion("Se ha cambiado el puerto RTS");
		Puerto<<127;
	}
	if(car == 64)     //Pulsa F6
	{
		if(Puerto.EstadoDTR()) Puerto.DesactivarDTR();
		else Puerto.ActivarDTR();
		MostrarEstados(Puerto);
		Informacion("Se ha cambiado el puerto DTR");
		Puerto<<127;
	}
	if(car == 62)	//Pulsa F4
	{
		EnviarCorreo(Puerto,salir, contador);
	}

}

void Interfaz::EnviarCorreo(TCom &Puerto, int &salir, int &contador){
	struct ffblk archivo;
	int done, exiit=0;
	char auxiliar[50], auxiliar2[50];
	//system("cd Pendie~1 >> log.txt");
	done = findfirst(".\\Pendie~1\\*.*",&archivo,0);
	//system("cd .. >> log.txt");
	while (!done&& !exiit)
	{
		if(kbhit() && getch() == 27){//pulsa escape
			Informacion("Se ha cancelado el envio de los demas ficheros.");
			return;
		}
		exiit = EnviarFichero(Puerto,salir, contador,archivo.ff_name);
		informacion.EscribirMensaje(archivo.ff_name);
		if(exiit == 0){
			strcpy(auxiliar2,"copy Pendie~1\\");
			strcat(auxiliar2, archivo.ff_name);
			strcpy(auxiliar," Enviado\\");
			strcat(auxiliar,archivo.ff_name);
			strcat(auxiliar2,auxiliar);
			strcat(auxiliar2," >> log.txt");
			//informacion.EscribirMensaje(auxiliar2);
			//system("pwd");
			system(auxiliar2);
			strcpy(auxiliar2,"del Pendie~1\\");
			strcat(auxiliar2, archivo.ff_name);
			strcat(auxiliar2, " >> log.txt");
			system(auxiliar2);
		}
		// system("cd Pendie~1 >> log.txt");
		done = findnext(&archivo);
		// system("cd ..  >> log.txt");


	}
	if(exiit == 0)
		informacion.EscribirMensaje("Se han enviado todos los archivos pendientes.");
	if(exiit == 1)
		informacion.EscribirMensaje("Envio de ficheros cancelado por el usuario.");
	if(exiit == -1)
        	informacion.EscribirMensaje("Se ha cancelado el envio de ficheros, puesto que alguno/s no se pueden abrir correctamente");
}