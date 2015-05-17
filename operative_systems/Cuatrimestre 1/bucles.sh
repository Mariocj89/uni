#if [ $# -le 1 ]
#then 
#	echo "Error"
#	exit
#fi
#lista=`seq 1 $1`

#muestra las carpetas de una carpeta pasada por parametro

lista=`ls $1`

for i in $lista
do
	if [ -d $1/$i ]
	then
		echo $1/$i
		sh $0 $1/$i
	fi

done

