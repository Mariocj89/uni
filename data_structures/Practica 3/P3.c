/*
 ============================================================================
 Name        : P3.c
 Author      : Mario
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef P3_H
#define P3_H
#include "P3.h"
#endif

IST Is;
CABFILEIT Cabis;
CABFILEDT Cabdf;
FILE *Fd;


void TestPrincipal(void)
//Se debe llamar obligatoriamente al principio...
//...del programa principal
{
	unsigned sz=0;
	char c;

    if(sizeof(unsigned int)!= UINTSZ){
        printf("\nModifica la linea:\n");
        printf("#define UINTSZ %d\n ", UINTSZ);
        printf("por la linea:\n");
        printf("#define UINTSZ %d\n",sizeof(unsigned int));
        printf("Introduce un carácter para continuar...");
        scanf("%c",&c);
        exit(1);
    }
    if(sizeof(float)!= FLOATSZ){
        printf("\nModifica la linea:\n");
        printf("#define FLOATSZ %d\n ", FLOATSZ);
        printf("por la linea:\n");
        printf("#define FLOATSZ %d\n",sizeof(float));
        printf("Introduce un carácter para continuar...");
        scanf("%c",&c);
        exit(1);
    }
    sz = sizeof(CABFILEDT);
    if (sz != PAGSZ){
        printf("\n tamaño de página cabecera datos incorrecto %d",sz);
        sz = 0;
    }
    sz = sizeof(REGT);
    if (sz != REGSZ){
        printf("\n tamaño de tipo registro incorrecto %d",sz);
        sz = 0;
    }
    sz = sizeof(PAGDT);
    if (sz != PAGSZ){
        printf("\n tamaño de página incorrecto %d",sz);
        sz = 0;
    }
    sz = sizeof(CABFILEIT);
    if (sz != PAGSZ){
        printf("\n tamaño de cabecera índice incorrecto %d",sz);
        sz = 0;
    }
    sz = sizeof(PAGIT);
    if (sz != PAGSZ){
        printf("\n tamaño de página índice incorrecto %d",sz);
        sz = 0;
    }
    if (sz == 0) {
    	printf("\nPulsa una tecla para continuar...");
        printf("Introduce un carácter para continuar...");
        scanf("%c",&c);
    	exit(1);
    }
}

FECHAT TraduceFecha (char *fuente)
{
 char *ptr;
 int offset = 0, i, size;
 char campo[2][3];
 int parte[2];
 FECHAT resul;

 for (i=0;i<2;i++){
        ptr = strchr(fuente+offset, '/');
        size = ptr - (fuente+offset);
        memmove(campo[i],fuente+offset,size);
        campo[i][size] = '\0';
        parte[i] = atoi(campo[i]);
        offset += size+1;
        };
 resul.dia = parte[0];
 resul.mes = parte[1];
 resul.anio = atoi(fuente+offset);
 return resul;
}

char ObtenSgteReg (FILE *fd, REGT *reg)
{
 char *ptr;
 int offset, size, i;
 char linea[255];
 char campo[80];

 if (!fgets(linea,255,fd)) return 0;
 offset = 0;
 for (i=0;i<6;i++){
         ptr = strchr(linea+offset, ';');
         if (ptr) size = ptr - (linea+offset);
         else size=strlen(linea+offset)-1;
         memmove(campo,linea+offset,size);
         campo[size] = '\0';
         offset += size + 1;
         switch (i){
                case 0 : strcpy(reg->codcli, campo);break;
                case 1 : reg->idpedido = atoi(campo);break;
                case 2 : strcpy(reg->nombre, campo);break;
                case 3 : strcpy (reg->ciudad, campo);break;
                case 4 : reg->fecha = TraduceFecha(campo);break;
                case 5 : reg->importe = atof (campo);break;
                }
         }
 return EXITO;
}

//*********** FUNCIONES PARA EL TRATAMIENTO BITVECTOR
void ClearAllBitvector (unsigned char *bitv, unsigned numbits)
//inicializa a ceros el bitvector que se pasa como párametro
{
    memset(bitv,0x0,BYTES_BITVECTOR(numbits));
}

void SetAllBitvector(unsigned char * bitv, unsigned numbits)
//Pone todos los bits a 1, los bits restantes (si los hay) los deja a 0
{
	int rbits;
	unsigned char mask;
	memset(bitv,UNOCHAR,BYTES_BITVECTOR(numbits));
	rbits =  numbits % BYTESZ;
	if (rbits != 0)
    {
        mask = UNOCHAR << (BYTESZ - rbits);
        bitv[EN_BYTE(numbits - 1)] = mask;
    }
}

void ActivaBit(unsigned char *bitv, unsigned numbits, unsigned bit)
// Activa el bit i-esimo del bitvector. El parámetro bit es un contador
// basado en 0
{
	if (numbits <= bit) return; //bit fuera del rango
	bitv[EN_BYTE(bit)] |= MASCARA_BYTE(bit);
}

void DesactivaBit(unsigned char *bitv, unsigned numbits, unsigned bit)
// Desactiva el bit del bitvector. El parámetro bit es un contador
// basado en 0.
{
 unsigned char mask;;

	if (numbits <= bit) return; //bit fuera del rango
	mask = MASCARA_BYTE(bit);
	mask = ~mask;
	bitv[EN_BYTE(bit)] &= mask;
}

unsigned char ValorBit(unsigned char *bitv, unsigned numbits, unsigned bit)
//Retorna el valor del bit indicado
{
		if (numbits <= bit) return ERRFUERADERANGO; //bit fuera del rango
		if (bitv[EN_BYTE(bit)] & MASCARA_BYTE(bit)) return 1;
		return 0;
}

char EsBitActivo (unsigned char *bitv, unsigned numbits, unsigned bit)
// Esta funci¢n nos indica si el bit en bitv se encuentra activo o no.
// bit es un contador basado en 0.
{

	if (numbits <= bit) return ERRFUERADERANGO; //bit fuera del rango
	return (bitv[EN_BYTE(bit)] & MASCARA_BYTE(bit));
}

unsigned PrimerBitNoActivo (unsigned char *bitv, unsigned numbits)
// Retorna la posición del primer bit en bitvector que se encuentre a 0.
{
 unsigned i;
 unsigned char b=0;

 //Buscamos el primer byte con algún bit a cero
 for(i=0;i<BYTES_BITVECTOR(numbits) && bitv[i]==UNOCHAR;i++);

 //Si todos estan a 1 retornamos numbits
 if(i==BYTES_BITVECTOR(numbits)) return numbits; //Todos activos

 //El byte en que nos encontramos tiene algún bit a cero, lo buscamos
//Si el bit más significativo está a cero, su complemento tiene dicho bit a 1
//por tanto su valor es mayor o igual a 128...
 b = ~bitv[i];
 if (b >= 128) return (i*BYTESZ);
 if (b >= 64) return (1 + i*BYTESZ);
 if (b >= 32) return (2 + i*BYTESZ);
 if (b >= 16) return (3 + i*BYTESZ);
 if (b >= 8) return (4 + i*BYTESZ);
 if (b >= 4) return (5 + i*BYTESZ);
 if (b >= 2) return (6 + i*BYTESZ);
 return (7 + i*BYTESZ);
}

unsigned PrimerBitActivo (unsigned char *bitv, unsigned numbits)
// Retorna la posici¢n del primer bit en bitvector que se encuentre a 1.
{
 unsigned i;

 for(i=0;i<BYTES_BITVECTOR(numbits) && bitv[i]==0;i++);
 if(i==BYTES_BITVECTOR(numbits)) return numbits; //Todos inactivos
 if (bitv[i]>= 128) return (i*BYTESZ);
 if (bitv[i]>= 64) return (1 + i*BYTESZ);
 if (bitv[i]>= 32) return (2 + i*BYTESZ);
 if (bitv[i]>= 16) return (3 + i*BYTESZ);
 if (bitv[i]>= 8) return (4 + i*BYTESZ);
 if (bitv[i]>= 4) return (5 + i*BYTESZ);
 if (bitv[i]>= 2) return (6 + i*BYTESZ);
 return (7 + i*BYTESZ);
}

unsigned NBAChar(unsigned char c)
//Cuenta el número de bits activos en un byte
{
	unsigned char B[3]={0x55,0x33,0x0F}; //Números mágicos
	unsigned char S[3] = {1,2,4};//Potencias de 2
	unsigned result = c;

	result = ((result >> S[0]) & B[0]) + (result & B[0]);
	result = ((result >> S[1]) & B[1]) + (result & B[1]);
	result = ((result >> S[2]) & B[2]) + (result & B[2]);
	return result;
}

unsigned NumeroBitsActivos (unsigned char *bitv, unsigned numbits)
// Retorna el número de bits activos en el bitvector.
{
 unsigned i,n = 0;

 for (i=0;i<BYTES_BITVECTOR(numbits);i++) //Para cada byte
    n += NBAChar(bitv[i]); //Cuenta los bits activos
 return n;
}

//****************FUNCIONES BÁSICAS DE I/O
char EscribePagina (void *pag, long pgsz, unsigned pagid, FILE *fd)
//escribe una página en un fichero; el tamaño de la página y su
//identificación (offset) se pasan también como parámetros

{
 unsigned long byte_offset, byte_offset_eof;

 byte_offset  = pagid;
 byte_offset *= pgsz;
 fseek(fd,0L,SEEK_END);
 byte_offset_eof = ftell(fd);
 if (byte_offset>byte_offset_eof){
		printf("Byte_offset incorrecto\n");
		exit(1);
		}
 fseek (fd, byte_offset, SEEK_SET);
 fwrite(pag,pgsz,1,fd);
 return EXITO;
}


char LeePagina (void *pagina, long pg_sz, unsigned pagid, FILE *fd)
//lee una página del fichero de datos; el identificador de la página y su
//tamaño se psan como parámetros
{
 unsigned long byte_offset, byte_offset_eof;

 byte_offset  = pagid;
 byte_offset *= pg_sz;
 fseek(fd,0L,SEEK_END);
 byte_offset_eof = ftell(fd);
 if (byte_offset>=byte_offset_eof){
		printf("Byte_offset incorrecto\n");
		exit(1);
		}
 fseek (fd, byte_offset, SEEK_SET);
 fread(pagina,pg_sz,1,fd);
 return EXITO;
}


void CreaFichero (const char *filename, void *pag, long pgsz)
//crea un fichero y lo inicializa añadiéndole la página cabecera que
//se pasa como parámetro
{
	 FILE   *fd;

	 fd = fopen(filename,"wb");
	 fwrite (pag,pgsz, 1, fd);
	 fclose (fd);
}

//**********FUNCIONES DE CONVERSIÓN Y TRATAMIENTO DE TRANSACCIONES
char ObtenSgteTr(FILE *fd, char *trcode, REGT *reg)
{
 char *ptr;
 int offset, size, i;
 char linea[255]; // Linea del fichero texto
 char campo[80];

 memset(reg,0x0,REGSZ);
 if (!fgets(linea,255,fd)) return FRACASO;
 sscanf(linea,"%c;",trcode);
 //En función del tipo de trans, actuamos
 switch(*trcode){
     case 'a':
     	offset = 2;
 		for (i=0;i<6;i++){
         	ptr = strchr(linea+offset, ';');
         	if (ptr) size = ptr - (linea+offset);
         	else size=strlen(linea+offset)-1;
         	memmove(campo,linea+offset,size);
         	campo[size] = '\0';
         	offset += size + 1;
         	switch (i){
                case 0 : strcpy(reg->codcli, campo);break;
                case 1 : reg->idpedido = atoi(campo);break;
                case 2 : strcpy(reg->nombre, campo);break;
                case 3 : strcpy (reg->ciudad, campo);break;
                case 4 : reg->fecha = TraduceFecha(campo);break;
                case 5 : reg->importe = atof (campo);break;
                }
         }
     	break;
     case 's':
     case 'b':
         sscanf(linea,"%c;%d",trcode,&(reg->idpedido));
         break;
     }
 return EXITO;
}
char *RegistroAString(REGT reg)
{
// Toma un registro y convierte sus datos a un formato visible
// incluyendolo en una cadena de caracteres
 char *linea;

 linea = (char *) malloc (255);
 sprintf(linea,"%.5s;%d;%s;%s;%d/%d/%d;%.4f",reg.codcli,\
        reg.idpedido,reg.nombre,reg.ciudad,reg.fecha.dia,\
        reg.fecha.mes,reg.fecha.anio,reg.importe);
 return linea;
}

void ProcesaTrans(void)
{
    FILE *ftr, *fl;
    char trcode=0x0;
    REGT reg;
    char res;
    unsigned count[3]={0,0,0}; //Contador transacciones

 	fl = fopen(NOMFICH_LOG,"at");

 	AperturaSistema();

    ftr = fopen(NOMFICH_TRA,"rt");
    printf("\nProcesando transacciones");
    fprintf(fl,"------------------INICIO PROCESO TRANSACCIONES--------------\n");
    while (ObtenSgteTr(ftr, &trcode,&reg)){
        switch(trcode){
            case 'a':
                res =  InsertaRegistro(reg);
            	switch (res){
					case ERRINDICEEXHAUSTO :
						fprintf(fl,"Indice lleno\n");
						break;
					case ERRARCHIVOEXHAUSTO :
						fprintf(fl,"Archivo lleno\n");
						break;
					case ERRCLAVEDUPLICADA :
						fprintf(fl,"Clave duplicada %d\n",reg.idpedido);
						break;
					default :
						fprintf(fl,"Se insertó el registro con clave %d\n",reg.idpedido);
						count[0]++;
            	}
                break;
            case 'b':
                res = BorraRegistro(reg.idpedido);
                if (res == FRACASO)
						fprintf(fl,"Clave inexistente, borrado fallido %d\n",reg.idpedido);
				else {
						fprintf(fl,"Se borró el registro con clave %d\n",reg.idpedido);
						count[1]++;
				}
                break;
            case 's':
            	res = BuscaRegistro(reg.idpedido, &reg);
                if (res == FRACASO)
						fprintf(fl,"Clave inexistente, búsqueda fallida %d\n",reg.idpedido);
				else {
						fprintf(fl,"Se localó el registro con clave %d: %s\n",reg.idpedido,RegistroAString(reg));
						count[2]++;
				}
                break;
            };
    }
    printf("\nFin de proceso.");
    fprintf(fl,"\nSe han realizado un total de %d transacciones con éxito:\n",count[0]+count[1]+count[2]);
    fprintf(fl,"\n%d inserciones, %d borrados y %d búsquedas\n",count[0],count[1],count[2]);
    fprintf(fl,"------------------ FIN PROCESO TRANSACCIONES --------------\n");
    fclose(ftr);
    CierreSistema();
 	fprintf(fl,"Sistema cerrado\n");
 	fclose(fl);
}

 // Funciones implementadas como ejercicio

//Crea el fichero de datos del sistema inizializando y usando la cabecera en memoria(Cabfd)
void CreaFicheroSistema (void){
	//iniciamos los atributos de la cabecera del archivo de datos(contenida en memoria principal)
	strcpy(Cabdf.nombrefichero, NOMFICH_DAT);
	Cabdf.ocupacion = 1; //empieza ocupando 1 pagina, la cabecera.
	Cabdf.pagid = 0;
	Cabdf.pagsz = PAGSZ;
	Cabdf.regsz = REGSZ;
	ClearAllBitvector(Cabdf.bitvector,MAXNUMPAGDATOS);//marcamos todas las paginas a 0(vacio)
	ActivaBit(Cabdf.bitvector,NUMREGPAG,0);//la pagina cabecera se marca como llena.
	CreaFichero(NOMFICH_DAT,&Cabdf,PAGSZ);

	/* Tratado por otras funciones:
	//inicializamos la cabecera del indice almacenada en memoria
	Cabis.entsz = ENTRADAINDICETSZ;
	strcpy(Cabis.nombrefichero,NOMFICH_NDX);
	Cabis.ocupacion = 1; //la ocupacion del fichero es 1, la cabecera(aunque fisicamente no existe aun)
	Cabis.numentradas = 0; //empieza ocupando 1 pagina, la cabecera.
	Cabis.pagsz = PAGINDTSZ;*/

}

