# coding=gb2312
MAX_BOOKS = 100
books = [{'name': '', 'author': '', 'publicationDate': ''}
         for _ in range(MAX_BOOKS)]  # _��ʾռλ��
numBooks = 0


def menu():
    print("**********��ӭʹ��ͼ�����ϵͳ**********")
    print("����������ѡ��:")
    print("1.���ͼ��")
    print("2.����ͼ��")
    print("3.ɾ��ͼ��")
    print("4.�о�ͼ��")
    print("5.�˳�ϵͳ")


def add_books():
    global numBooks
    if numBooks >= MAX_BOOKS:
        print("ͼ������,�޷������ͼ��")
        return
    books[numBooks]['name'] = input("��������������:\n")
    books[numBooks]['author'] = input("��������������:\n")
    books[numBooks]['publicationDate'] = input("���������ĳ�������:\n")
    numBooks += 1
    print("���ѳɹ���Ӹ���")


def search_books():
    name = input("����������Ҫ���ҵ�ͼ�������:")
    found = False
    for i in range(numBooks):
        if books[i]['name'] == name:
            print(f"�����ҵ�ͼ��Ϊ {books[i]['name']} {
                  books[i]['author']} {books[i]['publicationDate']}")
            found = True
    if not found:
        print("���޴���")


def delete_books():
    name = input("����������Ҫɾ����ͼ�������:")
    global numBooks
    for i in range(numBooks):
        if books[i]['name'] == name:
            books[i] = books[numBooks - 1]
            books[numBooks - 1] = {'name': '',
                                   'author': '', 'publicationDate': ''}
            numBooks -= 1
            print("���ѳɹ�ɾ����ͼ��")
            return
    print("���޴���")


def list_books():
    print("����Ϊ��ϵͳ����ͼ��:")
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
            print("�˳�ϵͳ����ӭ�´�ʹ��")
            break
        else:
            print("��Ч�����룬���ٴ�����")
