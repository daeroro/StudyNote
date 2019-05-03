#include <iostream>
#include <string.h>

using namespace std;

class Academy
{
	char *name;
	char *phone;

	public:
		Academy(char *n, char *p);
		void showInfo(void);
};

Academy::Academy(char *n, char *p)
{
	name = new char[strlen(n) + 1];
	strncpy(name, n, strlen(n));

	phone = new char[strlen(n) + 1];
	strncpy(phone, p, strlen(p));
}

void Academy::showInfo(void)
{
	cout << "name : " << name << endl;
	cout << "phone : " << phone << endl;
}

int main(void)
{
	char name[32] = "한지용";
	char phone[32] = "01056385019";

//	Academy a = Academy(name, phone);
	Academy a(name, phone);
//	Academy a("KOITT, "02-1577-1644");

	a.showInfo();

	return 0;
}
