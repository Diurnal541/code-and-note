#include <bits/stdc++.h>
using namespace std;
int main() {
    double x[21], y = 0;
    int z = 0;
    for (int i = 1; i <= 20; i++) {
        cin >> x[i];
        if (x[i] > 0)
            y += x[i];
        else if (x[i] < 0)
            z++;
    }
    cout << z << " ";
    y = y / (20 - z);
    printf("%.2lf", y);
    return 0;
}
