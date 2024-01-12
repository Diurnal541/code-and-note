# Nmap列举远程机器开放的端口

![image-20231221224111770](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221224111770.png)

![image-20231221224533123](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221224533123.png)

## ![image-20231221224812470](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221224812470.png)	–dns-servers

nmap进行探测之前要把域名通过DNS服务器解析为IP地址，我们也可以使用指定的DNS服务器进行解析。使用**--dns-servers**参数来指定

```shell
nmap --dns-servers 8.8.8.8 scanme.nmap.org
# --dns-servers 8.8.8.8：这个参数指定了要使用的DNS服务器的地址。在这个例子中，8.8.8.8 是Google的公共DNS服务器地址。
```

![image-20231221225102646](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221225102646.png)

![image-20231221225218188](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221225218188.png)

## -Pn（弃用）

对于已经知道主机存活或者防火墙开启的机器，可以使用**-Pn**参数来停止探测之前的ICMP请求。以达到不触发防火墙安全机制

![image-20231221225530544](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221225530544.png)

![image-20231221225543718](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221225543718.png)

## -p

对于默认的端口范围，并不能满足日常工作需要。可以使用**-p** m-n来指定探测端口范围为m-n之间的所有端口。

![image-20231221230148218](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221230148218.png)

![image-20231221230203233](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221230203233.png)

## 端口状态

* open 表示端口处于开放状态
* closed 表示端口处于关闭状态
* filtered 表示端口处于过滤无法收到返回的probe状态
* unfilterd 表示端口收到返回的probe，但是无法确认
* opend/unfilterd 表示端口处于开放或者是未过滤状态
* closed/unfilterd 表示端口处于关闭或者未过滤状态

## Nmap扫描技术查看

输入nmap -h来查看nmap自带的帮助信息

# Nmap识别目标机器上的服务指纹

## 服务指纹

![image-20231221230834810](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221230834810.png)

## Nmap识别服务指纹

```shell
nmap -sV IP #识别目标机器的服务信息
```

![image-20231221231412023](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221231412023.png)

![image-20231221231430167](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231221231430167.png)

## Nmap侵略性的探测

```shell
nmap -A -v -T4 IP地址 # 来探测目标机器的操作系统、服务等信息
# -A使用侵略性的探测，包括操作系统的识别，端口服务的指纹识别
# -v持续输出返回的解析
# -T4加快探测速度
# -A 参数：这个参数告诉 nmap 执行操作系统检测、版本检测、脚本扫描和跟踪路由等一系列高级扫描技术。这个参数的作用是执行全面的扫描，以获取目标主机的详细信息。
# -v 参数：这个参数表示“详细模式”或“冗长模式”，它告诉 nmap 输出更详细的信息，包括扫描过程中的详细日志和状态更新。
# -T4 参数：这个参数指定了扫描的速度/优先级。-T4 表示使用“快速”扫描模式，这意味着 nmap 将以较高的速度执行扫描，但仍会尝试保持低调以避免被目标系统检测到。
```

![image-20231222081250005](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222081250005.png)

![image-20231222081424544](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222081424544.png)

```shell
nmap -sC -sV -O 192.168.88.129 #来探测目标机器的操作系统、服务等信息
# -sC参数表示使用Nmap脚本进行探测，等同于 --script=default
# -sV参数表示探测目标机器上的服务信息
# -O参数表示探测目标机器的操作系统信息
# -sC 参数表示使用默认的脚本扫描。这将使Nmap运行一组常见的脚本来探测目标主机的漏洞和安全问题。
# -sV 参数表示进行版本检测。Nmap将尝试探测目标主机上运行的网络服务的版本信息。
# -O 参数表示进行操作系统检测。Nmap将尝试猜测目标主机正在运行的操作系统类型。
```

![image-20231222083836319](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222083836319.png)

![image-20231222083849339](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222083849339.png)

# Nmap发现局域网中的存活主机

## 主机发现

