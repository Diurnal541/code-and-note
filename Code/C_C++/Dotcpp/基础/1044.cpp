#include <iostream>
#include <string>
using namespace std;
int Sum(string str) {
    int sum = 0;
    for (int i = 0; i < str.length(); i++) {
        sum += int(str[i]);
    }
    return sum;
}
string find_max(string a, string b) {
    int sumA = Sum(a);
    int sumB = Sum(b);
    if (sumA > sumB) {
        return a;
    } else {
        return b;
    }
}
int main() {
    string a, b, c;
    cin >> a >> b >> c;
    string maxStr = find_max(a, find_max(b, c));
    if (maxStr == a) {
        if (find_max(b, c) == b) {
            cout << c << endl << b << endl << a << endl;
        } else {
            cout << b << endl << c << endl << a << endl;
        }
    } else if (maxStr == b) {
        if (find_max(a, c) == a) {
            cout << c << endl << a << endl << b << endl;
        } else {
            cout << a << endl << c << endl << b << endl;
        }
    } else {
        if (find_max(a, b) == a) {
            cout << b << endl << a << endl << c << endl;
        } else {
            cout << a << endl << b << endl << c << endl;
        }
    }
    return 0;
}
