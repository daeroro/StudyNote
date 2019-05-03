#include <iostream>

using namespace std;

class vsuper
{
public:
	void print()
	{
		cout << "Super" << endl;
	}
};

class vparent : public vsuper
{
public:
	void print()
	{
		cout << "Parent" << endl;
	}
};

class vchild : public vparent
{
public:
	void print()
	{
		cout << "Child" << endl;
	}
};

int main(void)
{
	vsuper *superpointer = new vsuper;
	vparent *parentpointer = new vparent;
	vchild *childpointer = new vchild;

	superpointer->print();
	superpointer = parentpointer;
	superpointer->print();
	superpointer = childpointer;
	superpointer->print();
	return 0;
}
