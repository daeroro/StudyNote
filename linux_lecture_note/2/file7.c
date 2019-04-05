#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char buf[32] = "test test test\n";

	fd = open("reading.txt", O_CREAT | O_RDWR | O_TRUNC);
	new_pos = lseek(fd, (off_t)0, SEEK_END);
	printf("new_pos = %ld\n", new_pos);

	write(fd, buf, sizeof(buf));

	close(fd);

	return 0;
}
