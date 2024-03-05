<?php
session_start();
$user_name = $_SESSION['user_name'];
$maxFileSize = 10000000;//文件大小限制为10mb以下
if (isset($_FILES['file'])){
    $file = $_FILES['file'];
    if ($file['size'] > $maxFileSize){
        echo "文件太大，不能上传！";
    } 
    else{
        $uploadFile = '../users/' . $user_name . '/' . basename($file['name']);
        move_uploaded_file($file['tmp_name'], $uploadFile);
    }
}
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>上传文件</title>
        <link href="../css/upload.css" rel="stylesheet">
    </head>
    <body>
        <div class="box">
            <div class="title">文件上传</div>
            <form method="post" action="" enctype="multipart/form-data">
                <input type="file" name="file" required>
                <input type="submit" value="上传"><br>
            </form>
            <a href="./index.php"><input type="button" value="返回主页 "></a>
        </div>
    </body>
</html>
