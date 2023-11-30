#### 随机字符串生成

echo $(dd if=/dev/urandom | base64 -w0 | dd bs=1 count=20 2>/dev/null)

让我们逐步解释这个命令的每个部分：

1. ```
   dd if=/dev/urandom
   ```

   dd命令从/dev/urandom设备中读取随机字节。

   - `/dev/urandom`是一个非阻塞的随机数生成器设备，在大多数操作系统上可用。

2. ```
   base64 -w0将输入数据以Base64格式编码，并设置无换行符的输出。
   
   `-w0`选项告诉`base64`命令输出的编码部分无换行符。
   ```

3. ```
   dd bs=1 count=20
   ```

   使用dd命令从前面的Base64编码输出中截取前20个字符（通过设置每块大小为1字节，总块数为20）。

   - 这个步骤实际上是为了从Base64编码的字符串中提取原始的20字节随机数据，去除Base64编码部分。

4. ```
   2>/dev/null
   ```

   将错误输出重定向到/dev/null以避免在命令行上显示错误信息。这样做是为了避免在控制台上显示`dd`命令的`dd: warning: partial read`错误消息。
   
   ##### echo $(dd if=/dev/zero bs=1 count=20 2>/dev/null)读入零字节

#### 输出到当前终端

```
cat test.txt > output.txt > /dev/tty
```

#### 软链接

索引节点ls -il(包括索引节点)

#### 命令后台运行

```  
nohup sleep 30 > /dev/null 2>&1 &
```

#### 特殊变量

$* 与 $@

```
# test.sh
echo $*
echo $@
```

在终端运行(第一次建test.sh文件要先给可执行权限)

```
chmod +x test.sh
./test.sh aa bb cc dd
# 输出
aa bb cc dd
aa bb cc dd
```

但是没有区别

再试试另一种方式

```
# test.sh
for param in "$*"
do 
  echo $param
done

echo "------------------"

for param in "$@"
do 
  echo $param
done
```

#### 通配符

1. 匹配文件名或路径中的单个字符：

```shell
ls file?.txt
```

该命令将匹配文件名为 `file1.txt`、`fileA.txt` 的文件，其中 `?` 匹配一个字符。

2.匹配任意多个字符：

```

ls files*
# 该命令将匹配类似于 files.txt、filestest.txt 的文件，其中 * 匹配任意多个字符（包括零个字符）。
```

匹配字符echo "abc" | grep '[abc]'

#### shell语法

**if**

```
#!/bin/bash
read -p "Enter your number:" number

if [ $number -gt 10 ]; then
    echo "Number is greater than 10"
elif [ $number -eq 10 ]; then
    echo "Number is 10"
else
    echo "Number is less than 10"
fi
```

**case**

```
#!/bin/bash
read -p "Enter a fruit: " fruit

case $fruit in
    "apple")
        echo "You chose apple."
        ;;
    "banana")
        echo "You chose banana."
        ;;
    "orange")
        echo "You chose orange."
        ;;
    *)  # 默认情况
        echo "Invalid fruit."
        ;;
esac
```

**while**

```
#!/bin/bash
counter=1

while [ $counter -le 5 ]
do
    echo "Counter: $counter"
    counter=$((counter + 1))
done
```

**for**

```
#!/bin/bash
list="redrock SRE"

for x in $list; do
    echo $x
done
for ((i=0; i<5; i++)); do
    echo "Number: $i"
done
```

**函数**

```
greet() {
    echo "Hello, $1!"
    echo "Nice to meet you."
}

# 调用函数
greet "John"
```

```
process_args() {
    echo "Processing..."
    echo "$1"
    echo "$2"
    shift 2
    echo "$@"
}

# 调用函数，并传递参数
process_args "hello" "I" "love" "redrock"
```

在这个示例中，我们定义了一个名为 `process_args` 的函数，用于处理函数参数。在函数内部，我们首先输出一个提示消息，然后使用 `$1` 和 `$2` 分别访问第一个和第二个参数的值。然后，我们使用 `shift 2` 命令，将参数列表整体向前移动两个位置，即丢弃了当前的 `$1` 和 `$2`。最后，我们输出剩余的所有参数列表 `$@`。



