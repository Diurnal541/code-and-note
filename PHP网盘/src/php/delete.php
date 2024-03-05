<?php
require 'connect_db.php';
session_start();
$user_name = $_SESSION['user_name'];
$sql = "DELETE FROM user where user_name='$user_name'";
$user_folder = "../users/" . $user_name;
if (mysqli_query($conn, $sql)){
    if (is_dir($user_folder)){
        $files = array_diff(scandir($user_folder), array('.', '..'));
        foreach ($files as $file){
            (is_dir("$user_folder/$file")) ? deleteFolder("$user_folder/$file") : unlink("$user_folder/$file");
        }
        rmdir($user_folder);
    }
    echo "<script>alert('用户删除成功，点击跳转登录页面');location='./login.php'</script>";
} 
else{
    echo "<script>alert('用户删除失败，点击返回');location='./index.php'</script>";
}
function deleteFolder($user_folder){
    $files = array_diff(scandir($user_folder), array('.', '..'));
    foreach($files as $file){
        (is_dir("$user_folder/$file")) ? deleteFolder("$user_folder/$file") : unlink("$user_folder/$file");
    }
    return rmdir($user_folder);
}
