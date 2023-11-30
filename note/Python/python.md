## 第一章 初识 Python

##### Python 是一门面向对象的解释型语言。

##### Python3.X 与 Python2.X 不兼容。

## 第二章 Python 语言基础

## 2.1 Python 语法特点

#### 2.1.1 注释规则

##### 【概念】 注释 是指在程序代码中添加的 标注性 的文字。将它们当做纯文本，并在执行代码时跳过这些纯

##### 文本。

##### （ 1 ）单行注释

##### （ 2 ）多行注释

##### 【概念】 在 Python 中 将 包 含 在 一 对 三引号 （'''......'''）或者（"""......"""）之间，并且 不属于任何语

##### 句 的内容认为是多注释。

#### 2.1.2 代码缩进

##### 【概念】 代码缩进 是指在每一行代码左端空出一定长度的 空白 ，从而可以更加清晰地从外观上看出程序

##### 的逻辑结构。

##### 不同于 C 语言或 Java 语言采用 { } 分隔代码块， Python 中采用 代码缩进 和 冒号 ： 区分代码之间的层

##### 次。

##### Python中 同一级代码缩进必须相同 。

###### # 注释内容

###### '''

###### 注释内容 1

###### 注释内容 2

###### ···

###### '''

###### """

###### 注释内容 1

###### 注释内容 2

###### ···

###### """

```
print('''a+b=''', 100 + 100 ) # 语句内部的'''a+b='''表示字符串定界符。
```

#### 2.1.3 编码规范

### 2.2 保留字与标识符

#### 2.2.1 保留字

##### 【概念】 保留字 是 Python 语言中已经被赋予特定意义的一些单词，开发程序时， 不可以作为变量、函

##### 数、类、模块和其他对象的名称来使用 。

#### 2.2.2 标识符

##### 【概念】 用来标识变量、函数、类、模块和其他对象的 名字 。

##### 由字母、下划线 “_”和数字组成且第一个字符不能是数字。

##### 不能使用 Python 中的保留字。

##### 大小写敏感。

### 2.3 变量

#### 2.3.1 理解 Python 中的变量

##### 变量是一个标签！

#### 2.3.2 变量的定义与使用

##### 变量名 必须是 大小写英文字母、数字或下划线 _ 的组合， 不能用数字开头 ， 并且对大小写敏感 。

##### 通过 赋值运算符 = 将变量名和想要赋予变量的值连接起来，变量的赋值操作完成了 声明 和定义的的过

##### 程。

##### 同一变量可以反复赋值，而且可以是不同类型的变量 ，这也是 Python 语言称之为 动态语言 的原因。

##### 【常量】 在程序运行过程中，值不能改变的量。

##### Python 中是没有常量的关键字的，只是我们常常约定使用大写字母组合的变量名表示常量，也有不要对

##### 其进行赋值的提醒作用。

### 2.4 基本数据类型

#### 2.4.1 数字类型

##### （ 1 ）整数

##### 整型（int） 取值为整数。

##### 十进制、八进制、二进制、十六进制整数之间的转换与计算。

##### （ 2 ）浮点数

##### 浮点型（float） 的取值为小数，当计算有精度要求时被使用，由于小数点可以在相应的二进制的不同位

##### 置浮动，故而称为浮点数。

##### 如果是非常大或者非常小的浮点数，就需要使用 科学计数法 表示，用 e 代替 10 。

##### （ 3 ）复数

##### 复数由实部和虚部组成，并且使用 j 或 J 表示虚部。

#### 2.4.2 字符串类型

##### 【概念】 字符串（str） 是连续的字符序列，可以是计算机所能表示的一切字符的集合。

##### 字符串是以 两个单引号 或 两个双引号 或 两个三引号 包裹起来的文本。

##### 单引号和双引号中的字符串必须在一行，三引号内部的字符串可以分布在连续的多行。

##### 【概念】 转义字符 是指使用 “ \ ” 对一些特殊字符进行转义。

##### Python 允许用 r “ ” 表示 “ ” 内部的字符串默认不转义。

###### 123 #十进制 123

```
0o123 #八进制 123
0b101 #二进制 101
0x1BD #十六进制1BD
3.14e9 #3140000000.
3.14 + 12.5j
```

##### 转义字符 说明

##### \ 续行符

##### \n 换行符

##### \0 空

##### \t 水平制表符，用于横向跳到下一制表位

##### \ " 双引号

##### \ ' 单引号

##### ** 一个反斜杠

##### \f 换页

##### \0dd 八进制数，dd 代表字符，如\012代表换行

##### \xhh 十六进制数，hh 代表字符，如\x0a代表换行

#### 2.4.3 布尔类型

##### 布尔类型（bool） 表示真值或假值。

##### 布尔值可以进行 and 、 or 和 not 运算。

##### and 和 or 运算分别用 & 和 | 表示。

##### not 运算为非运算，即把 True 变成 False ， False 变成 True 。

##### 空值

##### 空值（ NoneType ） 是 Python 里一个特殊的值，用 None 表示，一般用 None 填充表格中的缺失值。

#### 2.4.4 数据类型转换

##### Python 是 动态类型 的语言， 使用时不需要声明变量的类型 ，但有时仍然需要类型转换。

```
True #
False #
```

##### 函数 作用

##### int(x) 将 x 转换成整数类型

##### float(x) 将 x 转换成浮点数类型

##### str(x) 将 x 转换成字符串类型

##### chr(x) 将整数 x 转换为一个字符

##### ord(x) 将一个字符 x 转换为它对应的整数值

##### hex(x) 将一个整数 x 转换为十六进制字符串

##### oct(x) 将一个整数 x 转换为八进制字符串

### 2.5 运算符

#### 2.5.1 算数运算符

#### 2.5.2 赋值运算符

#### 2.5.3 比较（关系）运算符

#### 2.5.4 逻辑运算符

#### 2.5.5 位运算符

##### 1. “位与”运算

##### 二进制对应数位都为 1 时候，结果数位才是 1 ，否则为 0 。

##### 2. “位或”运算

##### 二进制对应数位有一个为 1 时候，结果数位就是 1 ，否则为 0 。

##### 3. “位异或”运算

##### 二进制对应数位相同时为 0 ，否则为 1 。

##### 4. “位取反”运算

##### 操作数对应的二进制数 1 修改为 0 ， 0 修改为 1 。

##### 5. 左移位运算符

##### x << n = x × 2^n

##### 6. 右移位运算符

##### x >> n = x / 2^n

#### 2.5.6 运算符的优先级

### 2.6 基本输入输出

#### 2.6.1 使用 input（）函数输入

##### Python3.x中 无论输入的是数字还是字符都将作为字符串读取 ，若需要数值则需对字符串进行类型转换。

#### 2.6.2 使用 print（）函数输出

##### 如果想要看变量的值，则直接在 print 后面加上变量名即可。

##### 如果是想要输出提示信息，如一句话，那我们需要将提示信息用 '' 单引号包裹起来（这使得内容构成一

##### 个字符串）。

```
variable = input("提示文字")
print(输出内容)
```

##### 使用逗号 , 隔开变量与其他剩余内容，则 print 在输出时会依次打印各个字符串或变量且自动换行，遇到

##### 逗号 , 时会输出一个空格。

## 第三章 流程控制语句

### 3.1 程序结构

### 3.2 选择语句

#### 3.2.1 if 语句

##### 注意，python中语句块是以冒号和缩进为标志的，另外语句后不要加分号。

#### 3.2.2 if...else 语句

#### 3.2.3 if...elif...else 语句

###### #基本语法：

```
if 表达式 :
语句块
```

###### #如果只有一条语句，那么语句块可以直接放到冒号后，如：

```
if a > b : max = a
```

###### #基本语法：

```
if 表达式 :
语句块 1
else :
语句块 2
```

##### Python 中没有 switch 语句，用此语句实现多重判断。

#### 3.2.4 if 语句的嵌套

##### 一定严格控制缩进量，注意冒号使用！

### 3.3 条件表达式

##### 使用条件表达式时，先计算中间的条件，如果结果为 True，返回 if 语句左边的值，否则返回 else 右边

##### 的值。

### 3.4 循环语句

#### 3.4.1 while 循环

##### 不要括弧 ()，不要花括弧 {}，不要分号，需要冒号+缩进。

#### 3.4.2 for 循环

##### 迭代变量用于保存读取出的值；

##### 对象为要遍历或迭代的对象，该对象可以是任意有序的序列对象，如字符串、列表和元组等；

##### 循环体为需要重复执行的语句。

##### range（）函数

##### 生成一系列连续的整数。

###### #基本语法：

```
if 表达式 1 :
语句块 1
elif 表达式 2 :
语句块 2
···
else :
语句块n
if 表达式 1 :
if 表达式 2 :
语句块 2
else :
语句块 3
else :
语句块 1
a = 1
b = 5
c = a if a > b else b
print(c) #
while 条件表达式 :
循环体
for 迭代变量 in 对象 :
循环体
```

