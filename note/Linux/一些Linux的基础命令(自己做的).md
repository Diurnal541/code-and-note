### 一、ls命令

==ls命令的作用是列出目录下的内容==
  **ls [-a -h -l] [Linux路径]**

*  -a -l -h是可选的选项[^-a是指显示出隐藏的内容（以.开头的文件默认被隐藏，需要-a才能显示出来）-l是指以列表的形式展示内容，并显示更多细节 -h需要和-l配合使用，显示出更具体的文件大小单位]
* Linux路径是此命令可选的参数
* 直接使用ls一般是直接查看默认目录下的内容，一般是HOME目录

### 二、cd命令

==cd命令的作用是更改当前所在的工作目录==
**cd [Linux路径]**

* cd命令无需选项，只有参数，表示要切换到哪个目录下
* cd命令直接执行，不写参数，表示回到用户的HOME目录

### 三、pwd命令

pwd命令没有选项，没有参数，直接使用即可
==作用是输出当前所在的工作目录==

### 四、相对路径和绝对路径

###### 绝对路径：

* cd /home/用户名/Desktop[^以根目录为起点，描述路径的一种写法，路径以/开头]
* .表示当前目录，比如cd ./Desktop
* ..表示回到上一级目录，比如cd .. 或 cd ../..
* ~表示用户的HOME目录，比如cd ~或 cd ~/Desktop

###### 相对路径：

* cd Desktop[^以当前目录为起点，描述路径的一种写法，路径描述无需以/开头]

### 五、mkdir命令

==mkdir命令可以创建新的**目录（文件夹）**==
**mkdir [-p] [Linux路径]**

* 参数必填，表示Linux路径，即要创建的文件夹的路径，相对路径或绝对路径均可
* -p选项可选，表示自动创建不存在的父目录，适用于创建连续多层级的目录(一次性创建多个文件)[^mkdir -p diurnal/test1/test2表示在当前工作目录下创建diurnal文件，在diurnal文件中创建test1文件，在test1文件中创建test2文件]

### 六、touch命令

==可以通过touch命令创建**文件**==
**touch [Linux路径]**

* touch命令无选项，参数必填，表示要创建的文件路径，相对、绝对、特殊路径符都可以使用

### 七、cat命令

==准备好文件内容后，可以通过cat查看内容==
**cat [Linux路径]**

* cat同样没有选项，只有必填参数，参数表示：被查看的文件路径，相对、绝对、特殊路径符都可使用

### 八、more命令

==more命令同样可以查看文件内容，不同于cat的是：==

* cat是直接将内容显示出来
* more支持翻页，如果文件内容过多，可以一页页的展示

**more [Linux路径]**

* 同样没有选项，只有必填参数，参数表示：被查看的文件路径，相对、绝对、特殊路径符都可以使用
* 在查看过程中，通过空格翻页
* 通过q退出查看

### 九、cp命令

==cp命令用语复制文件\文件夹==
**cp [-r] 参数1 参数2**

* -r选项，可选，用于复制**文件夹**使用，表示递归
* 参数1，Linux路径，表示被复制的文件或文件夹
* 参数2，Linux路径，表示要复制去的地方

#### scp命令

![image-20231105130058157](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231105130058157.png)



### 十、mv命令

==mv命令可以用于移动文件\文件夹==
**mv 参数1 参数2**

* 参数1，Linux路径，表示被移动的文件或文件夹
* 参数2，Linux路径，表示要移动去的地方，如果目标不存在，则进行改名，确保目标存在

### 十一、rm命令

==rm命令可用于删除文件、文件夹==
**rm [-r -f] 参数1 参数2 …… 参数N**

* 同cp命令一样，-r选项用于删除文件夹
* -f表示force，强制删除(不会弹出提示确认消息)[^普通用户删除内容不会弹出提示，只有root管理员用户删除内容会有提示，所以一般用户用不到-f选项]
  **rm命令支持通配符*，用来做模糊匹配**
  * 符号*表示通配符，即匹配任意内容(包含空)，示例：
  * test*，表示匹配任何以test开头的内容
  * *test，表示匹配任何以test结尾的内容
  * \*test\*，表示匹配任何包含test的内容

### 十二、如何切换root用户

<u>**输入su - root后输入密码，通过exit命令退出登录root**</u>

### 十三、which命令

==通过which命令，查看所使用的一系列命令的程序文件存放在哪里==
**which [要查找的命令]**

### 十四、find命令

==通过find命令，我们可以去搜索指定的文件的路径==
**find 起始路径 -name “被查找的文件名”**[^这里的引号是英文输入法的引号]

* **find命令同样可以使用通配符***
* test*，表示匹配任何以test开头的内容
* *test，表示匹配任何以test结尾的内容
* \*test\*，表示匹配任何包含test的内容

find命令还可以通过文件大小来查找
**find 起始路径 -size +\\- -n[k M G]**

* +、-表示大于和小于
* n表示大小数字
* kMG表示大小单位，k(小写字母)表示kb，M表示MB，G表示GB

