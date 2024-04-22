#include <iostream>
#include <cstdlib>
using namespace std;
typedef struct HZ
{
	int num;
	HZ *next;
}*node,Node;
node creat(int);
void show(node);
node del(node,int);
void get(node,int);
node insert(node,int,int);
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,N,a,e;
	cin >> n;
	node h = creat(n);
	cin >> N;
    for (int i = 0; i < N; i++)
	{
        string ch;
        cin >> ch;
        if (ch == "show") 
		{
           	show(h);
        } 
		else if (ch == "delete") 
		{
           	cin >> a;
           	h = del(h, a);
        } 
		else if (ch == "insert") 
		{
           	cin >> a >> e;
           	h = insert(h, a, e);
        } 
		else if (ch == "get") 
		{
           	cin >> a;
           	get(h, a);
        } 
		else 
		{
           	cout << "WRONG" << endl;
    	}
	}
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
		cin >> p->num;
		p->next = q->next;
		q->next = p;
	}
	return h;
}
void show(node h)
{
	if (h->next == NULL)
	{
		cout << "Link list is empty" << endl;
		return;
	}
	node q = h->next;
	while (q != NULL)
	{
		cout << q->num << " ";
		q = q->next;
	}
	cout << endl;
}
node del(node h, int a) 
{
    node q = h;
    for (int i = 0; i < a - 1; i++) 
	{
        q = q->next;
        if (q == NULL) 
		{
            cout << "delete fail" << endl;
            return h;
        }
    }
    if (q->next == NULL) 
	{
        cout << "delete fail" << endl;
    } 
	else 
	{
        node p = q->next;
        q->next = p->next;
        free(p);
        cout << "delete OK" << endl;
    }
    return h;
}
void get(node h,int a)
{
	node q = h;
	for (int i = 0;i < a;i++)
	{
		q = q->next;
	}
	if (q->next == NULL)
	{
		cout << "get fail" << endl;
	}
	else
	{
		cout << q->num;
	}
}
node insert(node h,int a,int e)
{
	node q = h;
	for (int i = 0;i < a - 1;i++)
	{
		q = q->next;
		if (q == NULL)
		{
			cout << "insert fail" << endl;
			return h;
		}
	}
	node p = (node)malloc(sizeof(Node));
	p->num = e;
	p->next = q->next;
	q->next = p;
	cout << "insert OK" << endl;
	return h;
}

