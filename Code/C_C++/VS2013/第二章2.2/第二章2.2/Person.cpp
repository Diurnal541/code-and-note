#include <iostream>
#include <string.h>
#include "Person.h"
using namespace std;
Person::Person(char nameV[], bool sexV, int ageV, float heightV, float weightV){
	cout << "��֪����ô�����˵����ԣ�������ɣ�" << endl;
	strncpy_s(name, nameV, sizeof(name));
	sex = sexV;
	age = ageV;
	height = heightV;
	weight = weightV;
}
Person::~Person(){
	cout << "������" << name << endl;
}
void Person::print(){
	cout << "����һ���ˣ��ҵ�����ֵΪ��" << name << "," << sex << "," << age << "," << height << endl;
}
void Person::eat(char obj[]){
	cout << "����һ���ˣ�" << name << "�����һ�û��ѧ����ô�ԡ�" << obj << endl;
}
void Person::sleep(void){
	cout << "����һ����" << name << "���һ�˯��������˵���������ô˯���ġ�" << endl;
}
