#include <iostream>
#include <cstring>
using namespace std;
struct student
{
	char name[100];
	int age;
	double score;
};
int main()
{
	int n;
	while (cin >> n)
	{
		student stu[n],t; 
		for (int i = 0;i < n;i++)
		{
			cin >> stu[i].name >> stu[i].age >> stu[i].score;
		}
	    for (int i = 0; i < n - 1; i++)
	    { 
	        for (int j = 0; j < n - 1 - i; j++)
	        {
	            if (stu[j].score > stu[j + 1].score)
	            {
	                t = stu[j];
	                stu[j] = stu[j + 1];
	                stu[j + 1] = t;
	            }
	            else if (stu[j].score == stu[j + 1].score)
	            {
	                if (strcmp(stu[j].name,stu[j + 1].name) > 0)
	                {
	                    t = stu[j];
	                    stu[j] = stu[j + 1];
	                    stu[j + 1] = t;
	                }
	                else if (strcmp(stu[j].name,stu[j+1].name) == 0)
	                {
	                    if (stu[j].age > stu[j + 1].age)
	                    {
	                        t = stu[j];
	                        stu[j] = stu[j + 1];
	                        stu[j + 1] = t;
	                    }
	                }
	            }
	        } 
		}
		for (int i = 0;i < n;i++)
		{
			cout << stu[i].name << " " << stu[i].age << " " << stu[i].score <<endl;
		}
	}
	return 0;
}