**示例：**

* 查找小于10kb的文件：find / -size -10k
* 查找大于100MB的文件：find / -size +100M
* 查找大于1GB的文件：find / -size +1G

### 十五、grep命令

 ==通过grep命令，从文件中通过关键字过滤文件行==
**grep [-n] 关键字 文件路径**

* 选项-n可选，表示在结果中匹配的行的行号
* 参数，关键字，必填，表示过滤的关键字，带有空格或其它特殊符号，建议使用“ ”将关键字包围起来
* 参数，文件路径，必填，表示要过滤内容的文件路径，<u>可作为内容输入端口</u>

### 十六、wc指令

==可以通过wc命令统计文件的行数、单词数量等==
**wc [-c -m -l -w] 文件路径**

* 选项，-c，统计bytes数量
* 选项，-m，统计字符数量
* 选项，-l，统计行数
* 选项，-w，统计单词数量
* 参数，文件路径，被统计的文件，<u>可作为内容输入端口</u>

### 十七、管道符(|)

==管道符的含义是：将管道符左边命令的结果，作为右边命令的输入==
<u>grep diurnal test.txt</u>**等同于**<u>cat test.txt | grep diurnal</u>

### 十八、Linux根目录

* /bin   此目录存放所有用户的命令
* /boot   不要动它！Linux内核及引导系统程序所需的文件
* /dev   所有设备文件的目录(如声卡、磁盘、光驱)
  1. <u>/dev/null “黑洞”，写入的一切数据皆会被丢弃</u>
  2. <u>/dev/random 真随机数生成器，可读取随机数据流，随机度高但是慢</u>
  3. <u>/dev/urandom 伪随机数，同上，但是随机度低但速度快</u>
  4. <u>/dev/zero “零”生成器，可以取到连续不断的零值</u>
  5. <u>/dev/tty 指向当前的终端</u>
* /etc   主要存放了系统配置方面的文件
* /home   各个用户的家目录
* /lib   库文件存放目录
* /lost+found   当系统意外崩溃或意外关机时，用语修复的文件碎片
* /mnt   用于临时挂载存储设备![This is mnt’s description ](E:\图片\微信图片_20231028202759.jpg)
* /var   存放内容常变动的文件目录
* /opt   自定义软件安装存放目录
* /proc   进程及内核信息存放目录
  1. <u>/proc/cpuinfo 本机的CPU的相关信息，包含频率、类型与运算功能等</u>
  2. <u>/proc/devices 这个文件记录了系统各个主要设备的主要设备代号，与mknod有关</u>
  3. <u>/proc/filesystems 目前系统已经载入的文件系统</u>
  4. <u>/proc/version 核心的版本，就是用uname -a显示的内容</u>
* /root   root用户家目录
* /tmp   临时文件目录
* /usr   系统存放程序的目录
* /sbin   给root用户使用的命令
* /sys   系统内核参数

### 十九、Linux链接

* 在Linux系统中有一种特殊的文件类型叫做链接
* 链接分为两种
  * 硬链接：硬链接和原文件必须处于同一文件系统，删除原文件对硬链接不会有影响，硬链接和原链接实际上是对同一份数据的两个引用，同时无法建立文件夹的硬链接
  * 软链接又叫符号链接，它类似快捷方式，指向一个路径，因此可以跨文件系统建立，当原文件被删除时，软链接也无法取得数据
                     **ln [-s] 原文件路径 目标文件路径**

### 二十、tree命令(前提是安装了tree插件)

