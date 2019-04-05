#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int fd;
	int flen, rlen = strlen(argv[2]);
	int idx;
	char rbuf[2] = "";
	char *cbuf;

	cbuf = (char*)malloc(rlen * sizeof(char));
	memset((char*)cbuf, 0, rlen);

	if(argc != 3)
	{
		fprintf(stderr, "%s : wrong arguments", argv[0]);
		exit(1);
	}

	fd = open("reading2.txt", O_RDWR);
	
	flen = strlen(argv[1]);	

	while(read(fd, rbuf, sizeof(rbuf)-1))
	{
		if(rbuf[0] == *argv[1])
		{
			
			idx = lseek(fd, (off_t)-1, SEEK_CUR);
			read(fd, cbuf, sizeof(cbuf)-1);
		
			printf("%s\n", cbuf);
			if(strcmp(cbuf, argv[1])==0)
			{
				lseek(fd, (off_t)(-flen), SEEK_CUR);
				write(fd, argv[2], strlen(argv[1]));
				printf("%s\n", cbuf);
			}	
		}
	}
	close(fd);	
}