#### 3.4.3 循环嵌套

##### 同 if 嵌套。

### 3.5 跳转语句

#### 3.5.1 break 语句

#### 3.5.2 continue 语句

```
range(start, end, step)
while 条件表达式 1 :
执行代码
if 条件表达式 :
break
while 条件表达式 1 :
执行代码
if 条件表达式 :
break
```

### 3.6 pass 空语句

##### 【概念】 pass 语句，表示 空 语句。它 不做任何事情 ，一般起到 占位 作用。

## 第四章 序列的应用

##### 序列 ：用于存放多个值的连续内存空间

##### 分为： 1.列表 2.元组 3.集合 4.字典 5.字符串

### 4.1 序列

##### 【概念】 序列是一块用于存放 多个 值的连续 内存空间 ，并且按一定顺序排列，可以通过 索引 取值。

##### Python 中的序列主要有列表、元组、集合、字典和字符串， 集合与字典 不支持 索引、切片、相加和相乘

##### 操作。

##### 【六种常用操作】 1.索引 2.切片 3.序列相加 4.乘法 5.检查某个元素是否是序列的成员 6.计算序列的长

##### 度、最大值和最小值

#### 4.1.1索引

##### 【概念】 序列每一个元素都有一个编号，也称之为 索引 ，索引序号是 从 0 开始 递增的，也即下标为 0 代表

##### 第一个元素。

##### 索引分为 正数索引 和 负数索引 ，正数索引 第一个 元素 下标为 0 ，负数索引 最后一个 元素 下标为 -

#### 4.1.2 切片

##### 【概念】 切片 是访问序列中元素的另一种方法，它可以 访问一定范围内的元素 ，通过切片操作可以生成

##### 一个新的序列。

#### 4.1.3 序列相加

##### 【概念】 Python中支持两种 相同类型 的 序列 相加操作，即将两个序列进行连接， 不会去除重复的元素 ，

##### 使用（+）运算符实现。

##### 相同类型是指同为列表、元组、集合等，序列中的元素类型可以不同。

##### 例如：

##### 注：不能将列表与字符串相加。

###### # 语法格式：

```
name[start : end : step]
# 切片区间 [start, end) 左闭右开
# step 为步长可忽略，默认为 1
a = [ 1 , 2 , 3 ]
b = ["abc", "SDU"]
print(a + b)
# 输出结果为 [1, 2, 'abc', 'SDU']
c = a + b
# c[2] = 'abc'
```

#### 4.1.4 乘法

##### 【概念】 Python中使用 数字 n 乘以一个 序列 会得到一个新的序列，其内容为原序列被 重复 n 次 的结

##### 果。

##### 此操作还可以初始化指定长度的列表

#### 4.1.5 检查某个元素是否是序列成员

##### 【概念】 Python中使用 in 关键字 查询某个元素是否为序列的成员

##### 例如：

#### 4.1.6 计算序列的长度、最大值和最小值

##### 【概念】 Python 中使用 len() 函数计算序列长度，使用 max() 函数返回序列中最大元素，使用 min() 函

##### 数返回序列中的最小元素。

##### Python 提供的其他部分内置函数：

###### # 此代码为错误代码

```
a = [ 1 , 2 , 3 ]
print(a + "abc")
a = [ 1 , 2 ]
print(a * 3 )
# 输出结果为[1, 2, 1, 2, 1, 2]
```

###### # 创建一个长度为 5 的空列表

```
emptylist = [None] * 5
```

###### # 语法格式

```
value in sequence
```

###### SDU = ["S", "D", "U"]

```
print("S" in SDU)
# 输出结果为 True
# not in 则相反
print("S" not in SDU)
# 输出结果为 False
num = [ 1 , 2 , 3 ]
print("序列的长度为", len(num))
# 输出结果为；序列的长度为 3
list() #将序列转换为列表
str() #将序列转换为字符串
sum() #计算元素和
sorted() #对元素进行排序
reversed() #反向序列中的元素
enumerate() #将序列组合为一个索引序列，多用在 for 循环中
```

### 4.2 列表

##### 【概念】 Python 中的列表是由一系列 按照特定顺序 排列的元素组成，是一种内置的 可变序列 ，形式

##### 上，所有元素都在一对 [] 中，相邻元素用 , 隔开（注意中英文符号）。内容上可以将整数、实数、字符

##### 串、列表、元组等任何类型放入列表中，同一列表中元素类型可以不同，这与其他语言不同。

#### 4.2.1 列表的创建和删除

##### 1. 使用赋值运算符直接创建列表

##### 2. 创建空链表

##### 3. 创建数值列表

##### List() 可以将 range 对象、字符串、元组或其他可迭代类型的数据转换为列表。

##### 4. 删除列表

#### 4.2.2 访问列表元素

###### # 语法格式

```
listname = [element_1, element_2, ···, element_n]
list = [ 1 , 'SDU', "山东大学", ["abc", 666 ]]
emptylist = []
a = list(range( 10 , 20 , 2 ))
# a = [10, 12, 14, 16, 18]
b = "SDU"
c = list(b)
# c = ["S", "D", "U"]
e = "123"
f = list(e)
# f = ['1', '2', '3']
del listname
list = ["山东大学", "世界一流大学", 666 , ["努力奋斗", 666 ]]
print(list)
# 输出结果为 ['山东大学', '世界一流大学', 666, ['努力奋斗', 666]]
print(list[ 3 ])
# 输出结果为 ['努力奋斗', 666]
print(list[ 1 : 3 ])
# 输出结果为 ['世界一流大学', 666]
```

#### 4.2.3 遍历列表

##### 1. 直接使用 for 循环

##### 2. for 循环和 enumerate() 函数

#### 4.2.4 添加、修改和删除列表元素

##### 1. 添加元素

##### （ 1 ）通过 + 链接序列

##### （ 2 ）通过 append（）方法在列表尾部添加元素

##### （ 3 ）通过 extend（）方法将一个列表添加到另一个列表中

##### （ 4 ）通过 insert（）向列表指定位置插入元素

##### 示例：

```
a = ["山东大学", 985 , 211 , "双一流"]
for item in a:
print(item)
# 输出结果为：
# 山东大学
# 985
# 211
# 双一流
a = ["山东大学", 985 , 211 , "双一流"]
for index, item in enumerate(a):
print(index + 1 , item)
# 输出结果为：
# 1 山东大学
# 2 985
# 3 211
# 4 双一流
listname.append(obj)
listname.extend(seq)
listname.insert(index, obj)
a = ["SDU", 211 ]
b = [ 985 , "双一流"]
print(a + b)  #["SDU", 211, 985, "双一流"]
a.append("世一大")
print(a)  #["SDU", 211, "世一大"]
a.extend(b)
print(a)  #["SDU", 211, "世一大", 985, "双一流"]
a.insert( 1 , "简称山大")
print(a)  #["SDU", "简称山大", 211, "世一大", 985, "双一流"]
```

##### 2. 修改元素

##### 3. 删除元素

##### （ 1 ）根据索引删除

##### （ 2 ）根据元素值删除

##### 示例：

#### 4.2.5 对列表进行统计和计算

##### 1. 获取指定元素出现次数

##### 2. 获取元素首次出现的下标

##### 3. 统计数值列表元素和

##### 示例：

```
a = ["SDU", 211 ]
a[ 1 ] = "985"
print(a)  #["SDU", 985]
del listname[i]
listname.pop(i)  #没有参数则pop最后一个元素
listname.remove(obj)
a = ["SDU", "简称山大", 211 , "世一大", 985 , "双一流"]
del a[ 1 ]
print(a)  #["SDU", 211, "世一大", 985, "双一流"]
a.pop(- 3 )
print(a)  #["SDU", 211, 985, "双一流"]
if a.count("双一流") > 0 :
a.remove("双一流")
print(a)  #["SDU", 211, 985]
listname.count(obj)
listname.index(obj)
sum(interable[,start])
a = list(range( 10 ))
print(a.count( 1 )) #
print(a.count(- 1 ))  #
print(a.index( 2 )) #
print(sum(a)) #
print(sum(a, 10000 ))  #
```

#### 4.2.6 对列表进行排序

##### 1. 使用列表对象的 sort() 方法

##### 在原列表上进行变化，改变原列表中元素的排列顺序

##### 示例：

##### 2. 使用内置的 sorted() 函数

##### 创建一个副本，并不改变原列表中元素顺序

##### 示例：

#### 4.2.7 列表推导式

##### 【概念】 列表推导式 可以 快速生成 一个 列表 ，或者根据某个列表 生成 满足指定需求的 列表 。

##### （ 1 ）生成指定范围的数值列表

##### （ 2 ）根据列表生成指定需求的列表

