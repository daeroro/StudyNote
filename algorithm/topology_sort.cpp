#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <cstdio>

#define NUM	7

using namespace std;

vector <int> v[NUM+1];
queue<int> q;
int a[NUM+1] = {0, 0, 1, 1, 1, 1, 2, 1};

int find_zero(void)
{
	int i;
	for(i=1; i<=NUM; i++)
	{
		if(a[i] == 0)
			return i;
	}
	return 0;
}

void topologySort(void)
{
	int i, node, vNum = NUM;

	for(i=1; i<=NUM; i++)
	{
		if(a[i] == 0)
		{
			q.push(i);
		}
	}

	while(!q.empty())
	{
		node = q.front();
		printf("%d ", node);

		q.pop();
		vNum--;

		for(i=0; i<v[node].size(); i++)
		{
			if((--a[v[node][i]]) == 0)
			{
				q.push(v[node][i]);
			}
		}
	}
	printf("\n");

	if(vNum != 0)
		printf("There are one or more cycle\n");
}

int main(void)
{
	//1->2
	v[1].push_back(2);
	
	//2->3
	v[2].push_back(3);

	//3->4
	v[3].push_back(4);

	//4->6
	v[4].push_back(6);

	//6->7
	v[6].push_back(7);

	//1->5
	v[1].push_back(5);
	
	//5->6
	v[5].push_back(6);

	topologySort();

	return 0;
}
