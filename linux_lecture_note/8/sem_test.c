#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>

void print_str(char * str)
{
	while(*str != '\0')
	{
		putchar(*str++);
		fflush(stdout);
	}
}

int main(void)
{
	sem_t *sem_id = NULL;
	sem_id = sem_open("order", O_CREAT, 0777, 1);

	if(!fork())
	{
		sem_wait(sem_id);
		print_str("-------------------------------\n");
		sem_post(sem_id);
	}
	else
	{
		usleep(100);
		sem_wait(sem_id);
		print_str("++++++++++++++++++++++++++++++++\n");
		sem_post(sem_id);
	}

	sem_close(sem_id);
	return 0;
}
