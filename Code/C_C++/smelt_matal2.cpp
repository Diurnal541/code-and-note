#include <iostream>
using namespace std;
int N;
const int MAX_N = 1e4 + 1;
int A[MAX_N], B[MAX_N];
bool check_min(int V)
{
    for (int i = 0; i < N;i++)
    {
        if (A[i] / V > B[i])
        {
            return false;
        }
        return true;
    }
}
bool check_max(int V)
{
    for (int i = 0; i < N;i++)
    {
        if (A[i] / V < B[i])
        {
            return false;
        }
        return true;
    }
}
int main()
{
    cin >> N;
    for (int i = 0; i < N;i++)
    {
        cin >> A[i] >> B[i];
    }
    int L = 1, R = 1e9, V_min;
    while (L <= R)
    {
        int mid = L + R >> 1;
        if (check_min(mid))
        {
            V_min = mid;
            R = mid - 1;
        }
        else
        {
            L = mid + 1;
        }
    }
    L = 1, R = 1e9;
    int V_max;
    while (L <= R)
    {
        int mid = L + R >> 1;
        if (check_max(mid))
        {
            V_max = mid;
            L = mid + 1;
        }
        else
        {
            R = mid - 1;
        }
    }
    cout << V_min + 1 << " " << V_max;
    return 0;
}