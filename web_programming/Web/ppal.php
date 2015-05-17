<HTML>
<HEAD>
<TITLE>Portada</TITLE>
<script>
var cantidad=9
function mover(){
	
	var VCapa=document.getElementById('bienvenida');
	if((parseInt(VCapa.style.left)<330)){
		VCapa.style.left=parseInt(VCapa.style.left)+cantidad;
		setTimeout("mover()",0)
		}
	} 

</script> 
</HEAD>
<BODY BGCOLOR="Black" onLoad="mover()">

<div id="bienvenida" style="position:absolute; width:353px; height:300px; border:1;background-color: #000000; left: -360; top: 199px;border:2px"> 
<div align="center">
  <p><img src="img/titulo.jpg" name="Imagen" align="middle" width="324" height="169" ><br> Bienvenidos a la Tienda!</p>
  <input type="button" value="CERRAR" onMouseDown="bienvenida.style.left=-1000">
</div>
</div>




<FONT COLOR="#FFFFCC"><U><h1>Bienvenido a Tienda Online,</h1></U></FONT><p>
<FONT COLOR="#CCFFCC" Size="+1" face="Times New Roman"> En nuestra página podrás adquirir los mejores productos del mercado.<br> En la columna de la izquierda te proporcionamos un indice para que puedas navegar rapidamente por nuestra pagina.<br> 
Gracias por usar nuestro servicio.</FONT><hr>
<p>



<?php
$link = mysql_connect ("localhost", "Curso", "cursoweb");
if (!$link)
MensajeError("No se pudo conectar");
else{
if (!mysql_select_db("tiendaonline", $link))
MensajeError ("No existe la Base de datos");
else{
$ConsultaSQL="SELECT titulo,fecha,texto from noticias";
$resultado = mysql_query($ConsultaSQL, $link);
$fila = mysql_fetch_array($resultado);
while ($fila!=false)
{
echo "<strong><u><FONT size=+3 COLOR=#00FFFF>";
echo ($fila[0]) ;
echo "</strong></font></u>";

echo "<div align='center'><strong><FONT size=+1 COLOR=#FFFFFF>";
echo ($fila[1]) ;
echo "</strong></font></div>";


echo "<br><br><strong><FONT COLOR=#FFFFFF>";
echo ($fila[2]) ;
echo "</strong></font><hr><br><br>";




$fila = mysql_fetch_array($resultado);

}
}
}
?>

<DIV align="right" style="bottom:">
<font color="#CCFF00"><STRONG>Webmaster:</STRONG><br><I>Mario Corchero Jiménez.</I><br><EM>Para Programacion Web Unex</EM></font>
</DIV>


</BODY>

</HTML>


