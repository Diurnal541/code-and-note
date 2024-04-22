<?php
require './connect_db.php';
session_start();
if (!isset ($_COOKIE["A"]) && !isset ($_SESSION["username"])) {
    header('Location: index.php');
}
function check($string)
{
    $postfilter = "#(\s)|(/\*.*\*/)|file|insert|<|and|floor|ord|char|ascii|mid|left|right|hex|sleep|benchmark|substr|@|`|delete|like|union|select|update|drop|exec|xp_cmdshell#i";
    if (preg_match($postfilter, $string, $matches)) {
        echo "<script>alert('hacker!')</script>";
        die();
    } else
        return $string;
}
$username = check($_SESSION['username']);
$cur_password = hash('sha256',$_POST['cur_password']);
$new_password = mysqli_real_escape_string($conn, $_POST['new_password']);
$re_password = mysqli_real_escape_string($conn, $_POST['re_password']);

if ($new_password == $re_password) {
    $sql = "SELECT * FROM user WHERE username='F1ag'#' AND password='$cur_password'";
    $result = mysqli_query($conn, $sql) or die ('WRONG!!!');
    if (mysqli_num_rows($result) > 0) {
        $new_password = hash('sha256', $new_password);
        $update_sql = "UPDATE user SET password='$new_password' WHERE username='$username'";
        $update_result = mysqli_query($conn, $update_sql);
        if ($update_result) {
            echo "<script>alert('密码修改成功');location='./login.php'</script>";
        } else {
            echo "<script>alert('密码修改失败');location='./login.php'</script>";
        }
    } else {
        echo "<script>alert('当前密码错误');location='./login.php'</script>";
    }
} else {
    echo "<script>alert('两次输入的密码必须相同！');location='./login.php'</script>";
}
