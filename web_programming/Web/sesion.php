<?php
if( $_SESSION["acceso"]== "si"){
	echo("<script>location.href='sesion2.php'</script>");
	}
?>

<HTML>
<body BGCOLOR=#000000>
<form name="form1" method="post" action="iniciosesion.php">
  <table width="991" border="0" cellpadding="0" cellspacing="0">
    <tr>
      <td height="176" colspan="6" valign="top"></td>
    </tr>
    <tr>
      <td width="357" height="27">&nbsp;</td>
      <td width="27" rowspan="4" valign="top" bgcolor="#666666"></td>
      <td width="182" bgcolor="#666666"></td>
      <td width="64" bgcolor="#666666"></td>
      <td width="25" rowspan="4" valign="top" bgcolor="#666666"></td>
      <td width="336"></td>
    </tr>
    <tr>
      <td height="46">&nbsp;</td>
      <td colspan="2" valign="top" bgcolor="#666666"><label><FONT COLOR=#FFFFFF>Contraseña:</FONT>
          <input name="password" type="password" id="password">
      </label></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td height="26">&nbsp;</td>
      <td bgcolor="#666666">&nbsp;</td>
      <td valign="top" bgcolor="#666666"><label>
      <input type="submit" name="Submit" value="Entrar">
      </label></td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td height="19">&nbsp;</td>
      <td bgcolor="#666666">&nbsp;</td>
      <td bgcolor="#666666">&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td height="83">&nbsp;</td>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
  </table>
</form>
</body>
</HTML>