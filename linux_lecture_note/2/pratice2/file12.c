#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage : exec target_file");
		exit(-1);
	}

	if(unlink(argv[1]))
	{
		perror(argv[0]);
		exit(-1);
	}
	return 0;
	
}
