#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_BOOKS 100
struct Book
{
    char name[100];
    char author[100];
    char publicationDate[100];
}books[MAX_BOOKS];

int numBooks = 0;
void menu()
{
    printf("**********��ӭʹ��ͼ�����ϵͳ**********\n");
    printf("����������ѡ��:\n");
    printf("1.���ͼ��\n");
    printf("2.����ͼ��\n");
    printf("3.ɾ��ͼ��\n");
    printf("4.�о�ͼ��\n");
    printf("5.�˳�ϵͳ\n");
}

void addbooks()
{
    if (numBooks >= MAX_BOOKS)
    {
        printf("ͼ������,�޷������ͼ��");
        return;
    }
    printf("��������������:\n");
    scanf("%s", books[numBooks].name);
    printf("��������������:\n");
    scanf("%s", books[numBooks].author);
    printf("���������ĳ�������:\n");
    scanf("%s", books[numBooks].publicationDate);
    numBooks++;
    printf("���ѳɹ���Ӹ���\n");
}
void searchbooks()
{
    char name[100];
    printf("����������Ҫ���ҵ�ͼ�������:");
    scanf("%s", name);
    for (int i = 0; i < numBooks;i++)
    {
        if (strcmp(books[i].name,name) == 0)
        {
            printf("�����ҵ�ͼ��Ϊ%s %s %s\n", books[i].name, books[i].author, books[i].publicationDate);
        }
        else
        {
            printf("���޴���\n");
        }
    }
}
void deletebooks()
{
    char name[100];
    printf("����������Ҫɾ����ͼ�������:");
    scanf("%s", name);
    for (int i = 0; i < numBooks;i++)
    {
        if (strcmp(books[i].name,name) == 0)
        {
            books[i] = books[numBooks - 1];
            numBooks--;
            printf("���ѳɹ�ɾ����ͼ��\n");
        }
        else
        {
            printf("���޴���\n");
        }
    }
}
void listbooks()
{
    printf("����Ϊ��ϵͳ����ͼ��:\n");
    for (int i = 0; i < numBooks;i++)
    {
        printf("%s %s %s\n", books[i].name, books[i].author, books[i].publicationDate);
    }
}
int main()
{
    int choice;
    while (1)
    {
        menu();
        scanf("%d", &choice);
        if (choice == 1)
        {
            addbooks();
        }
        else if (choice == 2)
        {
            searchbooks();
        }
        else if (choice == 3)
        {
            deletebooks();
        }
        else if (choice == 4)
        {
            listbooks();
        }
        else if (choice == 5) 
        {
            printf("�˳�ϵͳ����ӭ�´�ʹ��");
            return 0;
        }
        else 
        {
            printf("��Ч�����룬���ٴ�����\n");
        }
        sleep(3);
        system("cls");
    }
    return 0;
}
