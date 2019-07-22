#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	
	fd = open("text.txt", O_CREAT, 0644);
//
	printf("fd = %d\n", fd);	

	return 0;
}