```
listname.sort(key = None, reverse = False)
grade = [ 1 , 3 , 2 , 4 , 1 ]
grade.sort()
print(grade)  #[1, 1, 2, 3, 4]
grade.sort(reverse = True)
print(grade)  #[4, 3, 2, 1, 1]
char = ["AC", "TLE", "mle"]
char.sort()
print(char) #["AC", "TLE", "mle"]
char.sort(key = str.lower)
print(char) #["AC", "mle", "TLE"]
sorted(interable, key = None, reverse = False)
grade = [ 1 , 3 , 2 , 4 , 1 ]
grade_as = sorted(grade)
print(grade_as)  #[1, 1, 2, 3, 4]
grade_des = sorted(grade, reverse = True)
print(grade_des) #[4, 3, 2, 1, 1]
print(grade) #[1, 3, 2, 4, 1]
list = [Expression for var in range()]
import random
randnum = [random.randint( 10 , 100 ) for i in range( 3 )]
print(randnum)  #[12, 43, 22]
list = [Expression for var in list]
```

##### （ 3 ）从列表中选择符合条件的元素组成新的列表

#### 4.2.8 二维列表的使用

##### 【概念】 在Python中，二维列表是包含列表的列表，即一个列表的每一个元素又都是一个列表。

##### （ 1 ）直接定义二维列表

##### （ 2 ）使用嵌套的 for 循环创建

##### （ 3 ）使用列表推导式创建

### 4.3 元组

#### 4.3.0 定义

##### 与列表类似也是由一系列按特定顺序排列的元素组成，但是 不可变序列 （数值、字符串、元组），形式

##### 上元组中的所有元素均放在一对“( )”中，相邻的两个元素用“,”隔开， 元素类型可以不同 。 元组可用于保存

##### 程序中不可修改的内容 。

##### 不可变对象：

##### 对象 存放在地址中的值不会被改变 （所谓的改变是创建了一块新的地址并把新的对象的值放在新地址中

##### 原来的对象并没有发生变化）。

##### 如：Tuple，数值，Str

##### python 中的不可变数据类 型 int float string tuple ，不允许变量的值发生变化，如果改变了变量的值，相

##### 当于是新建了一个对象，而对于相同的值的对象，在内存中则只有一个对象 ( 交互模式下 tuple 例外 ) ，内

##### 部会有一个引用计数来记录有多少个变量引用这个对象。

##### 可变对象：

```
price = [ 2 , 5 , 18 , 100 ]
sale = [x * 0.5 for x in price]
print(sale) #[1.0, 2.5, 9.0, 50.0]
list = [Expression for var in list if condition]
price = [ 10 , 23 , 22 , 9 ]
sale = [x for x in price if x < 20 ]
print(sale) #[10, 9]
a = [[ 1 , 2 ], [ 2 , 3 ], [ 3 , 4 ]]  #三行两列的列表
a = []
for i in range( 2 ) :
a.append([])
for j in range( 3 ) :
a[i].append(j)
print(a)  #[[0, 1, 2], [0, 1, 2]]
a = [[j for j in range( 2 )] for i in range( 2 )]
print(a)  #[[0, 1], [0, 1]]
```

##### 对象 存放在地址中的值会原地改变 ，对于相同的值的不同对象，在内存中则会存在不同的对象，即每个

##### 对象都有自己的地址，相当于内存中对于同值的对象保存了多份。

##### 可变数据类型，允许变量的值发生变化，即如果对变量进行 append 、 += 等这种操作后，只是改变了变量

##### 的值，而不会新建一个对象，变量引用的对象的地址也不会变化，不过对于相同的值的不同对象，在内

##### 存中则会存在不同的对象，即每个对象都有自己的地址，相当于内存中对于同值的对象保存了多份，这

##### 里不存在引用计数，是实实在在的对象。

#### 4.3.1 元组的创建和删除

##### 1. 使用赋值运算符直接创建元组

##### 注意：

##### 2. 创建空元组

##### 3. 创建数值元组

##### 4. 删除元组

#### 4.3.2 访问元组元素

##### 同 list。

##### 元组遍历

##### 同 list。

##### 1. 直接使用 for 循环

```
tuplename = (element1, element2, ··· ,element n)
a = ("SDU")  #a实际为字符串
a = ("SDU",) #a为包含一个字符串元素的元组
emptytuple = ()
tuple(data)
#Data是可以转换为元组的数据，其类型可以是range对象、字符串、元组或其他可迭代类型的数据。
del tuplename
a = ("SDU", 211 , 985 )
#直接输出
print(a) #("SDU", 211, 985)
#索引
print(a[ 1 ])  #
#切片
print(a[ 1 :]) #(211, 985)
```

##### 2. for 循环和 enumerate() 函数

#### 4.3.3 修改元组元素

##### 元组 （不可变）* *不能**单独修改某一元素，可以将两个元组连接。

##### 元组可以整体重新赋值实现对元素的修改。

#### 4.3.4 元组推导式

##### 【概念】 元组推导式 可以快速 生成 一个 元组 ，或者根据某个元组 生成 满足指定需求的 元组 。

##### 同列表推导式， 但需要进行转换 ，使用 tuple（）函数。

#### 4.3.5 元组与列表的区别

```
a = ("清华", "北京", "山东")
for x in a :
print(x + "大学", end = " ")
# 输出结果为：
# 清华大学 北京大学 山东大学
a = ("清华", "北京", "山东")
for index, x in enumerate(a) :
print("Top" + str(index + 1 ), x + "大学", end = " ")
# 输出结果为：
# Top1 清华大学 Top2 北京大学 Top3 山东大学
a = ("清华", "北京")
b = ("山东",)
a = a + b
print(a)  #('清华', '北京', '山东')
a = ("清华", "北京")
print(a)  #('清华', '北京')
a = ("清华", "北京", "山东")
print(a)  #('清华', '北京', '山东')
import random
randnum = (random.randint( 10 , 100 ) for i in range( 3 ))
randnum = tuple(randnum)
print(randnum)  #(12, 43, 22)
```

##### 元组 列表

##### 不可变序列 可变序列

##### （不能添加、修改和删除元素，可以整体替换） （随时添加、修改或者删除）

##### 支持切片的操作 支持切片的操作

##### （只能访问元组中的元素） （可以访问、修改元组中的元素）

##### 元组访问速度快 列表访问速度慢

##### 元组可以作为字典键 列表不能作为字典的键

### 4.4 字典

#### 4.4.0 定义

##### Python中字典与列表类似，也是 可变序列 ，不过与列表不同，字典是 无序 的可变序列，保存的内容是以

##### “ 键Key-值Value ”对的形式存放的。 Key是唯一的 ， Value可以是多个 。字典在定义包含多个命名字段的

##### 对象时，用途大。字典又称关联数组或散列表(Hash)。

##### 特点：

##### （ 1 ）通过键key而不是索引来读取

##### （ 2 ）字典是任意对象的无序集合

##### （ 3 ）字典是可变的并且可以任意嵌套

##### （ 4 ）字典的键必须唯一

##### （ 5 ）字典的键 key必须不可变 ，可以使用数字、字符串或元组但是不可是列表。

#### 4.4.1 字典的创建和删除

##### 1. 直接创建

##### 2. 通过映射函数创建字典

##### zip（）函数：

##### 用于将多个列表或元组对应位置的元素组合为元组，并返回包含这些内容的zip对象。如果想获取元组，

##### 可以将zip对象使用tuple()函数转换这元组;如果想获取列表，则可以使用list()函数将其转换为列表。

```
dictionary = {"key1" : "value1", "key2" : "value2", ··· , "key n" : "value n" }
dic = {"SDU" : 985 , "BUPT" : 211 }
dictioanry = dict(zip(list1, list2))
a = ["SDU", "BUPT"]
b = [ 985 , 211 ]
dic = dict(zip(a, b))
print(dic)  #{'SDU': 985, 'BUPT': 211}
```

##### 3. 通过给定的关键字参数创建字典

##### 4. 通过给定的元组和列表创建字典

#### 4.4.2 通过键值对访问字典

##### dict.get（）方法：

#### 4.4.3 遍历字典

```
dictionary = dict(key1 = value1, key2 = value2, ··· , key n = value n)
dic = dict(SDU = 985 , BUPT = 211 )
print(dic)  #{'SDU': 985, 'BUPT': 211}
{(a1, a2, a3) : [b1, b2, b3]}
a = ("SDU", "BUPT")
b = [ 985 , 211 ]
dic = {a : b}
print(dic)  #{('SDU', 'BUPT'): [985, 211]}
a = ("SDU", "BUPT")
b = [ 985 , 211 ]
dic = dict(zip(a, b))
print(dic["SDU"]) #985
print(dic["THU"] if "THU" in dic else "None") #None
dictionary.get(key[, default])  #default选项：key不存在时返回默认值defaul
a = ("SDU", "BUPT")
b = [ 985 , 211 ]
dic = dict(zip(a, b))
print(dic.get("SDU", "None"))  #985
print(dic.get("THU", "None"))  #None
dictionary.items()
a = ("SDU", "BUPT")
b = [ 985 , 211 ]
dic = dict(zip(a, b))
for item in dic.items() :
print(item)
# ('SDU', 985)
# ('BUPT', 211)
for key, value in dic.items() :
print(key, value)
# SDU, 985
# BUPT, 211
```

