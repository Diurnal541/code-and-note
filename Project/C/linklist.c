#include <stdio.h>
#include <stdlib.h>
/*单链表结点类型*/
typedef struct
{
    int xh;	  /*学号*/
    float sg; /*身高*/
    int sex;  /*性别，0为男生，1为女生*/
} datatype;
typedef struct node
{
    datatype data;	   /*数据域*/
    struct node *next; /*指针域*/
} LinkNode;
/*带表头的单链表的基本运算函数*/
LinkNode *initList();					   /*置一个空表（带头结点）*/
void createList_1(LinkNode *head);		   /*创建单链表*/
void createList_2(LinkNode *head);		   /*创建单链表*/
void sort_xh(LinkNode *head);			   /*单链表排序*/
void reverse(LinkNode *head);			   /*单链表倒置*/
void pntList(LinkNode *head);			   /*打印单链表*/
void save(LinkNode *head, char strname[]); /*保存单链表到文件*/

/*置一个空表*/
LinkNode *initList()
{
    LinkNode *p;
    p = (LinkNode *)malloc(sizeof(LinkNode));
    p->next = NULL;
    return p;
}

/*创建单链表方法1*/
void createList_1(LinkNode *head)
{
    FILE *fp;
    datatype stu;
    LinkNode *p;
    if ((fp = fopen("../records.txt", "r")) == NULL)
    {
        printf("can not open read file !");
        exit(1);
    }
    while (!feof(fp))
    {
        fscanf(fp, "%d%f%d", &stu.xh, &stu.sg, &stu.sex);
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = stu;
        p->next = head->next;
        head->next = p;
    }
    fclose(fp);
}

/*创建单链表方法2*/
void createList_2(LinkNode *head)
{
    FILE *fp;
    datatype stu;
    LinkNode *p, *rear;
    if ((fp = fopen("../records.txt", "r")) == NULL)
    {
        printf("can not open read file !");
        exit(1);
    }
    rear = head;
    while (!feof(fp))
    {
        fscanf(fp, "%d%f%d", &stu.xh, &stu.sg, &stu.sex);
        p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = stu;
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    fclose(fp);
}

/*单链表排序*/
void sort_xh(LinkNode *head)
{
    LinkNode *q, *p, *u;
    p = head->next;
    head->next = NULL; /*利用原表头结点建新的空表*/
    while (p)
    {
        q = p;		 /*q为被插入的结点*/
        p = p->next; /*用p记录后继结点*/
        /*遍历新链表查找插入位置*/
        u = head;
        while (u->next != NULL) /*查找插入位置*/
        {
            if (u->next->data.xh > q->data.xh)
                break;
            u = u->next;
        }
        /*插入在u结点的后面*/
        q->next = u->next;
        u->next = q;
    }
}

/*单链表倒置*/
void reverse(LinkNode *head)
{
    LinkNode *p, *r;
    p = head->next;
    head->next = NULL;
    while (p)
    {
        r = p;
        p = p->next;
        /*r指向结点头插到链表*/
        r->next = head->next;
        head->next = r;
    }
}

/*输出单链表*/
void pntList(LinkNode *head)
{
    LinkNode *p;
    p = head->next;
    while (p != NULL)
    {
        printf("%2d: %.2f %d\n", p->data.xh, p->data.sg, p->data.sex);
        p = p->next;
    }
}

/*保存单链表到文件*/
void save(LinkNode *head, char strname[])
{
    FILE *fp;
    LinkNode *p;
    if ((fp = fopen(strname, "w")) == NULL)
    {
        printf("can not open write file !");
        exit(1);
    }
    p = head->next;
    while (p != NULL)
    {
        fprintf(fp, "%2d %5.2f %2d\n", p->data.xh, p->data.sg, p->data.sex);
        p = p->next;
    }
    fclose(fp);
}
