//dps深度搜索法，题解 
/*
#include<bits/stdc++.h>
using namespace std;
int g[5],a[5],m = 3,flag;
bool s[5];
void dfs(int t){
    if(t>m){
        for(int i=1;i<=m;i++)
            cout<<g[i]<<" ";
        cout << endl;
        //puts("");
        return;
    }
    for(int i=1;i<=m;i++)
        if(!s[i]){
            s[i]=true;
            if(i == flag)
                g[t]=a[m+1];             
            else
                g[t]=a[i]; 
            dfs(t+1);
            s[i]=false;
            // g[t]=0;
        }
}
int main(){
    for(int i=1;i<=4;i++)
        cin>>a[i];   
    for(flag=1;flag<=4;flag++) //flag代表排除这个数，比如说flag=1时，dps将不会输出带有1的组合，与第十五行呼应 
        dfs(1);
    return 0;
}
*/
//暴力法
/*
#include <iostream>
using namespace std;
int main()
{
	int a[4];
	for (int i = 0;i < 4;i++)
	{
		cin >> a[i];
	}
	for (int i = 3;i >= 0;i--)
	{
		for (int j = 0;j < 4;j++)
		{
			if (j != i)
			{
				for (int k = 0;k < 4;k++)
				{
					if (k != i && k != j)
					{
						cout << a[j] << " " << a[k] << " " << a[6 - i - j - k] << endl;
					}
				}
			}
		}
	}
	return 0;
}
*/
//dps深度搜索法，自己写的
#include <iostream>
using namespace std;
bool vis[10];
int a[4],b[3],flag;
void dps(int n)
{
	if (n == 3)
	{
		for (int i = 0;i < 3;i++)
		{
			cout << b[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 0;i < 3;i++)
	{
		if (!vis[i])
		{
			vis[i] = true;
			if (i == flag)
			{
				b[n] = a[3];
			}
			else
			{
				b[n] = a[i];
			}
			dps(n + 1);
			vis[i] = false;
		}
	}
}
int main()
{
	for (int i = 0;i < 4;i++)
	{
		cin >> a[i];
	}
	for (flag = 0;flag < 4;flag++)
	{
		dps(0);
	}
	return 0;
}
/*
//AI答案
#include <iostream>
#include <algorithm>
using namespace std;
void printPermutations(int arr[], int n) {
    do {
        for (int i = 0; i < n - 1; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } while (next_permutation(arr, arr + n));
}

int main() {
    int arr[4];
	for (int i = 0;i < 4;i++)
	{
		cin >> arr[i];
	} 
    int n = sizeof(arr) / sizeof(arr[0]);
    printPermutations(arr, n);
    return 0;
}
*/
