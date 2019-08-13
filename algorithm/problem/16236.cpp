#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

int N;
int map[20][20];

struct pos{
	int y, x, dist;
};

int visit[20][20];
struct pos shark;
int s_shark = 2;
int num, cNum;

bool operator<(struct pos a, struct pos b)
{
	if(a.dist == b.dist)
	{
		if(a.y == b.y)
			return a.x > b.x;
		else 
			return a.y > b.y;
	}
	else
		return a.dist > b.dist;
}

void dfs(void)
{
	queue<pos> q;
	priority_queue<pos> q_eat;
	//struct pos tPos = shark;
	struct pos nPos, ePos, tPos;
	int xadd[4] = {-1, 1, 0, 0};
	int yadd[4] = {0, 0, -1, 1};	
	int e_size = 0;

	q.push(shark);
	visit[shark.y][shark.x] = 1;
	map[shark.y][shark.x] = 0;

	while(!q.empty())
	{
repeat:
		shark = q.front();
		printf("shark %d %d %d\n", shark.dist, shark.y, shark.x);
		q.pop();

		for(int i=0; i<4; i++)
		{
			nPos.y = shark.y + yadd[i];
			nPos.x = shark.x + xadd[i];
			
			if(nPos.y < 0 || nPos.y >= N || nPos.x < 0 || nPos.x >= N )
				continue;
			
			if((s_shark >= map[nPos.y][nPos.x]) && (visit[nPos.y][nPos.x] == 0) )
			{
				nPos.dist = shark.dist + 1;
				printf("%d %d %d\n", nPos.dist, nPos.y, nPos.x);	
				visit[nPos.y][nPos.x] = 1;
				q.push(nPos);
				
				if((map[nPos.y][nPos.x] >0) && (s_shark > map[nPos.y][nPos.x]))
				{
					q_eat.push(nPos);
				}
			}
		}
	}


		if(!q_eat.empty())
		{
			ePos = q_eat.top();
			printf("eatable %d %d %d\n", ePos.dist, ePos.y, ePos.x);
			map[ePos.y][ePos.x] = 0;

			num += ePos.dist;

			cNum++;
			if(cNum == s_shark)
			{
				s_shark++;
				cNum = 0;
			}
			

			while(!q.empty())
				q.pop();

			while(!q_eat.empty())
			{	struct pos tmp = q_eat.top();
				printf("eatable %d %d %d\n", tmp.dist, tmp.y, tmp.x);
				q_eat.pop();
			}
			memset(visit, 0, sizeof(int) * 400);
			printf("num = %d\n\n", num);
			ePos.dist = 0;
			q.push(ePos);
			goto repeat;
		}		
	

	printf("%d\n", num);
}

int main(void)
{
	scanf("%d", &N);
	
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			scanf("%d", &map[i][j]);
			if(map[i][j] == 9)
			{
				shark.y = i;
				shark.x = j;
				shark.dist = 0;
			}
		}
	}

	dfs();
	
	return 0;
}
