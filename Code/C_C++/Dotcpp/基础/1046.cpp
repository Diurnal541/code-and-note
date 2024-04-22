#include <iostream>
#include <vector>
using namespace std;
void move(vector<int>& arr, int size) {
    for (int i = size - 1; i >= 0; i--) {
        arr[i + 1] = arr[i];
    }
}
void change(vector<int>& arr, int n, int m) {
    for (int i = 0; i < m; i++) {
        move(arr, n);
    }
    for (int i = m - 1; i >= 0; i--) {
        arr[i] = arr[n + i];
    }
}
int main() {
    int n, m;
    cin >> n;
    vector<int> arr(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> m;
    change(arr, n, m);
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
