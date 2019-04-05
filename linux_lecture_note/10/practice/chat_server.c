#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CLNT	100
#define BUF_SIZE	1024

typedef struct sockaddr_in 	si;
typedef struct sockaddr * 	sap;

int clnt_num;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mtx;

void err_handler(char * err)
{
	perror(err);
	exit(1);
}



void *th_handler(void * arg)
{
	char buf[1024] = {0};
	
}

int main(int argc, char ** argv)
{
	si serv_addr, clnt_addr;
	int serv_sock, clnt_sock;
	socklen_t clnt_addr_len;
	pthread_t t_id;

	if(argc != 2)
		err_handler("usage : %s <port>\n");

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(serv_sock, (sap)&serv_addr, sizeof(serv_addr))==-1)
		err_handler("bind() error");

	if(listen(serv_sock, 10)==-1)
		err_handler("listen() error");

	for(;;)
	{
		clnt_addr_len = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (sap)&clnt_addr, &clnt_addr_len);

		if(clnt_sock == -1)
			err_handler("accept() error");

		pthread_mutex_lock(&mtx);
		clnt_socks[clnt_num++] = clnt_sock;
		pthread_mutex_unlock(&mtx);

		pthread_create(&t_id, NULL, th_handler, &clnt_sock);
		pthread_detach(t_id);
		printf("Connecting IP address : %s\n", inet_ntoa(clnt_addr.sin_addr));

		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}
