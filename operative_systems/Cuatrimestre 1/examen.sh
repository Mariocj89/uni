actual=`pwd`;

if [ -f $actual/aux1 ]
then
	rm $actual/aux1;
fi

if [ -f $actual/aux2 ]
then
	rm $actual/aux2;
fi

if [ -f $actual/aux3 ]
then
	rm $actual/aux3;
fi

contador=1;
for i in `ls $actual`
do
	if [ -f $actual/$i ]
	then
		echo $contador $i >> $actual/aux1;
		contador=$(($contador+1));
	fi
done

dialog --menu "Examen" 0 0 0 `cat aux1` 2>$actual/aux2
if [ $? -eq 1 ]
then
	exit;
fi

num=`cat aux2`;
linea=`head -n$((num)) aux1 | tail -n1`;
echo $linea > aux3
cadena="Esta seguro de que desea borrar el fichero: "$fich;
read num fich < aux3
echo $fich

dialog --yesno "¿Esta seguro de que desea borrar el fichero: $fich?" 0 0;

if [ $? -eq 0 ]
then
	`rm $actual/$fich`
	if [ $? -eq 0 ]
	then
		dialog --msgbox "Se ha eliminado el fichero $fich" 0 0;
	fi	
fi