#### 4.4.4 添加、修改和删除字典元素

#### 4.4.5 字典推导式

### 4.5 集合

#### 4.5.0 定义

##### 【概念】 用于保存 不重复 元素，最好的应用是 去重 ，分为可变集合（set）和不可变集合

##### （frozenset）。

##### 形式上，集合所有元素都放在一对“{ }”中，相邻两个元素使用“,”分隔，并且集合是 无序 的。

##### 1. 直接创建

##### 2. 使用 set（）函数创建

##### 注意： 创建空集合的时候不能直接使用 {} （这样创建的是空字典），推荐使用 set() 创建。

#### 4.5.2 集合的添加和删除

###### #添加或修改

```
dictionary[key] = value
#删除
del dictionary[key]
dic = {"SDU" : 985 }
dic["BUPT"] = 211
print(dic)  #{'SDU': 985, 'BUPT': 211}
dic["SDU"] = 211
print(dic)  #{'SDU': 211, 'BUPT': 211}
del dic["BUPT"]
print(dic)  #{'SDU': 211}
import random
randnum = {i : random.randint( 10 , 100 ) for i in range( 1 , 5 )}
print(randnum)  #{1: 61, 2: 13, 3: 31, 4: 89}
setname = {element1, element2, element3, ··· , element n}
a = { 1 , "1", 2 , 2 , 3 }
print(a)  #{1, 2, 3, '1'}
set1 = set("你是一个一个")
print(set1) #{'一', '你', '个', '是'}
set2 = set([1.1, 2.2, 3.333])
print(set2) #{1.1, 2.2, 3.333}
```

##### 1. 添加元素

##### 2. 删除集合

##### 在 Python 中，可以使用 del 命令删除整个集合，也可以使用集合的 pop() 方法或者 remove() 方法删除

##### 一个元素，或者使用集合对象的clear() 方法清空集合，即删除集合中的全部元素，使其变为空集合。

##### 注意：在 set 中尽量避免使用 pop（）方法，因为 set 是无序集合。

#### 4.5.3 集合的交集"&"、并集"|"和差集"-"运算

### 4.6 列表、元组、字典和集合的区别

#### 列表：

```
setname.add(element)
mr = set(["C", "C++", "Java", "PHP"])
mr.add("Python")
print(mr) #{'PHP', 'C', 'Python', 'C++', 'Java'}
mr.pop()
print(mr) #{'C', 'Python', 'C++', 'Java'}
mr.remove("python") if "Python" in mr else print("查无此项")
print(mr) #{'Java', 'C', 'PHP'}
mr.clear()  #set()
py = set(["张三", "李四", "王二", "小明"])
c = set(["小胡", "小孙", "小齐", "小明", "王二"])
print("选择python课的同学：", py)  #{'张三', '王二', '李四', '小明'}
print("选择c语言课的同学：", c)  #{'小孙', '王二', '小胡', '小明',
'小齐'}#
print("同时选择python和C语言的同学（交集）：", py & c) #{'小明', '王二'}
print("全部同学（并集）：", py | c)  #{'小孙', '王二', '小胡', '张三',
'小明', '小齐', '李四'}
print("仅选民则python课的同学：", py - c)  #{'张三', '李四'}
```

#### 元组：

#### 字典：

#### 集合：

##### 集合内无重复元素，且集合内元素无序。

## 第五章 字符串及其表达式

### 5.1 字符串常用操作

#### 5.1.1 拼接字符串

##### 使用 + 字符将两个字符串进行链接。

#### 5.1.2 计算字符串长度

##### 默认情况下，len() 函数 不区分中英文和数字 ，所有字符均按照一个字节计算。为了获取实际字符串 占用

##### 字节数 ，需要用 encode() 方法。

```
a = "山东大学"
b = "威海校区"
c = a + b
print(c)  #"山东大学威海校区"
len(string) #计算字符元素个数
```

#### 5.1.3 截取字符串

#### 5.1.4 分割、合并字符串

##### Python中，字符串对象提供了分割、合并字符串的方法。分割字符串是把字符串分割成列表，合并字符

##### 串是把列表合并为字符串，二者是互逆操作。

##### 对字符串的操作方法都不会改变原来字符串的值。

##### 字符串的分割

##### 字符串的合并

```
str = "21机器人"
print(len(str)) #5
print(len(str.encode()))  #11 (2 + 3 * 3)
print(len(str.encode("gbk"))) #8 (2 + 2 * 3)
string[start : end : step]
str1 = "21级机器人工程"
sub1 = str1[ 1 ]
sub2 = str1[ 2 :]
sub3 = str1[: 4 ]
sub4 = str1[ 1 : 7 : 2 ]
print("原字符串：", str1)
print(sub1 + "\n" + sub2 + "\n" + sub3 + "\n" + sub4)
```

###### #原字符串： 21 级机器人工程

###### #1

###### #级机器人工程

###### #21级机

###### #1机人

```
str.split(sep, maxsplit)
#sep:用于指定分隔符，可包含多个字符。Sep参数默认为None 即所有空字符:空格、换行符“\n”、制表
符“\t”
#maxsplit:用于指分割的次数，-1表示没有限制
str1 = "山东大学，简称 山大 >>> http://www.sdu.edu.cn"
print("原字符串：", str1) #原字符串： 山东大学，简称 山大 >>> http://www.sdu.edu.cn
list1 = str1.split()
print(list1)  #['山东大学，简称', '山大', '>>>', 'www.sdu.edu.cn']
list2 = str1.split(">>>")
print(list2)  #['山东大学，简称 山大 ', ' http://www.sdu.edu.cn']
list3 = str1.split(".")
print(list3)  #['山东大学，简称 山大 >>> www', 'sdu', 'edu', 'cn']
list4 = str1.split(" ", 2 )
print(list4)  #['山东大学，简称', '山大', '>>> http://www.sdu.edu.cn']
strnew = string.join(iterable)
#string:合并时的分割符
#iterable:可迭代对象
```

#### 5.1.5 字符串的检索

##### 1. count（）方法

##### count() 方法用于检索指定字符串在另外一个字符串中 出现的次数 ，如果检索的字符串不存在，则返回

##### 0 ，否则返回出现的次数。

##### 2. find（）方法

##### 用于检索 是否包含 指定的字符串，若不存在则返回-1，否则返回 首次出现该子字符串的索引 。

##### Python 中 rfind() 返回字符串最后一次出现的位置。

##### 3.index（）方法

##### 用于检索是否包含指定的字符串，若不存在则 抛出异常 ，否则返回首次出现该子字符串的索引。

##### 4.startswith（）方法和 endswith（）方法

##### 用于检索字符串 是否以指定字符串开头/结尾 ，如果是则返回 True，否则返回 False。

```
list_friend = ["Mike", "Jerry", "John", "Tom"]
str_friend = " @".join(list_friend)
at = "@" + str_friend
print("您@的好友有：", at) #您@的好友有： @Mike @Jerry @John @Tom
str.count(sub[, start[, end]])
str1 = 'How do you do'
print(str1.count('o'))  #4
print(str1[ 0 : 5 ].count('o')) #1
print(str1[ 0 : 5 ])  #How d
print(str1.count('o', 1 , 5 ))  #1
str.find(sub[, start[, end]])
str3 = 'How do you do'
print(str3[ 1 : 5 ].find('o'))  #0
print(str3[ 1 : 5 ])  #ow d
print(str3.find('o', 1 , 5 )) #1
print(str3.find('x')) #-1
str5 = 'this is '
print(str5.find('is'))  #2
print(str5.rfind('is')) #5
str.index(sub[, start[, end]])
str.startswith(prefix[, start[, end]])
str.endswith(prefix[, start[, end]])
```

#### 5.1.6 字母的大小写转换

#### 5.1.7 去除字符串中的空格和特殊字符

##### 用于去除字符串 左右两侧 的空格和特殊字符（空格、制表符\t、回车符\r、换行符\n）。

##### 注：[ ] 内的内容为字符，若 [ ] 内为字符串则拆开单独当字符看待。

##### 使用 strip（）方法后 原字符串不变 。

#### 5.1.8 格式化字符串

##### 格式化字符串是指 先制定一个模板 ，在这个模板中 预留几个空位 ，然后根据需要 填上相应的内容 ，这些

##### 空位需要通过指定的符号标记（占位符），而这些符号不会显示出来。

