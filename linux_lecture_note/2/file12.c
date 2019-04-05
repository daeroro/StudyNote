#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage : exe del_file\n");
		exit(-1);
	}

	if(unlink(argv[1]))
	{
		perror(argv[1]);
		exit(-1);
	}
	return 0;
}
