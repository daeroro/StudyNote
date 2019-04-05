#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int fd;
	char buf[64];
	int ret;
	
	fd = open("myfifo", O_RDONLY);

	for(;;)
	{
		ret = read(0, buf, sizeof(buf));
		buf[ret - 1] = 0;
		printf("[Keyboard In] = %s\n", buf);

		ret = read(fd, buf, sizeof(buf));
		buf[ret - 1] = 0;
		printf("[Pipe In] = %s\n", buf);
	}
	return 0;
}