```
str5 = 'this is '
print(str5.startswith('this')) #True
print(str5.startswith('t'))  #True
str5 = 'this is'
print(str5.endswith('this')) #False
print(str5.endswith('is')) #True
print(str5.endswith('s'))  #True
strnew = string.lower()  #小写转换
strnew = string.upper()  #大写转换
str.strip([chars])
str7 = ' http://www.sdu.edu.cn \t\n\r'
print('原字符串str7:' + str7 + '。')
print('字符串:' + str7.strip() + '。')
#原字符串str7: http://www.sdu.edu.cn
#。
#字符串:http://www.sdu.edu.cn。
str8 = '@http://www.sdu.edu.cn...@.'
print('原字符串str8:' + str8)  #原字符串str8:@http://www.sdu.edu.cn...@.
print('字符串:' + str8.strip('@.'))  #字符串:http://www.sdu.edu.cn
print(str8) #@http://www.sdu.edu.cn...@.
str9 = 'dologood'
print('原字符串str9:' + str9)  #原字符串str9:dologood
print('字符串:' + str9.strip('od'))  #字符串:log
print(str9) #dologood
str.lstrip([chars])  #去除字符串左侧字符
str.rstrip([chars])  #去除字符串右侧字符
```

##### 1. 使用“%”操作符

##### 2.使用字符串对象的 format（）方法

##### Python2.6 开始，新增了一种格式化字符串的函数 str.format()，它增强了字符串格式化的功能。基本语

##### 法是通过 {} 和 : 来代替以前的 %占位符 。

```
'%[-][+][0][m][.n]格式化字符' % exp
```

###### '''

###### 格式化字符：

```
s：字符串
d：十进制整数
f：浮点数
'''
template = "编号: %09d\t公司名称：%s \t官网:http://www.%s.com" #定义模板
context1 = ( 7 , "百度", "baidu")
context2 = ( 8 , "明日学院", "mingrisoft")
print(template % context1)
print(template % context2)
#编号: 000000007 公司名称：百度 官网:http://www.baidu.com
#编号: 000000008 公司名称：明日学院 官网:http://www.mingrisoft.com
#0：右对齐； 9 ：占有宽度；d：十进制数；s：字符串
str.format(args)
#{[index][:[[fill]align][sign][#][width][.precision][type]]}
```

##### 位置映射

##### 关键字映射

```
print("{}{}".format("hello", world)) #不设置指定位置，按默认顺序
#"hello world"
print("{0}{1}".format("hello", "world")) #设置指定位置
#"hello world"
print("{1}:{0},{1}".format("hello", "world")) #设置指定位置
#"world:hello,world"
print("{server}{1}:{0}".format( 8888 ,'192.168.1.100',server='Web Server Info :'))
#Web Server Info :192.168.1.100:8888
```

##### 元素访问

##### 填充对齐

```
print("{0[0]}.{0[1]}".format(("baidu", "com")))
#baidu.com
my_list1 = ["山大威海", "sdu.wh"]
my_list2 = ["山大青岛", "sdu.qd"]
print("名称:{0[0]},{1[0]}, 地址:{0[1]},{1[1]}".format(my_list1, my_list2))
#名称:山大威海,山大青岛, 地址:sdu.wh,sdu.qd
print("{0} * {1} = {2:0>2}".format( 3 , 2 , 2 * 3 ))
#3 * 2 = 06
print("{:*^30}".format('centered'))
#***********centered***********
```

##### 精度设置

##### 数字格式：

##### 进制格式：

##### ^, <, > 分别是居中、左对齐、右对齐，后面带宽度， : 号后面带填充的字符，只能是一个字符，不指定

##### 则默认是用空格填充。

##### +表示在正数前显示 +，负数前显示 -； （空格）表示在正数前加空格；

##### b、d、o、x 分别是二进制、十进制、八进制、十六进制。

###### #九九乘法表

```
for i in range( 1 , 10 ):
a = 1
while a <= i:
print("{0} * {1} = {2:0>2}".format(a, i, a * i), end = "\t")
a += 1
print()
print("{:.3f}".format(3.1415))  #3.142
print("{:.10f}".format(3.1415)) #3.1415000000
```

##### ,千分位分隔符

##### python 中自带的字符串方法：

##### 1.python官方定义中的字母：默认为英文字母+汉字即可。

##### 2.python官方定义中的数字：默认为阿拉伯数字+带圈的数字即可。

### 5.2 字符串编码转换

##### 了解计算机编码： ASCLL、GBK、Unicode 等。

##### 了解 encode（） 方法编码和 decode（） 方法解码。

```
import math
print('1251+3950的结果是（以货币形式显示）：￥{:,.2f}元'.format( 1251 + 3950 )) # 以货币形式
显示
print('{0:.1f}用科学计数法表示：{0:E}'.format(120000.1)) # 用科学计数法表示
print('π取 5 位小数：{:.5f}'.format(math.pi)) # 输出小数点后五位
print('{0:d}的 16 进制结果是：{0:#x}'.format( 100 )) # 输出十六进制数
print('天才是由 {:.0%} 的灵感，加上 {:.0%} 的汗水 。'.format(0.01,0.99)) # 输出百分比，
并且不带小数
```

###### #1251+3950的结果是（以货币形式显示）：￥5,201.00元

###### #120000.1用科学计数法表示：1.200001E+05

```
#π取 5 位小数：3.14159
#100的 16 进制结果是：0x64
#天才是由 1% 的灵感，加上 99% 的汗水 。
str.isalpha()  #是否包含至少一个字符且所有字符都是英文或汉字，返回True/False
str.isdigit()  #是否只包含数字，返回True/False
str.isalnum()  #是否包含至少一个字符且所有字符都是字母或数字，返回True/False
c = "中文"
print(type(c), c)
c = c.encode("utf-8")  #使用 UTF-8 将 str 类型编码为 bytes 类型
print(type(c), c)
c = c.decode() #使用默认方式将 bytes 类型解码为 str 类型
print(type(c), c)
#<class 'str'> 中文
#<class 'bytes'> b'\xe4\xb8\xad\xe6\x96\x87'
#<class 'str'> 中文
```

##### . 匹配除换行符以外的任意字符

##### \w 匹配字母、数字、下划线或汉字

##### \W 匹配字母、数字、下划线或汉字 以外 的字符

##### \s 匹配任意的空白符

##### \b 匹配单词的开始或结束

##### \d 匹配数字

### 5.3 正则表达式

##### 【概念】 ：正则表达式是一种用来 匹配字符串 的强有力的武器。设计思想是用一种描述性的语言来给字

##### 符串定义一个规则，凡是符合规则的字符串，就认为它“匹配”，否则就不匹配。

#### 5.3.1 行定位符

##### 我们在写用户注册表单时，只允许用户名包含字符、数字、下划线和连接字符(-)，并设置用户名的长

##### 度，我们就可以使用以下正则表达式来设定。

#### 5.3.2 元字符

###### ^ 表示行的开始

###### $ 表示行的结尾

```
^tm #表示要匹配字符串以 tm 为开始的字符串，如"tm equal Tomorrow Moon"
tm$ #表示要匹配字符串以 tm 为结尾的字符串，如"Tomorrow Moon equal tm"
tm #可匹配任意位置的 tm
^tm$ #仅匹配 tm
```

##### ? 匹配前面的字符零次或一次 colou?r：匹配colour和color

##### + 匹配前面的字符 一次或多次 g o +gle：匹配的范围从gogle到goo...gle

##### * 匹配前面的字符 零次或多次 g o gle：匹配的范围从ggle到goo...gle

##### {n} 匹配前面的字符 n次 g o {2}gle：只匹配google

##### {n,} 匹配前面的字符 最少n次 g o {2,}gle：匹配的范围从google到goo...gle

##### {n,m}

##### 匹配前面的字符 最多m次 最少n

##### 次，

##### employ e {0,2}：匹配employ、employe和

##### employee

#### 5.3.3 限定符

#### 5.3.4 字符类

#### 5.3.5 排除字符

#### 5.3.6 选择字符

##### 正则表达式 从左到右 进行计算，并 遵循优先级顺序 ，相同优先级的从左到右进行运算，不同优先级的运

##### 算先高后低。下表从最高到最低说明了各种正则表达式运算符的优先级顺序：

```
\d{ 3 }\s+\d{ 3 , 8 }
#\d{3}表示匹配 3 个数字，例如'010'；
#\s可以匹配一个空格（也包括Tab等空白符），所以\s+表示至少有一个空格，例如匹配''，' '等；
#\d{3,8}表示3-8个数字，例如'1234567'。
```

###### #上面的正则表达式可以匹配以任意个空格隔开的带区号的电话号码。

###### #如果要匹配'010-12345'这样的号码

