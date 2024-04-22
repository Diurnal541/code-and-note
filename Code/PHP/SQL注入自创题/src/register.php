<?php
require './connect_db.php';

if (isset ($_POST['username']) && isset ($_POST['password'])) {
    $username = mysqli_real_escape_string($conn, $_POST['username']);
    $password = hash('sha256',$_POST['password']);
    if ($username == '' || $password == '') {
        exit ('账号密码不能为空!');
    } else {
        $select = "select username from user where username = '$username'";
        $result = mysqli_query($conn, $select);
        $row = mysqli_fetch_row($result);
        if (!$row) {
            $sql = "insert into user(username, password) values ('$username','$password');";
            if (mysqli_query($conn, $sql)) {
                echo "<script>alert('注册成功，请登录');location='./index.php'</script>";
            } else {
                echo "<script>alert('注册失败，请重新注册');
                location='./register.php'</script>";
            }
        } else {
            echo "<script>alert('用户已存在，请登录');location='./index.php'</script>";
        }
    }
}
require './register.html';
