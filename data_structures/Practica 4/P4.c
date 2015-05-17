/*
 ============================================================================
 Name        : P4.c
 Author      : Mario
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "P4.h"

//Funciones implementadas en el archivo de utilidades

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
// Interpreta la siguiente l¡nea del fichero fd, almacenando el contenido
// en el par metro reg. La funci¢n retorna un valor positivo si se hizo
// correctamente y un valor 0 en caso en que no hubiera m s l¡neas por
// interpretar.
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

char ObtenSgteTr(FILE *fd, char *trcode, REGT *reg, RANGOT *rango)
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
     case 'b':
         sscanf(linea,"%c;%d",trcode,&(reg->idpedido));
         break;
     case 'r':
         sscanf(linea,"%c;%d;%d",trcode,&(rango->min),&(rango->max));
         break;

     }
 return EXITO;
}

void GeneraArbolBMas (void)
{
	REGT reg;
	FILE *ff, *fl;
	char res;
	unsigned exitos = 0,fracasos = 0;

 printf("Generando arbol B+");
 //Abrimos fichero de log
 fl = fopen(NOMFICH_LOG,"wt");

 AperturaSistema();
 fprintf(fl,"Apertura del sistema\n");
 //Abrimos fichero fuente
 ff= fopen(NOMFICH_FTE,"rt");
 //Procesamos los registros
 while (ObtenSgteReg (ff, &reg)){
 	 	printf(".");
 	 	//printf("Se va a insertar el registro numero %d.\n", exitos+fracasos);
		res = InsertaReg (reg);
		if (res == EXITO) exitos++;
		else {
			fracasos++;
			fprintf(fl,"Clave duplicada %d\n",reg.idpedido);
		}
 }
 fprintf(fl,"Si insertaron con éxito %d registros\n",exitos);
 fprintf(fl,"Se produjeron %d fracasos\n",fracasos);
 CierreSistema();
 fprintf(fl,"Cierre del sistema\n");
 // Y cerramos fuente y log
 fclose(ff);
 fclose(fl);
 }


void ProcesaTrans(void)
{
    FILE *ftr, *fl, *fs;
    char trcode=0x0;
    REGT reg;
    RANGOT rango;
    char res;
    unsigned count[3]={0,0,0}; //Contador transacciones

        fl = fopen(NOMFICH_LOG,"at");

        AperturaSistema();

    ftr = fopen(NOMFICH_TRA,"rt");
    printf("\nProcesando transacciones");
    fprintf(fl,"------------------INICIO PROCESO TRANSACCIONES--------------\n");
    while (ObtenSgteTr(ftr, &trcode,&reg,&rango)){
        printf(".");
        switch(trcode){
            case 'a':
                res =  InsertaReg(reg);
                if (res == EXITO){
                                        fprintf(fl,"Se insertó el registro con clave %d\n",reg.idpedido);
                                        count[0]++;
                }
                break;
            case 'b':
                res = BuscaReg(reg.idpedido,&reg);
                if (res == FRACASO)
                                                fprintf(fl,"Clave inexistente, búsqueda fallida %d\n",reg.idpedido);
                                else {
                                                fprintf(fl,"Se localizó el registro con clave %d: %s\n",reg.idpedido,RegistroAString(reg));
                                                count[1]++;
                                }
                break;
            case 'r':
                res = BuscaRango(rango.min, rango.max);
                if (res == FRACASO)
                                                fprintf(fl,"Ningún registro en el rango [%d,%d]. Búsqueda fallida\n",rango.min,rango.max);
                                else {
                                        //Hay que procesar los datos del archivo de salida
                                        fs = fopen(NOMFICH_SAL,"rt");
                                        fprintf(fl,"Registros en el rango [%d,%d]:\n",rango.min,rango.max);
                                        while (ObtenSgteReg (fs,&reg))
                                                fprintf(fl,"%s\n",RegistroAString(reg));
                                        fclose(fs);
                                        count[2]++;
                                }
                break;
            } //Fin switch
    }//Fin while
    printf("\nFin de proceso.");
    fprintf(fl,"\nSe han realizado un total de %d transacciones con éxito:\n",count[0]+count[1]+count[2]);
    fprintf(fl,"\n%d inserciones, %d búsquedas exactas y %d búsquedas por rango\n",count[0],count[1],count[2]);
    fprintf(fl,"------------------ FIN PROCESO TRANSACCIONES --------------\n");
    fclose(ftr);
    CierreSistema();
        fprintf(fl,"Sistema cerrado\n");
        fclose(fl);
}

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

// Implementacion Propia:

/** Variables globales*/
CABFILEDT Cabdat;
CABFILEIT Cabind;
PAGIT Raiz;
FILE *Fi, *Fd;

