<?php
require './connect_db.php';
if (isset($_POST['user_name']) && isset($_POST['password'])){
    $user_name = $_POST['user_name'];
    $password = $_POST['password'];
    if ($user_name == '' || $password == ''){
        exit('账号和密码都不能为空');
    } 
    else{
        $select = "select user_name from user where user_name = '$user_name'";
        $result = mysqli_query($conn, $select);
        $row = mysqli_fetch_assoc($result);
        if (!$row){
            $user_folder = '../users/' . $user_name;
	    mkdir($user_folder);
            $sql = "insert into user(user_name,password,user_folder) values ('$user_name','$password','$user_folder');";
            if (mysqli_query($conn, $sql)){
                echo "<script>alert('注册成功，请登录');location='./login.php'</script>";
            } 
            else{
                echo "<script>alert('注册失败，请重新注册');location='./register.php'</script>";
            }
        } 
        else{
            echo "<script>alert('用户已经存在，请登录');location='./login.php'</script>";
        }
    }
}
require '../html/register.html';
