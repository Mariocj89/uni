#12/04/2011

#Mario Corchero Jiménez
#Manuel Cantonero Chamorro


#Se crea un objeto simulador
set ns [new Simulator]

#Se puede abrir un fichero que será utilizado para visualizar los datos de traza del NAM
set nf [open salida/out.nam w]
$ns namtrace-all $nf

#Definición del evento 'finish'
proc finish {} {
  global ns nf
  $ns flush-trace
  close $nf
  exec nam -a salida/out.nam &
 #Ejecutamos xgraph
  exec xgraph salida/CWND.tr salida/ssthresh.tr -t " " -geometry 800x400 -x Segundos -y CWND -tk -tkax &
  exit 0
}


#Abrimos los fichero de Xgraph
set f0 [open salida/CWND.tr w]
set f1 [open salida/ssthresh.tr w]

#Define a 'record' procedure
proc record {} {

        global AsrcEconomico f0 f1
        #Obtenemos una instancia del simulador
        set ns [Simulator instance]
        #Establecemos el tiempo después del cual el procedimiento volverá a ser ejecutado
        set time 0.0005
        #Obtenemos el valor de la ventana de congestión y ssthresh
        set cwnd0 [$AsrcEconomico set cwnd_]
        set ssthresh0 [$AsrcEconomico set ssthresh_]
        #Obtenemos el tiempo actual
        set now [$ns now]
        #Guardamos en el fichero el par de valores (tiempo cwnd)
        puts $f0 "$now $cwnd0"
        #Guardamos en el fichero el par de valores (tiempo sshthresh)
        puts $f1 "$now $ssthresh0"

        #Reprogramamos el procedimiento
        $ns at [expr $now+$time] "record"
}




#Se crean dos nodos y se asignan los identificadores 
set A [$ns node]
set B [$ns node]
set C [$ns node]
set D [$ns node]
for {set j 0} {$j<=6} { incr j } {
	set Ventas($j) [$ns node]
	set Informatica($j) [$ns node]
	set Economico($j) [$ns node]
	set RRHH($j) [$ns node]
}

#Creamos los enlaces dentro de los departamentos
set i 0
for {set j 0} {$j<=5} { incr j } {
	incr i
	$ns simplex-link $Ventas($j) $Ventas($i) 100Mb 0.1ms DropTail
}
$ns simplex-link $Ventas(6) $Ventas(0) 100Mb 0.1ms DropTail


for {set j 1} {$j<=6} { incr j } {
	$ns duplex-link $Informatica(0) $Informatica($j) 100Mb 0.1ms DropTail
	$ns duplex-link $RRHH(0) $RRHH($j) 100Mb 0.1ms DropTail
}


$ns duplex-link $Economico(0) $Economico(1) 100Mb 0.1ms DropTail
$ns duplex-link $Economico(0) $Economico(2) 100Mb 0.1ms DropTail
$ns duplex-link $Economico(1) $Economico(3) 100Mb 0.1ms DropTail
$ns duplex-link $Economico(1) $Economico(4) 100Mb 0.1ms DropTail
$ns duplex-link $Economico(2) $Economico(5) 100Mb 0.1ms DropTail
$ns duplex-link $Economico(2) $Economico(6) 100Mb 0.1ms DropTail

#Creamos los enlaces duplex entre los nodos
$ns duplex-link $A $Economico(0) 100Mb 0.01ms DropTail
$ns duplex-link $B $RRHH(0) 100Mb 0.01ms DropTail
$ns duplex-link $D $Ventas(0) 100Mb 0.01ms DropTail 
$ns duplex-link $D $Informatica(0) 100Mb 0.01ms DropTail 



#Creamos los enlaces simplex entre los nodos
$ns simplex-link $A $C 100Mb 0.1ms DropTail
$ns simplex-link $C $A 100Mb 0.1ms DropTail
$ns simplex-link $B $C 100Mb 0.1ms DropTail
$ns simplex-link $C $B 100Mb 0.1ms DropTail
$ns simplex-link $D $C 100Mb 1ms FQ
$ns simplex-link $C $D 100Mb 1ms DRR

$ns queue-limit $D $C 60

#Para visualizar datos de cola
#set redq [[$ns link $D $C] queue]
#set traceq [open salida/queue.tr w]
#$redq trace curq_
#$redq trace ave_
#$redq attach $traceq

