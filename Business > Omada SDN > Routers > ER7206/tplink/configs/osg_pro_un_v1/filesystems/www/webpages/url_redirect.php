<?php

header("Content-type: text/json; charset=utf-8");

$base_url = "http://localhost/strange/src/data";

$url = $_SERVER['PHP_SELF'];
$url = makeUrlPathReal($url);

$params = $_SERVER['QUERY_STRING'];

if($params !== ""){
	$url = $url.'?'.$params;
}

$url = strstr($url, '/cgi');
$url = makeUrlPathReal($url);

function makeUrlPathReal($url_old)
{
	$url_old = str_ireplace("cgi-bin2","cgi-bin",$url_old);
	return $url_old;
}

function trimSlant($url_old)
{
	if (substr($url_old, 0, 1) == '/')
	{
		$url_old = substr($url_old, 1, strlen($url_old));
	}
	if (substr($url_old, -1, 1) == '/')
	{
		$url_old = substr($url_old, 0, strlen($url_old)-1);
	}
	return $url_old;
}

function isstok($string)
{
	$preg = '/^[a-z0-9]+$/';
	if (preg_match($preg, $string))
	{
		return 1;
	}
	return 0;
}

function compareStringWithREX($string1, $string2)
{
	$headLen = strlen("/cgi-bin/luci/;stok=");
	
	if (strcmp(substr($string1, 0, $headLen), substr($string2, 0, $headLen)) == 0)
	{
		if (strcmp(strstr($string1, '/admin'), strstr($string2, '/admin')) == 0)
		{
			$stok1 = substr($string1,$headLen,
							strlen($string1)-$headLen-strlen(strstr($string1, '/admin')));
			$stok2 = substr($string2,$headLen,
							strlen($string2)-$headLen-strlen(strstr($string2, '/admin')));
			
			if (isstok($stok1) &&
				isstok($stok2))
			{				
				return 0;
			}
			else
			{
				/*
				echo $stok1."</br>";
				echo $stok2."</br>";
				echo 1;
				*/
			}
			
		}
		else
		{
			/*
			echo "-----------------</br>";
			echo strstr($string1, '/admin');
			echo "</br>";
			echo strstr($string2, '/admin');
			echo "</br>";
			*/
		}
	}
	else
	{
		//echo 'string1: '.$string1.'</br>';
		//echo 'string2: '.$string2.'</br>';
	}
	return 1;
}

function listDir($dir)
{
	if(is_dir($dir))
	{
		if ($dh = opendir($dir))
		{
			while (($file = readdir($dh)) != false)
			{
				if (is_dir($dir."/".$file))
				{
					if ($file != "." && $file != "..")
					{
						listDir($dir."/".$file."/");
					}
				}
				else
				{
					findJsonFromFile($dir."/".$file);
				}
			}
		}
	}
}

function findJsonFromFile($file)
{
	global $url;
	global $base_url;
	$fd = fopen($file, "r");
	while(!feof($fd))
	{
		$fileLine = fgets($fd);
		$fileLine = str_ireplace('\t', ' ', $fileLine);
		//echo $fileLine.'</br>';

		$preg = '/ +/';
		$fileLine = preg_replace($preg, ' ', $fileLine);
		//echo 'final'.$fileLine.'</br>';

		$lineArr = explode(" ", $fileLine);
		
		if (strcmp(trimSlant($lineArr[0]), trimSlant($url)) == 0)
		{
			$filename = trim(trimSlant($lineArr[1]));
			$headerUrl = $base_url.'/'.$filename;
			//echo $headerUrl;
			//header("location: ".$headerUrl);
            // sleep(0.8);
			readfile($headerUrl);
			
			exit;
		}
	}
}

listDir("./url_to_json");

//echo "hello";

?>