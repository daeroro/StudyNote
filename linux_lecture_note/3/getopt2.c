#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#define A_OPT	1
#define L_OPT	2
#define R_OPT	4

int main(int argc, char ** argv)
{
	DIR * dp;
	int opt_flag = 0;
	int i=0, cmd;
	struct dirent * p;

	while((cmd = getopt(argc, argv, "alR"))>0)
	{
		switch(cmd)
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
	printf("opt_flag = %d\n", opt_flag);
	return 0;
}
