<?php
session_start();
$user_name = $_SESSION['user_name'];
$filename = $_GET['filename'];
$file_dir = "../users/" . $user_name;//文件目录
$file_path = $file_dir . '/' . $filename;//文件名
$limit_rate = 60; //限制速率为60kb
if (!file_exists($file_path)){
    echo '文件不存在';
    exit;
}
header('Content-Description: File Transfer');//一些HTTP响应头
header('Content-Type: application/octet-stream');
header('Content-Disposition: attachment; filename="' . $filename . '"');
header('Expires: 0');
header('Cache-Control: must-revalidate');
header('Pragma: public');
header('Content-Length: ' . filesize($file_path));
$handle = fopen($file, 'rb');//用于打开文件，并返回一个文件指针$handle，$file表示要打开的文件，参数r表示只读，参数b表示以二进制模式打开文件
while (!feof($handle)){//这个函数用于检查文件指针所指向的文件是否已经达到末尾，返回一个布尔值
    echo fread($handle, $limit_rate * 1024);//以指定速率输出文件
    flush();//这个函数的作用是将当前缓冲区的内容立即发送给浏览器，如果不使用这个函数，那么输出的内容则会先缓存在服务器端，直到脚本执行完毕才会一次性发送给浏览器，这样就无法实现限速下载
    sleep(1);//每次输出内容后停顿1秒，以实现限速
}
fclose($handle);
exit;
