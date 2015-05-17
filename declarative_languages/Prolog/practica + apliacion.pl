%pulsa(+C,+N,-O) devuelve en O las casillas que se marcan al pulsar C con una anchura de tablero N
				 %mira una a una (a traves de una funcion sumergida) cuales se pueden pulsar
pulsa(C,N,[C|X]):- pulsa(C,N,X,4).
pulsa(casilla(A,B),N,[casilla(A,B1)|Xs],4):- B1 is B+1, X1 is B mod N,X1 \= 0, pulsa(casilla(A,B),N,Xs,3).
pulsa(casilla(A,B),N,Xs,4):-  X1 is B mod N,X1 = 0, pulsa(casilla(A,B),N,Xs,3).
pulsa(casilla(A,B),N,[casilla(A,B1)|Xs],3):- B1 is B-1, X1 is B mod N, X1 \= 1, pulsa(casilla(A,B),N,Xs,2).
pulsa(casilla(A,B),N,Xs,3):- X1 is B mod N, X1 = 1, pulsa(casilla(A,B),N,Xs,2).
pulsa(casilla(A,B),N,[casilla(A1,B)|Xs],2):- A1 is A+1, X1 is A mod N, X1 \= 0, pulsa(casilla(A,B),N,Xs,1).
pulsa(casilla(A,B),N,Xs,2):- X1 is A mod N, X1 = 0, pulsa(casilla(A,B),N,Xs,1).
pulsa(casilla(A,B),N,[casilla(A1,B)],1):-  A1 is A-1, X1 is A mod N,X1 \= 1.
pulsa(casilla(A,_),N,[],1):-  X1 is A mod N,X1 = 1.

%pulsar(+I,+C,+N,-S) dada una posicion inicial del tablero I con una anchura N, pulsa la casilla C obteniendose la posicion S
pulsar(I,C,N,S):- pulsa(C,N,O), xor(I,O,S).

%xor(+L1,+L2,-L3) realiza una "xor" de L1 y L2 y la mete en L3
xor(L,[],L).
xor(L1,[X|Xs],R):- inserta(L1,X,R1), xor(R1,Xs,R).


%inserta(+L,+C,-O) inserta el elemento C si no esta en la lista L y si esta, lo borra, devuelve la nueva lista O
inserta([],C,[C]).
inserta([X|Xs],C,[X|Ys]):- X \= C, inserta(Xs,C,Ys).
inserta([X|Xs],X,Xs).

%lights(+N,+T,Rs). Un tablero T de N de ancho se resuelve pulsado las casillas Rs
					%Recorre una a una todas las casillas del tableo comprobando si al pulsarla se obtendria solucion
lights(N,T,Rs):- NN is (N*N),NN1 is NN-1, lights(N,T,Rs,NN1).
lights(_,[],[],(-1)).	
lights(N,T,[casilla(A,B)|Rs],It):- It@> (-1), nextIt(T,N,It,It1,A,B), pulsar(T,casilla(A,B),N,T2), lights(N,T2,Rs,It1).
lights(N,T,Rs,It):- It@> (-1), nextIt(T,N,It,It1,_,_), lights(N,T,Rs,It1).

%nextIt(I,+N,+It,-Its,-A,-B) dada una iteracion It y una anchura de tablero N, la posicion del tablero I se pasa "podar"
						%obtenemos la siguiente iteracion y la casilla a las que corresponde
nextIt(I,N,It,Its,A,B):- AuxA is It//N, A is AuxA +1, AuxB is It mod N,B is AuxB+1, Its is It-1, PodaA is A+1,podaRama(PodaA,I).

autor('Mario Corchero Jiménez').

%posiciones iniciales:
tablero(1,3,[casilla(1,1),casilla(1,2),casilla(2,1)]).
tablero(2,6,[casilla(6,6)]). %solo abordable gracias a la poda
tablero(3,4,[casilla(1,4),casilla(1,2),casilla(2,3),casilla(1,3)]).
tablero(4,3,[casilla(3,3),casilla(2,3),casilla(3,2)]).

%pruebas
prueba(1):- write('Prueba sobre inserta'),inserta([1,2,3],2,[1,3]), inserta([1,3],2,[1,3,2]), write('<--Correcta!').
prueba(2):- write('Prueba sobre nextIt'),nextIt([casilla(1,1)],3,3,2,2,1),nextIt([casilla(1,1)],4,1,0,1,2), write('<--Correcta!').
prueba(3):- write('Prueba sobre xor'),xor([1,2,3,4,5],[2,3],[1,4,5]), xor([1,2,3,4,5],[0,3],[1,2,4,5,0]),write('<--Correcta!').
prueba(4):- write('Prueba sobre pulsar'),tablero(1,N,I),pulsar(I,casilla(1,1),N,[]),
					pulsar(I,casilla(2,1),N,[casilla(1, 2), casilla(2, 2), casilla(3, 1)]),write('<--Correcta!').
prueba(5):- write('Prueba sobre lights'), tablero(1,N1,I1),lights(N1,I1,[casilla(1,1)]),
											tablero(4,N4,I4),lights(N4,I4,[casilla(3,3)]),
											tablero(2,N2,I2),lights(N2,I2,_),write('<--Correcta!').
											
											
											
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Ampliacion 1

%podaRama(+A,+I)  dadas dos coordenadas y una situacion del tablero, determina si hay posibilidad de solucion
podaRama(_,[]).
podaRama(A,[casilla(X,_)|Xs]):-  A@>= X, podaRama(A,Xs).

							
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Ampliacion 2

%OnlyLights(+N,+T,Rs). Resuelve el juego solo pulsando las casilla encendidas
onlyLights(N,I,Xs):- onlyLights(N,I,Xs,[]).
onlyLights(_,[],[],_).	
onlyLights(N,[T|Ts],[T|S],M):- not(pertenece(T,M)), pulsar([T|Ts],T,N,T2), onlyLights(N,T2,S,[T|M]).
onlyLights(N,[T|Ts],S,M):- not(pertenece(T,M)), aniadir(T,Ts,T2), onlyLights(N,T2,S,[T|M]).

aniadir(E,[ ], [E]).
aniadir(E,[X|Xs],[X|Rs]):-aniadir(E,Xs,Rs).

pertenece(X, [X|_]).
pertenece(X, [_|Ys]) :- pertenece(X,Ys).

