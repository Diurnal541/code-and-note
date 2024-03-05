<?php
$user_name = "root";
$password = "czh051118";
$database = "db";
$host = 'host.docker.internal';
$conn = new mysqli($host, $user_name, $password, $database);
if (!$conn){
    die("Connect failed:" . mysqli_connect_error());
}