void CreaFicherosSistema (void)
//Preparar pedidos.dat y pedidos.ndx (crear 1 pagina vacia de cada) Machaca si existen.
{
        if(DEBUG) printf("Creados ficheros de sistema.\n");
	PAGDT pagd;
	PAGIT pagi;

	FILE *fd = fopen(NOMFICH_DAT,"wb");
	FILE *fi = fopen(NOMFICH_NDX,"wb");
	if(fd == NULL || fi == NULL) {
		printf("ERROR: No se ha podido crear un archivo.");
		exit(0);
	}

	memset(&Cabdat,0x0,PAGSZ);
	strcpy(Cabdat.nombrefichero,NOMFICH_DAT);
	Cabdat.ocupacion = 2; //Cabecera + pag vacia
//	Cabdat.pagid = 0;
	Cabdat.pagsz = PAGSZ;
	Cabdat.regsz = REGSZ;
	Cabdat.ultima = 1;
	memset(&pagd,0x0,PAGSZ);
//	pagd.anterior = 0;
//	pagd.ocupacion = 0;
	pagd.pagid = 1;
//	pagd.siguiente = 0;

	EscribePagina(&Cabdat,PAGSZ,0,fd);
	EscribePagina(&pagd,PAGSZ,pagd.pagid,fd);

	fclose(fd);

	memset(&Cabind,0x0,PAGISZ);
	strcpy(Cabind.nombrefichero ,NOMFICH_NDX);
	Cabind.ocupacion = 2; //Cabecera + pag vacia
	Cabind.orden = ORDEN;
//	Cabind.pagid = 0;
	Cabind.pagsz = PAGISZ;
	Cabind.raiz = 1;
        EscribePagina(&Cabind, PAGISZ, 0, fi);

	memset(&pagi,0x0,PAGISZ);
	pagi.altura = HOJA;
	pagi.pagid = 1;
	pagi.ocupacion = 0;
	pagi.ap[0] = 1;

	EscribePagina(&pagi,PAGISZ,pagi.pagid,fi);

	fclose(fi);

}

void AperturaSistema(void)
//Abre el sistema y lo deja listo para realizar busquedas
{
	Fd = fopen(NOMFICH_DAT,"r+b");
	if(Fd == NULL) {
		CreaFicherosSistema();
		Fd = fopen(NOMFICH_DAT,"r+b");
	}
	Fi = fopen(NOMFICH_NDX,"r+b");
	if(Fi == NULL){
		//TODO implementar recuperacion de indice a partir del dat
	}

	LeePagina(&Cabdat,PAGSZ,0,Fd);

	LeePagina(&Cabind,PAGISZ,0,Fi);

	if(DEBUG) printf("Obteniendo la raiz de la posicion %d\n", Cabind.raiz);
	fseek(Fi,Cabind.raiz*PAGISZ,SEEK_SET);
	fread(&Raiz,PAGISZ,1,Fi);
	if(DEBUG) printf("Se abre el sistema\n");
}

unsigned ObtenDirDescenso (unsigned idpedido, PAGIT *pag)
//Retorna el identificador de la pagina por la que tenemos que descender para obtener el reg
{
	int pos = 0;
	//buscamos la posicion de la pagina que nos interesa
	while(pos < pag->ocupacion && idpedido >= pag->sep[pos]) pos++;
	//TODO ¿porke peta?if(DEBUG) printf("Obtenida la direccion de descenso: %d\n", pag->ap[pos]);
	return pag ->ap[pos];
}

