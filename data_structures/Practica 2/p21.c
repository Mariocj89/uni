


// #ifndef P21_H_   ??
#include "p21.h"


char ColocaRegEnPag(PAGT *pagina, REGT reg, unsigned pos){
	if(NUMREGPAG <= pos) return FRACASO;
	pagina->reg[pos] = reg;
	return EXITO;
}

char ObtenRegDePag(PAGT pagina, REGT *reg, unsigned pos){
	if(NUMREGPAG <= pos) return FRACASO;
	*reg = pagina.reg[pos];
	return EXITO;
}

char InsertaRegistroEnPag(PAGT *pagina, REGT reg){
	if(pagina->ocupacion >= NUMREGPAG) return FRACASO;
	ColocaRegEnPag(pagina,reg,pagina->ocupacion++);
	return EXITO;
}

char CreaFichero(char *filename,void *cabecera, unsigned cabsz){
	FILE* fp = fopen(filename,"wb");
	if(fp == NULL) return FRACASO;
	fwrite(cabecera,cabsz, 1, fp);
	fclose(fp);
	return EXITO;
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
// Interpreta la siguiente lÍnea del fichero fd, almacenando el contenido
// en el parámetro reg. La función retorna un valor positivo si se hizo
// correctamente y un valor 0 en caso en que no hubiera más líneas por
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

char ConstruirPedidosDat(void){

	int ocupacion = 1;
	CABFILET cabf;
	strcpy(cabf.nomfich,"pedidos.dat");
	cabf.ocupacion = ocupacion;
	cabf.pagid = 0;
	cabf.pagsz = PAGSZ;
	cabf.regsz = REGSZ;

	CreaFichero(cabf.nomfich, &cabf, PAGSZ);

	PAGT pagina;
	pagina.ocupacion = 0;

	REGT reg;

	FILE *ftext = fopen("pedidos.txt","rt");
	FILE *fdat = fopen("pedidos.dat", "r+b");
	fread(&cabf,PAGSZ,1, fdat);

	fseek(fdat,0,SEEK_END);
	while(ObtenSgteReg(ftext, &reg)){
		if(InsertaRegistroEnPag(&pagina, reg) == FRACASO)
		{
			pagina.pagid =cabf.ocupacion;
			fwrite(&pagina,PAGSZ,1,fdat);
			cabf.ocupacion++;
			memset(&pagina,0x00,PAGSZ);
			pagina.ocupacion = 0;
			InsertaRegistroEnPag(&pagina, reg);
		}
	}
	pagina.pagid =cabf.ocupacion;
	fwrite(&pagina,PAGSZ,1,fdat);
	cabf.ocupacion++;
	fseek(fdat,0,SEEK_SET);
	fwrite(&cabf,PAGSZ,1, fdat);

	printf("Construidas %d paginas.\n",cabf.ocupacion);

	fclose(fdat);
	fclose(ftext);
	return FRACASO;
}

char *RegistroAString(REGT reg)
{
// Toma un registro y convierte sus datos a un formato visible
// incluyendolo en una cadena de caracteres
 char *linea;

 linea = (char *) malloc (255);
 sprintf(linea,"%.5s;%d;%s;%s;%d/%d/%d;%.4f\n",reg.codcli,\
        reg.idpedido,reg.nombre,reg.ciudad,reg.fecha.dia,\
        reg.fecha.mes,reg.fecha.anio,reg.importe);
 return linea;
}

char VolcadoPedidosDatARespedTxt(void)
{
	FILE *ftxt = fopen("pedidos2.txt","wt");
	FILE *fdat = fopen("pedidos.dat","rb");
	if(ftxt == NULL || fdat == NULL) return FRACASO;

	CABFILET cabfile;
	fread(&cabfile,PAGSZ,1,fdat);
	PAGT pagina;
	int i = 1, j = 0;
	for(i=1;i<cabfile.ocupacion;i++){
		fseek(fdat,i*PAGSZ,SEEK_SET);
		fread(&pagina,PAGSZ,1,fdat);
		printf("(%d)",pagina.pagid);
		for(j=0;j<pagina.ocupacion;j++) fprintf(ftxt,RegistroAString(pagina.reg[j]));
	}

	fclose(ftxt);
	fclose(fdat);
	return EXITO;
}

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
    sz = sizeof(CABFILET);
    if (sz != PAGSZ){
        printf("\n tamaño de página cabecera datos incorrecto %d",sz);
        sz = 0;
    }
    sz = sizeof(REGT);
    if (sz != REGSZ){
        printf("\n tamaño de tipo registro incorrecto %d",sz);
        sz = 0;
    }
    sz = sizeof(PAGT);
    if (sz != PAGSZ){
        printf("\n tamaño de página incorrecto %d",sz);
        sz = 0;
    }
    if (sz == 0) {
        printf("\nIntroduce un carácter para continuar...");
        scanf("%c",&c);
    	exit(1);
    }
}

int main(void) {
	TestPrincipal();
	ConstruirPedidosDat();
	VolcadoPedidosDatARespedTxt();
	return EXIT_SUCCESS;
}

