#include <bits/stdc++.h>
using namespace std;
int main() {
    int i, a[10] = {0}, min, min_i = 0;
    cin >> a[0];     // 把第一个数置为最值
    min = abs(a[0]); // 调用系统绝对值函数
    for (i = 1; i < 10; i++) {
        cin >> a[i];
        if (abs(a[i]) < min) {
            min = a[i]; // 找最小值
            min_i = i;  // 找最小值得位置
        }
    }
    swap(a[min_i], a[9]); // 交换值
    for (i = 0; i < 10; i++){
        cout << a[i] << " ";
    }
    return 0;
}
