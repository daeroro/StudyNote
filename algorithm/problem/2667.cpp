#include <iostream>
#include <algorithm>
#include <queue>

#include <cstdio>

using namespace std;

typedef struct posi{

	char x, y;

}POSI;

int N, tNum;
char map[25][26];
char visit[25][25];
vector <int> v;
//priority_queue<POSI> pq;

bool cmp(int a, int b)
{
	if(a<b)
		return 1;
	else return 0;
}

void bfs(void)
{
	int i, j, dNum = 0;
	char xadd[4] = {-1, 1, 0, 0};
	char yadd[4] = {0, 0, -1, 1};

	queue<POSI> q;
	POSI cNode, nNode, tNode;

	for(i=0; i<N; i++)
	{	
		for(j=0; j<N; j++)
		{
			if(visit[i][j] == 0)
			{
				visit[i][j] = 1;
				tNum--;
				if(map[i][j] == '1')
				{
					cNode.y = i;
					cNode.x = j;
					q.push(cNode);
					dNum++;
					goto repeat;
				}
			}
		}
	}
	
repeat:
	while(!q.empty())
	{
		nNode = q.front();
		q.pop();
		for(i=0; i<4; i++)
		{
			tNode.x = nNode.x + xadd[i];
			tNode.y = nNode.y + yadd[i];

			if(tNode.x < 0 || tNode.x > N || tNode.y<0 || tNode.y>N)
				continue;

			if(map[(int)tNode.y][(int)tNode.x] == '1' && visit[(int)tNode.y][(int)tNode.x] == 0)
			{
				q.push(tNode);
				visit[(int)tNode.y][(int)tNode.x] = 1;
				tNum--; dNum++;
			}
		}		
	}
	
	if(dNum)
		v.push_back(dNum);
}

int main(void)
{
	int i;
	scanf("%d", &N);

	for(i=0; i<N; i++)
	{
		scanf("%s", map[i]);
	}
/*
	for(i=0; i<N; i++)
	{	for(int j=0; j<N; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
*/
	tNum = N*N;

	while(tNum)
		bfs();

	sort(v.begin(), v.end(), cmp);

	cout<<v.size()<<endl;
	for(i=0; i<(int)v.size(); i++)
		printf("%d\n", v[i]);

	return 0;
}
