#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

class Student{
public:
	string name;
	int score;

	Student(string name, int score){
		this->name = name;
		this->score = score;
	}

	bool operator <(Student & student){
		return this->score < student.score;
	}
};


int main(void)
{
	int i;
	Student students[] = {
		Student("나동빈", 90),
		Student("이상욱", 93),
		Student("박한울", 97)
	};

	sort(students, students+3);

	for(i=0; i<3; i++)
		cout << students[i].name << ' ';
	printf("\n");
	
	return 0;
}
