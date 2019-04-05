#include <stdio.h>

int main(int argc, char ** argv)
{
	struct stat buf;
	char rwx[4] = "rwx";
	char sst[4] = "sst";
	char perm[11] = "----------";
	int i;

	if(argc != 2)
	{
		fprintf(stderr, "Usage : exe [file name or dir name]");
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
		{
			perm[i+1] = rwx[i%3];	
		}
	}
	for(i=0; i<3; i++)
	{
		if((buf.st_mode >> (-i))&1)
		{
			if(buf.st_mode
			perm[(i+1)*3] = sst[]
		}
	}

}
