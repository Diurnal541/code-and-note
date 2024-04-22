<?php
require './connect_db.php';
session_start();
if (!isset ($_COOKIE["A"])) {
    if (!isset ($_SESSION["username"])) {
        header('Location: index.php');
    }
    header('Location: index.php');
}
?>
<html>
    <head>
        <title>用户页面</title>
    </head>
    <body>
        <font size="4">你的名字是：</font>
        <?php
        echo $_SESSION['username'];
        ?>
        </br><font size="4">在这里修改你的密码</font></br>
        <form method="POST" action="./change_password.php">
            <tr><th>老密码：</th><td><input type="password" name="cur_password"></td></tr></br>
            <tr><th>新密码：</th><td><input type="password" name="new_password"></td></tr></br>
            <tr><th>再输入一遍：</th><td><input type="password" name="re_password"></td></tr></br>
            <tr><th></th><td><input type="submit" value="确认"><a href="./index.php"><input type="button" value="返回登录"></a></td></tr>
        </form>
    </body>
</html>