```
#由于'-'是特殊字符，在正则表达式中，要用'\'转义，所以，上面的正则是\d{3}\-\d{3,8}
```

###### 要做更精确地匹配，可以用[ ]表示范围，比如：

```
[ 0 - 9 a-zA-Z\_]可以匹配一个数字、字母或者下划线；
[ 0 - 9 a-zA-Z\_]+可以匹配至少由一个数字、字母或者下划线组成的字符串，比
如'a100'，'0_Z'，'Py3000'等等；
[a-zA-Z\_][ 0 - 9 a-zA-Z\_]*可以匹配由字母或下划线开头，后接任意个由一个数字、字母或者下划线组成
的字符串，也就是Python合法的变量；
[a-zA-Z\_][ 0 - 9 a-zA-Z\_]{ 0 , 19 }更精确地限制了变量的长度是 1 - 20 个字符（前面 1 个字符+后面最多
19 个字符）。
A|B可以匹配A或B，所以(P|p)ython可以匹配'Python'或者'python'。
[^a-zA-Z]
#^放在中括号内表示排除的意思。
#上述表达式用于匹配一个不是字母的字符。
(^\d{ 15 }$)|(^\d{ 18 }$)|(^\d{ 17 })(\d|X|x)$
#该表达式的意思是以匹配 15 位数字，或者 18 位数字，或者 17 位数字和最后一位。最后一位可以是数字，也可
以是X或者x。
```

#### 5.3.7 转义字符

#### 5.3.8 分组

#### 5.3.9 在 Python 中使用正则表达式语法

##### 字符串正则化时， 首先进行字符串转义 ， 然后进行正则转义 。因此，要特别注意 \ 的转义问题， 推荐使

##### 用原生字符串 ，避免错误。

##### 原生字符串 r" " 实际是 废掉了字符串转义的过程**。

```
正则表达式：(\s*)含义是：匹配任意个空白符
正则表达式：[\s*]含义是：匹配空白符或者*
```

### 5.4 使用re模块实现正则表达式操作

#### 5.4.1 匹配字符串

##### 1.使用 match（）方法进行匹配

##### re.match 用于从字符串开始处匹配，起始处匹配成功返回match对象，否则返回None。

##### 例如，匹配字符串是否以“mr_”开头，不区分字母大小写，代码如下：

```
re.match(pattern, string, [flags])
#re.I：不区分字母大小写
#re.A：让\w不匹配汉字
import re
pattern = r"mr_\w+"
string = "MR_SHOP mr_shop"
match = re.match(pattern, string, re.I)
print(match)  #<re.Match object; span=(0, 7), match='MR_SHOP'>
string = "项目名称MR_SHOP mr_shop"
match = re.match(pattern, string, re.I)
print(match)  #None
```

##### 可见，match（）方法 从字符串的开始位置开始匹配 ， 当第一个字符不符合条件时 ， 则不再进行匹配 ，

##### 直接返回None。

##### 如果正则表达式中定义了组，就可以在 Match 对象上用 group() 方法提取出子串。

##### 注意到 group(0) 永远是原始字符串，group(1)、group(2)......表示第 1 、 2 、......个子串。

```
import re
pattern = r"mr_\w+"
string = "MR_SHOP mr_shop"
match = re.match(pattern, string, re.I)
print("起始位置：", match.start()) #起始位置： 0
print("结束位置：", match.end()) #结束位置： 7
print("位置的元组:", match.span()) #位置的元组： (0, 7)
print("要匹配的字符串：", match.string) #要匹配的字符串： MR_SHOP mr_shop
print("匹配数据：", match.group()) #匹配数据： MR_SHOP
import re
line = "Cats are smarter than dogs"
# .*表示匹配除换行符（\n、\r）之外的任何单个或多个字符（.是元字符：出换行以外的字符）
matchObj = re.match(r"(.*) are (.*?) .*", line, re.M | re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ))
print("matchObj.group(1):", matchObj.group( 1 ))
print("matchObj.group(2):", matchObj.group( 2 ))
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs
#matchObj.group(1): Cats
#matchObj.group(2): smarter
import re
line = "Cats are smarter than dogs"
# .*表示匹配除换行符（\n、\r）之外的任何单个或多个字符（.是元字符：出换行以外的字符）
#贪婪模式
matchObj = re.match(r"(.*)are(.*)(.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2): smarter than dogs.
#matchObj.group(3):.
matchObj = re.match(r“(.*)are(.*) (.*)”, line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
```

##### 贪婪模式 会 尽可能多 的匹配字符，当当前字符 不匹配时 ，会进行一次 回溯 。

##### 非贪婪模式（懒惰模式）则不进行回溯。

```
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2): smarter than.
#matchObj.group(3): dogs.
```

###### #非贪婪模式

```
matchObj = re.match(r"(.*)are(.*?)(.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2):.
#matchObj.group(3): smarter than dogs.
matchObj = re.match(r"(.*) are (.+?)(.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2): s.
#matchObj.group(3): marter than dogs.
import re
line = "Cats are smarter than dogs"
# .*表示匹配除换行符（\n、\r）之外的任何单个或多个字符（.是元字符：出换行以外的字符）
#贪婪模式
```

##### 注： match() 方法用于从字符串的开始进行匹配，如果在起始位置匹配成功，则返回 Match 对象，否则

##### 返回 None 。

```
matchObj = re.match(r"(.*) are (.?)(.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2): s.
#matchObj.group(3): marter than dogs.
matchObj = re.match(r"(.*) are (.?) (.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#No match
# .*表示匹配除换行符（\n、\r）之外的任何单个或多个字符（.是元字符：出换行以外的字符）
matchObj = re.match(r"(.*) are (.??)(.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2):.
#matchObj.group(3): smarter than dogs.
# .*表示匹配除换行符（\n、\r）之外的任何单个或多个字符（.是元字符：出换行以外的字符）
matchObj = re.match(r"(.*) are (.*?) (.*)", line, re.M|re.I)
if matchObj :
print("matchObj.group(0):", matchObj.group( 0 ) + ".")
print("matchObj.group(1):", matchObj.group( 1 ) + ".")
print("matchObj.group(2):", matchObj.group( 2 ) + ".")
print("matchObj.group(3):", matchObj.group( 3 ) + ".")
else :
print("No match!!")
#matchObj.group(0): Cats are smarter than dogs.
#matchObj.group(1): Cats.
#matchObj.group(2): smarter.
#matchObj.group(3): than dogs.
```

##### 2. 使用 search（）方法进行匹配

##### 参数同 match（）方法。

##### re.search（） 扫描 整个字符串 并返回 第一个 成功的匹配。

##### 我们可以使用 group(num) 或 groups() 匹配对象函数来获取匹配表达式。

##### 3. 使用 findall（）方法进行匹配

##### 参数同 match（）方法。

##### re.findall（）在字符串中找到正则表达式所匹配的 所有子串 ，并 返回一个列表 ，如果没 有找到匹配 的，

##### 则返回 空列表 。

```
re.search(pattern, string, [flags])
import re
pattern = r"mr_\w+"
string = "MR_SHOP mr_shop"
match = re.search(pattern, string, re.I)
print(match)  #<re.Match object; span=(0, 7), match='MR_SHOP'>
string = "项目名称MR_SHOP mr_shop"
match = re.search(pattern, string, re.I)
print(match)  #<re.Match object; span=(4, 11), match='MR_SHOP'>
import re
line = "Cats are smarter than dogs"
# .*表示匹配除换行符（\n、\r）之外的任何单个或多个字符（.是元字符：出换行以外的字符）
searchObj = re.search(r"(.*) are (.*?) .*", line, re.M|re.I)
if searchObj :
print("searchObj.group(0):", searchObj.group( 0 ) + ".")
print("searchObj.group(1):", searchObj.group( 1 ) + ".")
print("searchObj.group(2):", searchObj.group( 2 ) + ".")
else :
print("No match!!")
#searchObj.group(0): Cats are smarter than dogs.
#searchObj.group(1): Cats.
#searchObj.group(2): smarter.
searchObj = re.search(r"(.*) are (.*) .*", line, re.M|re.I)
if searchObj :
print("searchObj.group(0):", searchObj.group( 0 ) + ".")
print("searchObj.group(1):", searchObj.group( 1 ) + ".")
print("searchObj.group(2):", searchObj.group( 2 ) + ".")
else :
print("No match!!")
#searchObj.group(0): Cats are smarter than dogs.
#searchObj.group(1): Cats.
#searchObj.group(2): smarter than.
re.findall(pattern, string, [flags])
```

##### 此外，findall（）的结果是 根据分组进行匹配 ，即 只返回分组所匹配的（最后）结果 ，如：

