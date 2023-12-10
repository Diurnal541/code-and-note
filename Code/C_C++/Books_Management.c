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
    printf("**********欢迎使用图书管理系统**********\n");
    printf("请输入您的选择:\n");
    printf("1.添加图书\n");
    printf("2.查找图书\n");
    printf("3.删除图书\n");
    printf("4.列举图书\n");
    printf("5.退出系统\n");
}

void addbooks()
{
    if (numBooks >= MAX_BOOKS)
    {
        printf("图书已满,无法再添加图书");
        return;
    }
    printf("请输入该书的名称:\n");
    scanf("%s", books[numBooks].name);
    printf("请输入该书的作者:\n");
    scanf("%s", books[numBooks].author);
    printf("请输入该书的出版日期:\n");
    scanf("%s", books[numBooks].publicationDate);
    numBooks++;
    printf("您已成功添加该书\n");
}
void searchbooks()
{
    char name[100];
    printf("请输入您想要查找的图书的名字:");
    scanf("%s", name);
    for (int i = 0; i < numBooks;i++)
    {
        if (strcmp(books[i].name,name) == 0)
        {
            printf("您查找的图书为%s %s %s\n", books[i].name, books[i].author, books[i].publicationDate);
        }
        else
        {
            printf("查无此书\n");
        }
    }
}
void deletebooks()
{
    char name[100];
    printf("请输入您想要删除的图书的名字:");
    scanf("%s", name);
    for (int i = 0; i < numBooks;i++)
    {
        if (strcmp(books[i].name,name) == 0)
        {
            books[i] = books[numBooks - 1];
            numBooks--;
            printf("您已成功删除该图书\n");
        }
        else
        {
            printf("查无此书\n");
        }
    }
}
void listbooks()
{
    printf("以下为本系统所有图书:\n");
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
            printf("退出系统，欢迎下次使用");
            return 0;
        }
        else 
        {
            printf("无效的输入，请再次输入\n");
        }
        sleep(3);
        system("cls");
    }
    return 0;
}