set qmon [$ns monitor-queue $D $C [open salida/queue.tr w] 0.1]
[$ns link $D $C] queue-sample-timeout;

#Crear los agentes y asociarlos
set AsrcEconomico [new Agent/TCP]
set AsrcInformatica [new Agent/UDP]
set AdstVentas [new Agent/TCPSink]
set AsrcVentas2 [new Agent/TCP]
set AdstRRHH [new Agent/Null]
set AdstRRHH2 [new Agent/TCPSink]

#Asociar los agentes
$ns attach-agent $Economico(3) $AsrcEconomico
$ns attach-agent $Informatica(5) $AsrcInformatica
$ns attach-agent $Ventas(4) $AdstVentas
$ns attach-agent $Ventas(1) $AsrcVentas2
$ns attach-agent $RRHH(5) $AdstRRHH
$ns attach-agent $RRHH(2) $AdstRRHH2

#Realizar los connect
$ns connect $AsrcEconomico $AdstVentas
$ns connect $AsrcInformatica $AdstRRHH
$ns connect $AsrcVentas2 $AdstRRHH2


#Generamos tráfico
set ftpTEcoVent [new Application/FTP]
set expTVentRRHH2 [new Application/Traffic/Exponential]
set telnetTInfRRHH [new Application/Traffic/CBR]


$ftpTEcoVent attach-agent $AsrcEconomico
$telnetTInfRRHH attach-agent $AsrcInformatica
$expTVentRRHH2 attach-agent $AsrcVentas2


$telnetTInfRRHH set packetSize_ 300 #tamaño de paquete en bytes
$telnetTInfRRHH set interval_ 0.00001 #intervalo de tiempo entre paquetes
$telnetTInfRRHH set rate_ 70Mb      #tasa de 10 Mbit/s
$expTVentRRHH2 set PacketSize_ 210
$expTVentRRHH2 set burst_time_ 5ms
$expTVentRRHH2 set idle_time_ 5ms
$expTVentRRHH2 set rate_ 50Mb

#Generamos trafico intraDepartamento
for {set j 0} {$j<=7} { incr j } {
	set ag($j) [new Agent/TCP]
	incr j	
	set ag($j) [new Agent/TCPSink]
}

$ns attach-agent $Economico(4) $ag(0)
$ns attach-agent $Economico(6) $ag(1)
$ns attach-agent $Informatica(4) $ag(2)
$ns attach-agent $Informatica(6) $ag(3)
$ns attach-agent $Ventas(4) $ag(6)
$ns attach-agent $Ventas(6) $ag(7)
$ns attach-agent $RRHH(4) $ag(4)
$ns attach-agent $RRHH(6) $ag(5)

$ns connect $ag(0) $ag(1)
$ns connect $ag(2) $ag(3)
$ns connect $ag(4) $ag(5)
$ns connect $ag(6) $ag(7)

for {set j 0} {$j<=7} { incr j } {
set ftpIntraDep($j) [new Application/FTP]
$ftpIntraDep($j) attach-agent $ag($j)
incr j
}

#introducimos errores
set loss [new ErrorModel]
$loss set rate_ 0.001
$loss unit packet
$ns lossmodel $loss $C $D


#asignar colores
$AsrcInformatica set class_ 1
$AsrcEconomico set class_ 2
$AsrcVentas2 set class_ 3
$ns color 1 Blue
$ns color 2 Red
$ns color 3 Yellow


#iniciar el tráfico
$ns at 0.3 "$telnetTInfRRHH start"
$ns at 0.2 "$ftpTEcoVent start"
$ns at 7 "$telnetTInfRRHH stop"
$ns at 7 "$ftpTEcoVent stop"
$ns at 0.1 "$expTVentRRHH2 start"
$ns at 7 "$expTVentRRHH2 stop"
for {set j 0} {$j<=7} { incr j } {
$ns at 0.05 "$ftpIntraDep($j) start"
$ns at 7 "$ftpIntraDep($j) stop"
incr j
}

#Se le dice al objeto simulador que ejecute 'finish' a los 5 segundos
$ns at 0.0 "record"
$ns at 7.5 "finish"


#Se ejecuta la simulación
$ns run





