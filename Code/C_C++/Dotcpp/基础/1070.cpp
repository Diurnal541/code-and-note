#include <iostream>
using namespace std;
int main()
{
    int a = 0, b = 0, c = 0, n;
    do
    {
        cin >> n;
        if (n >= 85){
            a++;
        }
        else if (n >= 60){
            b++;
        }
        else if (n > 0){
            c++;
        }
    } while (n > 0);
    cout << ">=85:" << a << endl
         << "60-84:" << b << endl
         << "<60:" << c;
    return 0;
}
