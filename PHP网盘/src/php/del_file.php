<?php
session_start();
$user_name = $_SESSION['user_name'];
$file_dir = "../users/" . $user_name;
if (isset($_GET['filename'])){
    $filename = $_GET['filename'];
    $file_path = $file_dir . '/' . $filename;
    unlink($file_path);
    header("location:./index.php");
}
