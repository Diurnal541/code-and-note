#include "linklist.c"
int count(LinkNode *head, float sg_fm, float sg_m); /*统计head为头指针的学生链表中身高达标人数并返回*/
void insertX(LinkNode *head, datatype x);           /*在学号从小到大排序的学生链表中插入值为x的学生仍保持学号的有序性*/
int delList(LinkNode *head, float sg);              /*删除head为头指针的学生链表中身高低于指定身高的所有学生结点，删除成功返回1，否则返回0*/

void main()
{
    LinkNode *head;
    int c, flag;
    float sg, sg_fm, sg_m;
    datatype x;
    /*建立与源数据文件同序的学生链表并输出；*/
    head = initList();  /*建空链表*/
    createList_2(head); /*调用建链表函数建立所需链表*/
    printf("\n与数据文件同序的学生链表：\n");
    pntList(head); /*调用函数打印输出链表中信息*/
    getchar();
    /*统计学生链表中身高达标人数（男女生的身高达标值由键盘输入）并打印结果；*/
    printf("\n输入达标的女生、男生身高值：");
    scanf("%f%f", &sg_fm, &sg_m);
    c = count(head, sg_fm, sg_m);
    printf("\n达标学生人数为：%d", c);
    getchar();

    /*对学生链表按学号进行排序*/
    sort_xh(head);

    /*在学生链表中插入指定的学生元素后使链表仍按学号有序*/
    x.xh = 3;
    x.sg = 1.67;
    x.sex = 0;
    insertX(head, x);
    printf("\n new list after insert:\n");
    pntList(head);
    getchar();

    /*对学生链表进行倒置，结果输出到文件result.txt中；*/
    reverse(head);
    save(head, "result.txt");
    getchar();

    /*删除链表中身高低于指定值的所有学生结点;*/
    sg = 1.67;
    flag = delList(head, sg);
    if (flag)
        printf("\ndelete succeed!\n");
    else
        printf("\ndelete failed\n");
    printf("\n new list after delete:\n");
    pntList(head);
    getchar();
}

// 统计学生链表中身高达标人数并返回(sg_fm女生身高达标值、sg_m男生身高达标值)
int count(LinkNode *head, float sg_fm, float sg_m)
{
    int n = 0;
    LinkNode *p;
    p = head->next;
    while (p != NULL)
    {
        if (p->data.sex == 0 && p->data.sg >= sg_fm)
        {
            n++;
        }
        if (p->data.sex == 1 && p->data.sg >= sg_m)
        {
            n++;
        }
        p = p->next;
    }
    return n;
}

// 删除学生链表中身高低于指定身高(存于sg中)的所有学生结点，删除成功返回1，否则返回0
int delList(LinkNode *head, float sg)
{
    LinkNode *p, *q;
    int flag = 0;
    q = head;
    p = head->next;
    while (p)
    {
        if (p->data.sg <= sg)
        {
            q->next = p->next;
            free(p);
            p = q->next;
            flag = 1;
        }
        else
        {
            q = p;
            p = p->next;
        }
    }

    return flag; /*删除成功返回1,否则返回0*/
}

// 在学号从小到大排序的学生链表中插入值为x的学生仍保持学号的有序性
void insertX(LinkNode *head, datatype x)
{
    LinkNode *q, *p, *s;
    s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    q = head;
    p = head->next;
    while (p != NULL)
    {
        if (s->data.xh > p->data.xh)
        {
            q = p;
            p = p->next;
        }
        else
        {
            s->next = p;
            q->next = s;
            break;
        }
    }
}
