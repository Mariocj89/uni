<?php
$link = mysql_connect ("localhost", "Curso", "cursoweb");
if (!$link)
echo("ERROR");
else{
if (!mysql_select_db("tiendaonline", $link))
echo("ERROR");
else{
$Consulta = "insert into productos values('".$_POST["Nombre"]."','".$_POST["tipo"]."','".$_POST["precio"]."','".$_POST["img"]."')";
echo $Consulta;
$resultado = mysql_query($Consulta, $link);
echo ("<script>location.href='sesion2.php'; alert('Inserccion realizada'); </script>");
}
}
?>