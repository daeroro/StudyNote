#define _GNE_SOURCE
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void test(void)
{
	printf("tgid(%d), pid(%d): thread\n", getpid(), syscall(__NR_gettid));
}

int main(void)
{
	int tid;
	pthread_t thread;
	pid_t pid = fork();

	if(!pid)
		printf("tgid(%d), pid(%d): child\n", getpid(), syscall(__NR_gettid));
	else
		printf("tgid(%d), pid(%d): parent\n", getpid(), syscall(__NR_gettid));

	tid = pthread_create(&thread, NULL, test, NULL);
	pthread_join(thread, NULL);

	return 0;
}