//Inserta una entrada en el Indice de forma ordenada
char InsertaEntradaISOrden(ENTRADAINDICET ent){
	if(MAXENTRADASIND <= Cabis.numentradas)
		{
		if(DEBUG) printf("ERROR INDICE EXAUSTO EN InsertaEntradaISOrden\n");
		return ERRINDICEEXHAUSTO;//No caben mas entradas en el indice
		}
	int i = Cabis.numentradas;
	while((i > 0) && (ent.idpedido > Is[i-1].idpedido)){
		Is[i] = Is[i-1];
		i--;
	}
	Is[i] = ent;
	Cabis.numentradas++;
	if(DEBUG) printf("Se ha insertado una entrada en el indice\n");
	return EXITO;
}

//Reconstruye el indice simple desde el fichero de datos
//PRE: indice simple vacio
void ReconstruyeIS(void){
	fread(&Cabdf,PAGSZ,1,Fd);
	PAGDT pagd;
	ENTRADAINDICET ent;

	//inicializamos los atributos de la cabecera del indice
	Cabis.entsz = ENTRADAINDICETSZ;
	strcpy(Cabis.nombrefichero,NOMFICH_NDX);
	Cabis.numentradas = 0;
	Cabis.ocupacion = 1; //1, la cabecera
	Cabis.pagid = 0;
	Cabis.pagsz = PAGINDTSZ;

	//Insertamos todas las entradas en el indice
	int i, j;
	for(i = 1; i < Cabdf.ocupacion; i++){
		fread(&pagd,PAGSZ,1,Fd);
		for(j = 0; j < pagd.ocupacion; j++){
			if(EsBitActivo(pagd.bitvector,NUMREGPAG,j)){
				ent.idpedido = pagd.reg[j].idpedido;
				ent.pagid = pagd.pagid;
				ent.posreg = j;
				InsertaEntradaISOrden(ent);
				Cabis.numentradas++;
			}
		}
	}
}

