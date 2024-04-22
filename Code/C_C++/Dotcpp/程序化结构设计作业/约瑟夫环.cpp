#include <iostream>
#include <iomanip>
using namespace std;
struct Jose
{
	int code;
	Jose *next;
};
int main()
{
	int numOfBoys, interval; //游戏的初值 
	cout << "Please input the number of boys,\n" << "interval counting:\n";
	cin >> numOfBoys >> interval;
	Jose *pJose = 0; //第一个小孩指针 
	Jose *pCurrent = 0; //当前小孩指针 
	Jose *pivot = 0; //前一个小孩指针 
	int itemsInLine = 1; //一行输出的项数 
	pJose = new Jose; //围成一个圈，先指定第一个小孩 
	pJose->code = 1;
	pJose->next = 0; //后面没有小孩 
	cout << setw(4) << pJose->code;
	pivot = pJose; 
	for (int i = 2;i <= numOfBoys;i++)
	{
		pCurrent = new Jose;
		pCurrent->code = i;
		pivot->next = pCurrent;
		pivot = pCurrent;
		if (itemsInLine++ % 10 == 0)
		{
			cout << endl;
		}
		cout << setw(4) << i;
	}
	pCurrent->next = pJose;
	itemsInLine = 0;
	pCurrent = pJose;
	while (pCurrent->next != pCurrent)
	{
		for (int j = 0;j < interval;j++)
		{
			pivot = pCurrent;
			pCurrent = pivot->next;
		}
		if (itemsInLine++ % 10 == 0)
		{
			cout << endl;
		}
		cout << setw(4) << pCurrent->code;
		pivot->next = pCurrent->next;
		delete pCurrent;
		pCurrent = pivot;
	}
	cout << "\n\nthe winner is " << pCurrent->code << endl;
	delete pCurrent;
	return 0;
}