CIDR（无类别域间路由，Class Inter-Domain Routing），可以快速表示一个网络。比如：**172.16.1.1/24 表示在 172.16.1.1-172.16.1.255之间 的所有主机IP地址**

```shell
nmap -sn CIDR # 对该网络中所有主机进行ping扫描，以探测主机存活性。扫描过程中使用了TCP SYN扫描、ICMP echo Request来探测主机存活
```

![image-20231222192635927](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222192635927.png)

上面这张图自动把 -sP 改成 -sn 了，因为-sP被弃用，取而代之的是-sn

![image-20231222192646614](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222192646614.png)

```shell
nmap -sn CIDR # 对该网络中所有主机进行ping扫描，以探测主机存活性
```

![image-20231222193105897](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222193105897.png)

```shell
nmap -sn CIDR -oX test.xml # 对该网络所有主机进行ping扫描，以探测主机存活性，同时将结果输出到test.xml文件中，以便后续使用。
```

# Nmap端口探测技巧

在实际环境中，当系统管理员对设备进行管理时，或者渗透测试人员对设备进行检测时，并不一定对所有的服务进行操作。极有可能是对某个或或者某个范围的服务进行检测。

如果对所有服务进行探测，那么会出现耗时长，费力不讨好的情况。针对这样的情况，我们很有必要了解如何使用Nmap来更加灵活的进行服务探测，避免全端口探测对服务器造成压力。

```shell
nmap -p80 scanme.nmap.org # -p80是指对80端口进行扫描
```

![image-20231222194026762](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222194026762.png)

![image-20231222194038139](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222194038139.png)

```shell
nmap -p80,135 scanme.nmap.org # 对80和135端口探测 
```

![image-20231222194234906](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222194234906.png)

![image-20231222194244760](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222194244760.png)

```shell
nmap -p1-100 scanme.nmap.org # 对1-100端口进行探测
```

![image-20231222194442574](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222194442574.png)

![image-20231222194454288](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222194454288.png)

```shell
nmap -p- 192.168.88.129 # 对所有端口进行探测
```

![image-20231222195840634](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222195840634.png)

![image-20231222195831821](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222195831821.png)

```shell
nmap -p T:25,U:53 scanme.nmap.org
# T:25表示探测TCP25号端口，U:53表示探测UDP的53号端口
# T:25,U:53表示同时扫描TCP端口25和UDP端口53。这意味着Nmap将尝试连接到TCP端口25和发送UDP数据包到UDP端口53，以检查这些端口的状态。
```

![image-20231222195901325](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222195901325.png)

![image-20231222195350503](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222195350503.png)

```shell
nmap -p smtp scanme.nmap.org # 通过服务名称来扫描端口
```

```shell
nmap -p s* scanme.nmap.org # 扫描所有s开头的服务的端口，*是通配符
```

```shell
nmap -p [1-65535]scanme.nmap.org # 扫描注册在nmap中的端口
```

# NSE脚本使用

NSE（Nmap Script Engine）Nmap的脚本引擎，内置很多可以用来扫描的、针对特定任务的脚本。通过NSE可以不断拓展Nmap的扫描策略，加强Nmap的功能。

Nmap中使用 --script 参数来指定调用的脚本，并且脚本存储在Nmap安装路径下的script文件夹下，对于kali Linux存储在/usr/share/nmap/script下。

```shell
nmap --script http-title 192.168.88.129
# --script http-title: 这个参数告诉Nmap工具要执行的脚本是http-title。这个脚本用于获取Web服务器的标题信息。
```

![image-20231222201438569](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222201438569.png)

```shell
 nmap --script http-headers 192.168.88.129 # 使用http-headers脚本来获取指定IP地址上HTTP服务的头信息。
```

![image-20231222201648398](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222201648398.png)

```shell
nmap -sV --script vuln 192.168.88.129
# -sV表示探测对于服务版本信息
# vuln脚本表示对漏洞进行扫描
```

![image-20231222203658780](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222203658780.png)

