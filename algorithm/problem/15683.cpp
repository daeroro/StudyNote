#include <iostream>
#include <queue>
#include <algorithm>

#include <cstdio>

using namespace std;

struct pos{
	int x, y, type;
};

int N, M;
int wNum;
int map[8][8];
int check[8][8];
queue<pos> q;

bool cmp(int a, int b)
{
	return a>b;
}

int f_max(int a, int b, int c, int d)
{
	int arr[4] = {a, b, c, d};
	int tmp = 0;

	for(int i=1; i<4; i++)
	{
		if(arr[tmp] < arr[i])
			tmp = i;
	}

	return tmp;
}

void find(void)
{
	int imax;
	int tNum = 0;
	struct pos tPos;
	int xblock = -1, yblock = -1;
	int res[4] = {0,};
	
	while(!q.empty())
	{
		tPos = q.front();
		q.pop();

		for(int i=tPos.x-1; i>=0; i--)
		{
			if(map[tPos.y][i] !=6)
				res[0]++;
			else break;
		}

		for(int i=tPos.y+1; i<N; i++)
		{
			if(map[i][tPos.x] != 6)
				res[1]++;
			else break;
		}
		for(int i=tPos.x+1; i<M; i++)
		{
			if(map[tPos.y][i] != 6)
				res[2]++;
			else break;
		}

		for(int i=tPos.y-1; i>=0; i--)
		{
			if(map[i][tPos.x] !=6)
				res[3]++;
			else break;
		}

		sort(res, res+4, cmp);
		printf("%d %d %d %d\n", res[0], res[1], res[2], res[3]);

		switch(tPos.type)
		{
			case 1:
				imax = f_max(res[0], res[1], res[2], res[3]);
				switch(imax)
				{
					case 0:
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						break;
					case 1:
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}

						break;
					case 2:
		    			for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
	
						break;
					case 3:
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}

						break;
				}
				break;

			case 2:
				imax = f_max(res[0]+res[2], res[1]+res[3], 0, 0);
				switch(imax)
				{
					case 0:
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						break;
					case 1:
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
						break;

				}
				break;

			case 3:
				imax = f_max(res[0]+res[1], res[1]+res[2], res[2]+res[3], res[3]+res[0]);
				switch(imax)
				{
					case 0:
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
						break;
					case 1:
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						break;
					case 2:
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
						break;
					case 3:
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						break;
				}
				break;

			case 4:
				imax = f_max(res[0]+res[1]+res[2], res[1]+res[2]+res[3],
						 res[2]+res[3]+res[0], res[3]+res[0]+res[1]);
				switch(imax)
				{
					case 0:
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						break;
					case 1:
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
						break;
					case 2:
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						break;
					case 3:
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
						break;
				}
				break;

			case 5:
						for(int i=tPos.x-1; i>=0; i--)
						{
							if(map[tPos.y][i] !=6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y+1; i<N; i++)
						{
							if(map[i][tPos.x] != 6)
								check[i][tPos.x] = 9;
							else break;
						}
		    				for(int i=tPos.x+1; i<M; i++)
						{
							if(map[tPos.y][i] != 6)
								check[tPos.y][i] = 9;
							else break;
						}
						for(int i=tPos.y-1; i>=0; i--)
						{
							if(map[i][tPos.x] !=6)
								check[i][tPos.x] = 9;
							else break;
						}
				break;
		}

	for(int i=0; i<4; i++)
		res[i] = 0;

	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			if(check[i][j] == 9)
				tNum++;
		}
	}
	printf("%d\n", N*M - wNum - tNum);
}

int main(void)
{
	struct pos tmp;
	scanf("%d %d", &N, &M);

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			scanf("%d", &map[i][j]);

			if(0 < map[i][j] && map[i][j] < 6)
			{
				tmp.x = j;
				tmp.y = i;
				tmp.type = map[i][j];
				q.push(tmp);
				wNum++;
			}
			else if(map[i][j] == 6)
			{
				wNum++;
			}
		}
	}

	find();

	return 0;
}
