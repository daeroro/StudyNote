#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

typedef struct sockaddr_in 	si;
typedef struct sockaddr * 	sap;

int main(int argc, char ** argv)
{
	int serv_sock, clnt_sock;
	si serv_addr, clnt_addr;
	socklen_t clnt_addrlen;
	char buf[] = "Hello Network Programming!!!\n";

	if(argc != 2)
	{
		fprintf(stderr, "usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0)
	{
		perror("socket(2) failed");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(serv_sock,  (sap)&serv_addr, sizeof(serv_addr))<0)
	{
		perror("bind(2) failed");
		exit(1);
	}

	if(listen(serv_sock, 10)<0)
	{
		perror("listen(2) failed");
		exit(1);
	}
	
	clnt_addrlen = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (sap)&clnt_addr, &clnt_addrlen);

	if(clnt_sock<0)
	{
		perror("accept(2) failed");
		exit(1);
	}

	write(clnt_sock, buf, sizeof(buf));
	
	close(clnt_sock);
	close(serv_sock);

	return 0;
}	
