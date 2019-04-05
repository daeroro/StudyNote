#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	off_t pos;
	char buf[32] = "test test test";

	fd = open("test.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
	write(fd, buf, sizeof(buf));

	close(fd);

	return 0;
}
