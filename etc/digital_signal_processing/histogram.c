#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define max_num 500
#define sample 25

void insnum(int * arr)
{
	int i, num=0;
	srand(time(NULL));

	memset(arr, 0, sizeof(arr));

	for(i=0; i<max_num; i++)
	{
		num = rand() % sample + 1;
		if(num)
		{
			arr[num-1] += 1;
		}
	}

	num=0;
	for(i=0; i < sample; i++)
		num += arr[i];
	
	if(num == max_num)
		printf("init success\n");

}

void print_arr(int * arr)
{
	int i, j;
	
	for(i=0; i<sample; i++)
	{
		printf("num %02d(%02d) ", i+1, arr[i]);
		for(j=0; j<arr[i]; j++)
			printf("#");
		printf("\n");
	}
}

int main(void)
{
	int node[sample] = {0,};
	int i, j, num = 0;

	insnum(node);
	print_arr(node);

	return 0;
}
