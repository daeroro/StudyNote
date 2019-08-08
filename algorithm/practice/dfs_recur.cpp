#include <iostream>
#include <vector>

#include <cstdio>

#define NUM 7

using namespace std;

vector <int> v[NUM+1];
int a[NUM+1];

void dfs_recur(int node)
{
	if(a[node]) return;
	printf("%d ", node);
	a[node] = 1;

	for(int i=0; i<v[node].size(); i++)
		dfs_recur(v[node][i]);
}

int main(void)
{
	//1-2
	v[1].push_back(2);
	v[2].push_back(1);

	//1-3
	v[1].push_back(3);
	v[3].push_back(1);

	//2-3
	v[2].push_back(3);
	v[3].push_back(2);

	//2-4
	v[2].push_back(4);
	v[4].push_back(2);

	//2-5
	v[2].push_back(5);
	v[5].push_back(2);

	//3-6
	v[3].push_back(6);
	v[6].push_back(3);

	//3-7
	v[3].push_back(7);
	v[7].push_back(3);

	//4-5
	v[4].push_back(5);
	v[5].push_back(4);

	//6-7
	v[6].push_back(7);
	v[7].push_back(6);

	dfs_recur(1);

	return 0;
}
