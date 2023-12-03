#include <bits/stdc++.h>
using namespace std;
void move(int n,int arr1[],int arr2[])
{
    int m;
    cin >> m;
    for (int i = 0; i < n - m;i++)
    {
        arr2[i + m] = arr1[i];
    }
    for (int i = 0; i < m;i++)
    {
        arr2[i] = arr1[n - m + i];
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, arr1[100], arr2[100];
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        cin >> arr1[i];
    }
    move(n, arr1, arr2);
    for (int i = 0; i < n;i++)
    {
        cout << arr2[i] << " ";
    }
    return 0;
}
