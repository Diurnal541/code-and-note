<?php
require './connect_db.php';
session_start();
function check($string)
{
    $postfilter = "#(\s)|(/\*.*\*/)|file|insert|<|and|floor|ord|char|ascii|mid|left|right|hex|sleep|benchmark|substr|@|`|delete|like|union|select|update|drop|exec|xp_cmdshell#i";
    if (preg_match($postfilter, $string, $matches)) {
        echo "<script>alert('hacker!')</script>";
        die();
    } else
        return $string;
}

if (isset($_POST['username']) && isset($_POST['password'])) {
    $username = check($_POST['username']);
    $password = hash('sha256', $_POST['password']);
    $sql = "SELECT * FROM user WHERE username = '$username' and password = '$password'";
    $query = mysqli_query($conn, $sql);
    if (mysqli_num_rows($query) == 1) {
        $_SESSION['username'] = $username;
        setcookie("A", 1, time() + 3600);
        if ($username == 'F1ag') {
            echo "<script>location='./F10g.php'</script>";
        } else {
            echo "<script>alert('登录成功，欢迎您');location='./login.php'</script>";
        }
    } else {
        echo "<script>alert('登录失败，请检查用户名和密码');location='./index.php'</script>";
    }
}
require './login.html';
