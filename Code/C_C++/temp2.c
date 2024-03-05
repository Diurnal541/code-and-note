#include <stdio.h>
#include <string.h>
#define MAXSIZE 11
typedef struct StaticLinkList
{
    char date[8];
    int next;
} SLL;
SLL list[MAXSIZE];
int sky = 0;
int head = 1;
int last = 1;
int len = 0;
void delete_(int x);
void insert_(int x, char *);
void search_(char *);
void show_();
void ini_();
int main(void)
{
    ini_();
    char order[8] = "\0";
    char str[MAXSIZE] = "\0";
    int x = 0;
    while (1)
    {
        if (scanf("%s", &order) == EOF)
            break;
        if (!(strcmp(order, "show")))
        {
            show_();
            printf("********************\n");
        }
        else if (!(strcmp(order, "search")))
        {
            scanf("%s", &str);
            search_(str);
            printf("********************\n");
        }
        else if (!(strcmp(order, "insert")))
        {
            scanf("%d%s", &x, &str);
            if (1 <= x && x <= (MAXSIZE - 2))
            {
                insert_(x, str);
            }
        }
        else if (!(strcmp(order, "delete")))
        {
            scanf("%d", &x);
            if (1 <= x && x <= len)
            {
                delete_(x);
            }
        }
    }
    return 0;
}
void ini_()
{
    SLL *p = list;
    int i = 0;
    for (i = 0; i < MAXSIZE; ++i)
    {
        p[i].next = (i + 1) % MAXSIZE;
    }
    p[0].next = 2;
    p[1].next = 0;
}
void show_()
{
    SLL *p = list;
    int i = 0;
    for (i = 0; i < MAXSIZE; ++i)
    {
        printf("%-8s%2d\n", p[i].date, p[i].next);
    }
}
void search_(char *str)
{
    int ptr = list[head].next;
    while ((ptr != 0) && (strcmp(list[ptr].date, str) != 0))
    {
        ptr = list[ptr].next;
    }
    printf("%2d\n", ptr);
}
void insert_(int x, char *str)
{
    int p = 0;
    p = list[sky].next;
    if (list[head].next != 0 && 1 == x)
    {
        list[sky].next = list[p].next;
        list[p].next = list[head].next;
        list[head].next = p;
    }
    else if (1 < x && x <= len)
    {
        list[sky].next = last;
        int i = 0;
        int q = 0;
        list[sky].next = list[p].next;
        q = list[head].next;
        for (i = 1; i < x - 1; ++i)
        {
            q = list[q].next;
        }
        list[p].next = list[q].next;
        list[q].next = p;
    }
    else if (len < x)
    {
        list[last].next = list[sky].next;
        last = list[sky].next;
        list[sky].next = list[p].next;
        list[p].next = sky;
    }
    ++len;
    strcpy(list[p].date, str);
}
void delete_(int x)
{
    if (1 == x)
    {
        int p = 0, q = 0;
        p = list[sky].next;
        q = list[head].next;
        list[sky].next = list[head].next;
        list[head].next = list[list[head].next].next;
        list[q].next = p;
    }
    else
    {
        int i = 0;
        int p = 0, q = 0;
        q = list[head].next;
        for (i = 1; i < x - 1; ++i)
        {
            q = list[q].next;
        }
        p = list[q].next;
        list[q].next = list[p].next;
        list[p].next = list[sky].next;
        list[sky].next = p;
    }
    --len;
}
