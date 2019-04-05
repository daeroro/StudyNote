#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;
	char buf[32] = "";	

	fd = open("test.txt", O_RDWR);
	read(fd, buf, sizeof(buf));

	printf("%s\n", buf);

	close(fd);
	return 0;

}
