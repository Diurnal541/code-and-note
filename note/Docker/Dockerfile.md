# Dockerfile

## 1、docker build

docker build 基于dockerfile制作镜像
docker build [OPTIONS] PATH | URL | -
OPTIONS参数
-t:给镜像打标签
-c:-cpu-shares int:CPU份额
-m:-memory bytes:内存限制
--build-arg:设置构建时变量(构建时候修改ARG指令的参数)

## 2、 FROM

​    FROM指令必须是Dockerfile中非注释行的第一个指令，为镜像文件构建过程指定基础镜像，后续的指令运行于此基础镜像所提供的运行环境

    FROM <repository>[:<tag>]
    或
    FROM <repository>@<digest>
    <repository>:指定作为base image的名称
    <tag>:base image的标签，省略时候默认latest
    <digest>:镜像的哈希码
    
    示例：
    FROM busybox:latest

## 3、 MAINTAINER

用于让dockerfile制作者提供本人的详细信息

    MAINTAINER <authtor's detail>
    
    示例:
    FROM busybox:latest
    MAINTAINER "Along <along@along.com>"

## 4、 COPY

用于从docker 主机复制新文件或者目录至创建的新镜像指定路径中
COPY \<src>... \<dest>

    <src>：要复制的源文件或目录
    <dest>：目标路径，即正在创建的镜像的文件系统路径

## 5、 ADD

