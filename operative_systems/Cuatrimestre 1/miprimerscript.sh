while true
do
	clear
	echo AGENDA TELEFONICA
	echo 1.Buscar
	echo 2.Insertar Ordenado
	echo 3.Borrar
	echo 4.Listar
	echo 5.Salir
	echo Introducir opcion
	read opcion
	case $opcion in
		1) echo Introduzca el nombre a buscar: ;
		   read nombre;
		   grep $nombre listado;
		   if [ $? -eq 1 ]
		   then echo $nombre no existe;
		   fi
		   echo Pulse enter para continuar...; 
		   read aux;;
		2) echo Introduce nombre:
		   read nombre;
		   echo Introduce telefono:
		   read telefono;
		   echo $nombre $telefono >> listado;
		   sort listado > aux;
		   mv aux listado;;
		3) echo Introduzca el nomber a eliminar: ;
		   read nombre;
		   grep -v $nombre > aux
		   if [ $? -eq 1 ]
		   then echo No se ha encontrado el nombre;
		   else echo Borrado con exito;
		   fi
		   mv aux listado;;
		4) cat listado;
			echo Pulse enter para continuar...; 
			read aux;;
		5) exit;;
	esac
done