//Esta funcion inserta 1 entrada al final del inidice
char InsertaEntradaISFinal(ENTRADAINDICET ent){
	if(Cabis.numentradas >= MAXENTRADASIND) return ERRINDICEEXHAUSTO;
	Is[Cabis.numentradas] = ent;
	Cabis.numentradas++;
	if(DEBUG) printf("Se ha insertado una entrada en el indice\n");
	return EXITO;
}

//Recupera el IS de archivo
void CargaIS(FILE *fi){

	fread(&Cabis,PAGINDTSZ,1,fi);
	int i, j;
	PAGIT pagi;
	for(i = 1; i < Cabis.ocupacion; i++){
		fread(&pagi,PAGSZ,1,fi);
		for(j = 0; j < pagi.ocupacion; j++){
			InsertaEntradaISFinal(pagi.entrada[j]);
		}
	}
	remove(NOMFICH_NDX);//borramos para que los archivos no queden desactualizados.
}

//Inicia el sistema, preparando el IndiceSimple, las cabeceras en memoria y el flujo del fichero de datos
char AperturaSistema(void){
	//Abrimos el archivo de datos
	Fd = fopen(NOMFICH_DAT,"r+b");
	if(Fd == NULL){
		if(DEBUG) printf("No existe pedidos.dat, se procede a crearlo");
		CreaFicheroSistema();
		Fd = fopen(NOMFICH_DAT,"r+b");
	}

	//recuperamos el indice simple(de archivo o reconstruyendolo)
	FILE *fi = fopen(NOMFICH_NDX,"rb");
	if (fi != NULL) CargaIS(fi);
	else ReconstruyeIS();
	if(DEBUG) printf("El sistema se ha abierto correctamente");
	return EXITO;
}

