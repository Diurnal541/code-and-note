#include <iostream>
#include <malloc.h>
using namespace std;
typedef struct student
{
	int id;
	int score;
	student *next;	
}*node,Node;
node creat(int);
void print(node);
void order(node,node);
int main()
{
	int m,n;
	cin >> n >> m;
	node h1 = creat(n);
	node h2 = creat(m);
	order(h1,h2);
	print(h1);
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
		cin >> (*p).id >> (*p).score;
		p->next = NULL;
		q->next = p;
		q = p;
	}
	return h;
}
void print(node h)
{
	node cur = h->next;
	while (cur != NULL)
	{
		cout << (*cur).id << " " <<(*cur).score << endl;
		cur = cur->next;
	}
}
void order(node h1, node h2)
{
	node q = h1;
	while (q->next != NULL)
	{
		q = q->next;
	}
	q->next = h2->next; //头节点为NULL，所以要跳过头节点 
	node p = h1->next;
	while (p != NULL)
	{
		node min = p;
		node temp = p->next;
		while (temp != NULL)
		{
			if (temp->id < min->id)
			{
				min = temp;
			}
			temp = temp->next;
		}
		int id_temp = p->id;
		int score_temp = p->score;
		p->id = min->id;
		p->score = min->score;
		min->id = id_temp;
		min->score = score_temp;
		p = p->next;
	}
}

