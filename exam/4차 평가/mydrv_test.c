#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUFFER	26
char bin[MAX_BUFFER];
char bout[MAX_BUFFER];

int main(void)
{
	int fd, i, c = 65;
	int write_ret = 0, read_ret = 0;

	if((fd = open("/dev/mydevicefile", O_RDWR))<0)
	{
		perror("open()");
		return -1;
	}

	write_ret = write(fd, bout, 5);
	read_ret = read(fd, bin, 10);
	printf("write_ret = %d, read_ret = %d\n", write_ret, read_ret);

	printf("lseek = %ld\n", lseek(fd, 7, SEEK_END));

	close(fd);
	return 0;
}
