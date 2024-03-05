<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>用户管理</title>
    <link href="../css/manage_users.css" rel="stylesheet">
</head>
<body>
    <div class="box">
        <h1>用户管理</h1>
        <table>
            <tr>
                <th>用户名</th>
                <th>密码</th>
                <th>用户文件夹</th>
            </tr>
            <?php
            require 'connect_db.php';
            $sql = "SELECT user_name, user_folder, password FROM user WHERE user_name != 'diurnal'";
            $result = $conn->query($sql);
            if ($result->num_rows > 0){
                while ($row = $result->fetch_assoc()){
                    echo "<tr>";
                    echo "<td>" . $row["user_name"] . "</td>";
                    echo "<td>" . $row["password"] . "</td>";
                    echo "<td>" . $row["user_folder"] . "</td>";
                    echo "</tr>";
                }
            }
            $conn->close();
            ?>
        </table>
    </div>
</body>
</html>
