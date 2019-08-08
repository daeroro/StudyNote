#include <iostream>
#include <vector>
#include <stack>

#include <cstdio>

#define NUM 7

using namespace std;

vector<int> v[NUM+1];
int visit[NUM+1];

void dfs(int start)
{
	int i, node, idx, vNum = NUM;
	stack<int> s;

	s.push(start);
	visit[start] = 1;
	vNum--;
	printf("%d ", start);
	
	while(vNum)
	{
repeat:
		node = s.top();
	
		for(i=0; i<v[node].size(); i++)
		{
			if(visit[v[node][i]]) continue;
			else
			{
				s.push(v[node][i]);
				visit[v[node][i]] = 1;
				vNum--;
				printf("%d ", v[node][i]);
				goto repeat;
			}	
		}
		s.pop();		
	}
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

	dfs(1);

	return 0;
}
