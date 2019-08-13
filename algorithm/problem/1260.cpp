#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

#include <cstdio>

using namespace std;

int N, M, V;

vector<int> v[1001];

bool cmp(int a, int b)
{
	if(a<b)
		return 1;
	else
		return 0;
}

void dfs(int start)
{
	stack<int> s;
	int visit[1001] = {0, };
	int tNode, nNode, i;	

	s.push(start);
	visit[start] = 1;
	printf("%d ", start);


repeat:
	while(!s.empty())
	{
		tNode = s.top();

		sort(v[tNode].begin(), v[tNode].end(), cmp);

		for(i=0; i<(int)v[tNode].size(); i++)
		{
			nNode = v[tNode][i];
			if(visit[nNode] == 0)
			{
				s.push(nNode);
				visit[nNode] = 1;
				printf("%d ", nNode);
				goto repeat;
			}			
		}

			s.pop();
	}
}

void bfs(int start)
{
	queue<int> q;
	int visit[1001] = {0, };
	int tNode, nNode, i;

	q.push(start);
	visit[start] = 1;

	while(!q.empty())
	{
		tNode = q.front();
		printf("%d ", tNode);
		q.pop();

		for(i=0; i<(int)v[tNode].size(); i++)
		{
			nNode = v[tNode][i];
			if(visit[nNode] == 0)
			{
				q.push(nNode);
				visit[nNode] = 1;
			}
		}
	}
}

int main(void)
{
	int i, v1, v2;

	scanf("%d %d %d", &N, &M, &V);	
	for(i=0; i<M; i++)
	{
		scanf("%d %d", &v1, &v2);
		v[v1].push_back(v2);
		v[v2].push_back(v1);
	}

	dfs(V);
	printf("\n");
	bfs(V);

	return 0;
}
