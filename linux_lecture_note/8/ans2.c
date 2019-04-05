#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define TEST1	777777777
#define TEST2 	2222222222

#define PTEST	250000000

int arr[PTEST] = {7};
int init[PTEST];

typedef struct timeval tv;

double get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("runtime = %lf sec\n", end.tv_usec / 1000000.0);

	return end.tv_usec / 1000000.0;
}

int do_sum(int n,  int * init)
{
	int i, tmp;
	for(i=0; i<n; i++)
		tmp += init[i];

	return tmp;
}

void * task1(void * x)
{
	int i;
	for(i=0; i<125000000; i++)
		arr[i] = arr[0] + do_sum(i, init);
}

void * task2(void * x)
{
	int i;
	for(i=125000000; i<PTEST; i++)
		arr[i] = arr[0] + do_sum(i, init);
}

int main(void)
{

	pthread_t A, B;
	unsigned int i, cnt = 0;
	tv start, end;

	srand(time(NULL));

	for(i=0; i<PTEST; i++)
		init[i] = rand() % 10 + 1;

	pthread_create(&A, NULL, task1, init);
	pthread_create(&B, NULL, task1, init);

	gettimeofday(&start, NULL);

	for(i=1; i<PTEST; i++)
		arr[i] = arr[i-1] + init[i];

	gettimeofday(&end, NULL);

	printf("arr[%d] = %d\n", PTEST -1, arr[PTEST -1]);

	get_runtime(start, end);

	gettimeofday(&start, NULL);
	
	pthread_join(A, NULL);
	pthread_join(B, NULL);

	gettimeofday(&end, NULL);

	get_runtime(start, end);

	return 0;
}
