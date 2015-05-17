limpieza(){ #borramos todos los archivos auxiliares
  clear;
  if [ -d temp ]
  then
      rm -r temp;
  fi
}
sacar_directorios(){
	ls -l -k $1 > temp/aux1;
	indice=2;
	numerador=3;
	wc -l temp/aux1 > temp/aux2;
	read nlineas xxx <temp/aux2;
	echo "." "1"  >temp/fichdir;
	echo ".." "2"  >> temp/fichdir;
	while [ $nlineas -ge $indice ] #almacenamos en un fichero la lista de ficheros y sus tamaños
	do
		head -n$indice temp/aux1 | tail -n1 >temp/aux2;
		read a b c d e f g nom1 < temp/aux2;
		if [ -d $1/$nom1 ]
		then
			echo $nom1 $numerador >> temp/fichdir;
			numerador=$(($numerador+1));
		fi
		indice=$(($indice+1));	
	done	
}
pulsado_cancelar(){
  if [ $1 -eq 1 ] #si pulsa cancel sale del scrip
  then
	limpieza;
	dialog --msgbox "Fin del programa" 0 0;
	clear;
  	exit;
  fi
}
simplificar_ruta() {
	ruta1=`pwd`;
	cd $actual;
	actual=`pwd`;
	cd $ruta1;
}

#obtenemos el directorio de trabajo
if [ $# -eq 1 ]
then
	actual=$1;
	simplificar_ruta;
else
	actual=`pwd`;
fi

#creamos un directorio temporal
if [ ! -d temp ]
then
	mkdir temp;
fi

ls -l -k $actual > temp/aux1;
indice=2;
wc -l temp/aux1 > temp/aux2;
read nlineas xxx <temp/aux2;
echo "." "0KB*" >temp/fich1;
echo ".." "0KB*" >> temp/fich1;
while [ $nlineas -ge $indice ] #almacenamos en un fichero la lista de ficheros y sus tamaños
do
	head -n$indice temp/aux1 | tail -n1 >temp/aux2;
	read a b c d tam f g nom < temp/aux2;
	if [ -f $actual/$nom ]
	then
		echo $nom $tam"KB" >> temp/fich1;
	else
		echo $nom $tam"KB*" >> temp/fich1;
	fi
	indice=$(($indice+1));
done
dialog --menu $actual 0 0 0 `cat temp/fich1` 2>temp/fopcion;

pulsado_cancelar $?

nom=`cat temp/fopcion`;

if [ -f $actual/$nom ] #si es un fichero
then
	echo $nom | grep -i *.txt;
	if [ $? -eq 0 ]
	then
		dialog --menu $actual/$nom 0 0 0 1 "buscar" 2 "copiar" 3 "renombrar" 4 "mover" 5 "borrar" 6 "visualizar" 2>temp/fopcion;
	else
		dialog --menu $actual/$nom 0 0 0 1 "buscar" 2 "copiar" 3 "renombrar" 4 "mover" 5 "borrar" 2>temp/fopcion;
	fi
	pulsado_cancelar $?;
	case `cat temp/fopcion` in
		1) clear; echo "Inotroduzca el texto a buscar en el archivo:"; read texto; dialog --msgbox "Se ha encontrado el texto $texto en las siguientes lineas: `grep $texto $actual/$nom`" 0 0;;
		2) directorio=$actual; seguir=1;
			while [ $seguir -eq 1 ]; 
			do
			sacar_directorios $actual;
			dialog --menu "Selccione un directorio:" 0 0 0 `cat temp/fichdir` 2>temp/fopcion;
			pulsado_cancelar $?
			actual=$actual/`cat temp/fopcion`;
			simplificar_ruta;
			dialog --yesno "Desea copiar $nom a $actual?" 0 0;
			seguir=$?;
			done
			cp $directorio/$nom $actual/$nom;
			actual=$directorio;
			dialog --msgbox "Se ha copiado el fichero $nom" 0 0;;
		4) directorio=$actual; seguir=1;
			while [ $seguir -eq 1 ]; 
			do
			sacar_directorios $actual;
			dialog --menu "Selccione un directorio:" 0 0 0 `cat temp/fichdir` 2>temp/fopcion;
			pulsado_cancelar $?;
			actual=$actual/`cat temp/fopcion`;
			simplificar_ruta;
			dialog --yesno "Desea mover $nom a $actual?" 0 0;
			seguir=$?;
			done
			mv $directorio/$nom $actual/$nom;
			actual=$directorio;
			dialog --msgbox "Se ha movido el fichero $nom" 0 0;;
		3) clear; echo "Introduzca el nuevo nombre:"; read nnombre; mv $actual/$nom $actual/$nnombre; dialog --msgbox "$nom renombrado a $nnombre" 0 0;;
		5) rm $actual/$nom; dialog --msgbox "Se ha borrado el fichero $nom" 0 0;;
		6) clear; dialog --msgbox "Contenido del fichero $nom: `cat $actual/$nom`" 0 0;;
	esac
	sh $0 $actual;
else	#si es un directorio
	sh $0 $actual/$nom;
fi


limpieza;