```
import re
pattern = r"mr_\w+"
string = "MR_SHOP mr_shop"
match = re.findall(pattern, string, re.I)
print(match)  #['MR_SHOP', 'mr_shop']
string = "项目名称MR_SHOP mr_shop"
match = re.findall(pattern, string)
print(match)  #['mr_shop']
import re
pattern = r"[1-9]{1,3}(\.[0-9]{1,3}){3}"
str1 = "127.0.0.1 192.168.1.66"
match = re.findall(pattern, str1)
print(match)  #['.1', '.66']
pattern = r"([1-9]{1,3}(\.[0-9]{1,3}){3})"
str1 = "127.0.0.1 192.168.1.66"
match = re.findall(pattern, str1)
print(match)  #[('127.0.0.1', '.1'), ('192.168.1.66', '.66')]
>>> import re
>>> s = "qwe asd zxc rty fgh vbn uio jkl"
>>> match = re.findall("\w+\s+\w+", s)
>>> print(match)
['qwe asd', 'zxc rty', 'fgh vbn', 'uio jkl']
>>> match = re.findall("(\w+)\s+\w+", s)
>>> print(match)
['qwe', 'zxc', 'fgh', 'uio']
>>> match = re.findall("((\w+)\s+\w+)", s)
>>> print(match)
[('qwe asd', 'qwe'), ('zxc rty', 'zxc'), ('fgh vbn', 'fgh'), ('uio jkl', 'uio')]
>>> match = re.findall("(\w+(\w+)\s+\w+)(\s+\w+)", s)
>>> print(match)
[('qwe asd', 'e', ' zxc'), ('rty fgh', 'y', ' vbn')]
```

#### 5.4.2 使用正则表达式替换字符串

##### 把 string 中能匹配 pattern 的前 count 个内容换成 repl。

#### 5.4.3 使用正则表达式分割字符串

##### 把 string 按照能匹配 pattern 的内容最多进行 maxsplit 次分割并返回列表。

```
pattern = r"[1-9]{1,3}(\.[0-9]{1,3}){3}"
findallobj = re.findall( pattern, str1, re.M|re.I)
if findallobj:
print ("findallobj : ", findallobj)
else:
print ("Nothing found!!")
#findallobj : ['.1', '.66']
pattern=r'((\.[0-9]{1,3}){3})'
#findallobj : [('.3.2.1', '.1'), ('.168.1.66', '.66')]
pattern=r'(\.[0-9]{1,3}){2}'
#findallobj : ['.2', '.1']
re.sub(pattern, repl, string, count, flags)
re.split(pattern, string, [maxsplit], [flags])
```

## 第六章 函数

##### 【概念】 ： 函数 就是可以完成某项工作的 代码块 。

### 6.1 函数的创建和调用

#### 6.1.1 创建一个函数

##### 即使函数没有参数也 必须保留() ， 不要漏掉 ：

##### 例如，定义一个过滤危险字符的函数filterchar()，代码如下:

```
def functionname([parameterlist]):
['''comments''']
[functionbody] #return
def filterchar(string) :
'''功能'''
import re
pattern = r"(黑客)|(抓包)|(监听)(Trojan)"
sub = re.sub(pattern, "@_@", string)
print(sub)
```

#### 6.1.2 调用函数

### 6.2 参数传递

#### 6.2.1 形式参数和实际参数

##### 不可变对象→值传递：改变形参值，实参不变

##### 可变对象→引用传递：改变形参值，实参变化

```
functionname([parametersvalue])
def function_tips() :
import datetime #导入日期时间类
mot = ["Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"]
day = datetime.datetime.now().weekday()  #获取当前星期
print(mot[day])
```

###### #*****************调用函数*****************#

```
function_tips()
def ChangeInt(a):
a = 10
b = 2
ChangeInt(b)
print(b) #2
```

#### 6.2.2 位置参数

##### 【概念】 ： 位置参数 是必须按照定义时的 个数 和 顺序 进行参数传递，也称 必备参数 。

##### 1. 数量必须与定义时一致

```
def changeme(mylist):
"修改传入的列表"
mylist.append([ 1 , 2 , 3 , 4 ])
print ("函数内取值: ", mylist) #[10, 20, 30, 1, 2, 3, 4]
return
# 调用changeme函数
mylist1 = [ 10 , 20 , 30 ]
changeme(mylist1)
print ("函数外取值: ", mylist1)  #[10, 20, 30, 1, 2, 3, 4]
a=[ 1 , 2 , 3 ]
b=[ 1 , 2 , 3 ]
a.append( 4 )
print(a)  #[1, 2, 3, 4] (引用传递)
a = 'hello word'
a.replace('word','python')
print(a)  #"hello word" (值传递)
def demo(obj) :
print("原值：", obj)
obj += obj
```

###### #调用函数

```
mot = "AAA"
print("函数调用前：", mot)
demo(mot)
print("函数调用后：", mot)
mot = ["A", "A", "A"]
print("函数调用前：", mot)
demo(mot)
print("函数调用后：", mot)
```

###### #函数调用前： AAA

###### #原值： AAA

###### #函数调用后： AAA

###### #函数调用前： ['A', 'A', 'A']

###### #原值： ['A', 'A', 'A']

###### #函数调用后： ['A', 'A', 'A', 'A', 'A', 'A']

```
def function(name, number) :
······
function("A") (×)
function("A", 12 , 123 ) (×)
function("A", 12 ) (√)
```

##### 2. 位置必须与定义时一致

#### 6.2.3 关键字参数

##### 【概念】 ： 关键字参数 是指使用形式参数的名字来确定输入的参数值。

#### 6.2.4 为参数设置默认值

##### 可变对象做默认参数时：

##### Python函数在定义的时候，默认参数L的值就被计算出来了，即[]，因为默认参数 L也是一个变量 ，它指

##### 向对象[]，每次调用该函数，如果改变了L的内容，则下次调用时，默认参数的内容就变了，不再是函数

##### 定义时的[]了。

```
def function(name, height, weight) :
······
function("A", 60 , 175 ) (×)
function("A", 175 , 60 ) (√)
def function(name, height, weight) :
······
function(weight = 60 , name = "A", height = 175 )
def functionname(···, [parameter1 = defaultvalue1]):
[functionbody]
```

###### #默认参数放在所有参数的最后

```
def function(height, weight, name = "A") :
······
function( 175 , 60 ) (√)
def add_end(L = []):
L.append('SDU')
return L
print(add_end([ 1 , 2 , 3 ])) #[1, 2, 3, 'SDU']
print(add_end(['x', 'y', 'z'])) #['x', 'y', 'z', 'SDU']
def add_end(L = []):
L.append('SDU')
return L
print(add_end())  #['SDU']
print(add_end())  #['SDU', 'SDU']
def add_end(L = None):
if L is None:
L = []
L.append('SDU')
return L
print(add_end()) #['SDU']
print(add_end()) #['SDU']
```

##### Python的默认参数 只会在函数定义时被确定 ，而不是每次调用时重新确定，所以，一旦在函数中修改了

##### 默认参数，则在随后的调用中都会生效；由于这个特性，在定义函数时，如果默认参数使用可变的对象

##### 类型，如空列表，会导致逻辑出错。

##### 定义函数时，为形式参数设置默认值要牢记一点： 默认参数必须指向不可变对象 。

##### 在python中函数的默认参数在定义时确定，而不是每次调用时初始化值，如果不显式的对默认参数赋

##### 值，那么使用的是在编译时确定的对象。

##### 可变对象 这个对象内存地址不变，但是内容可以变。

##### 多学两招：在Python中，可以使用“函数名.*defaults*”查看函数的默认值参数的当前值，其结果是一个

##### 元组。例如，显示上面定义的 function() 函数的默认值参数的当前值,可以使用“function.*defaults*"， 结

##### 果为“('路人 ')”。

#### 6.2.5 可变参数

##### 【概念】 ：可变参数就是传入的参数个数是可变的，可以是 1 个、 2 个到任意个，还可以是 0 个。

##### 1. *parameter

##### 这种形式表示接收任意多个实际参数并将其放到一个元组中。

##### Python 允许在 list 或 tuple 前面加一个 * 号，把 list 或 tuple 的元素变成可变参数传进去。

```
def add_to(v, target = []) :
target.append(v)
return target
add_to( 1 )
add_to( 2 )
r = add_to( 3 )
print(r) #[1, 2, 3]
def add_to(v, target = None) :
if target is None : #不建议使用 target == None
target = []
target.append(v)
return target
add_to( 1 )
add_to( 2 )
r = add_to( 3 )
print(r) #[3]
def fun(*number) :
for item in number :
print(item, end = " ")
print("A")
fun() #A
fun( 1 )  #1 A
fun( 1 , 2 ) #1 2 A
```

###### #如果想要使用一个已经存在的列表作为函数的可变参数，可以在列表的名称前加"*"。

```
list1 = [ 1 , 2 , 3 ]
fun(*list1) #1 2 3 A
```

##### 2. **parameter

