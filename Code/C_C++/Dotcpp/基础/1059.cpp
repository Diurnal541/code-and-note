#include <iostream>
using namespace std;
int main()
{
    int n, i, m = -1, j = 0;
    cin >> n;
    for (i = 0; i < n; i++) {
        m = m + 3;
        j = j + m;
    }
    cout << j << endl;
    return 0;
}