**tree -L 1 /**
上述指令可以翻译为“只显示以/(根目录)开头的目录树的第一级”，-L选项告诉树你想看到多少层目录

### 二十一、echo命令

==通过echo命令在命令行内输出指定内容==
**echo 输出的内容**

* 无需选项，只有一个参数，表示要输出的内容，复杂内容[^空格或\等特殊符号]可以用“ ”包围
* 反引号 ` ![反引号](../图片/微信图片_20231029100406.png)

### 二十二、重定向符

![重定向符](../图片/微信图片_20231029100858.png)

一个>会使原有的内容被覆盖，两个>>使内容叠加

### 二十三、tail命令

![tail](../图片/微信图片_20231029101149.png)

### 二十四、vim模式

快捷键

![vim](../图片/微信图片_20231029113527.png)

![vim](../图片/微信图片_20231029113809.png)

![vim](../图片/微信图片_20231029114116.png)

### 二十五、用户和用户组管理

==以下命令皆需root用户执行==

* **创建用户组**
  groupadd 用户组名
* **删除用户组**
  groupdel 用户组名
* **创建用户**
  useradd [-g -d] 用户名[^-g指定用户的组，不指定-g，会创建同名组并自动加入，指定-g需要组已经存在，如已存在同名组，必须使用-g][^-d指定用户的HOME路径，不指定，HOME目录默认在:/home/用户名]
* **删除用户**
  userdel [-r] 用户名[^-r，删除用户的HOME目录，不使用-r，删除用户时，HOME目录保留]
* **查看用户所属组**
  id [用户名] [^用户名，被查看的用户，如果不提供则查看自身]
* **修改用户所属组**
  usermod -aG 用户组 用户名 [^将指定用户加入指定用户组]
* **使用getent命令，可以查看当前系统中有那些用户**
  <u>getent passwd</u>
  共会展示七份信息分别是：
  用户名：密码(x)：用户ID：组ID：描述信息(无用)：HOME目录：执行终端(默认bash)
  <u>getent group</u>
  查看系统全部组信息

### 二十六、认知权限信息

![quanxian](../图片/微信图片_20231029121909.png)

![quanxian](../图片/微信图片_20231029123044.png)

d  rwx  r-x  r-x (r:可读 w:可写 x:可执行)
r,w,x三个权限一个萝卜一个坑，-则表示无该权限，r-x表示没有w权限
![quanxian](../图片/微信图片_20231029123659.png)

### 二十七、chmod命令

![chmod](../图片/微信图片_20231029141557.png)

**chmod u+x 文件名 指的是使用户的权限再添加一个x**

![image-20231031184056711](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031184056711.png)

### 二十八、chown命令(chgrp命令)

![image-20231031184204967](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031184204967.png)

**chgrp root test.txt 相当于 chown :root test.txt**

### 二十九、一些快捷键

ctrl+c 强制停止
ctrl+l 清屏
ctrl+d 退出或登出
history 查看历史输入过的命令
!作为命令前缀，自动执行上一次匹配前缀的命令(如果不久前输入了python，输入!py可快速进行命令)
ctrl+r 输入内容去匹配历史命令
![image-20231031185204317](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031185204317.png)

### 三十、软件安装(yum和apt命令)

![image-20231031185339643](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031185339643.png)

![image-20231031185421254](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031185421254.png)

### 三十一、systemctl命令

![image-20231031185516938](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031185516938.png)

### 三十二、软链接(ln命令)

![image-20231031185707426](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031185707426.png)

### 三十三、时间和时区(date命令)

![image-20231031190239591](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031190239591.png)

![image-20231031190410896](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031190410896.png)

![image-20231031190507038](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031190507038.png)

![image-20231031190738061](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031190738061.png)

![image-20231031190837730](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031190837730.png)

### 三十四、IP地址、主机名

 ![image-20231031191237377](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031191237377.png)

![image-20231031191548023](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031191548023.png)

![image-20231031191841618](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031191841618.png)

![image-20231031191927179](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031191927179.png)

![image-20231031192214909](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031192214909.png)

### 三十五、网络传输(ping命令,wget命令,curl命令)

![image-20231031193128336](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031193128336.png)

![image-20231031193617561](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031193617561.png)

![image-20231031195300055](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031195300055.png)

![image-20231031195336840](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031195336840.png)

###  三十六、端口(nmap命令,netstat命令)

![image-20231031195741110](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031195741110.png)

![image-20231031195916101](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031195916101.png)

![image-20231031200042484](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031200042484.png)

![image-20231031200330079](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031200330079.png)

![image-20231031200552407](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031200552407.png)

### 三十七、进程管理

![image-20231031201355532](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231031201355532.png)

![image-20231101205224186](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101205224186.png)

 ![image-20231101210431398](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101210431398.png)

### 三十八、主机状态(top命令)

###### 1.系统资源监控

![image-20231101211002354](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101211002354.png)

![image-20231101211214410](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101211214410.png)

![image-20231101211649527](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101211649527.png)

![image-20231101211837513](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101211837513.png)

top -p [PID]
top -d 3(改成三秒刷新一次)
![image-20231101212256595](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101212256595.png)

按下f键后，通过上下左右键和空格键控制

###### 2.磁盘信息监控

![image-20231101213015252](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101213015252.png)

![image-20231101213047432](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101213047432.png)

![image-20231101213313940](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101213313940.png)

###### 3.网络信息监控

![image-20231101213616242](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101213616242.png)

### 三十九、环境变量(env命令、$符号)

![image-20231101214129047](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101214129047.png)

![image-20231101214335749](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101214335749.png)

![image-20231101214603338](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101214603338.png)

![image-20231101214828167](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101214828167.png)

1. 通过vim ~/.bashrc(/etc/profile)命令编辑.bashrc(profile)文件，在底下输入export 变量名=变量值，保存退出
2. 输入source .bashrc(profile)配置文件

![image-20231101215646897](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231101215646897.png)

### 四十、上传、下载(rz、sz命令)

![image-20231102081735844](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231102081735844.png)

### 四十一、压缩、解压(tar命令、zip命令、unzip命令)

![image-20231102082255836](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231102082255836.png)

![image-20231102083248906](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231102083248906.png)

![image-20231102083904181](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231102083904181.png)

![image-20231102084447396](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231102084447396.png)

![image-20231102084745225](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231102084745225.png)

==解压时有同名内容会替换掉原有文件或文件夹==

