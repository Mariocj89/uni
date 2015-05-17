#Saca por "salida.txt" todos los fichers que pertenezcan al usuario pasado por el primer parametro o que ocupen mas que el tamaño pasado por el segundo parametro
if [ $# -ne 2 ]
then
	echo "Error, número incorrecto de parametros.";
fi
if [ -f salida.txt ]
then 
	rm salida.txt
fi
actual=`pwd`;
ls -l $actual > aux1;
wc -l aux1 > aux2;
read numlineas basura < aux2;
contador=1;
while [ $contador -le $numlineas ]
do
	head -n$contador aux1 | tail -n1 > aux2;
	read a b usuario c tam d e nom < aux2;
	if [ -f $actual/$nom ]
	then
		if [ $usuario = $1 ]
		then
			echo $nom >> salida.txt;
		else
			if [ $tam -ge $2 ]
			then
				echo $nom >> salida.txt;
			fi
		fi
	fi
	contador=$(($contador+1));
done
rm aux1;
rm aux2;
dialog --msgbox "salida.txt contiente los ficheros del usuario $1 o mayores que $2 del directorio $actual" 0 0; 
clear;
