<?php 
	/** Proxy para permitir llamadas cross domain (diferente puerto = diferente dominio)*/
	
	include 'server.php';
	
	$token = $_GET["token"];
	$camara = $_GET["camara"];

	$url = $server."GetDetallesCamara?token=".$token."&camara=".urlencode($camara);
	$headers = get_headers($url );	

	if (!preg_match('/^HTTP\/\d\.\d\s+(200|301|302)/', $headers[0])){
		header('HTTP/1.0 404 Not Found');
	}
	else
	{	
		$res =  file_get_contents($url,FILE_TEXT);
		echo $res;
	}
?>