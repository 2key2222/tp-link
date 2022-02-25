<?php

header("Content-type: text/plain; charset=utf-8");
$url = './pages/userrpm/accessControl.html';
if(isset($_GET['href'])){
    $url = './pages/userrpm/'.$_GET['href'];
}
$t = file_get_contents($url);
echo $t;

?>