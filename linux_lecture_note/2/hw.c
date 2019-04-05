#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static void do_replace(int fd, char * f_word, char * r_word);

int main(int argc, char ** argv)
{
	int fd = open("reading.txt", O_RDWR);

	if(argc != 3)
	{
		fprintf(stderr, "wrong arguments\n");
		exit(1);
	}
	
	do_replace(fd, argv[1], argv[2]);

	close(fd);
	return 0;
}

static void do_replace(int fd, char * f_word, char * r_word)
{	
	int flen = strlen(f_word);
	char buf[2] = {0};
	char * rbuf;

	rbuf = (char*)malloc(sizeof(char) * 5); 

	while(read(fd, buf, 1) > 0)
	{
		if(buf[0] == f_word[0])
		{
			lseek(fd, (off_t)(-1), SEEK_CUR);
			read(fd, rbuf, flen);
			
			if(!strcmp(rbuf,f_word))
			{
					
			}			
		}
	}
}
