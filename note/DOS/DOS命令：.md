一.常用的DOS命令：

1.查看目录内容 dir

2.创建目录文件 md

3.打开指定目录命令 cd

4.删除当前指定的子目录 rd

5.改变当前盘符 盘符+冒号

6.文件复制拷贝 copy

7.显示文本文件内容命令 type

8.更改文件名 ren

9.删除文件命令 del

10.清楚屏幕命令 cls

11.退出命令 exit

12.修改CMD背景加字体颜色 color

13.取名字 title

14.将一个或多个文件从一个目录移动到指定的目录 move

15.查询解析域名的IP地址 nslookup

16.显示当前电脑的TCP/IP网络配置值 ipconfig

17.网络检测命令 ping

18.最基础命令 echo  

19.特殊命令：

1.修改文件属性 attrib

2.快速生成一个空的大文件 fsutil file createnew c:\system.ini 文件大小字节

3.修改关联性 assoc .txt=exefile

二.详细解析

1.DIR：

dir 查看当前目录中的文件和文件夹

dir 盘符：\文件名 查看指定目录下的文件和文件夹

dir /a 显示指定属性的文件夹

2.MD：

md 盘符：\文件名 在指定目录下新建一个文件夹

md 文件名 在当前目录下新建一个文件夹

3.CD:

cd 盘符：\文件名 切换到指定目录下

cd \ 返回根目录下

4.RD:

rd  盘符：\文件名 删除指定文件夹

rd . /s/q 删除所有文件夹

5.COPY:

copy 源文件 目的路径

eg：d:\test这个文件复制到D盘根目录下  copy d:\test\test.txt d:\

 注：copy只能复制文件，对于文件夹的复制，则需要另请高明

copy con 文件名.扩展名

（正文）

ctrl + z 结束编写      创建一个简单文本文件的命令    con  指的是计算机屏幕



输入hah.bat运行 

 

copy D:\hah\a\www.txt ..\b\ 将a中拷贝到B中（注：txt 空格..无空格\b\）



6.TYPE：

type +文件名.扩展名 |more    分页查看文本文件内容

7.REN:

ren 新名字 旧名字     修改文件和文件夹名字

8. DEL:

del 盘符：\文件名.扩展名 删除指定路径下的文件

del 文件名.扩展名 删除当前目录下的文件

del *.txt 表示将当前目录下的txt文件全部删除

del *.zip 表示将当前目录下的zip文件全部删除

del *.* /s/q 表示将包括根文件夹的文件全部删除

9.COLOR:

color + 两个参数 （第一个参数为背景颜色，第二个参数为字体颜色）



10.MOVE:

move 文件名.扩展名 c:\    将文件从D盘移动到C盘(注：移动时若不在当前目录下则需要用绝对路径）



11.NSLOOKUP:

nslookup +网站的域名         查询解析该域名的IP地址



12.IPCONFIG:

ipconfig   显示当前电脑的TCP/IP网络配置值 

ipconfig/all   显示当前电脑的TCP/IP网络配置值的详细信息

13.PING:

ping -l 数字 IP地址     修改ping包大小



ping 目标ip地址        测试网络连通性

ping -t 目标ip地址        一直ping

ping -n 数字 目标IP地址            修改ping包数量

（注：如果ping不通，对方可能不在线或者开着防火墙） 

14.特殊命令:

attrib +h +s    修改文件属性

 

fsutil file createnew c:\system.ini 102400000000    快速生成一个空的大文件

assoc txt=exefile   修改关联性

解： assoc txt=txtfile 

15.ECHO:

echo 文件内容 > 文件名   新建文件内容

echo 文件内容 >> 文件名      增加文件内容

echo  内容   在屏幕上输出内容

echo.    输出一个空格

@echo off     不显示执行过程

