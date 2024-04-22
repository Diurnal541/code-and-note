#include <iostream>
using namespace std;
#include <cstdio>
int main() {
    float s = 0, t = 1;
    for (int i = 1; i <= 30; i++) {
        t *= i;
        s += t;
    }
    printf("%.2e", s); // 输出科学计数法
    return 0;
}
