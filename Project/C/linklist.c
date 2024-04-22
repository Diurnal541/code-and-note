#include <stdio.h>
#include <stdlib.h>
/*������������*/
typedef struct
{
    int xh;	  /*ѧ��*/
    float sg; /*���*/
    int sex;  /*�Ա�0Ϊ������1ΪŮ��*/
} datatype;
typedef struct node
{
    datatype data;	   /*������*/
    struct node *next; /*ָ����*/
} LinkNode;
/*����ͷ�ĵ�����Ļ������㺯��*/
LinkNode *initList();					   /*��һ���ձ���ͷ��㣩*/
void createList_1(LinkNode *head);		   /*����������*/
void createList_2(LinkNode *head);		   /*����������*/
void sort_xh(LinkNode *head);			   /*����������*/
void reverse(LinkNode *head);			   /*��������*/
void pntList(LinkNode *head);			   /*��ӡ������*/
void save(LinkNode *head, char strname[]); /*���浥�����ļ�*/

/*��һ���ձ�*/
LinkNode *initList()
{
    LinkNode *p;
    p = (LinkNode *)malloc(sizeof(LinkNode));
    p->next = NULL;
    return p;
}

/*������������1*/
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

/*������������2*/
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

/*����������*/
void sort_xh(LinkNode *head)
{
    LinkNode *q, *p, *u;
    p = head->next;
    head->next = NULL; /*����ԭ��ͷ��㽨�µĿձ�*/
    while (p)
    {
        q = p;		 /*qΪ������Ľ��*/
        p = p->next; /*��p��¼��̽��*/
        /*������������Ҳ���λ��*/
        u = head;
        while (u->next != NULL) /*���Ҳ���λ��*/
        {
            if (u->next->data.xh > q->data.xh)
                break;
            u = u->next;
        }
        /*������u���ĺ���*/
        q->next = u->next;
        u->next = q;
    }
}

/*��������*/
void reverse(LinkNode *head)
{
    LinkNode *p, *r;
    p = head->next;
    head->next = NULL;
    while (p)
    {
        r = p;
        p = p->next;
        /*rָ����ͷ�嵽����*/
        r->next = head->next;
        head->next = r;
    }
}

/*���������*/
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

/*���浥�����ļ�*/
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
