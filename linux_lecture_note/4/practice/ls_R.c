#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static void recursive_ent(char * path);

int main(int argc, char ** argv)
{
	struct stat buf;

	if(argc != 2)
	{
		fprintf(stderr, "Usage : exe [file name or dir name]");
		exit(-1);
	}
	
	if(lstat(argv[1], &buf)<0) 
	{
		perror(argv[1]);
		exit(-1);
	}
	if(S_ISDIR(buf.st_mode))
		recursive_ent(argv[1]);
	else
		printf("%s\n", argv[1]);
}

static void recursive_ent(char * path)
{
	DIR * dp;
	struct dirent * ent;
	struct stat buf;

	chdir(path);
	dp = opendir(".");
	printf("%s :\n", path);
	while(ent = readdir(dp))
	{
		printf("\t%s\n", ent->d_name);
	}
	rewinddir(dp);
	
	while(ent = readdir(dp))
	{
		if(ent->d_name[0] == '.')
			continue;

		lstat(ent->d_name, &buf);
		printf("name = %s, mode = %d\n", ent->d_name, buf.st_mode);
		if(S_ISDIR(buf.st_mode))
			recursive_ent(ent->d_name);
	}
}
