#include <iostream>
using namespace std;
void strTrans(char*,char*);
int main() 
{
	char s[20]="1ABCZabcz",d[20];
	strTrans(s,d);
	cout << d << endl;
    return 0;
}
void strTrans(char *src,char *dst)
{
	char *p1 = src;
	char *p2 = dst;
	while (*p1)
	{
		if (!isalpha(*p1))
		{
			*p2 = *p1;
		}
		else
		{
			if (*p1 == 'Z')
			{
				*p2 = 'A';
			}
			else if (*p1 == 'z')
			{
				*p2 = 'a';
			}
			else
			{
				*p2 = *p1 + 1;
			}
		}
		p1++;
		p2++;
	}
	*p2 = '\0';
}

