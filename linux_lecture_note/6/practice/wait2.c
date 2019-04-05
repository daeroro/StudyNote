#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void term_status(int status)
{
	if(WIFEXITED(status))
		printf("(exit) status : 0x%x\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("(signal) status : 0x%x\n", WTERMSIG(status));
}

static void my_sig(int sig)
{
	int status;
	printf("signo = %d\n", sig);
	
	wait(&status);
	term_status(status);
}

int main(void)
{
	struct sigaction act;
	pid_t pid;
	int i;

	act.sa_handler = my_sig;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;

	sigaction(SIGCHLD, &act, NULL);

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
		sleep(5);
		exit(0);
	}
	else
	{
		perror("fork() ");
		exit(-1);
	}

	return 0;
}
