#Diseñar un shell script que reciba dos parametros de entrada correspondientes a dos valores numericos, hacer control de argumentos, deben ser dos valores. Mostrar un mensaje por pantalla indicando cual de los dos numeros introducidos es mayor o bien si los numeros son iguales.

if [ $# -ne 2 ]
then
	echo "Sintaxis correcta: sh $0 num1 mum2"
	exit
fi

if [ $1 -gt $2 ]
then
	echo "El primer parametro es mayor que el segundo"
elif [ $2 -gt $1 ]
then
	echo "El segundo parametro es mayor que el primero"
else
	echo "Los parametros son iguales"
fi
	
