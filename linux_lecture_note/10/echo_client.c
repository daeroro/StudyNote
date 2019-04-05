#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

typedef struct sockaddr_in	 	si;
typedef struct sockaddr *		sap;

int sock;

#define BUF_SIZE 				1024

void call_exit(int sig)
{
	close(sock);
	exit(0);
}

void err_handler(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char **argv)
{
	int str_len;
	si serv_addr;
	char msg[BUF_SIZE];
	char *m = "input msg(q to quit):";
	
	signal(SIGINT, call_exit);

	if(argc != 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(-1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sock == -1)
		err_handler("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (sap)&serv_addr, sizeof(serv_addr)) == -1)
		err_handler("connect() error");
	else
		puts("Success to Connect");

	for(;;)
	{
		fputs("Input msg(q to quit) : ", stdout);
		fgets(msg, BUF_SIZE, stdin);
		
		if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
			break;
	
		write(sock, msg, strlen(msg));
		str_len = read(sock, msg, BUF_SIZE-1);

		if(str_len == -1)
			err_handler("read() error");
		msg[str_len] = 0;

		printf("msg from server : %s\n", msg);

		memset(msg, 0, sizeof(msg));
	}
	close(sock);

	return 0;
}
