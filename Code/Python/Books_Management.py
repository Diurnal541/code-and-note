# coding=gb2312
MAX_BOOKS = 100
books = [{'name': '', 'author': '', 'publicationDate': ''}
         for _ in range(MAX_BOOKS)]  # _表示占位符
numBooks = 0


def menu():
    print("**********欢迎使用图书管理系统**********")
    print("请输入您的选择:")
    print("1.添加图书")
    print("2.查找图书")
    print("3.删除图书")
    print("4.列举图书")
    print("5.退出系统")


def add_books():
    global numBooks
    if numBooks >= MAX_BOOKS:
        print("图书已满,无法再添加图书")
        return
    books[numBooks]['name'] = input("请输入该书的名称:\n")
    books[numBooks]['author'] = input("请输入该书的作者:\n")
    books[numBooks]['publicationDate'] = input("请输入该书的出版日期:\n")
    numBooks += 1
    print("您已成功添加该书")


def search_books():
    name = input("请输入您想要查找的图书的名字:")
    found = False
    for i in range(numBooks):
        if books[i]['name'] == name:
            print(f"您查找的图书为 {books[i]['name']} {
                  books[i]['author']} {books[i]['publicationDate']}")
            found = True
    if not found:
        print("查无此书")


def delete_books():
    name = input("请输入您想要删除的图书的名字:")
    global numBooks
    for i in range(numBooks):
        if books[i]['name'] == name:
            books[i] = books[numBooks - 1]
            books[numBooks - 1] = {'name': '',
                                   'author': '', 'publicationDate': ''}
            numBooks -= 1
            print("您已成功删除该图书")
            return
    print("查无此书")


def list_books():
    print("以下为本系统所有图书:")
    for i in range(numBooks):
        print(books[i]['name'], books[i]['author'],
              books[i]['publicationDate'])


if __name__ == "__main__":
    while True:
        menu()
        choice = int(input())
        if choice == 1:
            add_books()
        elif choice == 2:
            search_books()
        elif choice == 3:
            delete_books()
        elif choice == 4:
            list_books()
        elif choice == 5:
            print("退出系统，欢迎下次使用")
            break
        else:
            print("无效的输入，请再次输入")
