#include <stdio.h>
#include <string.h>
#define MAXSIZE 11
typedef char ElemType[8];
typedef struct
{
    ElemType data;
    int cur;
} NodeType;
NodeType space[MAXSIZE];
typedef struct
{
    int elem;
    int length;
    int listSize;
} SLinkList;
int LocateElem_SL(SLinkList &S, ElemType e)
{
    int i;
    i = S.elem;
    while (i && strcmp(space[i].data, e))
        i = space[i].cur;
    return i;
}
void InitSpace_SL()
{
    memset(space, 0, sizeof(space));
    for (int i = 0; i < MAXSIZE - 1; ++i)
        space[i].cur = i + 1;
    space[MAXSIZE - 1].cur = 0;
}
int Malloc_SL()
{
    int i = space[0].cur;
    if (i)
        space[0].cur = space[i].cur;
    return i;
}
void Free_SL(int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}
void Insert_SL(SLinkList &S, int i, ElemType e)
{
    int cur = S.elem;
    int j = 0;
    int newNodeIndex;
    while (j < i - 1)
    {
        cur = space[cur].cur;
        ++j;
    }
    newNodeIndex = Malloc_SL();
    strcpy(space[newNodeIndex].data, e);
    space[newNodeIndex].cur = 0;
    space[newNodeIndex].cur = space[cur].cur;
    space[cur].cur = newNodeIndex;
    S.length++;
}
void Delete_SL(SLinkList &S, int i)
{
    int cur = S.elem;
    int j = 0;
    int delCur;
    while (j < i - 1)
    {
        cur = space[cur].cur;
        ++j;
    }
    delCur = space[cur].cur;
    space[cur].cur = space[delCur].cur;
    Free_SL(delCur);
    S.length--;
}
void CreateList_SL(SLinkList &S)
{
    S.elem = Malloc_SL();
    space[S.elem].cur = 0;
    S.length = 0;
    S.listSize = 9;
}
void Show_space()
{
    int i;
    for (i = 0; i < MAXSIZE; i++)
    {
        printf("%-8s%2d\n", space[i].data, space[i].cur);
    }
}
int main()
{
    SLinkList S;
    char str[10];
    int a;
    ElemType e;
    InitSpace_SL();
    CreateList_SL(S);
    while (scanf("%s", str) != EOF)
    {
        if (strcmp(str, "insert") == 0)
        {
            scanf("%d%s", &a, e);
            Insert_SL(S, a, e);
        }
        else if (strcmp(str, "delete") == 0)
        {
            scanf("%d", &a);
            Delete_SL(S, a);
        }
        else if (strcmp(str, "search") == 0)
        {
            scanf("%s", e);
            printf("%2d\n********************\n", LocateElem_SL(S, e));
        }
        else if (strcmp(str, "show") == 0)
        {
            Show_space();
            puts("********************");
        }
    }
    return 0;
}
