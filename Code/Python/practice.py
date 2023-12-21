#coding=gb2312
def register():
    print("""1-----管理员登录
2-----读者登录""")
    choice = input("请选择:")
    while 1:
        if choice == "1":
            name = input("请输入账号：")
            password = input("请输入密码：")
            if name == "2917396028" and password == "t13699136150":
                print("欢迎登录")
                manager.Menu1()
                break
            else:
                print("账号或密码错误，请重新输入")
        elif choice == "2":
            name = input("请输入账号：")
            password = input("请输入密码：")
            if name == "3595436547" and password == "t13699136150":
                print("欢迎登录")
                manager.Menu2()
                break
            else:
                print("账号或密码错误，请重新输入")
        else:
            print("请输入正确选择")
            register()

class Book:
    def __init__(self,name,author,status,book_index):
        self.name = name
        self.author = author
        self.status = status
        self.book_index = book_index

    def __str__(self):
        if self.status == 1:
            stats = "未借出"
        elif self.status == 0:
            stats = "已借出"
        else:
            stats = "状态异常"
        return f"书名:《{self.name}》,作者:{self.author},状态:<{self.status}>,位置:{self.book_index}"

class Bookmanage():
    books = []
    def start(self):
        self.books.append(Book("平凡的世界", "路遥", 1, "198014765100001"))
        self.books.append(Book("白夜行", "东野圭吾", 1, "1981014764100001"))
        self.books.append(Book("解忧杂货铺", "东野圭吾", 1, "1981014763100001"))
        # 1.打开文件

    def Menu1(self):
        self.start()
        while 1:
            print("""1-----查询图书
2-----增加图书
3-----借阅图书
4-----归还图书
5-----退出系统""")
            choice = input("请选择：")

            if choice == "1":
                self.show_all_book()
            elif choice == "2":
                self.add_book()
            elif choice == "3":
                self.borrow_Book()
            elif choice == "4":
                self.return_book()
            elif choice == "5":
                print("欢迎下次使用")
                break
            else:
                print("请输入正确选项")

    def Menu2(self):
        self.start()
        while 1:
            print("""1-----查询图书
2-----借阅图书
3-----归还图书
4-----退出系统""")
            choice = input("请选择：")
            if choice == "1":
                self.show_all_book()
            elif choice == "2":
                self.borrow_Book()
            elif choice == "3":
                self.return_book()
            elif choice == "4":
                print("欢迎下次使用")
                break
            else:
                print("请输入正确选项")

    def show_all_book(self):
        for book in self.books:
            print(book)

    def add_book(self):
        name = input("图书名:")
        author = input("作者:")
        book_index = input("编号:")
        self.books.append(Book(name, author, 1, book_index))
        print(f"图书《{name}》增加成功")

    def borrow_Book(self):
        name = input("图书名：")
        for book in self.books:
            if book.name == name:
                ret = book
                if ret.status == 0:
                    print(f"书籍《{name}》已借出")
                    break
                else:
                    ret.status = 0
                    print(f"书籍《{name}》借阅成功")
                    break
        else:
            print(f"书籍《{name}》不存在")

    def return_book(self):
        name = input("图书名：")
        for book in self.books:
            ret = book
            if ret.name == name:
                if ret.status == 0:
                    ret.status = 1
                    print(f"书籍《{name}》已归还")
                    break
                else:
                    print(f"书籍《{name}》未借出")
                    break
        else:
            print(f"书籍《{name}》不存在")


print("----------欢迎进入图书管理系统----------")
manager = Bookmanage()
register()
