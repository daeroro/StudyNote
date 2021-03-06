#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	struct stat buf;
	char ch;

	if(argc!=2)
	{
		printf("Usage : exe filename or dir name\n");
		exit(-1);
	}
	
	lstat(argv[1], &buf);

	if(S_ISDIR(buf.st_mode))
		ch = 'd';
	else if(S_ISREG(buf.st_mode))
		ch = '-';
	else if(S_ISFIFO(buf.st_mode))
		ch = 'p';
	else if(S_ISCHR(buf.st_mode))
		ch = 'c';
	else if(S_ISBLK(buf.st_mode))
		ch = 'b';

	printf("%s dir type = %c\n", argv[1], ch);
	
	return 0;
}