//Realiza la busqueda(binaria) de un dato en el indice. (Devuelve la posicion por parametro)
char BuscaEnIndice (unsigned clave, unsigned *pos){
	int izquierda = 0, derecha = Cabis.numentradas-1, encontrado = 0;
	while (! encontrado && izquierda <= derecha)
	{
		*pos = (izquierda + derecha) / 2;
	    if (clave < Is[*pos].idpedido)
	    	derecha = *pos - 1;
	    else if (clave > Is[*pos].idpedido)
	    	izquierda = *pos + 1;
	    else
	        encontrado = 1;
	}
	if(encontrado) return EXITO;
	else return FRACASO;

}

//Busca y devuelve un registro(por parametro)
char BuscaRegistro(unsigned clave, REGT *reg){
	unsigned pos = 0;
	char resultado = BuscaEnIndice(clave, &pos);
	if(resultado == FRACASO) return FRACASO;

	unsigned npag = Is[pos].pagid;
	unsigned nreg = Is[pos].posreg;

	PAGDT pag;
	fseek(Fd,npag*PAGSZ,SEEK_SET);
	fread(&pag,PAGSZ,1,Fd);

	*reg = pag.reg[nreg];

	return EXITO;
}

//Busca un hueco para un registro en el fichero
char LocalizaDestinoRegistro (PAGDT *pag, unsigned *posreg){
/*	fseek(Fd,0,SEEK_SET);
	fread(&Cabdf,PAGSZ,1,Fd);*/
	int npag;
	npag = PrimerBitNoActivo(Cabdf.bitvector,MAXNUMPAGDATOS);
	if(DEBUG) printf("Primera pagina no llena: %d\n", npag);
	if(npag == MAXNUMPAGDATOS) return FRACASO;
	if(npag == Cabdf.ocupacion){ //Crear una nueva pagina
		pag->ocupacion = 0;
		pag->pagid = Cabdf.ocupacion;
		ClearAllBitvector(pag->bitvector,NUMREGPAG);
		Cabdf.ocupacion++;
		fwrite(pag,PAGSZ,1,Fd);
		/*//actualizamos la cabecera
		fseek(Fd,0,SEEK_SET);
		fwrite(&Cabdf,PAGSZ,1,Fd);*/
		*posreg = 0;
		if(DEBUG) printf("Se ha creado una nueva pagina\n");
	}
	else{ //Tenemos un hueco en una pagina
		fseek(Fd,npag*PAGSZ,SEEK_SET);
		fread(pag,PAGSZ,1,Fd);
		*posreg = PrimerBitNoActivo(pag->bitvector,NUMREGPAG);
		if(DEBUG) printf("hueco en la posicion %d\n", *posreg);
	}

	return EXITO;
}

