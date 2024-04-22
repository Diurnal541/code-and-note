#include <iostream>
using namespace std;
#define LEAP_YEAR(y) ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) ? "L" : "N")
int main(){
    int y;
    cin >> y;
    cout << LEAP_YEAR(y) << endl;
    return 0;
}
