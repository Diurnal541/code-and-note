from django.shortcuts import render, HttpResponse, redirect

# Create your views here.
def index(request):
    return HttpResponse("Hello World!!!")

def tpl(request):
    name = "张三"
    roles = ["管理员", "CEO", "保安"]
    user_info = {"name":"李四", "salary":10000,"role":"CEO"}
    return render(
        request,
        "tpl.html",
        {
            "n1":name,
            "n2":roles,
            "n3":user_info
        }
    )
def something(request):
    # request是一个对象，封装了用户发送过来的所有请求相关数据

    # 1.获取请求方式：GET/POST
    print(request.method)

    # 2.在URL上传递值 /something/?n1=123&n2=234，在pycharm的终端上显示出来
    print(request.GET)

    # 3.用POST方法传递值
    print(request.POST)

    # 4.【响应】 HttpResponse("返回内容")，内容字符串返回给请求者。
    # return HttpResponse("返回内容")

    # 5.【响应】读取HTML内容 + 渲染（替换） -> 字符串，返回给用户浏览器。
    # return render(request, 'something.html', {"title":"来了"})

    # 6.【响应】让浏览器重定向到其它页面
    return redirect("https://baidu.com")
def login(request):
    if request.method == "GET":
        return render(request, 'login.html')
    else:
        # 如果是POST请求，获取用户提交的数据
        # print(request.POST)
        username = request.POST.get("user")
        password = request.POST.get("pwd")
        if username == "root" and password == "123":
            # return HttpResponse("登录成功")
            return redirect("https://www.baidu.com")
        else:
            return render(request, 'login.html', {"error_msg":"登录失败"})

from app01 import models
def orm(request):
    # ###插入数据库数据（新建）###
    # models.Department.objects.create(title="销售部")
    # models.Department.objects.create(title="IT部")
    # models.Department.objects.create(title="运营部")
    #
    # models.UserInfo.objects.create(name="张三", password="123", age="32")
    # models.UserInfo.objects.create(name="李四", password="234", age="28")
    # ###删除###
    # models.UserInfo.objects.filter(id=3).delete()# 删除id=3的数据
    # models.Department.objects.all().delete()# 删除所有数据

    # ###筛选###
    data_list = models.UserInfo.objects.all()
    print(data_list)# <UserInfo: UserInfo object (1)>, <UserInfo: UserInfo object (2)>
    for obj in data_list:
        print(obj.id, obj.name, obj.password, obj.age)
        # 1 张三 123 32
        # 2 李四 234 28
    # ###更新###
    models.UserInfo.objects.all().update(password=999)
    models.UserInfo.objects.filter(id=2).update(age=999)
    models.UserInfo.objects.filter(name="张三").update(age=888)

    return HttpResponse("成功")

def user_list(request):
    data_list = models.UserInfo.objects.all()
    return render(request, "user_list.html", {"data_list": data_list})
def user_add(request):
    if request.method == "GET":
        return render(request, "user_add.html")
    else:
        # 获取用户数据
        username = request.POST.get("username")
        password = request.POST.get("password")
        age = request.POST.get("age")
        # 添加到数据库
        models.UserInfo.objects.create(name=username, password=password, age=age)

        return redirect("/user/list")
def user_delete(request):
    id = request.GET.get("id")
    models.UserInfo.objects.filter(id=id).delete()
    return HttpResponse("删除成功")
