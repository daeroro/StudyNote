#include <queue>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int N, L, R;
int sum, snum, tNum, flag;
int idx;

int a[2500];

void move(void)
{


	int i, num = N *N;
	int emt, xidx, yidx, nx, ny, tmp;
	queue<int> q;
	int xadd[4] = {0, 0, -1, 1};
	int yadd[4] = {-1, 1, 0, 0};

repeat:

	int v[2500] = {0,};
	int b[2500] = {0,};

	while(num)
	{
		for(i=0; i<N*N; i++)
		{
			if(!v[i])
			{
				q.push(i);
				v[i] = 1;
				b[idx++] = i;		

				snum++;
				num--;
				break;
			}
		}
		
		while(!q.empty())
		{
			emt = q.front();
			q.pop();
			xidx = emt / N;
			yidx = emt % N;

			for(i=0; i<4; i++)
			{
				nx = xidx + xadd[i];
				ny = yidx + yadd[i];

				if(nx<0 || nx>= N || ny<0 || ny>=N)
					continue;

				tmp = abs(a[N*xidx+yidx] - a[N*nx+ny]);

				if(v[N*nx+ny] == 0 && L<=tmp && tmp <= R)
				{
					q.push(N*nx+ny);
					v[N*nx+ny] = 1;
					b[idx++] = N*nx+ny;
					snum++;
					num--;
				}
			}
			
		}

		for(i=0; i<snum; i++)
		{
			sum += a[b[i]];
		}
		tmp = sum/snum;

		for(i=0; i<snum; i++)
		{
			a[b[i]] = tmp;
		}

		if(snum > 1)
			flag = 1;		

		sum = 0; snum = 0; idx = 0;
	}
	if(flag == 1)
	{
		tNum++;
		flag=0;
		num = N*N;
		goto repeat;
	}

	printf("%d\n", tNum);
}

int main(void)
{
	int i;

	scanf("%d", &N);
	scanf("%d", &L);
	scanf("%d", &R);

	for(i=0; i<N*N; i++)
		scanf("%d", &a[i]);
	
	move();

	//for(i=0; i<N*N; i++)
	//	printf("%d ", a[i]);

	
	return 0;
}