```shell
nmap -sV --script="version,discovery" 192.168.88.129 # 发现和版本信息分类进行探测
# --script="version,discovery"：这也是nmap命令的一个选项，用于指定要运行的脚本。在这个例子中，指定了两个脚本，分别是"version"和"discovery"。这些脚本用于执行特定的任务，比如获取服务版本信息和执行发现扫描。
```

![image-20231222205730104](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222205730104.png)

![image-20231222205800585](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222205800585.png)

```shell
nmap -sV --script="not exploit" 192.168.88.129 # 使用Nmap除了exploit分类之外的其他分类进行探测
# -sV：这是nmap命令的一个参数，表示进行版本检测。它告诉nmap在扫描过程中尝试探测目标主机上运行的服务的版本信息。
# --script="not exploit"：这是nmap命令的另一个参数，表示指定要运行的脚本。在这里，“not exploit”是一个脚本的名称，它告诉nmap在扫描过程中不要运行与利用漏洞相关的脚本。
# 因此，整个命令的含义是使用nmap工具对IP地址为192.168.88.129的主机进行扫描，其中包括进行版本检测，并且在扫描过程中不运行与利用漏洞相关的脚本。
```



```shell
nmap -sV --script "(http*) and not (http-slowors and http-brute)" 192.168.88.129 # 使用Nmap中http*的脚本，但是除了http-slowors和http-brute
# -sV 参数表示进行版本检测。这将使Nmap尝试探测目标主机上运行的服务的版本信息。
# --script 参数后面跟着的是脚本的过滤条件。在这个例子中，使用的是一个复杂的条件，它包括两部分：
# (http*) 表示选择所有与HTTP相关的脚本。这将使Nmap只运行与HTTP服务相关的脚本。
# not (http-slowloris and http-brute) 表示排除名为http-slowloris和http-brute的脚本。这将阻止Nmap运行与慢速攻击和暴力破解相关的HTTP脚本。
# 综上所述，这个命令的含义是使用Nmap对IP地址为192.168.88.129的主机进行版本检测，并且只运行与HTTP服务相关的脚本，同时排除与慢速攻击和暴力破解相关的HTTP脚本。
```



```shell
nmap -sV --script exploit -d 3 --script-trace 192.168.88.129 # 使用Nmap中exploit，但是在使用的同时开启调试模式
# -sV：这个参数表示进行版本检测。Nmap将尝试探测目标主机上的开放端口所运行的服务的版本信息。
# --script exploit：这个参数指定了要运行的Nmap脚本。在这种情况下，exploit脚本用于检测目标主机上是否存在已知的漏洞或安全问题。
# -d 3：这个参数表示Nmap的调试级别。在这里，-d 3表示将调试级别设置为3，以便输出更详细的调试信息。
# --script-trace：这个参数用于启用脚本追踪功能。当使用此参数时，Nmap将输出有关脚本执行过程的详细信息，包括脚本的执行顺序和结果。
# 通过这条命令，Nmap将对指定的IP地址进行版本检测，并尝试利用exploit脚本来探测目标主机上的已知漏洞或安全问题。同时，Nmap还会输出详细的调试信息和脚本执行过程的追踪信息。
```

## NSE参数的使用

```shell
nmap -sV --script http-title --script-args http.useragent="Mozilla 999" 192.168.88.129 # 使用nmap的http-title脚本，并指定使用对应的user-agent
# -sV：这个参数指示Nmap对目标进行服务版本检测。它将尝试确定目标主机上运行的每个开放端口的服务及其版本信息。
# --script http-title：这个参数指示Nmap运行名为http-title的NSE（Nmap脚本引擎）脚本。这个脚本用于从HTTP服务中提取标题信息。
# --script-args http.useragent="Mozilla 999"：这个参数用于设置http-title脚本的参数。在这种情况下，它设置了HTTP请求的用户代理标头为Mozilla 999。用户代理标头是一个HTTP标头，用于标识发出请求的用户代理软件的信息。
# 因此，整个命令的含义是使用Nmap对IP地址为192.168.88.129的主机进行服务版本检测，并使用http-title脚本从HTTP服务中提取标题信息，同时设置HTTP请求的用户代理标头为Mozilla 999。
```

