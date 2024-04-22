#include "linklist.c"
int count(LinkNode *head, float sg_fm, float sg_m); /*ͳ��headΪͷָ���ѧ����������ߴ������������*/
void insertX(LinkNode *head, datatype x);           /*��ѧ�Ŵ�С���������ѧ�������в���ֵΪx��ѧ���Ա���ѧ�ŵ�������*/
int delList(LinkNode *head, float sg);              /*ɾ��headΪͷָ���ѧ����������ߵ���ָ����ߵ�����ѧ����㣬ɾ���ɹ�����1�����򷵻�0*/

void main()
{
    LinkNode *head;
    int c, flag;
    float sg, sg_fm, sg_m;
    datatype x;
    /*������Դ�����ļ�ͬ���ѧ�����������*/
    head = initList();  /*��������*/
    createList_2(head); /*���ý�������������������*/
    printf("\n�������ļ�ͬ���ѧ������\n");
    pntList(head); /*���ú�����ӡ�����������Ϣ*/
    getchar();
    /*ͳ��ѧ����������ߴ����������Ů������ߴ��ֵ�ɼ������룩����ӡ�����*/
    printf("\n�������Ů�����������ֵ��");
    scanf("%f%f", &sg_fm, &sg_m);
    c = count(head, sg_fm, sg_m);
    printf("\n���ѧ������Ϊ��%d", c);
    getchar();

    /*��ѧ������ѧ�Ž�������*/
    sort_xh(head);

    /*��ѧ�������в���ָ����ѧ��Ԫ�غ�ʹ�����԰�ѧ������*/
    x.xh = 3;
    x.sg = 1.67;
    x.sex = 0;
    insertX(head, x);
    printf("\n new list after insert:\n");
    pntList(head);
    getchar();

    /*��ѧ��������е��ã����������ļ�result.txt�У�*/
    reverse(head);
    save(head, "result.txt");
    getchar();

    /*ɾ����������ߵ���ָ��ֵ������ѧ�����;*/
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

// ͳ��ѧ����������ߴ������������(sg_fmŮ����ߴ��ֵ��sg_m������ߴ��ֵ)
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

// ɾ��ѧ����������ߵ���ָ�����(����sg��)������ѧ����㣬ɾ���ɹ�����1�����򷵻�0
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

    return flag; /*ɾ���ɹ�����1,���򷵻�0*/
}

// ��ѧ�Ŵ�С���������ѧ�������в���ֵΪx��ѧ���Ա���ѧ�ŵ�������
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
