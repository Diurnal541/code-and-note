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
	int numOfBoys, interval; //��Ϸ�ĳ�ֵ 
	cout << "Please input the number of boys,\n" << "interval counting:\n";
	cin >> numOfBoys >> interval;
	Jose *pJose = 0; //��һ��С��ָ�� 
	Jose *pCurrent = 0; //��ǰС��ָ�� 
	Jose *pivot = 0; //ǰһ��С��ָ�� 
	int itemsInLine = 1; //һ����������� 
	pJose = new Jose; //Χ��һ��Ȧ����ָ����һ��С�� 
	pJose->code = 1;
	pJose->next = 0; //����û��С�� 
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

