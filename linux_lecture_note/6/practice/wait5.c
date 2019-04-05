#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void term_status(int status)
{
	if(WIFEXITED(status))
		printf("exit : %d\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("signal : %d\n", WTERMSIG(status));
}

static void my_chd(int signo)
{
	int status;
	
	if(waitpid(-1, &status, WNOHANG)>0)
		term_status(status);
}

static void my_int(int status)
{
	if(waitpid(-1, &status, WNOHANG)>0)
		term_status(status);
}

int main(void)
{
	pid_t pid;
	int status;
	int i;

	signal(SIGCHLD, my_chd);
	signal(SIGINT, my_int);

	if((pid = fork())>0)
	{
		for(i=0; i<10000; i++)
		{
			usleep(50000);
			printf("%d\n", i+1);
		}
	}
	else if(!pid)
	{
		sleep(50);
		abort();
	}
	else
	{
		perror("fork() ");
		exit(1);
	}
}
