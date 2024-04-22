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
};
stu stus[N];
int n;
void input(stu stus[],int n){
	for (int i = 0;i < n;i++){
		cin >> stus[i].id >> stus[i].name >> stus[i].math >> stus[i].chinese >> stus[i].english; 
	}
}
void print(stu stus[],int n){
	for (int i = 0;i < n;i++){
		cout << stus[i].id << "," << stus[i].name << "," << stus[i].math << "," << stus[i].chinese << "," << stus[i].english << endl;
	}
}
int main(){
	cin >> n;
	input(stus,n);
	print(stus,n);
	return 0;
}
