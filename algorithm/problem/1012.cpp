#include <iostream>
#include <vector>
#include <queue>

#include <cstdio>
#include <cstdlib>

using namespace std;

typedef struct posi{
	
	int x, y;
	
}POSI;

int T;
int M, N, K;
priority_queue<int> pq;

void bfs(vector<POSI> v)
{
	int i, vNum = (int)v.size();
	POSI tNode, cNode, nNode;
	int num = 0;
	int visit[50][50];
	int yadd[4] = {-1, 1, 0,0};
	int xadd[4] = {0, 0, -1, 1};
	queue<POSI> q;

	while(vNum>0)
	{
		for(i = 0; i<(int)v.size(); i++)
		{
			tNode = v[i];
			if(visit[tNode.x][tNode.y] == 0)
			{
				visit[tNode.x][tNode.y] = 1;
				q.push(tNode);
				num++; vNum--;
	
				break;
			}
		}
		
		while(!q.empty())
		{
			cNode = q.front();
			q.pop();
			

			for(i=0; i<4; i++)
			{

				nNode.y = cNode.y + yadd[i];
				nNode.x = cNode.x + xadd[i];

				if(nNode.x < 0 || nNode.x >= M || nNode.y < 0 || nNode.y >= N)
					continue;
				
				if(visit[nNode.x][nNode.y] == 0)
				{
					for(int j=0; j<(int)v.size(); j++)
					{
						if(v[j].x == nNode.x && v[j].y == nNode.y)
						{
							visit[nNode.x][nNode.y] = 1;

							q.push(nNode);
							vNum--;
							break;
						}
					}
				} 
			}
		}
	
	}
	printf("%d\n", num);
}

int main(void)
{
	int i, j, xtmp = 0, ytmp = 0;
	POSI pos;

	scanf("%d", &T);

	vector<POSI> v[T];

	for(i=0; i<T; i++)
	{
		scanf("%d %d %d", &M, &N, &K);

		for(j=0; j<K; j++)
		{
			scanf("%d %d", &ytmp, &xtmp);
			pos.y = ytmp;
			pos.x = xtmp;
			v[i].push_back(pos);
		}
	}
	for(i=0; i<T; i++)
		bfs(v[i]);

	return 0;
}
