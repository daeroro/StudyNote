#include <stdio.h>

#define INF 1000000
#define NUM 4

int g[NUM][NUM] = {0, 5, INF, 8,
			7, 0, 9, INF,
			2, INF, 0, 4,
			INF, INF, 3, 0};

void print_arr(void)
{
	int i, j;
	for(i=0; i<NUM; i++)
	{
		for(j=0; j<NUM; j++)
		{
			printf("%5d ", g[i][j]);
		}
		printf("\n");
	}
}

void floyd_warshall(void)
{
	int i, j, k, dst, tdst;
	//반복 - 노드 수만큼
	for(i=0; i<NUM; i++)
	{
		for(j=0; j<NUM; j++)
		{
			dst = g[j][i];
			for(k=0; k<NUM; k++)
			{
				tdst = dst + g[i][k];
				if(tdst < g[j][k])
					g[j][k] = tdst;
			}
		}
	}
}

int main(void)
{
	floyd_warshall();

	print_arr();

	return 0;
}
