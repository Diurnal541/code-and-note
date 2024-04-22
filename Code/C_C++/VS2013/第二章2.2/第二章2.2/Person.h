class Person
{
public:
	Person(char nameV[], bool sexV, int ageV, float heightV, float wightV);
	~Person();
	void eat(char obj[]);
	void sleep(void);
	void print();

private:
	char name[20];
	bool sex;
	int age;
	float height;
	float weight;
};
