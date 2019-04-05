#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr_in	si;
typedef struct sockaddr * 	sap;

void err_handler(char * str)
{
	fprintf(stderr, "%s", str);
	exit(1);
}

int main(int argc, char ** argv)
{
	int sock, len;
	si addr;
	char msg[64] = {0};

	if(argc != 3)
	{
		fprintf(stderr, "usage : %s <ip> <port>", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock<0)
		err_handler("socket(2) failed\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock, (sap)&addr, sizeof(addr))<0)
		err_handler("connect(2) failed\n");
	else
		printf("connect success..\n");

	if((len = read(sock, msg, sizeof(msg)))<0) 
		err_handler("read(2) failed\n");

	write(1, msg, len);

	close(sock);

	return 0;	
}
