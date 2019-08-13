#include <iostream>
#include <vector>
#include <queue>

#include <cstdio>

using namespace std;

int V, E;

vector<int> v[101];

void bfs(int start)
{
	queue<int> q;
	int visit[101] = {0, };
	int tNode, nNode, i, num = 0;

	q.push(start);
	visit[start] = 1;

	while(!q.empty())
	{
		tNode = q.front();
		num++;
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
	printf("%d\n", num-1);
}

int main(void)
{
	int i, v1, v2;

	scanf("%d %d", &V, &E);
	for(i=0; i<E; i++)
	{
		scanf("%d %d", &v1, &v2);
		v[v1].push_back(v2);
		v[v2].push_back(v1);
	}

	bfs(1);	

	return 0;
}