## NSE更新

```shell
nmap --script-updatedb # 更新脚本数据库
```

## NSE脚本分类

- **auth：这些脚本涉及目标系统上的身份验证凭据（或绕过它们）。**例如，x11-access，ftp-anon和oracle-enum-users。使用暴力破解攻击来确定凭据的脚本被放置在brute类别中。
- **broadcast：这些脚本通常用于通过在本地网络上广播来发现未在命令行上列出的主机。**使用newtargets脚本参数可以允许这些脚本自动将它们发现的主机添加到Nmap扫描队列中。
- **brute：这些脚本使用暴力破解攻击来猜测远程服务器的身份验证凭据。**Nmap包含用于暴力破解数十种协议的脚本，包括http-brute，oracle-brute，snmp-brute等。
- **default：这些脚本是默认设置的脚本集，在使用-sC或-A选项时运行，而不是使用--script列出脚本。**默认扫描需要产生有价值和可操作的信息。默认脚本需要产生有价值和可操作的信息。如果即使脚本作者都很难解释为什么普通的网络或安全专业人员会发现输出有价值，那么该脚本就不应该默认运行。
- **discovery：这些脚本尝试通过查询公共注册表、启用SNMP的设备、目录服务等来主动发现网络的更多信息。**
- **dos：这些脚本可能导致拒绝服务。**有时这是为了测试对拒绝服务方法的漏洞性，但更常见的是测试传统漏洞的一个不受欢迎但必要的副作用。
- **exploit：这些脚本旨在积极利用某些漏洞。**例如jdwp-exec和http-shellshock。
- **external：这些脚本可能会向第三方数据库或其他网络资源发送数据。**例如whois-ip，它会连接到whois服务器以了解目标地址的信息。
- **fuzzer：这些脚本旨在向服务器软件发送意外或随机的字段。**这种技术对于发现软件中未发现的错误和漏洞非常有用，但它既是一个缓慢的过程，也是带宽密集型的。
- **intrusive：这些脚本非常具有侵入性，因为它们在远程系统上使用了大量资源，很可能会使系统或服务崩溃，或者很可能被远程管理员视为攻击。**
- **malware：这些脚本用于检测与恶意软件相关的问题。**
- **safe：这些脚本通常是安全的，不太可能对目标系统造成负面影响。**
- **version：这些脚本用于检测目标系统的版本信息。**
- **vuln：这些脚本用于检测目标系统的漏洞**

https://nmap.org/nsedoc/这个网站提供更详细的信息

# 使用特定网卡进行探测

Nmap是一款可拓展性强的工具，并且有些NSE脚本支持嗅探。但是这种功能需要网卡支持混杂模式才可以。或者当计算机上有两张网卡，并且两张网卡对应不同的网络。

Nmap提供了切换使用特定网卡进行探测的参数 -e

## 指定网卡进行探测

```shell
nmap -e eth0 192.168.88.1/24
# 使用 nmap 工具，通过 eth0 网络接口对 192.168.88.1/24 范围内的 IP 地址进行扫描。
```

```shell
nmap -iflist # 列出网卡信息
```

![image-20231222221020072](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231222221020072.png)

up代表开启，down代表关闭

# 对比扫描结果ndiff

对某个网络进行探测的时候，有可能之前有探测过的结果，现在探测过后，需要对之前的结果与现在的结果来对比，找到两次不同点。

监视网络变化，达到网络监控的目的。

## 工具ndiff介绍

在Nmap整个工程中，除了主要的nmap工具之外，还包括很多其他工具。如ndiff工具。

```shell
nmap -A -v -T4 192.168.88.129 -oX kali1.xml # 先进行一次扫描，并将扫描结果存入kali1.xml
service apache2 start # 启动apache2
nmap -A -v -T4 192.168.88.129 -oX kali2.xml # 再进行一次扫描，并将扫描结果存入kali2.xml
ndiff kali1.xml kali2.xml # 对比两个文件的不同
```



