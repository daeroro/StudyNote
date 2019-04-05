#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

typedef struct sockaddr_in	si;
typedef struct sockaddr *	sap;

int serv_sock, clnt_sock;

void err_handler(char * err)
{
	perror(err);
	exit(1);
}

void call_exit(int sig)
{
	close(serv_sock);
	close(clnt_sock);
	exit(0);
}

int main(int argc, char ** argv)
{
	si serv_addr, clnt_addr;
	socklen_t clnt_addr_len;	
	char buf[BUF_SIZE];
	int nr;

	if(argc != 2)
	{
		fprintf(stderr, "usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	signal(SIGINT, call_exit);

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0)
		err_handler("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(serv_sock, (sap)&serv_addr, sizeof(serv_addr))<0)
		err_handler("bind() error");

	if(listen(serv_sock, 5)<0)
		err_handler("listen() error");

	for(;;)
	{
		clnt_addr_len = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (sap)&clnt_addr, &clnt_addr_len);
		if(clnt_sock < 0)
			err_handler("accept() error");
	
		while((nr = read(clnt_sock, buf, sizeof(buf)))>0)
		{
			if(write(clnt_sock, buf, nr)<0)
				err_handler("write() error");
		}
		close(clnt_sock);
	}
	close(serv_sock);

	return 0;
}
