#coding=gb2312
def register():
    print("""1-----����Ա��¼
2-----���ߵ�¼""")
    choice = input("��ѡ��:")
    while 1:
        if choice == "1":
            name = input("�������˺ţ�")
            password = input("���������룺")
            if name == "2917396028" and password == "t13699136150":
                print("��ӭ��¼")
                manager.Menu1()
                break
            else:
                print("�˺Ż������������������")
        elif choice == "2":
            name = input("�������˺ţ�")
            password = input("���������룺")
            if name == "3595436547" and password == "t13699136150":
                print("��ӭ��¼")
                manager.Menu2()
                break
            else:
                print("�˺Ż������������������")
        else:
            print("��������ȷѡ��")
            register()

class Book:
    def __init__(self,name,author,status,book_index):
        self.name = name
        self.author = author
        self.status = status
        self.book_index = book_index

    def __str__(self):
        if self.status == 1:
            stats = "δ���"
        elif self.status == 0:
            stats = "�ѽ��"
        else:
            stats = "״̬�쳣"
        return f"����:��{self.name}��,����:{self.author},״̬:<{self.status}>,λ��:{self.book_index}"

class Bookmanage():
    books = []
    def start(self):
        self.books.append(Book("ƽ��������", "·ң", 1, "198014765100001"))
        self.books.append(Book("��ҹ��", "��Ұ����", 1, "1981014764100001"))
        self.books.append(Book("�����ӻ���", "��Ұ����", 1, "1981014763100001"))
        # 1.���ļ�

    def Menu1(self):
        self.start()
        while 1:
            print("""1-----��ѯͼ��
2-----����ͼ��
3-----����ͼ��
4-----�黹ͼ��
5-----�˳�ϵͳ""")
            choice = input("��ѡ��")

            if choice == "1":
                self.show_all_book()
            elif choice == "2":
                self.add_book()
            elif choice == "3":
                self.borrow_Book()
            elif choice == "4":
                self.return_book()
            elif choice == "5":
                print("��ӭ�´�ʹ��")
                break
            else:
                print("��������ȷѡ��")

    def Menu2(self):
        self.start()
        while 1:
            print("""1-----��ѯͼ��
2-----����ͼ��
3-----�黹ͼ��
4-----�˳�ϵͳ""")
            choice = input("��ѡ��")
            if choice == "1":
                self.show_all_book()
            elif choice == "2":
                self.borrow_Book()
            elif choice == "3":
                self.return_book()
            elif choice == "4":
                print("��ӭ�´�ʹ��")
                break
            else:
                print("��������ȷѡ��")

    def show_all_book(self):
        for book in self.books:
            print(book)

    def add_book(self):
        name = input("ͼ����:")
        author = input("����:")
        book_index = input("���:")
        self.books.append(Book(name, author, 1, book_index))
        print(f"ͼ�顶{name}�����ӳɹ�")

    def borrow_Book(self):
        name = input("ͼ������")
        for book in self.books:
            if book.name == name:
                ret = book
                if ret.status == 0:
                    print(f"�鼮��{name}���ѽ��")
                    break
                else:
                    ret.status = 0
                    print(f"�鼮��{name}�����ĳɹ�")
                    break
        else:
            print(f"�鼮��{name}��������")

    def return_book(self):
        name = input("ͼ������")
        for book in self.books:
            ret = book
            if ret.name == name:
                if ret.status == 0:
                    ret.status = 1
                    print(f"�鼮��{name}���ѹ黹")
                    break
                else:
                    print(f"�鼮��{name}��δ���")
                    break
        else:
            print(f"�鼮��{name}��������")


print("----------��ӭ����ͼ�����ϵͳ----------")
manager = Bookmanage()
register()
