# Kali渗透

![image-20231220130043199](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220130043199.png)

msfconsole

![image-20231220130137805](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220130137805.png)

search ms17_010

![image-20231220130226730](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220130226730.png)

![image-20231220130327384](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220130327384.png)

![image-20231220131014518](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131014518.png)

![image-20231220131030349](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131030349.png)

![image-20231220131046280](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131046280.png)

![image-20231220131204820](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131204820.png)

![image-20231220131503331](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131503331.png)

![image-20231220131531087](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131531087.png)

![image-20231220131930826](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20231220131930826.png)

# 信息收集

* 信息收集是渗透测试成功的保障
* 更多的暴露面
* 更大的可能性

## 主动信息收集

通过直接访问网站在网站上进行操作、对网站进行扫描等，这种是网络流量经过目标服务器的信息手机方式

## 被动信息收集

基于公开的渠道，比如搜索引擎等，在不与目标系统直接交互的情况下获取信息，并且尽量避免留下痕迹

## 收集哪些信息

* 服务器信息（端口、服务、真实IP）
* 网站信息（网站架构（操作系统、中间件、数据库、编程语言）、指纹信息、WAF、敏感目录、敏感文件、源码泄露、旁站查询、C段查询）
* 域名信息（whois、备案信息、子域名）
* 人员信息（姓名、职务、生日、联系电话、邮件地址）

## 域名信息收集

域名：一串用点分隔的名字组成的internet上某一台计算机或计算机组的名称。

DNS：域名系统，是互联网的一项服务。作为将域名和IP地址相互映射的一个分布式数据库，能够使人更方便地访问互联网。

## 域名分类

* 顶级域名：.com
* 二级域名：baidu.com
* 三级域名：www.baidu.com
* 政府域名：.gov
* 商业域名：.com
* 教育域名：.edu

## Whois

whois是用来查询域名的IP以及所有者等信息的传输协议。就是一个用来查询域名是否被注册，以及注册域名的详细信息的数据库（如域名所有人，域名注册商）

通过whois查询可以获得域名注册者邮箱地址等信息。一般情况下对于中小型网站域名注册者就是网站管理员。利用搜索引擎对whois查询到的信息进行搜索，获得更多域名注册者个人信息。

## 域名信息------whois

Web接口查询：

* https://whois.aliyun.com/
* https://www.whois365.com/cn/
* http://whois.chinaz.com/

whois命令行查询

Whois baidu.com

## 域名信息------备案信息

web接口查询：

* http://www.beianbeian.com/
* http://www.beian.gov.cn/portal/registerSys
* http://icp.chinaz.com/

## 域名信息------whois反查

### 注册人/邮箱反查

先通过whois获取注册人和邮箱，再通过注册人和邮箱反查域名

缺点是很多公司都是DNS解析的运营商注册的，查到的是运营商代替个人和公司注册的网站信息

http://whois.chinaz.com/reverse?ddlSearchMode=1

http://whois.4.cn/reverse

https://whois.aizhan.com/

## 子域名信息收集

子域名指二级域名，二级域名是顶级域名（一级域名）的下一级

比如mail.heetian.com和bbs.heetian.com是heetian.com的子域，而heetian.com则是顶级域名.com的子域

### Google搜索引擎的使用技巧

|   语法   |           用法           |
| :------: | :----------------------: |
|   site   |         指定域名         |
|  inurl   |  URL中存在的关键字页面   |
|  intext  |   网页内容里面的关键字   |
| Filetype |       指定文件类型       |
| intitle  |    网页标题中的关键字    |
|   link   | 返回你所有的指定域名链接 |
|   info   |     查找指定站点信息     |
|  cache   |  搜索Google里的内容缓存  |

* **site**:xuegod.cn

  site:.jp

  site:.uk

  site:.com

  site:.net

* **inurl**:qq.txt

  inurl:admin.php

  inurl:admin_login.php

