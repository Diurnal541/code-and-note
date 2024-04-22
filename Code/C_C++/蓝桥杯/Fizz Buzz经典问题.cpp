#include<iostream>
using namespace std;
int main(){
	int num;
	cin >> num;
	if (num % 3 == 0){
		if (num % 5 == 0){
			cout << "FizzBuzz" << endl;
			return 0;
		}
		else{
			cout << "Fizz" << endl;
			return 0;
		}
	}
	if (num % 5 == 0){
		if (num % 3 == 0){
			cout << "FizzBuzz" << endl;
			return 0;
		}
		else{
			cout << "Buzz" << endl;
			return 0;
		}
	}
	cout << num << endl;
	return 0;
}
