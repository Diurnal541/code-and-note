<?php
session_start();
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>网盘</title>
    <link href="../css/index.css" rel="stylesheet">
</head>
<body>
    <div class="box">
        <div class="top">
            <div class="title">网盘管理系统</div>
            <div class="func">
                <a href="./upload.php">上传文件</a>
                <a href="./delete.php">删除该用户</a>
                <a href="./logout.php">退出登录</a>
            </div>
        </div>
        <div class="files">
            <?php
            $user_name = $_SESSION['user_name'];
            $file_dir = "../users/" . $user_name;
            $files = scandir($file_dir);
            foreach ($files as $file){
                if ($file !== '.' && $file !== '..'){
                    $extension = pathinfo($file, PATHINFO_EXTENSION);
                    if (in_array($extension, array('jpg', 'jpeg', 'png', 'gif'))){
                        echo '<div class="image">';
                        echo '<img src="' . $file_dir . '/' . $file . '">';
                        echo '<div class="action">';
                        echo '<a href="./del_file.php?filename=' . urlencode($file) . '">删除</a>';
                        echo '<a href="./download.php?filename=' . urlencode($file) . '">下载</a>';
                        echo '</div>';
                        echo '</div>';
                    }
                    else{
                        echo '<div class="file"> ' . $file . '';
                        echo '<div class="action">';
                        echo '<a href="./del_file.php?filename=' . urlencode($file) . '">删除</a>';
                        echo '<a href="./download.php?filename=' . urlencode($file) . '">下载</a>';
                        echo '</div>';
                        echo '</div>';
                    }
                }
            }
            ?>
        </div>
    </div>
</body>
</html>
