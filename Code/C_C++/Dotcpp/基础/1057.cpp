#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    float x;
    cin >> x;
    if (x < 1) {
        cout << fixed << setprecision(2) << x << endl;
    }
    else if (x >= 1 && x < 10) {
        cout << fixed << setprecision(2) << 2 * x - 1 << endl;
    }
    else {
        cout << fixed << setprecision(2) << 3 * x - 11 << endl;
    }
    return 0;
}
