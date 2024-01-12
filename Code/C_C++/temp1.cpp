#include <iostream>
#include <malloc.h>
using namespace std;
typedef struct AAAAA
{
	int num;
	AAAAA *next;
} *node, Node;
node creat(int);
void print(node);
int main()
{
	int n;
	cin >> n;
	node h = creat(n);
	print(h);
	return 0;
}
node creat(int n)
{
	node h = (node)malloc(sizeof(Node));
	h->next = NULL;
	node q = h;
	node p;
	for (int i = 0; i < n; i++)
	{
		p = (node)malloc(sizeof(Node));
		cin >> (*p).num;
		p->next = q;
		q = p;
	}
	return h;
}
void print(node h)
{
	node q = h->next;
	while (q != NULL)
	{
		cout << (*q).num;
		q = q->next;
	}
}
