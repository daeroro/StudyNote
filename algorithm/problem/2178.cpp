#include <iostream>
#include <queue>

#include <cstdio>

using namespace std;

struct POS{
	int x, y, dist;
};

int N, M, mNum[2];
char ** map;
int visit[100][100];

void bfs(int sx, int sy)
{
	struct POS cPos, nPos;
	queue<POS> q;
	char xadd[4] = {-1, 1, 0, 0};
	char yadd[4] = {0, 0, -1, 1};

	cPos.x = sx;
	cPos.y = sy;
	cPos.dist = 1;
	q.push(cPos);
	visit[cPos.y][cPos.x] = 1;

	int j = 0;

	while(!q.empty())
	{
		cPos = q.front();
		q.pop();

		for(int i=0; i<4; i++)
		{
			nPos.x = cPos.x + xadd[i];
			nPos.y = cPos.y + yadd[i];

			if(nPos.x <0 || nPos.x >= M || nPos.y <0 || nPos.y >= N)
				continue;

			if((visit[nPos.y][nPos.x] == 0) && (map[nPos.y][nPos.x] == '1'))
			{

				nPos.dist = cPos.dist + 1;
				visit[nPos.y][nPos.x] = 1;
				q.push(nPos);

				if(nPos.y == (N-1) && nPos.x == (M-2))
					mNum[0] = nPos.dist;

				if(nPos.y == (N-2) && nPos.x == (M-1))
					mNum[1] = nPos.dist;

			}
		}
	}
	
	if(mNum[0] == 0)
		printf("%d\n", mNum[1]+1);
	else if(mNum[1] == 0)
		printf("%d\n", mNum[0]+1);
	else if(mNum[0] <= mNum[1])
		printf("%d\n", mNum[0]+1);
	else
		printf("%d\n", mNum[1]+1);
}

int main(void)
{
	scanf("%d %d", &N, &M);

	map = (char **)malloc(sizeof(char *)*N);
	
	for(int i=0; i<N; i++)
	{
		map[i] = (char *)malloc(sizeof(char) * (M+1));
		scanf("%s", map[i]);
	}

	for(int i=0; i<N; i++)
	{
		printf("%s\n", map[i]);
	}
	
	bfs(0, 0);

	return 0;
}
