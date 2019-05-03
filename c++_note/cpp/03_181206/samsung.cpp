#include <iostream>
#include <string.h>

using namespace std;

class Samsung
{
private:
	int account;
	char division[300];

public:
	Samsung(int ac, char *e);
	int getAccount(void);
	char *getDivision(void);
	void setAccount(int account);
	void setDivision(char *d);
	void showInfo(void);
};

Samsung::Samsung(int ac, char *e)
{
	account = ac;
	strcpy(division, e);
}

void Samsung::setAccount(int account)
{
	this->account = account;
}

void Samsung::setDivision(char *d)
{
	strcpy(division, d);
}

int Samsung::getAccount(void)
{
	return account;
}

char *Samsung::getDivision(void)
{
	return division;
}

void Samsung::showInfo(void)
{
	cout << "Parent Class showInfo" <<endl;
	cout << "Account : " << account << endl;
}

class Heritor : public Samsung
{
	int age;
	char position[20];

public:
	Heritor(int ac, char *e, int a, char *p); // 상속 인자 전달
	int getAge(void);
	char *getPosition(void);
	void showInfo(void);
};
// 상속 생성자 유의하기, parent class의 멤버를 뒤에 붙여줘야함.
Heritor::Heritor(int ac, char *e, int a, char *p) : Samsung(ac, e)
{
	age = a;
	strcpy(position, p);
}

int Heritor::getAge(void)
{
	return age;
}

char *Heritor::getPosition(void)
{
	return position;
}

void Heritor::showInfo(void)
{
	cout << "계좌 보유액 : " << getAccount() << endl;
	cout << "부서 : " << getDivision() << endl;
	cout << "나이 : " << getAge() << endl;
	cout << "직급 : " << getPosition() << endl;
}

int main(void)
{
	char division[200] = "반도체, 방산, 전자, 중공업";
	char position[30] = "대표이사";
	Samsung Su(100, position);
	Heritor Kim(100000000, division, 25, position);
	Samsung Ku(200, position);
	Su.showInfo();
	Ku.showInfo();
	Kim.showInfo();
	cout << "\n부모 클래스의 함수 호출로 자식 클래스 변경하기\n" << endl;
	
	Kim.setAccount(0);
	Kim.setDivision("파산");
	Kim.showInfo();

	return 0;
}
