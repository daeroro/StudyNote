#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char rbuf[64] = "";

	fd = open("reading.txt", O_RDWR);

	read(fd, rbuf, sizeof(rbuf));
	printf("rbuf = %s", rbuf);
	
	close(fd);
	
	return 0;
}
