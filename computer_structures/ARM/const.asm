
ESCAPE	EQU 27

;Parametros del cuadrado que "delimita" la pantalla
cuadrado_x EQU 10
cuadrado_y EQU 10
cuadrado_alto EQU 180
cuadrado_ancho EQU 300


;parametros de la circunferencia que contiene la flecha
circunf_x EQU 160
circunf_y EQU 170
circunf_radio EQU 10
circunf_color EQU 4

;Parametros del cursor
cursor_color EQU 1
cursor_x_ini  EQU circunf_x
cursor_y_ini  equ circunf_y-10

;Lugar donde se colocara el angulo
angulo_x EQU 25
angulo_y EQU 22

;retardo a realizar
ciclos_40ms EQU 47727
ciclos_1ms EQU 1193


;coordenadas
coord_por_cuadrante equ 10 ;numero de coordenadas que tendra cada cuadrante