char ObtenRegDePag (unsigned idpedido, PAGDT *pag, REGT *reg, unsigned *pos)
//Busca y devuelve por parametro(si existe) un registro en una pagina.
{
	*pos = 0;
	//buscamos la posicion del registro que nos interesa
	while((*pos) < pag->ocupacion && idpedido > pag->reg[*pos].idpedido){
	  (*pos)++;
	}
	if((*pos) < pag->ocupacion && idpedido == pag->reg[*pos].idpedido){
		memcpy(reg,&(pag->reg[*pos]),REGSZ);
		if(DEBUG) printf("Obtenido registro de la pagina: %d con id: %d\n", pag->pagid, idpedido);
		return EXITO;
	}
	else{
		//pos ya esta en la posicion correcta.
		if(DEBUG) printf("No se ha podido obtener el registro con id: %d de la pagina. %d\n", idpedido, pag->pagid);
		return FRACASO;
	}
}

char BuscaReg (unsigned idpedido, REGT *reg)
//Busca y devuelve por parametro un registro
{
	PAGIT pind;
	PAGDT pdat;
	pind = Raiz;
	while(pind.altura == INTERNO)
	  LeePagina(&pind,PAGISZ,ObtenDirDescenso(idpedido,&pind),Fi);

	//Obtenemos la pagina de datos en la que se encuentra:
	LeePagina(&pdat,PAGSZ,ObtenDirDescenso(idpedido,&pind),Fd);

	//Sacamos el registro(o la posicion en la que deberia estar[pos])
	unsigned pos;
	if(DEBUG) printf("(BuscaReg)El registro con id: %d se encuentra/deberia en la posicion: %d", idpedido, pos);
	return ObtenRegDePag(idpedido,&pdat,reg,&pos);
}

char InsertaEnPagSec (REGT reg, PAGDT *pag, unsigned pos)
//Inserta un registro en una pagina de datos, devuelve desborde si no cabe
{

	if(pag->ocupacion >= NUMREGPAG) return DESBORDE;
	if(pos > pag->ocupacion) return FRACASO;
	//Movemos todos los registros para crear el hueco
	int i = pag->ocupacion;
	while(i > pos)
	{
		pag->reg[i] = pag->reg[i-1];
		i--;
	}
	//insertamos el registro que queremos
	pag->reg[i] = reg;
	pag->ocupacion++;
	fseek(Fd,pag->pagid * PAGSZ,SEEK_SET);
	fwrite(pag,PAGSZ,1,Fd);

	return EXITO;
}

char DividePagSec (REGT reg, PAGDT *pagd, unsigned pos, unsigned *sep, unsigned *ap)
//Divide una pagin al insertar un registro.
{
	REGT new_vec[NUMREGPAG+1];

	//Movemos todos los registros a nuestro vector auxiliar
	int i = 0;
	while(i < pos)
	{
		new_vec[i] = pagd->reg[i];
		i++;
	}
	new_vec[i] = reg;
	i++;
	while(i < NUMREGPAG+1)
	{
		new_vec[i] = pagd->reg[i-1];
		i++;
	}

	//Preparamos la nueva pagina y vaciamos la antigua
	PAGDT new_pag;
	memset(&new_pag,0x0,PAGSZ);
	new_pag.pagid = Cabdat.ocupacion;
	Cabdat.ocupacion++;

	pagd->ocupacion = 0;

	//Repartimos los registros del vector auxiliar entre las 2 paginas
	i = 0;
	int j = 0;
	while(i <= (NUMREGPAG+1)/2)
	{
		pagd->reg[i] = new_vec[i];
		i++;
		pagd->ocupacion++;
	}
	while(i < NUMREGPAG+1)
	{
		new_pag.reg[j] = new_vec[i];
		i++;
		j++;
		new_pag.ocupacion++;
	}

	//"Arreglamos" los identificadores
	if(pagd->siguiente != 0){
		PAGDT pnext;
		LeePagina(&pnext,PAGSZ,pagd->siguiente,Fd);
		pnext.anterior = new_pag.pagid;
		EscribePagina(&pnext, PAGSZ, pnext.pagid,Fd);
	}
	new_pag.siguiente = pagd->siguiente;
	new_pag.anterior = pagd->pagid;
	pagd->siguiente = new_pag.pagid;

	//SALVAR LAS PAGINA
	EscribePagina(pagd,PAGSZ,pagd->pagid,Fd);
	EscribePagina(&new_pag,PAGSZ,new_pag.pagid,Fd);

	*ap = new_pag.pagid;
	*sep = new_pag.reg[0].idpedido;

	return EXITO;
}

