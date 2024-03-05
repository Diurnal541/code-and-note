<?php
require 'connect_db.php';
if (isset($_POST['user_name']) && isset($_POST['password'])){
    $user_name = $_POST["user_name"];
    $password = $_POST["password"];
    $sql = "SELECT user_name, password FROM user WHERE user_name = '$user_name' AND password = '$password';";
    $result = mysqli_query($conn, $sql);
    $row = mysqli_fetch_assoc($result);
    if (!$row){
        echo "<script>alert('账号不存在或密码错误，点击前往注册');location='./register.php'</script>";
    } 
    else{
        session_start();
        $_SESSION['user_name'] = $_POST['user_name'];
        if ($_POST['user_name'] === "diurnal") {
            echo "<script>alert('登录成功，欢迎您，超级管理员');location='./s_index.php'</script>";
        } 
        else{
            echo "<script>alert('登录成功，欢迎您');location='./index.php'</script>";
        }
    }
}
require '../html/login.html';
