<HTML>
<HEAD>
<TITLE>Menu</TITLE>
<script>
var b=1;
var mensaje='Bienvenidos a Tienda Online.';
var temp='';
function Mostrar() {

	temp=mensaje.substring(0,b);
	window.status=temp;
	b++;
	
	if(b>mensaje.length){
		b=0;
		setTimeout("Mostrar()",1000); 
		}
	else{
		setTimeout("Mostrar()",50); 
		}
	
}
</script>
</HEAD>
<BODY BGCOLOR="Black" onLoad="Mostrar()">
<!este menu debe ir modificandose cuando se añadan nuevas opciones>
<br>
<br>
<br><br><br><br><br><br>
<FONT color="#0000FF" size="+3"> Menu </FONT>
<hr>
<FONT COLOR="#FFFF00" size="+2">
<ol>
  <li><a href="ppal.php" target="PRINCIPAL">Portada.</a></li>
  <li><a href="productos.php" target="PRINCIPAL">Productos.</span></a></li>
  <li><a href="pedido.html" target="PRINCIPAL">Pedido.</a></li><br>
  <li><a href="sesion.php" target="PRINCIPAL">Jefe.</a></li>
  <li><a href="empleado.php" target="PRINCIPAL">Empleados.</a></li>
</ol>
</FONT>
<hr>
</BODY>

</HTML>