//Inserta una entrada en una posicion desplazando las necesarias
char InsertaEntradaISPos(ENTRADAINDICET ent, unsigned pos){
	if(pos == NUMMAXREG) return ERRFUERADERANGO;
	if(MAXENTRADASIND <= Cabis.numentradas) return ERRINDICEEXHAUSTO;
	int i = Cabis.numentradas;
	while(i > pos){
		Is[i] = Is[i-1];
		i--;
	}
	Is[i] = ent;
	Cabis.numentradas++;
	if(DEBUG) printf("Se ha insertado una entrada en el indice\n");
	return EXITO;
}

//Inserta un registro y su  clave en el indice
char InsertaRegistro (REGT reg){
	//Comprobamos si la clave ya existe
	unsigned posind;
	char error = BuscaEnIndice(reg.idpedido,&posind);
	if(error == EXITO)
		{
		if(DEBUG) printf("Error de clave duplicada al Insertar Registro");
		return ERRCLAVEDUPLICADA;
		}
	//if(error == ERRFUERADERANGO) return ERRFUERADERANGO;

	//Insertamos el registro
	PAGDT pag;
	unsigned posreg;
	if(LocalizaDestinoRegistro(&pag,&posreg) == FRACASO)
	{
		if(DEBUG) printf("Error Archivo Exausto al Insertar Registro\n");
		return ERRARCHIVOEXHAUSTO;
	}
	pag.reg[posreg] = reg;
	pag.ocupacion++;
	ActivaBit(pag.bitvector,NUMREGPAG,posreg);


	//Comprobamos si se ha llenado la pagina
	if(PrimerBitNoActivo(pag.bitvector,NUMREGPAG) == NUMREGPAG){//Si esta llena
		/*fseek(Fd,0,SEEK_SET);
		fread(&Cabdf,PAGSZ,1,Fd);*/
		ActivaBit(Cabdf.bitvector,MAXNUMPAGDATOS,pag.pagid); //Marcamos la pagina llena
		if(DEBUG) printf("Se ha llenado una pagina\n");
		//Actualizamos la cabecera
		/*fseek(Fd,0,SEEK_SET);
		fwrite(&Cabdf,PAGSZ,1,Fd);*/
		if(DEBUG) printf("Pagina %d llena.\n", pag.pagid);
	}

	//Añadimos la clave al indice
	ENTRADAINDICET ent;
	ent.idpedido = reg.idpedido;
	ent.pagid = pag.pagid;
	ent.posreg = posreg;
	if(InsertaEntradaISPos(ent,posind) == ERRINDICEEXHAUSTO)
		{
		if(DEBUG) printf("Error indice exausto al Insertar Registro\n");
		return ERRINDICEEXHAUSTO;
		}
	if(DEBUG) printf("Se ha insertado el registro %d correctamente\n", reg.idpedido);

	//Escribimos la pagina
	fseek(Fd,pag.pagid*PAGSZ,SEEK_SET);
	fwrite(&pag,PAGSZ,1,Fd);

	return EXITO;
}

