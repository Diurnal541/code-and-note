<?php
$username = "root";
$password = "czh051118";
$database = "ctf";
$host = 'localhost';
$conn = new mysqli($host, $username, $password, $database);
if (!$conn) {
    die ("Connect failed:" . mysqli_connect_error());
}
