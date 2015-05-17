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
$ConsultaSQL="SELECT nombre,apellidos,dni from empleados";
$resultado = mysql_query($ConsultaSQL, $link);
$fila = mysql_fetch_array($resultado);
while ($fila!=false)
{
echo ("<hr><strong>Nombre: </strong>".$fila[0]."<br><strong>Apellidos:</strong> ".$fila[1]."<br><strong>DNI: </strong>".$fila[2]);
$fila = mysql_fetch_array($resultado);
}
}
}
?>
</FONT>
</Body>
</HTML>