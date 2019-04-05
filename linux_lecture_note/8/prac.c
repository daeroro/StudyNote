#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#define LEN_DATA 100000

typedef struct timeval tv; 
 
int res1[LEN_DATA];
int res2[LEN_DATA];
 
double get_runtime(tv start, tv end) 
{ 
    end.tv_usec = end.tv_usec - start.tv_usec; 
    end.tv_sec = end.tv_sec - start.tv_sec; 
    end.tv_usec += end.tv_sec * 1000000; 
    
    printf("runtime = %lf sec\n", end.tv_usec / 1000000.0); 
    
    return end.tv_usec / 1000000.0; 
}

int do_sum(int to)
{
	int i, tmp;

	for(i=0; i<to; i++)
	{
		tmp += res2[i];
	}
	return tmp;
}

void * task1(void * x)
{
	int i;

	for(i=1; i<25000; i++)
		res1[i] = res1[0] + do_sum(i);
}

void * task2(void * x)
{
	int i;

	for(i=25000; i<50000; i++)
		res1[i] = res1[0] + do_sum(i);
}

void * task3(void *x)
{
	int i;
	
	for(i=50000; i<75000; i++)
		res1[i] = res1[0] + do_sum(i);
}

void * task4(void *x)
{
	int i;
	for(i=75000; i<100000; i++)
		res1[i] = res1[0] + do_sum(i);
}

void * task5(void * x)
{
	int i;
	for(i=0; i<100000; i++)
		res1[i] = res1[0] + do_sum(i);
}

int main(void)
{
	int i;
	tv start, end;
	pthread_t A, B, C, D, E;

//	memset(res1, '1', sizeof(int)*1000);
//	memset(res2, '1', sizeof(int)*1000);

	for(i=0; i<100000; i++)
	{
		res1[i] = 1;
		res2[i] = 1;
	}

	for(i=0; i<100000; i++)
		printf("%d ", res1[i]);

	pthread_create(&A, NULL, task1, NULL);
	pthread_create(&B, NULL, task2, NULL);
	pthread_create(&C, NULL, task3, NULL);
	pthread_create(&D, NULL, task4, NULL);
	pthread_create(&E, NULL, task5, NULL);

//thread 4개
	gettimeofday(&start, NULL);

	pthread_join(A, NULL);
	pthread_join(B, NULL);
	pthread_join(C, NULL);
	pthread_join(D, NULL);

	gettimeofday(&end, NULL);

	get_runtime(start, end);

	for(i=0; i<1000; i++)
	//	printf("%d ", res1[i]);


//thread 1개
	gettimeofday(&start, NULL);
	
	pthread_join(E, NULL);

	gettimeofday(&end, NULL);

	get_runtime(start, end);


	return 0;
}
