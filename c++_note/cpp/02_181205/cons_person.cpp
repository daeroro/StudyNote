#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Person
{
private:
	int age;
	char name[32];
	char job[32];

public:
	Person(void);
	Person(int a, char *n, char *j);
	int getAge(void);
	void setAge(int old);

	char *getName(void);
	void setName(char *nm);
	
	char *getJob(void);
	void setJob(char *j);
};

Person::Person(void)
{
	cout << "Defalut Person construct" << endl;
}

Person::Person(int a, char *n, char *j)
{
	setAge(a);
	strncpy(name, n, strlen(n));
	strncpy(job, j, strlen(j));
}

void Person::setAge(int old)
{
	age = old;
}

int Person::getAge(void)
{
	return age;
}

void Person::setName(char *nm)
{
	strcpy(name,nm);
}

char *Person::getName(void)
{
	return name;
}

void Person::setJob(char *j)
{
	strcpy(job,j);
}

char *Person::getJob(void)
{
	return job;
}

int main(void)
{
	char data[32] = "나바보";

	Person p = Person();

	p.setAge(41);
	cout<<"age= "<<p.getAge()<<endl;

	p.setName("나백수");
	cout<<"name= "<<p.getName()<<endl;

	p.setJob("백수");
	cout<<"Job= "<<p.getJob()<<endl;

	char name1[32] = "남자";
	char job1[32] = "난남자";

	Person p1 = Person(23, name1, job1);

	cout << "age = " << p1.getAge() << endl;
	cout << "name = " << p1.getName() << endl;
	cout << "job = " << p1.getJob() << endl;
	
	return 0;
}
