#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	int i;
	char perm[11] = "----------";
	char rwx[4] = "rwx";
	struct stat buf;

	if(argc != 2)
	{
		fprintf(stderr, "Usage : exe filename or dirname");
		exit(-1);
	}

	lstat(argv[1], &buf);
	
	if(S_ISREG(buf.st_mode))
		perm[0] = '-';
	else if(S_ISDIR(buf.st_mode))
		perm[0] = 'd';
	else if(S_ISCHR(buf.st_mode))
		perm[0] = 'c';
	else if(S_ISBLK(buf.st_mode))
		perm[0] = 'b';
	else if(S_ISFIFO(buf.st_mode))
		perm[0] = 'p';
	
	for(i=0; i<9; i++)
	{
		if((buf.st_mode >> (8-i))&1)
			perm[i+1] = rwx[i%3];
	}
	
	printf("%s %s\n", perm, argv[1]);
	return 0; 
}
