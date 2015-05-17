<?php
$link = mysql_connect ("localhost", "Curso", "cursoweb");
if (!$link)
echo("ERROR");
else{
if (!mysql_select_db("tiendaonline", $link))
echo("ERROR");
else{
$Consulta = "insert into noticias values('".$_POST["titulo"]."','".$_POST["fecha"]."','".$_POST["noticia"]."')";
echo $Consulta;
$resultado = mysql_query($Consulta, $link);
echo ("<script>location.href='empleado2.php'; alert('Inserccion realizada'); </script>");


}
}
?>