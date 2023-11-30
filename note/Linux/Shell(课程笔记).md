### 一、Shebang 

![image-20231103170950626](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103170950626.png)

### 二、执行shell脚本的方式

![image-20231103172005818](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103172005818.png)

### 三、shell和运维

![image-20231103172212589](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103172212589.png)

### 四、脚本语言

![image-20231103172405762](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103172405762.png)

**shell语言定义的变量，数据类型默认都是字符串**

### 五、关于单双引号的问题

双引号能够识别变量，双引号能够实现转义
单引号不能识别变量，只会原样输出，单引号不能实现转义

### 六、反引号 `

当在脚本中运行一些指令并且将执行的结果赋给变量的时候需要使用反引号

### 七、只读变量(readonly语法)

readonly 变量名
示例:
a=10
readonly a
a=20
echo $a
最后的输出结果是10，而不是20

### 八、接收用户输入(read语法)

read -p 提示信息 变量名
示例:
![image-20231103184721233](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103184721233.png)

![image-20231103184730215](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103184730215.png)

### 九、删除变量(unset语法)(了解)

unset 变量名

![image-20231103185544581](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103185544581.png)

![image-20231103185624630](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103185624630.png)

### 十、条件判断句(if)

###### 语法一:(一个条件)

if condition
then
    command1
    command2
   …
fi
单行写法:if [condition];then command;fi

###### 语法二:(两个条件)

if condition
then
    command1
    command2
    …
else
    command
fi

###### 语法三:(多个条件)

if condition1
then
    command1
elif condition2
then
    command3
else
    commandN
fi

### 十一、运算符

###### 1. 算术运算符

a=10,b=20

![image-20231103190525449](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103190525449.png)

原生bash不支持简单的数学运算，但是可以通过其他命令来实现，例如 awk 和expr,expr最常用

![image-20231103190815127](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231103190815127.png)

注意，*容易被识别为通配符，要使它的含义为乘号，需要加反斜杠\\\*



