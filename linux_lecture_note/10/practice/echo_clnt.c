#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE	1024

typedef struct sockaddr_in 	si;
typedef struct sockaddr * 	sap;
int serv_sock;

void err_handler(char * err)
{
	perror(err);
	exit(1);
}

int main(int argc, char ** argv)
{
	si serv_addr;
	int nr;
	char buf[BUF_SIZE];

	if(argc != 3)
	{
		fprintf(stderr, "usage : %s <ip> <port>", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0)
		err_handler("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(serv_sock, (sap)&serv_addr, sizeof(serv_addr))<0)
		perror("connect() error");
	else
		printf("connect success..\n");
	
	for(;;)
	{
		printf("Input(q/Q to quit) : ");
		fgets(buf, BUF_SIZE, stdin);

		if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
			break;
	
		if(write(serv_sock, buf, sizeof(buf))<0)
			err_handler("serv_write() error");

		if((nr = read(serv_sock, buf, BUF_SIZE))<0)
			err_handler("serv_read() error");

		printf("msg from server : %s", buf);
		
		memset(buf, 0, sizeof(buf));
	}
	close(serv_sock);

	return 0;
}