​    指令类似于COPY指令，ADD支持使用TAR文件和URL路径
​    ADD \<src> .. \<dest>
​    

    1、拷贝单个文件
    ADD ./a.txt WORKDIR/b
    
    2、拷贝多个文件
    ADD指令支持通配符，常用的示例如下：
    #拷贝当前目录下的bin文件夹的所有sh文件到/usr/bin目录下
    ADD ./bin/*.sh /usr/bin/
    
    #拷贝当前目录下的bin文件夹的所有带后缀的文件到/usr/bin目录下
    ADD ./bin/*.* /usr/bin/
    
    #拷贝当前目录下的bin文件夹的所有不带后缀的文件到/usr/bin目录下
    ADD ./bin/* /usr/bin/
    
    #拷贝当前目录下的bin文件夹的所有文件到/usr/bin目录下（/usr/bin目录原有的文件会保留）
    ADD ./bin/ /usr/bin/
    
    3、拷贝文件夹
    ADD ./config /usr/bin/config

## 6、 WORKDIR

用于为Dockerfile中所有的RUN、CMD、ENTRYPOINT、COPY和ADD指定设定工作目录
WORKDIR \<dirpath>

## 7、 VOLUME

​    用于在image中创建一个挂载点目录
​    VOLUME \<mountpoint>

## 8、 EXPOSE

​    用于为容器打开指定要监听的端口以实现与外部通信
​    EXPOSE \<port>[/ \<protocol>] [\<port>[/ \<protocol>]

    <protocol>用于指定传输层协议，可为tcp或udp二者之一，默认为TCP协议
    EXPOSE指令可一次指定多个端口，例如：EXPOSE 11211/udp 11211/tcp

## 9、 ENV

​    用于为镜像定义所需的环境变量，并可被Dockerfile文件中位于其后的其它指令(如ENV、ADD、COPY等)所调用
​    调用格式为$variable_ name 或 ${variable_ name}
​    ENV \<key> \<value>   一次只能设置一个
​    或
​    ENV \<key>=\<value>   一次可以设置多个键值对

## 10、 RUN

​    用于指定docker build过程中运行的程序，其可以是任何命令
​    RUN \<command> 
​    或
​    RUN ["\<executable>", "\<param1>", "\<param2>"]
​    第一种格式中，\<command>通常是一个shell命令， 且以“/bin/sh -c”来运行它，这意味着此进程在容器中的PID不为1,
​    不能接收Unix信号，因此，当使用docker stop \<container>命令停止容器时，此进程接收不到SIGTERM信号；

    第二种语法格式中的参数是一个JSON格式的数组，其中<executable>为要运行的命令，后面的 <paramN>为传递给命令
    的选项或参数；
    然而，此种格式指定的命令不会以“/bin/sh -c”来发起，因此常见的shell操作如变量替换以及通配符(?,*等)替换将不会进行；
    不过， 如果要运行的命令依赖于此shell特性的话，可以将其替换为类似下面的格式。
    RUN ["/bin/bash", "-c", "<executable>", "<param1>"]

## 11、CMD

​    类似于RUN指令，CMD指令也可用于运行任何命令或应用程序
​    RUN指令运行于映像文件构建过程中，而CMD指令运行于基于Dockerfile构建出的新映像文件启动一个容器时
​    

    CMD指令的首要目的在于为启动的容器指定默认要运行的程序，且其运行结束后，容器也将终止；不过，
    CMD指定的命令其可以被docker run的命令行选项所覆盖
    
    Dockerfile中可以存在多个CMD指令，但仅最后一个会生效
    
    CMD <command>  
    或
    CMD ["<executable>","<param1>","<param2>"] 
    或
    CMD ["<param1>","<param2>"]
    
    前两种语法格式的意义同RUN
    第三种则用于为ENTRYPOINT指令提供默认参数
    json数组中，要使用双引号，单引号会出错

## 12、ENTRYPOINT

​    类似CMD指令的功能，用于为容器指定默认运行程序，从而使得容器像是一个单独的可执行程序
​    与CMD不同的是，由ENTRYPOINT启动的程序不会被docker run命令行指定的参数所覆盖，而且，
​    这些命令行参数会被当作参数传递给ENTRYPOINT指定指定的程序
​    不过，docker run命令的 --entrypoint选项的参数可覆盖ENTRYPOINT指令指定的程序
​    

    ENTRYPOINT <command>
    或
    ENTRYPOINT ["<executable>", "<param1>", "<param2>"]
    
    docker run命令传入的命令参数会覆盖CMD指令的内容并且附加到ENTRYPOINT命令最后做为其参数使用
    Dockerfile文件中也可以存在多个ENTRYPOINT指令，但仅有最后一个会生效

## 13、HEALTHCHECK

​    HEALTHCHECK指令告诉Docker如何测试容器以检查它是否仍在工作。
​    即使服务器进程仍在运行，这也可以检测出陷入无限循环且无法处理新连接的Web服务器等情况
​    

    HEALTHCHECK [OPTIONS] CMD command (通过在容器内运行命令来检查容器运行状况)
    HEALTHCHECK NONE (禁用从基础映像继承的任何运行状况检查)
    
    OPTIONS 选项：
    --interval=DURATION (default: 30s)：每隔多长时间探测一次，默认30秒
    -- timeout= DURATION (default: 30s)：服务响应超时时长，默认30秒
    --start-period= DURATION (default: 0s)：服务启动多久后开始探测，默认0秒
    --retries=N (default: 3)：认为检测失败几次为宕机，默认3次
    
    返回值：
    0：容器成功是健康的，随时可以使用
    1：不健康的容器无法正常工作
    2：保留不使用此退出代码

## 14、ONBUILD

​    用于在Dockerfile中定义一个触发器
​    Dockerfile用于build映像文件，此映像文件亦可作为base image被另一个Dockerfile用作FROM指令的参数，
​    并以之构建新的映像文件
​    在后面的这个Dockerfile中的FROM指令在build过程中被执行时，将会“触发”创建其base image的Dockerfile文件
​    中的ONBUILD指令定义的触发器
​    

    ONBUILD < Instruction>
    尽管任何指令都可注册成为触发器指令，但ONBUILD不能自我嵌套，且不会触发FROM和MAINTAINER指令
    使用包含ONBUILD指令的Dockerfile构建的镜像应该使用特殊的标签，例如ruby:2.0-onbuil
    在ONBUILD指令中使用ADD或COPY指令应该格外小心，因为新构建过程的上下文在缺少指定的源文件时会失败

## 15、USER

​    用于指定运行image时的或运行Dockerfile中任何RUN、CMD或EntRyPoInT指令指定的程序时的用户名或UID
​    默认情况下，container的运行身份为root用户
​    

    USER <UID>| <U JserName >
    需要注意的是，<UID>可以为任意数字，但实践中其必须为/etc/ passwd中某用户的有效UID,否则，docker run命令将运行失败

## 16、ARG

​    ARG指令类似ENV，定义了一个变量；区别于ENV：用户可以在构建时docker build --build-arg <varname> = <value> 
​    进行对变量的修改；ENV不可以
​    如果用户指定了未在Dockerfile中定义的构建参数，那么构建输出警告
​    

    ARG <name>[= <default value>]
    Dockerfile可以包含一个或多个ARG指令

## 17、STOPSIGNAL

​    STOPSIGNAL指令设置将发送到容器出口的系统调用信号
​    此信号可以是与内核的系统调用表中的位置匹配的有效无符号数，例如9，或者SIGNAME格式的信号名，例如SIGKILL。
​    

    STOPSIGNAL signal