//Elimina una entrada del indice Simple
char EliminaEntradaIS(unsigned pos){
	if(pos >= Cabis.numentradas)
		{
		if(DEBUG) printf("Error fuera de tango en EliminaEntradaIS\n");
		return ERRFUERADERANGO;
		}
	int i = Cabis.numentradas-1; //se situa en el último elemento
	for(i = pos; i < Cabis.numentradas-1; i++){
		Is[i] = Is[i+1];
	}
	Cabis.numentradas--;
	if(DEBUG) printf("Se ha eliminado una entrada del IS\n");
	return EXITO;
}

//Borra un registro del sistema
char BorraRegistro(unsigned clave){
	unsigned int pos;
	if(BuscaEnIndice(clave,&pos) == FRACASO) return FRACASO;//no se ha encontrado el elemento

	PAGDT pag;
	fseek(Fd,Is[pos].pagid*PAGSZ,SEEK_SET);
	fread(&pag,PAGSZ,1,Fd);

	//marcamos el registro como libre(no ocupado=0)
	DesactivaBit(pag.bitvector,NUMREGPAG,Is[pos].posreg);

	//actualizamos la pagina
	fseek(Fd,Is[pos].pagid*PAGSZ,SEEK_SET);
	fwrite(&pag,PAGSZ,1,Fd);

	EliminaEntradaIS(pos);
	if(DEBUG) printf("Se ha eliminado un registro\n");
	return EXITO;
}

