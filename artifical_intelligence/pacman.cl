
(in-package :common-graphics-user)



;;;Codigo correspondiente todos los modulos necesarios para el correcto funcionamiento de la practica.

;;; Pasar las lineas de una fichero a una lista [devuelve una lista de cadenas]
(defun fileLinesToList(fichero)
	(with-open-file ( fich1 fichero :direction :input )
		(let ((aux 'a)(lista nil))
			(loop while (not (equal aux nil)) do
				(setf aux (read-line fich1 nil))
				(if (not (equal aux nil)) (setf lista (append lista (list aux))))
			)
		lista
		)
	)	
)

;;dada una lista de cadenas[que representa una matriz],  la convierte en matriz
(defun obtenerMatriz (lista)
	(let ((aux t)(matriz)(i 0)(j 0))
		;;;Creamos la matriz de num.cadenas * long.cadenas
		(setf matriz (make-array (list (length lista) (length (first lista))) :initial-element t))
		(loop for cadena in lista do
			(with-input-from-string (stream cadena)
				(setf aux t)
				(setf j 0)
				(loop while (not (equal aux nil)) do
					(setf aux (read-char stream nil))
					(if (not (equal aux nil)) (setf (aref matriz i j) aux))
					(setf j (+ j 1))
				)
			)
			(setf i (+ i 1))
		)
		matriz
	)
  )
  
;;convierte una matiz en una lista de listas
(defun matrizToList (matriz &aux sal fila)
		(loop for i from 0 to (- (array-dimension matriz 0) 1) do
			(setf fila nil)
			(loop for j from 0 to (- (array-dimension matriz 1) 1) do
				(setf fila (append fila (list (aref matriz i j))))
			)
			(setf sal (append sal (list fila)))
		)
		sal
)

;;Convierte una matriz en una lista de lineas
(defun matrizToLineList (matriz)
	;;;A través de mapcar aplicamos a cada elemento de la lista una funcion lambda que convierte un elemento en una string. :)
	(MAPCAR #'(LAMBDA (X) (COERCE X 'STRING)) (matrizToList matriz))
  )

;;Dibuja una matriz
(defun pintarMatriz(matriz)
	(loop for linea in (matrizToLineList matriz) do
		(pintar linea)
	)
)

;;funcion heuristica que da una puntuacion a una casilla (cuanto mayor puntuacion mejor)
;;--------------------------------------------------------------------------------------------
;;argumentos:			casilla:	casilla de la que obtener la funcion heuristica
;;						matriz:		matriz actual
;;						fruta:		posicion de la fruta
;;						fantasmas:	posicion de los fantasmas
;;						visitados:	casillas visitadas
;;						pacman:		casilla en la que se encuentra actualmente pacman
;;						pesos:		pesos que se le da a las caracteristicas
;;--------------------------------------------------------------------------------------------
;;caracteristicas:		                1:distancia euc a la fruta
;;						2:distancia euc a los fantasmas	
;;						3:numero de adyacentes de la casilla
;;						4:Si se encuentra, numero de casillas minima para llegar a la fruta
;;						5:Si se encuentra, Suma de numero de casillas minima para llegar a los fantasmas
;;						6:Numero de veces que se a pisado la casilla en los ultimos movimientos
(defun heu (casilla matriz fruta fantasmas visitados pacman pesos &aux caract1 caract2 caract3 caract4 caract5 caract6)
	(setf caract1 (sqrt (+ (pow2(- (nth 0 casilla) (nth 0 fruta))) (pow2(- (nth 1 casilla) (nth 1 fruta))))))
	(setf caract2 0)
	(loop for fant in fantasmas do
		(setf caract2 (+ caract2 (sqrt (+ (pow2(- (nth 0 casilla) (nth 0 fant))) (pow2(- (nth 1 casilla) (nth 1 fant)))))))
	)
	(setf caract3 (length (adyacentes matriz (first casilla) (first (rest casilla)))))
	(setf caract4 (rutasEscalada casilla fruta matriz 10 20 pacman 40))
	(setf caract5 0)
	(loop for fant in fantasmas do
		(setf caract5 (+ caract5 (pow2 (rutasEscalada casilla fant matriz 10 4 pacman 25))))
	)	
	(setf caract6 (count-if #'(lambda(X) (iguales X casilla)) visitados))
	(+ (* (nth 0 pesos) caract1) (* (nth 1 pesos) caract2) (* (nth 2 pesos) caract3) (* (nth 3 pesos) caract4) (* (nth 4 pesos) caract5) (* (nth 5 pesos) caract6))
)

;;;^2
(defun pow2 (num)
	(* num num)
)

;;saca los primeros x elementos
(defun getfirsts (cantidad lista)
	(if (equal cantidad 0) 
		nil
		(cons (first lista) (getfirsts (- cantidad 1) (rest lista)))
	)
)

;;aplica el metodo de aprendizaje "algoritmos geneticos"
;;un indivudo es de la forma:   ("% de exito" "vector de pesos")
(defun genetico (ruta numiteraciones &optional (numIndividuos 5) (seleccion 2) (pruebas-por-ind 10) (nummutaciones 1) &aux aux aux2 aux3 aux4 (individuos))
	(loop for i from 2 to seleccion do
		(setf aux (list -1 (random-int 20) (random-int 20) (random-int 20) (random-int 20) (random-int 20) (random-int 20)))
		(setf individuos (cons aux individuos))
	)
	(setf individuos (cons (list -1 -3 1 1 -10 20 -10) individuos))
	;;inicio del algoritmo:
	(loop for i from 1 to numiteraciones do

		;;realizar mutaciones
		(loop for i from 1 to nummutaciones do
			(setf aux (random (length individuos)));;individuo a cambiar
			(setf aux2 (+ 1 (random 6)));;peso a cambiar
			(setf individuos (cons (change-val aux2 (nth aux individuos) (+ (nth aux2 (nth aux individuos)) (random-int 50))) individuos))
		)

		;;realizamos apareamiento hasta tener el numero deseado de indviduos
		(loop while (< (length individuos) numIndividuos) do
			(setf aux (random (length individuos)));;individuo1 a aparear
			(setf aux2 (random (length individuos)));;individuo2 a aparear
			(setf aux4 (+ 1 (random 6)));caracteristica a pasar de ind2 a ind1
			(setf aux3 (nth aux individuos));;individuo nuevo, comienza como ind1
			(setf aux3 (change-val aux4 aux3 (nth aux4 (nth aux2 individuos))));;pasamos la caracteristica
			(setf aux3 (change-val 0 aux3 -1));;indicamos que aun no se ha evaluado
			(setf individuos (cons aux3 individuos))
		)
		
		;;realizar evaluacion
		(loop for i from 0 to (- (length individuos) 1) do
			(if (equal -1 (nth 0 (nth i individuos)));;si no ha sido evaluado anteriormente
				(setf individuos (change-val i individuos (change-val 0 (nth i individuos) (evaluar-individuo ruta (nth i individuos) pruebas-por-ind))))
			)
		)
		
		;;realizar seleccion. 
		(loop while (< seleccion (length individuos)) do
			(setf aux (nth 0 (nth 0 individuos)));;minimo
			(setf aux2 0);;elemento minimo
			(loop for i from 1 to (- (length individuos) 1) do
				(if (> aux (nth 0 (nth i individuos))) 
					(progn
						(setf aux2 i)
						(setf aux (nth 0 (nth i individuos)))
					)
				)
			)
			(setf individuos (del-elem aux2 individuos));;eliminamos al peor
		)
		(pintar "INDIVIDUOS ACTUALES:")
		(loop for i from 0 to (- (length individuos) 1) do
			(pintar-otro (nth i individuos))
		)
	)
	
	;;devolvemos el porcentaje del mejor individuo
	(setf aux (nth 0 (nth 0 individuos)));;maximo
	(setf aux2 0);;elemento maximo	
	(loop for i from 1 to (- (length individuos) 1) do
		(if (< aux (nth 0 (nth i individuos))) 
			(progn
				(setf aux2 i)
				(setf aux (nth 0 (nth i individuos)))
			)
		)
	)
	(pintar "Mejor porcentaje obtenido:")
  (setf (value (find-component :editable_porcentaje dialogo)) (write-to-string (nth 0 (nth aux2 individuos))))
    	(setf (value (find-component :editable_vector dialogo)) (write-to-string (nth aux2 individuos)))
)

;;evalua el porcentaje de exito de un individuo
(defun evaluar-individuo (ruta individuo &optional (pruebas-por-ind 10) &aux (ganadas 0) (total 0))
	(loop for i from 0 to (- pruebas-por-ind 1) do
		(if (simulacion ruta nil (rest individuo))
			(setf ganadas (+ ganadas 1))
		)
		(setf total (+ total 1))
	)
	(/ ganadas total)
)

;;aplica el algoritmo de aprendizaje ajuste de parametros
(defun ajuste-parametros (ruta numaprendizajes &optional (simulaciones 10) &aux aux (ganadas 0) (perdidas 0) pesosActual pesosAnterior (porcentajeAnterior -1))
	(setf pesosActual (list -3 1 1 -10 20 -10));;inicializamos los pesos
	(loop for i from 1 to numaprendizajes do
		(setf ganadas 0)
		(setf perdidas 0)
		(loop for j from 1 to simulaciones do
			(if (simulacion ruta nil pesosActual)
				(progn (setf ganadas (+ ganadas 1)) (setf (value (find-component :editable_ganadas dialogo)) (write-to-string ganadas)))
				(progn (setf perdidas (+ perdidas 1)) (setf (value (find-component :editable_perdidas dialogo)) (write-to-string perdidas)))
			)
		)
		(if (> (/ ganadas (+ ganadas perdidas)) porcentajeAnterior);;a conseguido un mejor porcentaje
			(progn
				(setf pesosAnterior pesosActual)
				(setf porcentajeAnterior (/ ganadas (+ ganadas perdidas)))
                                (pintar "pesos cambiados")
                                (setf (value (find-component :editable_vector dialogo)) (write-to-string pesosAnterior))
				(setf (value (find-component :editable_porcentaje dialogo)) (write-to-string porcentajeAnterior))
			)
		)
		;;creamos un nuevo vector de pesos
		(setf aux (random (length pesosAnterior)))
		(if (equal (mod i 8) 0)
			(setf pesosActual (change-val aux pesosAnterior (+ (* (random-int 10) 10) (nth aux pesosAnterior))));;pequeño ajuste;;;cambio drastico
			(setf pesosActual (change-val aux pesosAnterior (+ (random-int 10) (nth aux pesosAnterior))));;pequeño ajuste
		)
	)
)

;;obtiene un numero aleatorio aleatorio entre -maximo y + maximo, ambos no inclusives
(defun random-int (maximo)
	(- (random (* maximo 2)) maximo)
)

;;cambia un elemento de la lista
(defun change-val  (pos lista elem )
	(cond
		((equal lista nil) nil)	
		((equal pos 0)	(cons elem (rest lista)))
		(T (cons (first lista) (change-val (- pos 1) (rest lista) elem)))
	)
)

;;borra un elemento de la lista
(defun del-elem  (pos lista )
	(cond
		((equal lista nil) nil)	
		((equal pos 0)	(rest lista))
		(T (cons (first lista) (del-elem (- pos 1) (rest lista))))
	)
  )
;;inicializa las variables globales para una ejecucion unica
(defun inicializarUnica (&aux aux)
	(setf matriz (obtenerMatriz (fileLinesToList rutafich)))
         ;;lectura de los fantasmas, pacmas y fruta
        (setf fantasmas nil)
        (setf pacman nil)
  (setf fruta nil)
  (setf it 0) (setf fin nil) (setf res nil) (setf visitados nil)
	(loop for ind from 0 to (- (array-dimension matriz 0) 1) do
		(loop for ind2 from 0 to (- (array-dimension matriz 1) 1) do
			(progn
				(setf aux (aref matriz ind ind2))
				(cond 
					( (equal aux #\P) (setf pacman (list ind ind2)) )
					( (equal aux #\F) (setf fruta (list ind ind2)) )
					( (equal aux (aref matriz 0 0)) ());;;pared
                                        ( (equal aux #\Space) ());;;blanco
                                        ( (equal aux #\Return) ()) ;;;fin de linea
					( T (setf fantasmas (cons (list ind ind2 aux) fantasmas)))
				)
			)
		)				
       )
)
;;realiza una iteración de simlación única
(defun iteracion (&optional (pesos (list -3 1 1 -10 20 -10)) &aux aux aux2 aux3 aux4)
  
 (setf aux2 nil)
		(loop for elemFan in fantasmas do
			(setf aux (adyacentes matriz (first elemFan) (first (rest elemFan))));;;todos los adyacentes
			(if (not (equal nil aux)) (progn
				(setf aux (nth (random (length aux)) aux));;adyacente al que se mueve
				(setf (aref matriz (first elemFan) (first (rest elemFan))) #\Space)				
				(setf (aref matriz (first aux) (first (rest aux))) (nth 2 elemFan))
				(setf aux2 (cons (list (first aux) (first (rest aux)) (nth 2 elemFan)) aux2))
			))
		)
		(setf fantasmas aux2)
			
		;;comprobar comido o muerto
		(setf aux (adyacentes matriz (first pacman) (first (rest pacman))));;;todos los adyacentes de pacman
		(loop for ady in (cons pacman aux) do
			(cond 
				((equal ady fruta) (progn (setf fin "Pacman come la fruta!") (setf res T)))
				((> (count-if #'(lambda(X) (iguales X ady)) fantasmas) 0) (setf fin "Se han comido a Pacman!"));;res esta a nil por defecto
			)
		)
		


				(setf it (+ it 1))
				(pintar-otro it)
				(pintarMatriz matriz)
		
			
		;;codigo relativo al movimiento de pacman
							;;;(setf aux (obtenerDestino matriz fantasmas pacman fruta))
							;;;(setf (aref matriz (first pacman) (first (rest pacman))) #\Space)	
							;;;(setf (aref matriz (first aux) (first (rest aux))) #\P)
							;;;(setf pacman aux)
		(if (not fin) (progn					
			(setf aux (adyacentes matriz (first pacman) (first (rest pacman))));;;todos los adyacentes
			(setf aux2 (heu (first aux) matriz fruta fantasmas visitados pacman pesos))
			(setf aux3 (first aux))
			(loop for casilla in (rest aux) do
				(setf aux4 (heu casilla matriz fruta fantasmas visitados pacman pesos))
				(if (> aux4 aux2) (progn (setf aux2 aux4) (setf aux3 casilla)))
			)
			(setf (aref matriz (first pacman) (first (rest pacman))) #\Space)				
			(setf (aref matriz (first aux3) (first (rest aux3))) #\P)
			(setf visitados (cons pacman visitados))
			(setf pacman (list (first aux3) (first (rest aux3))) )
		)) 
  (if (not (equal fin nil)) 
        (setf enjuego nil))
  )


;;realiza una simulacion del laberinto
(defun simulacion (ruta traza &optional (pesos (list -3 1 1 -10 20 -10)) &aux aux aux2 aux3 aux4 matriz fantasmas pacman fruta (it 0) (fin nil) (res nil) (visitados nil))
	(setf matriz (obtenerMatriz (fileLinesToList ruta)))
	(if traza
		(pintarMatriz matriz)
	)
	
	;;lectura de los fantasmas, pacmas y fruta
	(loop for ind from 0 to (- (array-dimension matriz 0) 1) do
		(loop for ind2 from 0 to (- (array-dimension matriz 1) 1) do
			(progn
				(setf aux (aref matriz ind ind2))
				(cond 
					( (equal aux #\P) (setf pacman (list ind ind2)) )
					( (equal aux #\F) (setf fruta (list ind ind2)) )
					( (equal aux (aref matriz 0 0)) ());;;pared
                                        ( (equal aux #\Space) ());;;blanco
                                        ( (equal aux #\Return) ()) ;;;fin de linea
					( T (setf fantasmas (cons (list ind ind2 aux) fantasmas)))
				)
			)
		)				
	)
	
	(loop while (equal nil fin) do
		
		;;pulse una tecla
		;;(if traza 
		;;	(read-char)		
		;;)
		
		;;codigo relativo al movimiento del fantasma
		(setf aux2 nil)
		(loop for elemFan in fantasmas do
			(setf aux (adyacentes matriz (first elemFan) (first (rest elemFan))));;;todos los adyacentes
			(if (not (equal nil aux)) (progn
				(setf aux (nth (random (length aux)) aux));;adyacente al que se mueve
				(setf (aref matriz (first elemFan) (first (rest elemFan))) #\Space)				
				(setf (aref matriz (first aux) (first (rest aux))) (nth 2 elemFan))
				(setf aux2 (cons (list (first aux) (first (rest aux)) (nth 2 elemFan)) aux2))
			))
		)
		(setf fantasmas aux2)
			
		;;comprobar comido o muerto
		(setf aux (adyacentes matriz (first pacman) (first (rest pacman))));;;todos los adyacentes de pacman
		(loop for ady in (cons pacman aux) do
			(cond 
				((equal ady fruta) (progn (setf fin "Pacman come la fruta!") (setf res T)))
				((> (count-if #'(lambda(X) (iguales X ady)) fantasmas) 0) (setf fin "Se han comido a Pacman!"));;res esta a nil por defecto
			)
		)
		
		(if traza 
			(progn
				(setf it (+ it 1))
				(pintar-otro it)
				(pintarMatriz matriz)
		))
			
		;;codigo relativo al movimiento de pacman
							;;;(setf aux (obtenerDestino matriz fantasmas pacman fruta))
							;;;(setf (aref matriz (first pacman) (first (rest pacman))) #\Space)	
							;;;(setf (aref matriz (first aux) (first (rest aux))) #\P)
							;;;(setf pacman aux)
		(if (not fin) (progn					
			(setf aux (adyacentes matriz (first pacman) (first (rest pacman))));;;todos los adyacentes
			(setf aux2 (heu (first aux) matriz fruta fantasmas visitados pacman pesos))
			(setf aux3 (first aux))
			(loop for casilla in (rest aux) do
				(setf aux4 (heu casilla matriz fruta fantasmas visitados pacman pesos))
				(if (> aux4 aux2) (progn (setf aux2 aux4) (setf aux3 casilla)))
			)
			(setf (aref matriz (first pacman) (first (rest pacman))) #\Space)				
			(setf (aref matriz (first aux3) (first (rest aux3))) #\P)
			(setf visitados (cons pacman visitados))
			(setf pacman (list (first aux3) (first (rest aux3))) )
		))
	
	)
	
	;;(if traza 
		(pintar-otro fin)
	;;)
	res
)

;;comprueba si dos casillas son iguales
(defun iguales (casilla1 casilla2)
	(and (equal (first casilla1) (first casilla2)) (equal (first (rest casilla1)) (first (rest casilla2))))
)
;;dada una posicion i,j y una matriz, obtiene las casillas adyacentes. [Se consideran no adayacentes las casillas que contengan el valor del parametro wrong]
(defun adyacentes (matriz i j &optional (wrong #\*) &aux (sal nil))
	(if (not (equal (aref matriz i (+ j 1)) wrong)) (setf sal (cons (list i (+ j 1)) sal)))
	(if (not (equal (aref matriz i (- j 1)) wrong)) (setf sal (cons (list i (- j 1)) sal)))
	(if (not (equal (aref matriz (+ i 1) j) wrong)) (setf sal (cons (list (+ i 1) j) sal)))
	(if (not (equal (aref matriz (- i 1) j) wrong)) (setf sal (cons (list (- i 1) j) sal)))
	sal
)

;;;quita todos los elementos de x que esten en visitados
(defun limpiar(X visitados)
  (loop for elem in visitados do (setf X (borrar elem X)))
  X
  )
;;;Borra un elemento de una lista 
(defun borrar (elem x)
	(if (equal x nil)
		nil
		(if (equal elem (first x))
			(borrar elem (rest x))
			(cons (first x) (borrar elem (rest x)))
		)
	)
)


;;obtiene todas las rutas (listas de listas de puntos (i j)) para llegar de origen a destino
;;visitados: listas de las posiciones visitadas. matrizPos: matriz de posiciones
(defun rutas (origen destino visitados matrizPos pasosRestantes &aux ady listAux)
	(setf ady (adyacentes matrizPos (first origen) (first (rest origen))))
	(setf ady (limpiar ady visitados))	
	(cond
		((equal origen destino) (list (list origen)) )			;;estamos en el destino
		((equal ady nil) nil	)			;;no nos pdemos mover
		((equal pasosRestantes 0) nil)		;;ha llegado al limite
		( T (progn (loop for elem in ady do
			(setf listAux (append (aniadirMultiple origen (rutas elem destino (cons elem visitados) matrizPos (- pasosRestantes 1))) listAux))
			)
			listAux
			)
		)
		
	)
)

;;;añade un elemento a todos los elementos(listas) de una lista. Atencion, invierte el orden.
(defun aniadirMultiple (elem lista &aux listAux)
		(loop for listElem in lista do
			(setf listAux (cons (cons elem listElem) listAux))
		)
		listAux
)
  
;;halla una ruta con generacion y prueba
(defun rutasEscalada (origen destino matriz iteraciones pasos anterior resSiNoFinded &aux aux posActual (findedParcial nil) (findedFinal nil) resParcial resFinal visitados )
	(setf resFinal (* 2 pasos))
	(loop for i from 0 to iteraciones do
		(setf resParcial 0)
		(setf posActual origen)
		(setf findedParcial nil)
		(setf visitados (list posActual anterior))
		(loop for j from 0 to pasos do
			(setf aux (adyacentes matriz (first posActual) (nth 1 posActual)))
			(setf aux (limpiar aux visitados))
			(if (equal aux nil)	;;No quedan adyacentes
				(setf j pasos)
				(progn
					(setf posActual (nth (random (length aux)) aux));;cogemos un adyacente cualquiera
					(if (iguales posActual destino) (progn (setf j pasos) (setf findedParcial T)))
					(setf resParcial (+ resParcial 1))
				)
			)
			(setf visitados (cons visitados posActual))
		)
		(if (and findedParcial (> resFinal resParcial)) (setf resFinal resParcial))
		(setf findedFinal (or findedFinal findedParcial))
	)
	(if findedFinal
		resFinal
		resSiNoFinded
	)
)


;;;Control de los botones del entorno gráfico implementado en la práctica.

;;;Boton referente a la carga del laberinto desde una ruta especificada en el componente editable_fich
(defun form1-b_cargar-on-click (dialog widget)
  (declare (ignorable dialog widget))
  (setf dialogo dialog)
  (setf enjuego nil)
  (if (not (equal (value (find-component :editable_fich dialog)) ""))
      (progn 
        (pintarmatriz(obtenermatriz(filelinestolist (value (find-component :editable_fich dialog)))))
        (setf rutafich (value (find-component :editable_fich dialog)))
        )
    )
  
  t)

;;; Boton que se encarga de realizar la simulación utilizando el algoritmo de ajuste de parámetros.
(defun form1-b_parametros-on-click (dialog widget)
  (declare (ignorable dialog widget))
  (let ((numApren)(numIter))
    (if (AND (not( equal (value (find-component :editable_numaprendizaje dialog)) "")) (not (equal (value (find-component :editable_numiteraciones dialog)) "")))
        (progn 
          (setf numApren (parse-integer(value (find-component :editable_numaprendizaje dialog))))
          (setf numIter (parse-integer(value (find-component :editable_numiteraciones dialog))))
          (ajuste-parametros rutafich numApren numIter)
          )
      )
   )

  t)

;;;Boton que se encarga de realizar la salida de la aplicacion.
(defun form1-b_salir-on-click (dialog widget)
  (declare (ignorable dialog widget))
  (exit)
  t)

;;;Boton que se encarga de iniciar la simulacion utilizando algoritmo genetico.
(defun form1-b_genetico-on-click (dialog widget)
  (declare (ignorable dialog widget))
  (let ((numApren)(numIter))
    (if (AND (not( equal (value (find-component :editable_numaprendizaje dialog)) "")) (not (equal (value (find-component :editable_numiteraciones dialog)) "")))
        (progn 
      (setf numApren (parse-integer(value (find-component :editable_numaprendizaje dialog))))
      (setf numIter (parse-integer(value (find-component :editable_numiteraciones dialog))))
          (genetico rutafich numApren numIter)
          )
      )
   )
  
  t)

;;;Boton que se encarga de ir avanzando paso a paso la simulación, cuando no se realizan metedos de aprendizaje como algoritmo geneticos o ajuste de parametros.
(defun form1-b_avanzar-on-click-1 (dialog widget)
  (declare (ignorable dialog widget))
    (if (AND (not (equal (value (find-component :editable_numpasos dialog)) "")) enjuego )        
      (progn (setf (value (find-component :editable_numpasos dialog)) (write-to-string (+ (parse-integer (value (find-component :editable_numpasos dialog))) 1)))
    (iteracion))
    )
  t)
;;;Modulo que se encarga de pintar la informacion de la simulacion en multi_simulacion
(defun pintar (linea)
     (setf (value (find-component :multi_simulacion dialogo)) (concatenate 'string (value (find-component :multi_simulacion dialogo)) (format nil "~%")  linea))
  )
;;;Modulo que se encarga de pintar la informacion de la simulacion en multi_simulacion cuando es un valor distinto de string
(defun pintar-otro (linea)
     (setf (value (find-component :multi_simulacion dialogo)) (concatenate 'string (value (find-component :multi_simulacion dialogo)) (format nil "~%")  (write-to-string linea)))
)
;;;Boton que se encarga de iniciar una partida individual de nuestro programa.
(defun form1-b_individual-on-click (dialog widget)
  (declare (ignorable dialog widget))
  (if (not enjuego)
      (progn
        (setf enjuego T)
        (inicializarUnica )
        )
    )
  t)
;;;Modulo que se encarga de limpiar la pantalla donde se escribe toda la informacion.
(defun form1-b_limpiar-on-click (dialog widget)
  (declare (ignorable dialog widget))
  (setf (value (find-component :multi_simulacion dialogo)) "")
  t)
