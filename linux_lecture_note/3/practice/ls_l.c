#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

#define A_OPT 	1
#define L_OPT	2
#define R_OPT	4

int main(int argc, char ** argv)
{
	DIR * dp;
	int opt, i=1;
	int opt_flag = 0;
	struct dirent * ent;
	struct stat buf;
	char c = 0;

	dp = opendir(".");

	while((opt = getopt(argc, argv, "alR"))>0)
	{
		switch(opt)
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
				printf("Usage : exe -a or l or R\n");
				break;
		}
	}

	while(ent = readdir(dp))
	{
		if(opt_flag & L_OPT)
		{
			lstat(ent->d_name, &buf);
			
			printf("%d\n", buf.st_mode);
			if(S_ISDIR(buf.st_mode))
				c = 'd';
			else if(S_ISCHR(buf.st_mode))
				c = 'c';
			else if(S_ISBLK(buf.st_mode))
				c = 'b';
			else if(S_ISFIFO(buf.st_mode))
				c = 'p';
			else if(S_ISREG(buf.st_mode))
				c = '-';

			if(!(opt_flag & A_OPT))
			{
				if(ent->d_name[0] == '.');
					continue;
			}

			printf("%s\n", ent->d_name);
		}
		else
		{
			if(!(opt_flag & A_OPT))
			{
				if(ent->d_name[0] == '.')
					continue;
			}
			printf("%-12s", ent->d_name);
			if(!(i++%5))
				printf("\n");
		}
	}
	printf("\n");
	return 0;
}