//Guarda el indice simple en un archivo
char SalvaguardaIS(char* filename){
	CreaFichero(NOMFICH_NDX,&Cabis,PAGINDTSZ);
	FILE *fi = fopen(NOMFICH_NDX,"r+b");
	fseek(fi,PAGINDTSZ,SEEK_SET); //nos colocamos tras la cabecera
	if(fi == NULL) return FRACASO;
	PAGIT pag;
	pag.pagid = 0;
	int i = 0, j;
	while(i < Cabis.numentradas){
		pag.pagid++;
		pag.ocupacion = 0;
		for(j = 0; j < NUMENTRADASPAG && i < Cabis.numentradas; j++, i++){
			pag.entrada[j] = Is[i];
			pag.ocupacion++;
		}
		fwrite(&pag,PAGINDTSZ,1,fi);//salvamos la pagina
		Cabis.ocupacion++;
	}
	//actualizamos la cabecera
	fseek(fi,0,SEEK_SET);
	fwrite(&Cabis,PAGINDTSZ,1,fi);
	fclose(fi);
	return EXITO;
}

//Realiza las operaciones necesarias antes de terminar la aplicacion
void CierreSistema(void){
	//Actualizamos la cabecera del archivo de datos
	fseek(Fd,0,SEEK_SET);
	fwrite(&Cabdf,PAGSZ,1,Fd);

	SalvaguardaIS(NOMFICH_NDX);

	if(Fd != NULL)
	{
		fclose(Fd);
		Fd = NULL;
	}
}

