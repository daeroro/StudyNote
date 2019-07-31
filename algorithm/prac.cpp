#include <iostream>
#include <cstdio>

using namespace std;

int main(void)
{
	string arr[2];

	arr[0] = "145C";
	arr[1] = "A910";

	printf("%d\n", arr[0].compare(arr[1]));
	
	return 0;
}
