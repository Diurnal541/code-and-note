#include <iostream>
#include <string>
using namespace std;
const int N = 101;
struct stu{
	string id;
	string name;
	int math;
	int chinese;
	int english;
	int sum;
};
stu stus[N];
int n;
void input(stu stus[],int n){
	for (int i = 0;i < n;i++){
		cin >> stus[i].id >> stus[i].name >> stus[i].math >> stus[i].chinese >> stus[i].english; 
		stus[i].sum = stus[i].math + stus[i].chinese + stus[i].english;
	}
}
int main(){
	cin >> n;
	input(stus,n);
	double sum_m = 0,sum_c = 0,sum_e = 0;
	int max_stu = 0;
	for (int i = 0;i < n;i++){
		sum_m += stus[i].math;
		sum_c += stus[i].chinese;
		sum_e += stus[i].english;
	}
	cout << sum_m / n * 1.0 << " " << sum_c / n * 1.0 << " " << sum_e / n * 1.0 << endl;
	for (int i = 0;i < n;i++){
		max_stu = max(max_stu,stus[i].sum);
	}
	for (int i = 0;i < n;i++){
		if (max_stu == stus[i].sum){
			cout << stus[i].id << " " << stus[i].name << " " << stus[i].math << " " << stus[i].chinese << " " << stus[i].english << endl;
		}
	}
	return 0;
}