char InsertaEnPagInd (unsigned sep, unsigned ap, PAGIT *pag)
//Inserta una clave en una pagina indice.
{
	//TODO debemos controlar si se intenta insertar un separador que ya existe??
	if(pag->ocupacion >= ORDEN-1) return DESBORDE;
	//Movemos todos los apuntadores y separadores para crear hueco
	int i = pag->ocupacion;
	while(i > 0 && sep < pag->sep[i-1])
	{
		pag->sep[i] = pag->sep[i-1];
		pag->ap[i+1] = pag->ap[i];
		i--;
	}
	//insertamos en la posicion obtenida
	pag->sep[i] = sep;
	pag->ap[i+1] = ap;
	pag->ocupacion++;
	EscribePagina(pag,PAGISZ,pag->pagid,Fi);

	return EXITO;
}

char DividePagInd (unsigned sep, unsigned ap, PAGIT *pagd, unsigned *sepa, unsigned *apa)
//Divide una pagina al insertar un separador.
{
	 unsigned vec_sep[ORDEN];
	 unsigned vec_ap[ORDEN+1];

	//Movemos todos los los apuntadores y separadores a nuestro vector auxiliar
	int i = 0;
	while(sep > pagd->sep[i]&&i<ORDEN)
	{
		vec_sep[i] = pagd->sep[i];
		vec_ap[i] = pagd->ap[i];
		i++;
	}
	vec_ap[i] = pagd->ap[i];//Tenemos que insertar el "hijo" derecho del ultimo separador.
	//Insertamos el separador y el apuntador que nos dan.
	vec_sep[i] = sep;
	vec_ap[i+1] = ap;
	i++;
	while(i < ORDEN)
	{
		vec_sep[i] = pagd->sep[i-1];
		vec_ap[i+1] = pagd->ap[i];
		i++;
	}

	//Preparamos la nueva pagina y vaciamos la antigua
	PAGIT new_pag;
	memset(&new_pag,0x0,PAGISZ);
	new_pag.pagid = Cabind.ocupacion;
	new_pag.altura = pagd->altura;
	Cabind.ocupacion++;
	pagd->ocupacion = 0;


	//Repartimos los registros del vector auxiliar entre las 2 paginas
	i = 0;
	int j = 0;
	while(i < (ORDEN-1)/2)
	{
		pagd->sep[i] = vec_sep[i];
		pagd->ap[i] = vec_ap[i];
		i++;
		pagd->ocupacion++;
	}
	//El separador del "medio" lo devolvemos(por parametro) y añadimos el apuntador derecho del ultimo separador
	*sepa = vec_sep[i];
	pagd->ap[i] = vec_ap[i];
	i++;
	while(i < ORDEN)
	{
		new_pag.sep[j] = vec_sep[i];
		new_pag.ap[j] = vec_ap[i];
		i++;
		j++;
		new_pag.ocupacion++;
	}
	new_pag.ap[j] = vec_ap[i];//Tenems que poner el ultimo apuntador

	//SALVAR LAS PAGINA
	EscribePagina(pagd,PAGISZ,pagd->pagid,Fi);
	EscribePagina(&new_pag,PAGISZ,new_pag.pagid,Fi);

	*apa = new_pag.pagid;

	return EXITO;
}

