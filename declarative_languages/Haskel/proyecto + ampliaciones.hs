--dada una posicion del tablero, obtenemos el resultado de pulsar una casilla
pulsar:: Int->[(Int,Int)]->(Int,Int)->[(Int,Int)]
pulsar n xs c = xor xs (purgar n (adyacentes c))

--dada una lista, elimina un elemento si esta, en caso contrario lo inserta
insertar::Eq x => [x] -> x -> [x]
insertar [] x = [x]
insertar (x:xs) y | x == y = xs
				  | otherwise = (x: (insertar xs y) )
				  
--dada dos listas, realiza una xor entre ellas
xor:: Eq a => [a]->[a]->[a]
xor xs [] = xs
xor xs (y:ys) = insertar (xor xs ys) y
--xor xs ys = foldr (insertar xs) xs ys

--comprueba que una casilla es valida para un tamaño de tablero
valido:: Int -> (Int,Int) -> Bool
valido n (x,y) | x < 1 || x > n = False
				|y < 1 || y > n = False
				|otherwise = True

--eliminar todos las casillas no validas para un tamaño dado de tablero
purgar:: Int -> [(Int,Int)] -> [(Int,Int)]
purgar n xs = [x|x<-xs,valido n x]

--dada una posicion, genera todas las posiciones adyacentes y ella misma (validas o no)
adyacentes:: (Int,Int) -> [(Int,Int)]
adyacentes (x,y) = [(x,y-1),(x,y+1),(x-1,y),(x+1,y),(x,y)]

--genera una lista con todas las casillas del tablero para un tamaño dado
tablero::Int->[(Int,Int)]
tablero n = zip [x| y<- [1..n],x<- replicate n y] (cycle [1..n])

--obtiene todas las sublistas de una lista
subs::[a]->[[a]]
subs [] = [ [] ]
subs (x:xs) = map (x:) subsxs ++ subsxs where subsxs = subs xs

--obtiene todas las posibles soluciones para un tablero de tamaño n
soluciones::Int->[[(Int,Int)]]
soluciones n = subs (tablero n)

--intenta solucionar un tablero con una solucion
solucionar:: Int -> [(Int,Int)] -> [(Int,Int)]-> Bool
solucionar _ [] []  = True
solucionar n t (x:xs) = solucionar n (pulsar n t x) xs
solucionar _ _ _ = False		--si no se puede meter por ningun otro sitio, no hay solucion

--obtiene las soluciones validas del juego
lights:: Int-> [(Int,Int)] -> [[(Int,Int)]]
lights n t = [x|x<-soluciones n, solucionar n t x]

--------------------------------------------------------------------------------------------------
---------------------------AMPLIACION 1    -   LIGHTS ON------------------------------------------
--------------------------------------------------------------------------------------------------
--comprueba si un elemento pertenece a una lista
member:: Eq a => [a] -> a -> Bool
member [] _ = False
member (x:xs) y = (x == y || member xs y)

--comprueba si dos listas sin repetidos son iguales
iguales::Eq a =>[a] -> [a] -> Bool
iguales l1 l2 = (length l1 == length l2) && foldr (&&) True (map (member l1) l2)

--intenta solucionar un tablero con una solucion
solucionar2:: Int -> [(Int,Int)] -> [(Int,Int)]-> Bool
solucionar2 n t [] = iguales t (tablero n)
solucionar2 n t (x:xs) = solucionar2 n (pulsar n t x) xs

--La solcion consiste en obtener el tablero entero encendido
lightsOn::Int-> [(Int,Int)] -> [[(Int,Int)]]
lightsOn n t = [x|x<-soluciones n, solucionar2 n t x]


--------------------------------------------------------------------------------------------------
---------------------------AMPLIACION 2    -   SPECIAL LIGHTS------------------------------------
--------------------------------------------------------------------------------------------------
--dada una posicion del tablero, obtenemos el resultado de pulsar una casilla
pulsarP:: Int->[(Int,Int)]->(Int,Int)->((Int,Int)->[(Int,Int)])->[(Int,Int)]
pulsarP n xs c f = xor xs (purgar n (f c))

--intenta solucionar un tablero con una solucion
solucionarP:: Int -> [(Int,Int)] -> [(Int,Int)]-> ((Int,Int)->[(Int,Int)]) ->Bool
solucionarP _ [] [] _  = True
solucionarP n t (x:xs) f = solucionarP n (pulsarP n t x f) xs f
solucionarP _ _ _ _ = False		--si no se puede meter por ningun otro sitio, no hay solucion

--obtiene las soluciones validas del juego
specialLights:: Int-> [(Int,Int)] -> ((Int,Int)->[(Int,Int)]) -> [[(Int,Int)]]
specialLights n t f = [x|x<-soluciones n, solucionarP n t x f]