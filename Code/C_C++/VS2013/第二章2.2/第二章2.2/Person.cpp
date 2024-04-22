#include <iostream>
#include <string.h>
#include "Person.h"
using namespace std;
Person::Person(char nameV[], bool sexV, int ageV, float heightV, float weightV){
	cout << "我知道怎么设置人的属性，我已完成！" << endl;
	strncpy_s(name, nameV, sizeof(name));
	sex = sexV;
	age = ageV;
	height = heightV;
	weight = weightV;
}
Person::~Person(){
	cout << "析构：" << name << endl;
}
void Person::print(){
	cout << "我是一个人，我的属性值为：" << name << "," << sex << "," << age << "," << height << endl;
}
void Person::eat(char obj[]){
	cout << "我是一个人：" << name << "，但我还没有学会怎么吃。" << obj << endl;
}
void Person::sleep(void){
	cout << "我是一个人" << name << "，我会睡觉，但还说不清楚是怎么睡觉的。" << endl;
}