char InsertaRegR (REGT reg, PAGIT *pagact, unsigned *sepa, unsigned *apa)
{
	REGT regaux;
	unsigned dir, pos;
	unsigned sep, ap;
	char ret;
	if(pagact->altura == HOJA){
		dir = ObtenDirDescenso(reg.idpedido,pagact);
		PAGDT pagdt;
		if(DEBUG) printf("Leyendo pagina secuencia: %d\n",dir);
		LeePagina(&pagdt,PAGSZ,dir, Fd);
		if(ObtenRegDePag(reg.idpedido,&pagdt,&regaux,&pos) == EXITO) return ERRCLAVEDUPLICADA;
		if(InsertaEnPagSec(reg,&pagdt,pos) == EXITO) return EXITO;
		DividePagSec(reg, &pagdt, pos, &sep, &ap);
		if( InsertaEnPagInd( sep,ap,pagact) == EXITO) return EXITO;
		DividePagInd(sep,ap,pagact,sepa,apa);
		return ASCENSO;
	}
	dir = ObtenDirDescenso(reg.idpedido,pagact);
	PAGIT pagind;
	LeePagina(&pagind, PAGISZ, dir, Fi);
	ret = InsertaRegR(reg, &pagind, sepa, apa);
	if(ret == ASCENSO){
		if( InsertaEnPagInd( *sepa,*apa,pagact) == EXITO) return EXITO;
		DividePagInd(sep,ap,pagact,sepa,apa);
		return ASCENSO;
	}
	return ret;
}

char CreaRaiz(unsigned sep,unsigned api,unsigned apd)
{
	PAGIT pagind;
	pagind.altura = INTERNO;
	pagind.ocupacion = 1;
	pagind.pagid = Cabind.ocupacion++;
	pagind.sep[0] = sep;
	pagind.ap[0] = api;
	pagind.ap[1] = apd;
	//Escribimos la raiz, ya que va a ser sustituida.
	EscribePagina(&Raiz, PAGISZ, Raiz.pagid, Fi);
	Raiz = pagind;
	Cabind.raiz = pagind.pagid;
	//Escribimos la nueva raiz en el fichero
	//Necesario, puesto que si se crea una pagina indice posterior, se escribiria en una posicion incorrecta
	EscribePagina(&Raiz, PAGISZ, Raiz.pagid, Fi);
	return EXITO;
}

char InsertaReg (REGT reg)
{
	char ret;
	unsigned sepa, apa;
	ret = InsertaRegR(reg, &Raiz, &sepa, &apa);
	if(ret == ERRCLAVEDUPLICADA) return FRACASO;
	if(ret == ASCENSO)
			CreaRaiz(sepa,Raiz.pagid,apa);
	return EXITO;
}

void CierreSistema(void)
{
	EscribePagina(&Cabdat,PAGSZ,Cabdat.pagid,Fd);
	EscribePagina(&Cabind,PAGISZ,Cabind.pagid,Fi);
	EscribePagina(&Raiz,PAGISZ,Raiz.pagid,Fi);
	fclose(Fd);
	fclose(Fi);
}

char BuscaRango (unsigned min, unsigned max)
{
        if(min > max) return FRACASO;
        PAGIT pind;
        PAGDT pdat;
        REGT reg;
        pind = Raiz;
        FILE *ffind = fopen(NOMFICH_SAL, "wt");
        while(pind.altura == INTERNO)
          LeePagina(&pind,PAGISZ,ObtenDirDescenso(min,&pind),Fi);

        //Obtenemos la pagina de datos en la que se encuentra:
        LeePagina(&pdat,PAGSZ,ObtenDirDescenso(min,&pind),Fd);

        //Sacamos el registro(o la posicion en la que deberia estar[pos])
        unsigned pos, salir = 0;
        char res = FRACASO;
        ObtenRegDePag(min,&pdat,&reg,&pos);

        do{
          if( pos >= pdat.ocupacion){//Si nos encontramos en el ultimo registro
            if(pdat.siguiente == 0) {
              salir = 1;
            }
            else{
              LeePagina(&pdat,PAGSZ, pdat.siguiente, Fd);
              pos = 0;
            }
          }
          if(pdat.reg[pos].idpedido > max){//Si el pedido actual es mayor que el maximo salimos
            salir = 1;
          }
          else{
            res = EXITO;
            fprintf(ffind,RegistroAString(pdat.reg[pos]));
            fprintf(ffind,"\n");
            pos++;
          }
        }while(!salir);
        fclose(ffind);
        return res;
}

int main(void) {
        if(DEBUG) printf("NUMREGPAG: %d, ORDEN: %d.\n",NUMREGPAG,ORDEN);
        GeneraArbolBMas();
	ProcesaTrans();

	return EXIT_SUCCESS;
}
