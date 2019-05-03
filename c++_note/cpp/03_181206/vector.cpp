#include <iostream>

using namespace std;

class Vector
{
private:
	int x;
	int y;
	int z;

public:
	Vector(int x, int y, int z);
	Vector operator+(Vector& v);
	Vector operator-(Vector& v);
	Vector operator*(int scale);
	int inner(Vector &v);
	friend Vector operator*(int scale, Vector& v);
	void showInfo(void);
};

Vector::Vector(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector::showInfo(void)
{
	cout << x << ", " << y << ", " << z << endl;
}

Vector Vector::operator+(Vector& v)
{
	Vector tmp(x + v.x, y + v.y, z + v.z);
	return tmp;
}

Vector Vector::operator-(Vector& v)
{
	Vector tmp(x - v.x, y - v.y, z - v.z);
	return tmp;
}

Vector Vector::operator*(int scale)
{
	Vector tmp(x * scale, y * scale, z * scale);
	return tmp;
}

int Vector::inner(Vector &v)
{

	int x_mul = x * v.x;
	int y_mul = y * v.y;
	int z_mul = z * v.z;

	return x_mul + y_mul + z_mul;

//	return x * v.x + y * v.y + z * v.z;
}

Vector operator*(int scale, Vector& v)
{
	return v * scale;
}

int main(void)
{
	int in = 0;

	Vector v1(1, 2, 3);
	Vector v2(4, 5, 6);

	Vector v3 = v1 + v2;
	v3.showInfo();

	Vector v4 = v3 - v2;
	v4.showInfo();

	Vector v5 = v4 * 3;
	v5.showInfo();

	Vector v6 = 3 * v4;
	v6.showInfo();
		
	in = v1.inner(v2);
	cout << "v1 inner v2 : " << in << endl;
	return 0;
}
