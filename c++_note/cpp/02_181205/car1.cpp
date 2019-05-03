/*
	생성자 
*/

#include <iostream>
#include <string.h>

using namespace std;

class Car 
{
private:
    int speed;
    char color[32];

public:
	Car(void);
	Car(int s, char *c);
    void setSpeed(int s);
    int getSpeed(void);
    void setColor(char *c);
    char *getColor(void);
};

Car::Car(void)
{
	cout << "I'm a Car!!" << endl;
}

Car::Car(int s, char *c)
{
	setSpeed(s);
//	setColor(c);
	strncpy(color, c, strlen(c));
	cout << "I'm Car Default Construct car" << endl;
}
// Car:: << Car라는 구조체에 있는 함수포인터를 밑에와 같이 정의하겟다는 거에요.
void Car::setSpeed(int s)
{
    speed = s;
}

int Car::getSpeed(void)
{
    return speed;
}

void Car::setColor(char *c)
{
    strcpy(color, c);
}

char *Car::getColor(void)
{
    return color;
}

int main(void) 
{
	Car c = Car();
 	c.setSpeed(180);
	cout << "speed = " << c.getSpeed() << endl;

	c.setColor("파랑");
	cout << "색깔 = " << c.getColor() << endl;

	char color[32] = "빨강";
	c = Car(200, color); // 생성자를 통해 처음부터 초기화를 시켜준다.
	cout << "speed = " << c.getSpeed() << endl;
	cout << "색깔 = " << c.getColor() << endl;
	return 0;
}
