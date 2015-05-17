<HTML>
<HEAD>
<TITLE>Productos</TITLE>
</HEAD>
<BODY BGCOLOR="Black">
<A name="arriba"></A>
<p><B><FONT COLOR="#FFFFFF" SIZE="+2">Elige la categorias que deseas ver:</FONT></B>
<p>





<?php

echo " <SELECT NAME='LISTA' SIZE=1> ";


$link = mysql_connect ("localhost", "root");
if (!$link)
MensajeError("No se pudo conectar");
else{
if (!mysql_select_db("tiendaonline", $link))
MensajeError ("No existe la Base de datos");
else{
$ConsultaSQL="SELECT Tipo from productos";
$resultado = mysql_query($ConsultaSQL, $link);
$fila = mysql_fetch_array($resultado);
while ($fila!=false)
{

echo ("<OPTION VALUE='".$fila[0]."'>".$fila[0]."</OPTION>");
$fila = mysql_fetch_array($resultado);
}
}
}
?>
</select>










<p>
<p>
<B><FONT COLOR="#FFFFFF" SIZE="+1">Nota: Haga click en las imagenes para ampliarlas </FONT></B>
<br><B><FONT COLOR="#FFFFFF" SIZE="+1"><a href="#arriba" target="_self"> Subir </a></FONT></B>
</BODY>

</HTML>





/*<H2><FONT COLOR="#FFFFFF">RATONES</FONT></H2>
<table width="100%" border="3" cellspacing="2" cellpadding="1">
  <tr>
    <th bgcolor="#FFFFFF" >Nombre:</th>
    <th bgcolor="#FFFFFF" >TRUST MINI OPTICO 2520P</th>
    <th bgcolor="#FFFFFF">S96 NEGRO PS2 OPTICO OEM</th>
    <th bgcolor="#FFFFFF">RATON LOGITECH G9 LASER </th>
  </tr>
  <tr>
    <th bgcolor="#FFFFFF">Imagen:</th>
    <td bgcolor="#FFFFFF"><a href="Img/raton1.jpg" target="_blank"><img src="Img/raton1.jpg" width="324" height="169"></a></td>
    <td bgcolor="#FFFFFF"><a href="Img/raton2.jpg" target="_blank"><img src="Img/raton2.jpg" width="324" height="169"></a></td>
    <td bgcolor="#FFFFFF"><a href="Img/raton3.jpg" target="_blank"><img src="Img/raton3.jpg" width="324" height="169"></a></td>
  </tr>
  <tr>
    <th bgcolor="#FFFFFF" >Precio:</th>
    <td bgcolor="#FFFFFF"><div align="center">7,70€</div></td>
    <td bgcolor="#FFFFFF"><div align="center">5,40€</div></td>
    <td bgcolor="#FFFFFF"><div align="center">71,10€</div></td>
  </tr>
</table>
<p>
<H2><font color="#FFFFFF">TECLADOS</font></H2>
<table width="100%" border="3" cellspacing="2" cellpadding="1">
  <tr>
    <th bgcolor="#FFFFFF" >Nombre:</th>
    <th bgcolor="#FFFFFF" >G15 KEYBOARD USB</th>
    <th bgcolor="#FFFFFF">UNYKA 3 EN 1 MULTIMEDIA</th>
    <th bgcolor="#FFFFFF">GENIUS KB600 OPTICO NEGRO</th>
  </tr>
  <tr>
    <th bgcolor="#FFFFFF">Imagen:</th>
    <td bgcolor="#FFFFFF"><a href="Img/teclado1.jpg" TARGET="_blank"><img src="Img/teclado1.jpg" width="324" height="169"></a></td>
    <td bgcolor="#FFFFFF"><a href="Img/teclado2.jpg" TARGET="_blank"><img src="Img/teclado2.jpg" width="324" height="169"></a></td>
    <td bgcolor="#FFFFFF"><a href="Img/teclado3.jpg" TARGET="_blank"><img src="Img/teclado3.jpg" width="324" height="169"></a></td>
  </tr>
  <tr>
    <th bgcolor="#FFFFFF" >Precio:</th>
    <td bgcolor="#FFFFFF"><div align="center">83,10€</div></td>
    <td bgcolor="#FFFFFF"><div align="center">14,30€</div></td>
    <td bgcolor="#FFFFFF"><div align="center">16,10€</div></td>
  </tr>
</table>
<p>
<H2><font color="#FFFFFF">MONITORES</font></H2>
<table width="100%" border="3" cellspacing="2" cellpadding="1">
  <tr>
    <th bgcolor="#FFFFFF" >Nombre:</th>
    <th bgcolor="#FFFFFF" >LG LCD L196WTQ-SF 19 PLATA </th>
    <th bgcolor="#FFFFFF">MONITOR TFT 20W SAMSUNG SM2043NW</th>
    <th bgcolor="#FFFFFF">MON 20 TFT LG L204WS-SF PAN </th>
  </tr>
  <tr>
    <th bgcolor="#FFFFFF">Imagen:</th>
    <td bgcolor="#FFFFFF"><a href="Img/mon1.jpg" TARGET="_blank"><img src="Img/mon1.jpg" width="324" height="169"></a></td>
    <td bgcolor="#FFFFFF"><a href="Img/mon2.jpg" TARGET="_blank"><img src="Img/mon2.jpg" width="324" height="169"></a></td>
    <td bgcolor="#FFFFFF"><a href="Img/mon3.jpg" TARGET="_blank"><img src="Img/mon3.jpg" width="324" height="169"></a></td>
  </tr>
  <tr>
    <th bgcolor="#FFFFFF" >Precio:</th>
    <td bgcolor="#FFFFFF"><div align="center">146,30€</div></td>
    <td bgcolor="#FFFFFF"><div align="center">139,50€</div></td>
    <td bgcolor="#FFFFFF"><div align="center">145,60€</div></td>
  </tr>
</table>*/