//Genera el fichero pedidos.dat a partir de un fichero fuente
char GeneraPedidosDat(void){

	//Iniciamos el sistema
	AperturaSistema();
	FILE * ftext = fopen(NOMFICH_FTE,"rw");
	if(ftext == NULL) return FRACASO;
	REGT reg;
	while(ObtenSgteReg(ftext,&reg) && (InsertaRegistro(reg) == EXITO)){;}
	if(DEBUG) printf("Se han generado %d paginas en el fichero pedidos.dat y %d paginas en el fichero pedidos.ndx. \nRegistros insertados: %d \n",Cabdf.ocupacion,Cabis.ocupacion,Cabis.numentradas);


	return EXITO;
}

void PruebasManuales(){
	REGT reg;
	//Pruebas manuales
	strcpy(reg.ciudad,"zafra");
	strcpy(reg.codcli,"00102");
	strcpy(reg.nombre,"mario");
	reg.idpedido = 5;
	reg.importe = 500;
	FECHAT fech;
	fech.dia = 1;
	fech.anio = 3;
	fech.mes = 2;
	reg.fecha = fech;
	//InsertaRegistro(reg);
	int j = 0;
	for (j = 0; j < 1101; j++){
	reg.idpedido = j;
	InsertaRegistro(reg);}
	//fin pruebas manuales
	printf("Se han generado %d paginas en el fichero pedidos.dat y %d paginas en el fichero pedidos.ndx. \nRegistros insertados: %d \n",Cabdf.ocupacion,Cabis.ocupacion,Cabis.numentradas);

}

//Debemos de tener Fd abierto
char GenerarPedidosTxt(){
	FILE *ftxt = fopen("salida.txt","wt");
	if(ftxt == NULL) return FRACASO;
	if(Fd == NULL)
	{
		Fd = fopen(NOMFICH_DAT,"r+b");
		fread(&Cabdf,PAGSZ,1,Fd);
	}//Si esta abierto, suponemos que la cabecera esta actualizada

	PAGDT pag;
	int i, j;
	for(i = 1; i < Cabdf.ocupacion;i++)
	{
		fseek(Fd,i*PAGSZ,SEEK_SET);
		fread(&pag,PAGSZ,1,Fd);
		if(DEBUG) printf("Procesando(Dat a TXT) pagina: %d\n", pag.pagid);
		for(j = 0; j < pag.ocupacion; j++)	if(EsBitActivo(pag.bitvector,NUMREGPAG,j))
		{
			if(DEBUG) printf("Se escribe(a TXT) el registro: %d\n",pag.reg[j].idpedido);
			fprintf(ftxt,"%s\n",RegistroAString(pag.reg[j]));
		}
	}

	printf("Generado salida.txt");
	fclose(ftxt);
	return EXITO;
}

int main(void) {
	//borramos los posibles rastros de antiguas sesiones
	remove(NOMFICH_DAT);
	remove(NOMFICH_NDX);
	remove(NOMFICH_LOG);
	GeneraPedidosDat();
	GenerarPedidosTxt();

	CierreSistema();
	//ProcesaTrans();
	return EXIT_SUCCESS;
}
