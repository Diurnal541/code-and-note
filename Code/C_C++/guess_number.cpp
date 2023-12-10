#include<iostream>
#include<ctime>
using namespace std;
int main(){
	srand(time(0));
	int num = rand() % 100 + 1;
	int guess_num = 0;
	int count = 0;
	cout << "请输入您想猜的数字:";
	cin >> guess_num;
	while (guess_num != num){
		if (guess_num > num){
			cout << "您猜的数字太大了,请再次输入:";
			cin >> guess_num;
			count += 1;
		}
		else if (guess_num < num) {
			cout << "您猜的数字太小了请再次输入:";
			cin >> guess_num;
			count += 1;
		}
	}
	cout << "您猜对了！您一共猜了" << count + 1 << "次" << endl;
	system("pause");
	return 0;
}