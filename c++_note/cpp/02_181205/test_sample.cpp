#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLING_TIME 0.0001
using namespace std;

class Sample{
private:
	float time[256];
	float velocity[256];

public:
	Sample(void);
	Sample(float *);
	void setTime(float *);
	void setVel(float *);
	void printData(void);
	friend float intergal(Sample &s);
};

Sample::Sample(void)
{
	cout << "Call Sample Constructor" << endl;
}

Sample::Sample(float *velocity)
{
	cout << "Call INT Constructor" << endl;
	for(int i = 0; i < 256; i++)
	{
		time[i] = SAMPLING_TIME;
		this->velocity[i] = velocity[i];
		cout << "time[" << i << "]" << "data = " << time[i] << endl;
	}
}	

void Sample::setTime(float *time)
{
	for(int i = 0; i < 256; i++)
		this->time[i] = SAMPLING_TIME;
}

void Sample::setVel(float *velocity)
{
	for(int i = 0; i < 256; i++)
		this->velocity[i] = velocity[i];
}

void Sample::printData(void)
{
	for(int i = 0; i < 256; i++)
	{
		//cout << "Time Data = " << this->time[i];
		cout << " Velocity Data = " << this->velocity[i] << "m/s" << endl;
	}
}

float intergal(Sample &s)
{
	float res = 0.0f;
	for(int i = 0; i < 256; i++)
		res += s.time[i] * s.velocity[i];

	return res;
}

int main(void)
{
	float v[256] = {0};

	srand(time(0));	
	for(int i = 0; i < 256; i++)
		v[i] = rand() % 201 - 75;

	Sample s(v);
	s.printData();

	cout << "result = " << intergal(s) <<"m" << endl;
	return 0;
}
