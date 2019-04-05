#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	DIR * dp;
	int i=1;
	struct dirent * ent;

	dp = opendir(".");
	while(ent = readdir(dp))
	{
		if(ent->d_name[0] == '.')
			continue;
		printf("%-12s", ent->d_name);
		if(!(i++%5))
			printf("\n");
	}
	printf("\n");
	return 0;
}