* intitle:后台登录

  intitle:index.of.bash_history

  * index.of表示包含index.of字段，出现该字段表示网站目录是对我们开放的，我们可以查看到网站目录下的所有文件信息
  * .bash_history表示我们要筛选的文件名称，也可以替换成其他的敏感信息文件，该文件记录了用户的历史命令记录

  查找discuz论坛中存储mysql密码的配置文件config_global.php

* cache返回的结果是被搜索引擎收录时的页面，比如一些页面被删除了，我们可以通过cache还是可以访问。

  cache:xuegod.cn

* filetype:torrent kail

  * Kail是我们要搜索的关键字
  * filetype指定文件类型
  * torrent文件类型名称，torrent是种子文件，可以填写任意扩展名

  filetype:pdf 渗透安全

* apache site:bbs.xuegod.cn

  apache是我们搜索的关键字

  site可查询网站的收录情况

  bbs.xuegod.cn目标网站：学神官方论坛

* intext:user.sql intitle:index.of 组合使用技巧

  intext:user.sql查询包含user.sql用户数据库信息的页面

  intitle:index.of表示网站目录是开放状态

### 第三方网站查询

https://dnsdumpster.com

http://tool.chinaz.com/subdomain

网络空间安全搜索引擎

https://fofa.so/

### ssl证书查询

https://crt.sh/

### js文件发现子域名JSFinder

https://github.com/Threezh1/JSFinder

- **简单爬取**

```
python JSFinder.py -u http://www.mi.com
```



