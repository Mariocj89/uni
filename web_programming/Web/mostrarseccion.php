<HTML>
<Body BGCOLOR=#000000>
<Font COLOR=#FFFFFF>
<BR><BR><BR><BR>

<?php
$link = mysql_connect ("localhost", "Curso", "cursoweb");
if (!$link)
MensajeError("No se pudo conectar");
else{
if (!mysql_select_db("tiendaonline", $link))
MensajeError ("No existe la Base de datos");
else{

$Aux=$_REQUEST["LISTA"];

$ConsultaSQL="SELECT Nombre,Tipo,Precio,Imagen from productos where Tipo='$Aux'";
$resultado = mysql_query($ConsultaSQL, $link);
$fila = mysql_fetch_array($resultado);

while ($fila!=false)
{




echo ("<div align='center'> 
<table width='75%' height='197' border='2' cellpadding='0' cellspacing='0' bordercolor='#0000FF' bgcolor='#999999'>
  <tr>
    <td width='58%' height='193' ><div align='center'><a target='blank' href='".$fila[3]."'><img src='".$fila[3]."' width='280' height='191'></a></div></td>
    <td width='42%' ><div align='center'><font color='#FFFFFF'><strong><font color='#000000'>Nombre: </font></strong><font color='#000000'>".$fila[0]."</font></font><font color='#000000'><br><strong>Tipo:</strong></font></font><font color='#000000'>".$fila[1]."<br><strong>Precio: </strong>".$fila[2]."€</font><br></div></td></tr></table></div><br><br>");






$fila = mysql_fetch_array($resultado);
}



}}

?>





</FONT>
</Body>
</HTML>