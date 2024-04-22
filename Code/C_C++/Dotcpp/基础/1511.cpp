#include <iostream>
#include <malloc.h>
using namespace std;
typedef struct complex
{
	int shi;
	int xu;
	complex *next;
}*node,Node;
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
	for (int i = 0;i < n;i++)
	{
		p = (node)malloc(sizeof(Node));
		cin >> (*p).shi >> (*p).xu;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	return h;
}
void print(node h)
{
	int s1 = 0,s2 = 0;
	node q = h->next;
	while (q != NULL)
	{
		s1 += (*q).shi;
		s2 += (*q).xu;
		q = q->next;
	} 
	cout << s1 << "+" << s2 << "i" << endl;
}

