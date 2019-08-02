#include <iostream>
#include <vector>

#include <cstdio>

using namespace std;

#define TRUE 1

vector<int> v[8];
int check[8];

void dfs_recursive(int visit);

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

	dfs_recursive(1);
	
	return 0;
}

void dfs_recursive(int visit)
{
	int i, c = visit;
	check[c] = TRUE;
	printf("%d ", visit);

	for(i=0; i<v[c].size(); i++)
	{
		if(check[v[c][i]] != TRUE)
		{
			c = v[c][i];
			dfs_recursive(c);
		}
	}
}
