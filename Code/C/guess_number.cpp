#include<iostream>
#include<ctime>
using namespace std;
int main(){
	srand(time(0));
	int num = rand() % 100 + 1;
	int guess_num = 0;
	int count = 0;
	cout << "����������µ�����:";
	cin >> guess_num;
	while (guess_num != num){
		if (guess_num > num){
			cout << "���µ�����̫����,���ٴ�����:";
			cin >> guess_num;
			count += 1;
		}
		else if (guess_num < num) {
			cout << "���µ�����̫С�����ٴ�����:";
			cin >> guess_num;
			count += 1;
		}
	}
	cout << "���¶��ˣ���һ������" << count + 1 << "��" << endl;
	system("pause");
	return 0;
}