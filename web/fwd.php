<?php

$stream = "http://live.kboo.fm:8000/high";
$st = fopen($stream, "rb");

foreach($http_response_header as $header)
{
	header($header);
}

while(!feof($st))
{
	print (fgets($st));
}

fclose($st);

?>
