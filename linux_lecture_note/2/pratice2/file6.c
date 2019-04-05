#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
	int fd;
	off_t pos;

	fd = open("reading.txt", O_RDONLY, 0644);
	pos = lseek(fd, (off_t)0, SEEK_END);
	printf("pos = %ld\n", pos);

	close(fd);
	return 0;
}
