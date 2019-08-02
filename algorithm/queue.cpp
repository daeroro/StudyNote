#include <iostream>
#include <queue>

#include <cstdio>

using namespace std;

int main(void)
{
	int i;
	
	queue<int> q;

	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);

	q.pop();

	while(!q.empty())
	{
		printf("%d ", q.front());
		q.pop();		
	}
	printf("\n");

	return 0;
}
