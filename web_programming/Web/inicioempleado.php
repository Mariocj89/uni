<HTML>
<Body BGCOLOR=#000000>
<Font COLOR=#FFFFFF>
<BR><BR><BR><BR><BR><BR><BR><BR><BR><BR>

<?php
$link = mysql_connect ("localhost", "Curso", "cursoweb");
if (!$link)
MensajeError("No se pudo conectar");
else{
if (!mysql_select_db("tiendaonline", $link))
MensajeError ("No existe la Base de datos");
else{
$ConsultaSQL="SELECT nombre,contrasenia,dni from empleados";
$resultado = mysql_query($ConsultaSQL, $link);
$fila = mysql_fetch_array($resultado);
while ($fila!=false)
{
if(  $fila[2] == $_REQUEST["dni"] && $fila[1] == $_REQUEST["password"] ){
	echo("<script>location.href='empleado2.php'; </script>");}
$fila = mysql_fetch_array($resultado);
}
echo("<script> alert('contraseña incorrecta'); location.href='empleado.php' </script>");
}
}
?>
</FONT>
</Body>
</HTML>