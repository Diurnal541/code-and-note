#include <iostream>
#include "Person.h"
using namespace std;
Person p1("����", 0, 18, 180.5, 65.3);
void main(){
	p1.print();
	cout << endl;
	Person p2("����", 1, 16, 165, 46.5);
	p2.print();
	system("pause");
}
