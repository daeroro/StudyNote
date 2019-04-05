#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#define PTEST 250000000

int arr[PTEST] = {7};
int init[PTEST];
int res[5];

typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %lf sec\n", end.tv_usec /1000000.0);
	return end.tv_usec / 1000000.0;
}

void * task1(void * x) 
{
	int i;
	int * tmp;
	tmp = x;
	for(i= 0; i<(*tmp); i++)
		res[0] += init[i]; 
}

void * task2(void * x)
{
	int i;
	int * tmp;
	tmp = x;
	for(i=(*tmp); i<2*(*tmp); i++)
		res[1] += init[i];
}

void * task3(void * x)
{
	int i;
	int *tmp;
	tmp = x;
	for(i=2*(*tmp); i<3*(*tmp); i++)
		res[2] += init[i];
}

void * task4(void * x)
{
	int i;
	int *tmp;
	tmp = x;
	for(i= 3*(*tmp); i<4*(*tmp); i++)
		res[3] += init[i];
}

int main(void)
{
	int i, j;
	tv start, end;
	pthread_t A, B, C, D;
	int num = PTEST / 4;

	srand(time(NULL));

	for(i=0; i<PTEST; i++)
		init[i] = rand() % 10 + 1;

	pthread_create(&A, NULL, task1, &num);
	pthread_create(&B, NULL, task2, &num);
	pthread_create(&C, NULL, task3, &num);
	pthread_create(&D, NULL, task4, &num);

	gettimeofday(&start, NULL);

	pthread_join(A, NULL);
	pthread_join(B, NULL);
	pthread_join(C, NULL);
	pthread_join(D, NULL);

	res[4] = res[0] + res[1] + res[2] + res[3] + arr[0];
	

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST -1, res[4]);
	get_runtime(start, end);

//-----------------------------------------------------------
	gettimeofday(&start, NULL);
	
	for(i=0; i<PTEST; i++)
		arr[PTEST-1] += init[i];
	arr[PTEST-1] += arr[0];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST-1, arr[PTEST-1]);
	get_runtime(start, end);

	arr[PTEST -1] = 0;
//-----------------------------------------------------------
	gettimeofday(&start, NULL);
	
	for(i=0; i<PTEST/4; i++)
	{
		for(j=0; j<4; j++)
		{
			arr[PTEST -1] += init[ i + j * (PTEST / 4)];
		}
	}

	arr[PTEST-1] += arr[0];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST-1, arr[PTEST-1]);
	get_runtime(start, end);

	return 0;
}