##### 这种形式表示接收任意多个类似关键字参数一样显式赋值的实际参数，并将其放到一个字典中。

##### 例如，定义一个函数，让其可以接收任意多个显式赋值的实际数，代码如下:

### 6.3 返回值

##### 在 Python 中，可以在函数体内使用 return 语句为函数指定返回值，该返回值可以是任意类型，且 无论

##### return 语句出现在函数的什么位置，只要得到执行就直接结束函数的执行 。

##### 多个返回值将保存一个元组。

### 6.4 变量的作用域

##### 【概念】 ：变量的作用域是指程序代码能够访问该变量的 区域 ，如果超出该区域，再访问时就会出现错

##### 误。

#### 6.4.1 局部变量

#### 6.4.2 全局变量

##### 与局部变量对应，全局变量为能够作用于函数内外的变量。

##### （ 1 ）如果一个变量，在函数外定义，那么不仅在函数外可以访问到，在函数内也可以访问到。在函数体

##### 以外定义的变量是全局变量。

##### 当局部变量与全局变量重名时，对函数体的变量进行赋值后，不影响函数体外的变量。

```
def function(*person) :
for list_person in person :
for item in person :
name = item[ 0 ]
height = item[ 1 ]
weight = item[ 2 ]
······
list1 = [("A", 175 , 60 ), ("B", 165 , 50 )]
list2 = [("C", 175 , 60 ), ("D", 165 , 50 )]
function(list1, list2)
def function(**sign) :
for key, value in sign.items() :
print(key, value)
function(A = 10 , B = 11 )
function(C = 12 , D = 13 , E = 14 )
```

###### #如果想要使用一个已经存在的字典作为函数的可亦参数，可以在空曲的夕称前加“**”

```
dict1 = {A : 10 , B : 11 , C : 12 }
function(**dict1)
return [value]
```

##### (2）在函数体内定义，并且使用 global 关键字修饰后，该变量也就变为全局变量。在函数体外也可以访

##### 问到该变量，并且在函数体内还可以对其进行修改。

##### 尽量避免全局和局部变量重名！

##### 函数内部的变量名称如果第一次出现，且出现在=前面，实际为定一个局部变量；函数内部变量名如果第

##### 一次出现且出现在=后面，且该变量在全局中已定义，那么就是引用全局变量。

```
a = 10
def test():
a = a + 1
print(a)
test()
```

###### #该程序报错！

```
#函数体内第一个a为定义的一个局部变量，后面的a为局部变量a的值，但a此时并没有赋值，程序报错
```

### 6.5 匿名函数

##### 回调函数

```
a = 10
def test():
s = a + 1
print(s)
test() #11
#等号后面的a为全局变量
img1 = [ 1 , 2 , 3 ]
img2 = [ 4 , 5 , 6 ]
def displ():
print(img1)
def modi():
img1 = img2
modi()
displ() #[1, 2, 3]
#modi函数中的img1为局部变量，不会修改全局变量的值
```

## 第七章 面向对象程序设计

### 7.1 面向对象概述

#### 7.1.1 对象

##### 面向对象：

##### 优点：易维护、易复用、易扩展，由于面向对象有封装、继承、多态性的特性，可以设计出低耦合的系

##### 统，使系统 更加灵活、更加易于维护。

##### 缺点：性能比面向过程低。

##### 面向过程：

##### 优点：性能比面向对象高，因为类调用时需要实例化，开销比较大，比较消耗资源;比如单片机、嵌入式

##### 开发、 Linux/Unix等一般采用面向过程开发，性能是最重要的因素。

##### 缺点：没有面向对象易维护、易复用、易扩展。

##### 通常将 对象 划分为 两个部分 ，即 静态部分 与 动态部分 。

##### 静态部分 被称为“ 属性 ”，任何对象都具备自身属性，这些属性不仅是客观存在的，而且是不能被忽视

##### 的，如人的性别。

##### 动态部分 指的是 对象的行为 ，即对象执行的动作，如人可以跑步。

#### 7.1.2 类

##### 类 是 封装对象的属性和行为 的 载体 ，反过来说具有相同属性和行为的一类实体被称为类。

##### Python 语言中，类是一种抽象的概念，如定义一个大雁类，该类中可以定义每个对象共有的属性和方

##### 法，而某只具体的大雁则是大雁类的一个对象， 对象是类的实例。

#### 7.1.3 面向对象程序设计的特点

##### 面向对象程序设计具有 三大基本特征 ： 封装 、 继承 和 多态 。

##### 1. 封装

##### 封装 是面向对象编程的核心思想，将 对象的属性和行为封装起来 ，其载体就是类,类通常会对客户 隐藏其

##### 实现细节 ，这就是封装的思想。

##### 2. 继承

##### 继承 是实现重复利用的重要手段，子类通过 继承复用了 父类的属性和行为的同时 又添加了 子类特有的属

##### 性和行为。

##### Python中可以说子类的实例都是父类的实例。

##### 3. 多态

##### 将父类对象应用于子类的特征就是 多态 。

##### 子类继承父类特征的同时，也具备了自己的特征，并且能够实现不同的效果，这就是多态化的结构。

### 7.2 类的定义和使用

#### 7.2.1 类的定义

##### statement：类体，主要由类变量（或类成员)、方法和属性等定义语句组成。

##### 如果在定义类时，没想好类的具体功能，也可以在类体中直接使用 pass 语句代替

#### 7.2.2 创建类的实例

#### 7.2.3 创建 **init**（）方法

```
class ClassName :  #大写字母开头的“驼峰式命名法”
'''类的帮助信息'''
statement
wildGoose = Geese()
print(wildGoose)
#wildGoose 是 Geese 类的实例
```

##### *init* () 中必须添加 self ，否则会报错！

#### 7.2.4 创建类的成员并访问

##### 类的成员主要由 实例方法 和 数据成员 组成。

##### 1. 创建实例方法并访问

```
class Geese :
def __init__(self) : #构造方法
print("我是大雁类")
wildGoose = Geese()  #大雁类的实例
```

##### 2. 创建数据成员并访问

##### 类属性在所有实例之间共享值！

##### 实例属性只能通过实例名访问。如果通过类名访问实例属性，将抛出异常！

### 7.3 属性

##### 略

### 7.4 继承

#### 7.4.1 继承的基本语法

#### 7.4.2 方法重写

#### 7.4.3 派生类中调用基类的**init**()方法

## 第八章 模块

### 8.1 模块概述

##### 在 Python 中，一个扩展名为“.py”的文件就称之为一个模块。

##### 通常情况下，将能够实现某一特定功能的代码放置在一个文件中作为一个模块，方便其他程序脚本导入

##### 使用。

##### 可以避免函数名和变量名冲突，还可以提高代码的复用性。

### 8.2 自定义模块

#### 8.2.1 创建模块

#### 8.2.2 使用 import 语句导入模块

##### 创建模块后，就可以在其他程序中使用该模块了，要使用模块需要先以模块的形式加载模块中的代码，

##### 可以使用 import 语句实现：

##### 使用 import 语句导入模块时，每执行一条 import 语句都会 创建一个新的命名空间 ，并且 在该命名空间

##### 中执行与.py文件相关的所有语句 ；在执行时，需在具体的变量、函数和类名前加上“ 模块名. ”前缀。

#### 8.2.3 使用 from···import 语句导入模块

##### 如果不想每次导入模块时都创建一个新的命名空间，而是 将具体的定义导入当前命名空间 ，可以使用

##### from...import 语句，使用该语句则 不再需要添加前缀，直接通过变量、函数和类名等访问即可 。

```
import modulename [as alias] #alisas 是别名
from modelname import member
```

#### 8.2.4 模块搜索目录

### 8.3 以主程序的形式执行

### 8.4 Python 中的包

#### 8.4.1 Python 程序的包结构

#### 8.4.2 创建和使用包

### 8.5 引用其他模块

#### 8.5.2 第三方模块的下载与安装

## 第九章 异常处理及程序调试

### 9.1 异常概述

##### 一个 python 的文件有两种使用的方法，第一是直接作为脚本执行，第二是 import 到其他的 python 脚本

##### 中被调用（模块重用）执行。

##### 因此 if **name** == "main" : 的作用就是控制这两种情况执行代码的过程，在 if **name** == 'main':

##### 下的代码只有在第一种情况下（即文件作为脚本直接执行）才会被执行，而import到其他脚本中是不会

##### 被执行的。

### 9.2 异常处理语句

#### 9.2.1 try···except语句

#### 9.2.2 try···except···else语句

#### 9.2.3 try···except···finally语句

#### 9.2.4 使用 raise 语句抛出异常

##### python 会自动引发异常，也可以通过raise 显示地引发异常。 一旦执行 了 raise 语 句， raise 后面的语

##### 句将不能执行 。

##### 为了捕获异常，"except"语句必须有用相同的异常来抛出类对象或者字符串。