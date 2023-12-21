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

![image-20231209104841909](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231209104841909.png)

**SQL注入带来的威胁**

* 猜解后台数据库，盗取网站敏感信息
* 绕过验证登录网站的后台
* 借助数据库的存储过程进行提权等操作

![image-20231209105105479](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231209105105479.png)

## SQL Injection Type

### union联合查询注入

Gifts union select 1,2,3,4#

### Boolean-Base布尔型注入

永真型注入:a' or **1=1**#

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

### Error-Based报错型注入

### 堆叠注入

a'**;**drop database databasename;

