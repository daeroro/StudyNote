#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	int opt;

	while((opt = getopt(argc, argv, "alR"))>0)
	{
		switch(opt)
		{
			case 'a':
				printf("a option\n");
				break;
			case 'l':
				printf("l option\n");
				break;
			case 'R':
				printf("R option\n");
				break;
			default:
				printf("Usage : exe -a or l or R\n");
				break;				
		}
	}

	return 0;
}