这个命令会爬取 [http://www.mi.com](http://www.mi.com/) 这单个页面的所有的js链接，并在其中发现url和子域名

返回示例：

```
url:http://www.mi.com                                         
Find 50 URL:                                                  
http://api-order.test.mi.com                                  
http://api.order.mi.com                                       
http://userid.xiaomi.com/userId                               
http://order.mi.com/site/login?redirectUrl=                                                   
...已省略                            
                                                              
Find 26 Subdomain:                                            
api-order.test.mi.com                                         
api.order.mi.com                                              
userid.xiaomi.com                                             
order.mi.com                                                                                              
...已省略
```



- **深度爬取**

```
python JSFinder.py -u http://www.mi.com -d
```



深入一层页面爬取JS，时间会消耗的更长。

建议使用-ou 和 -os来指定保存URL和子域名的文件名。 例如：

```
python JSFinder.py -u http://www.mi.com -d -ou mi_url.txt -os mi_subdomain.txt
```



- **批量指定URL/指定JS**

指定URL：

```shell
python JSFinder.py -f text.txt
```



指定JS：

```shell
python JSFinder.py -f text.txt -j
```



可以用brupsuite爬取网站后提取出URL或者JS链接，保存到txt文件中，一行一个。

指定URL或JS就不需要加深度爬取，单个页面即可。

- **其他**

-c 指定cookie来爬取页面 例：

```shell
python JSFinder.py -u http://www.mi.com -c "session=xxx"
```



-ou 指定文件名保存URL链接 例：

```shell
python JSFinder.py -u http://www.mi.com -ou mi_url.txt
```



-os 指定文件名保存子域名 例：

```shell
python JSFinder.py -u http://www.mi.com -os mi_subdomain.txt
```



- **注意**

url 不用加引号

url 需要http:// 或 https://

指定JS文件爬取时，返回的URL为相对URL

指定URL文件爬取时，返回的相对URL都会以指定的第一个链接的域名作为其域名来转化为绝对URL。

- **截图**

实测简单爬取：

```shell
python3 JSFinder.py -u https://www.jd.com/
```



URL:

[![02.jpg](https://camo.githubusercontent.com/f76142c576feee24876a4169f566d4af0eae4adba35e4023d57e36d2ad116e11/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f61524f46493566433355794b3845502e6a7067)](https://camo.githubusercontent.com/f76142c576feee24876a4169f566d4af0eae4adba35e4023d57e36d2ad116e11/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f61524f46493566433355794b3845502e6a7067)

[![03.jpg](https://camo.githubusercontent.com/0a15f4f8c9098896f4f0f2841fcf47858e71f41b07de603cade4253ff0af27c2/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f72584334426261376f4d77384148572e6a7067)](https://camo.githubusercontent.com/0a15f4f8c9098896f4f0f2841fcf47858e71f41b07de603cade4253ff0af27c2/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f72584334426261376f4d77384148572e6a7067)

Subdomain:

[![01.jpg](https://camo.githubusercontent.com/ff3f417dd10f040a2d2bc1b7037ca9ff89f1f977e41be80483b7205aec4dcab7/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f36395776446d7937616c34685166642e6a7067)](https://camo.githubusercontent.com/ff3f417dd10f040a2d2bc1b7037ca9ff89f1f977e41be80483b7205aec4dcab7/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f36395776446d7937616c34685166642e6a7067)

实测深度爬取：

```shell
python3 JSFinder.py -u https://www.jd.com/ -d -ou jd_url.txt -os jd_domain.txt
```



[![05.jpg](https://camo.githubusercontent.com/be489889c8bacbf1099129f2f33f55f5d3ffbd8a47abf505fa8a178c2b0b56b0/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f64687854516e615734656639567a752e6a7067)](https://camo.githubusercontent.com/be489889c8bacbf1099129f2f33f55f5d3ffbd8a47abf505fa8a178c2b0b56b0/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f64687854516e615734656639567a752e6a7067)

[![06.jpg](https://camo.githubusercontent.com/3dee639e565c3a57d2d022adf2b9317cecddbbf4ff9a172f8a83f041d5d4901b/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f4e415839506e4c6157366d656c566b2e6a7067)](https://camo.githubusercontent.com/3dee639e565c3a57d2d022adf2b9317cecddbbf4ff9a172f8a83f041d5d4901b/68747470733a2f2f692e6c6f6c692e6e65742f323032302f30352f32342f4e415839506e4c6157366d656c566b2e6a7067)

实际测试：

```shell
http://www.oppo.com
URL:4426 个
子域名：24 个

http://www.mi.com
URL:1043 个
子域名：111 个

http://www.jd.com
URL:3627 个
子域名：306 个
```

### 子域名挖掘机

不常用，不好用

### OneForAll

优点：功能强大

缺点：需要api

https://github.com/shmilylty/OneForAll

python3 oneforall.py –target hetianlab.com run

### Subdomainsbrute

https://github.com/lijiejie/subDomainsBrute

![image-20231220221003967](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220221003967.png)

## IP地址信息收集

### IP反查域名

http://stool.chinaz.com/same

https://tools.ipip.net/ipdomain.php

![image-20231220221945458](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220221945458.png)

### 域名查询IP

http://ip.tool.chinaz.com/

### CDN

![image-20231220222143790](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220222143790.png)

### 判断CDN---多地ping

http://ping.chinaz.com/

http://www.webkaka.com/Ping.aspx

### 绕过CDN---国外访问

https://asm.ca.com/en/ping.php

### 绕过CDN---查询子域名IP

### 绕过CDN---phpinfo文件

![image-20231220222826925](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220222826925.png)

![image-20231220222842328](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220222842328.png)

### 绕过CDN---Mx记录邮件服务

![image-20231220222907455](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220222907455.png)

### 绕过CDN---查询历史DNS记录

https://dnsdb.io/zh-cn/

https://securitytrails.com/

https://x.threatbook.cn/

### Nmap

nmap -sP www.XXX.com/24 || nmap -sP 192.168.1.*

### Cwebscanner

https://github.com/se55i0n/Cwebscanner

快速扫描C段web应用，获取请求状态code、server、title信息

![image-20231220224333554](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20231220224333554.png)
