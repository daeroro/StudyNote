#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define A_OPT	1
#define L_OPT	2
#define R_OPT	4

int main(int argc, char **argv)
{
	DIR * dp;
	int opt, i=1;
	int opt_flag = 0;
	struct dirent * ent;
	

	dp = opendir(".");
	
	while((opt = getopt(argc, argv, "alR"))>0)
	{
		switch (opt)
		{
			case 'a':
				opt_flag |= A_OPT;
				break;
			case 'l':
				opt_flag |= L_OPT;
				break;
			case 'R':
				opt_flag |= R_OPT;
				break;
			default:
				printf("exe -a or l or R\n");
				break;
		}
	}

	while((ent = readdir(dp)))
	{
		if(!(opt_flag & A_OPT))
		{
			if(ent->d_name[0] == '.')
				continue;
		}
			printf("%-12s", ent->d_name);
			if(!((i++)%5))
				printf("\n");
		
	}
	printf("\n");
	closedir(dp);

	return 0;
}
